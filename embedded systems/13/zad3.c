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
 // ADMUX |= 0b1110;
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

int main(){
     // zainicjalizuj ADC
    uart_init();
    DDRB |= _BV(PB5);
  // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    adc_init();
  //  uint8_t cnt = 0;
    while(1){

        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        uint16_t v = ADC;


        // R = V/I
        // R = (p/1024)*1.1 / I

        // V = p *(1.1/1024)
        //R = p *(1.1/1024) / 0.00013
        //R = p *(1.1/1024)/ (13/100000)
        //R = p *(1.1/1024) * (100000/13)
        //R = p * (11/1024) * (10000/13)
        //R = p * (11/1024) * (5^4 * 2^4 /13)
        //R = p * (11/64) *(625/13)
        //R = p * (6875 / 832)
        //R = p * 8.26

        double R = (double)v * 8.26;
        double R0 = 4700.0; double B= 2613.7; double T0= 298.15;
        float T = ((R0*T0)/(T0*log((R/R0)) +B))  - 273.15;

        int t2 = (int)T;
        printf("zmierzono %u\r\n",v);
        printf("R: = %d.%d \r\n",(int)R/10,(int)R%10);
        printf("Tmp= %d.%d \r\n",t2/10,t2%10);
        _delay_ms(100);
    }

}

