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
  ADMUX   = _BV(REFS0) | _BV(REFS1); // referencja AVcc, wejście ADC0
 // ADMUX |= 0b1110;
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

FILE uart_file;

volatile int16_t T;
volatile int16_t ta;
volatile uint8_t cnt=0;

ISR(ADC_vect){
    uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
    cnt++;
    // v_o = tc * ta + v_0
    // v_0 = 500 mV
    // tc = 10.0 mV/°C
    // ta = (v_o - v_0)/ tc
    // ta = (v_o - 500)/10
    // ta = v_o/10 - 50
    // v_o = 1100 * adc /1023
    // ta = (1100*adc)/(10*1023) - 50
    // ta = (110*adc)/1023 - 50
   // printf("v: %d\r\n",v);
    double v2 = (double)v;
    v2 = (v*1.1)/1024;
    double t2 = (v2 - 0.55) * 100;
    ta = t2;
    if (ta < T-1){
        PORTB |= _BV(PB5);
        // printf("v: %d\r\n ta %d", v,ta);
    }
    if ( ta > T){
        PORTB &= ~_BV(PB5);
        //printf("v2: %d\r\n ta %d", v,ta);
    }
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
}

int main(){
     // zainicjalizuj ADC
    uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    adc_init();
    DDRB |= _BV(PB5);
    char c;
    ADCSRA |= _BV(ADIE);
    ADCSRA |= _BV(ADSC);
    sei();
    while(1){
        scanf("%c", &c);
        if (c == 'S') {
            scanf("%d", &T);
        } else if (c == 'R') {
            printf("ta %d T: %d cnt: %d\r\n", ta,T,cnt);
        }

        _delay_ms(1000);
    }
}
