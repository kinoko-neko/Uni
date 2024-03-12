#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <math.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}


// inicjalizacja ADC

void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
 // ADMUX |= 0b1110;
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

void timer1_init()
{
  // ustaw tryb licznika
  // COM1A = 10   -- non-inverting mode
  // WGM1  = 1110 -- fast PWM top=ICR1
  // CS1   = 101  -- prescaler 1024
  // ICR1  = 15624
  // częstotliwość 16e6/(1024*(1+15624)) = 1 Hz
  // wzór: datasheet 20.12.3 str. 164
  ICR1 = 2046;
  TCCR1A = _BV(COM1B1) | _BV(WGM11) ; // Tryb Fast PWM
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS11); // 8
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB2);
}

FILE uart_file;

int main(){
    // zainicjalizuj ADC
      uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    adc_init();
    printf("start\n\r");
    timer1_init();
    DDRB |= _BV(PB4) | _BV(PB3);
    PORTB |= _BV(PB4);
  //  OCR1A = ICR1/2;

    uint8_t cnt = 0;
    while(1){
        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        uint16_t v = ADC;
        // printf("%d\n",v);
        if (v < 512) {
            OCR1B = (512-v)*4;
            PORTB |= _BV(PB4);
            PORTB &= ~_BV(PB3);
        }
        else{
            OCR1B = (v-512)*4;
            PORTB &= ~_BV(PB4);
            PORTB |= _BV(PB3);
        }

        _delay_ms(100);
    }

}

