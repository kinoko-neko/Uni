#include <avr/io.h>
#include <stdio.h>
#include <avr/sfr_defs.h>
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

void adc_init(){
  ADMUX   = _BV(REFS0) | _BV(REFS1); // referencja AVcc, wejście ADC0
  // ADMUX   = _BV(REFS0);
 // ADMUX |= 0b1110;
  DIDR0   = _BV(ADC1D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;
const uint8_t siz=8;
volatile uint8_t wsk = 0;
volatile int16_t tab[8];

volatile uint8_t cnta = 0;
ISR(ADC_vect){
    cnta++;
    uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
    tab[wsk] = v;
    tab[wsk] -= 512;
    wsk++;
    if(wsk>=siz) wsk = 0;
}

void timer1_init() //timer do pomiarow na pid
{
    TCCR1B = _BV(CS11) | _BV(WGM13) | _BV(WGM12); //preskaler 8
    ICR1 = 250;
    OCR1A = 0;
    TIMSK1 |= _BV(ICIE1);

}

volatile uint8_t cntt =0;
ISR(TIMER1_CAPT_vect){
 //pomiar na potencjometrze
    cntt++;
    ADCSRA |= _BV(ADSC); // zlec pomiar
}


int main(){
     // zainicjalizuj ADC
    uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    adc_init();
    timer1_init();
    ADCSRA |= _BV(ADIE);
    sei();
  //  uint8_t cnt = 0;
    while(1){
        int32_t sum =0;
        int32_t xref = 170;
        int32_t L;
        printf("%d %d %d %d cnta: %d cntt: %d\r\n",tab[0],tab[1],tab[2],tab[3],cnta,cntt);
        for(int i =0; i<siz; i++){
            sum += tab[i]*tab[i];
        }
        sum >>= 3;
        sum = sqrt(sum);
        L = (20.0* log10f((double)sum/(double)xref));

        printf("sr: %ld L:%ld\r\n",sum,L);
        _delay_ms(100);
    }
}

