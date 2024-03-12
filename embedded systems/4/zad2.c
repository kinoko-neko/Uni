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
  ICR1 = 255;
  TCCR1A = _BV(COM1A1) | _BV(WGM11) ; // Tryb Fast PWM
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10); // Brak prescalera
  // ustaw pin OC1A (PB1) jako wyjście
  DDRB |= _BV(PB1);
}


const uint8_t exp_table[] = {255,128,104,84,67,53,41,32,24,18,13,9,6,4,2,1};
const uint16_t sub=388;
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
    OCR1A = 0;
    _delay_ms(2000);
  //  OCR1A = ICR1/2;


    while(1){
        OCR1A = 0;
        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
    //    uint16_t vol = (11264/v);
        // vout = vin * (R1/(R1 + R2))
     //   printf("Odczytano: %u" "\r\n", v);

        uint16_t b=1;

        if (v < 1024) {
        // Przelicz wartość pomiaru na jasność z wykorzystaniem tablicy wykładniczej
          b=exp_table[v>> 6]; // Przesunięcie bitowe o 6 to odpowiednik dzielenia przez 64
        } else {
            b=0; // Maksymalna jasność
        }
        printf("Odczytano: %u b=%u" "\r\n", v,b);

       // for(uint8_t j=0; j<255;j++){
            OCR1A = b;

            _delay_us(255000);
       // }
       _delay_ms(1000);
    }

}
