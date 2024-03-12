#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
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
  ADMUX = /*_BV(REFS1) | _BV(REFS0) |*/ _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA = _BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0) | _BV(ADEN);
}

const uint8_t siz = 100;
uint16_t norm[100];
volatile uint16_t slep[100];
volatile uint8_t i;

ISR(ADC_vect){
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t v = ADC;
    slep[i] = v; // weź zmierzoną wartość (0..1023)
}

FILE uart_file;

int main(){
    // zainicjalizuj ADC
    adc_init();
    uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    sei();
    set_sleep_mode(SLEEP_MODE_ADC);
    printf("start\n\r");
    while(1){
        for (int8_t i=0;i<siz;i++){
            ADCSRA |= _BV(ADSC); // wykonaj konwersję
            while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
            ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
            uint16_t v = ADC;    // weź zmierzoną wartość (0..1023)
            norm[i] = v;
        }

        ADCSRA |= _BV(ADIE);
        for (i = 0; i < siz; i++)
            sleep_mode();
        ADCSRA &= ~_BV(ADIE);

        for(int8_t i=0;i<siz;i++){
            printf("%d %d\n\r",norm[i],slep[i]);
        }
        _delay_ms(1000);
    }

}
