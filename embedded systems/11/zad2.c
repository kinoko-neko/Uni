#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>

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
  DIDR0   = _BV(ADC0D) | _BV(ADC1D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
//  ADCSRA = _BV(ADPS2);
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
  ICR1 = 3999;
  OCR1A = 0;
  TCCR1A = _BV(COM1A1);
  TCCR1B = _BV(WGM13) | _BV(CS11); // 8
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
}

volatile uint16_t vc, vo;
ISR(TIMER1_CAPT_vect){
    ADMUX |= _BV(MUX0);
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    vc = ADC;
    //printf("cap: %d\r\n",v);
    ADMUX &= ~_BV(MUX0);
    //TIMSK1 &= ~_BV(ICIE1);
    TIMSK1 &= ~_BV(ICIE1);
  //  TIFR1 &= ~_BV(ICF1);
}

ISR(TIMER1_OVF_vect){
    ADMUX |= _BV(MUX0);
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    vo = ADC;
  //  printf("ovf: %d\r\n",v);
    ADMUX &= ~_BV(MUX0);
   // TIMSK1 &= ~_BV(TOIE1);
    TIMSK1 &= ~_BV(TOIE1);
   // TIFR1 &= ~_BV(TOV1);
  //  TIFR1 &= ~_BV(TOV1);
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
  //  sei();
    uint8_t cnt = 0;
    while(1){

        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        uint16_t v = ADC;
        OCR1A = v*2;
        _delay_ms(10);
        cnt++;
        if(cnt == 10){
            cnt = 0;
            printf("v: %d\r\n",v);

            printf("cap %u ovf: %u\r\n",vc,vo);
            sei();
            TIMSK1 |= _BV(ICIE1) | _BV(TOIE1);
            TIFR1 |= _BV(ICF1) | _BV(TOV1);
             _delay_ms(60);
            cli();
        }

    }

}

