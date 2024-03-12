#include <avr/io.h>
#include <stdio.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>
#include <math.h>
#include <avr/interrupt.h>
#include "pid.c"
#include "pid.h"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

#define kp     10.0
/*
#define ki     0.0
#define kd     0.0
*/
#define ki     3.0
#define kd     20.0
volatile struct PID_DATA pidData;

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

FILE uart_file;
#define TIME_INTERVAL   157

// inicjalizacja ADC

void adc_init(){
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
 // ADMUX |= 0b1110;
  DIDR0   = _BV(ADC0D) | _BV(ADC1D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS2); // preskaler 4
  ADCSRA |= _BV(ADEN); // włącz ADC
}

void timer1_init(){
    TCCR1A = _BV(WGM21);
    TCCR1A = _BV(COM1A1);
    TCCR1B = _BV(CS11) | _BV(WGM13);
    ICR1 = 5115;
    OCR1A = 0;
    TIMSK1 |= _BV(ICIE1);
    DDRB |= _BV(PB1);
}

volatile uint16_t sv;
volatile uint16_t sv2;
volatile uint16_t tv;
volatile int32_t ol;
volatile uint16_t cnt;
volatile uint16_t cnt2;

ISR(TIMER1_CAPT_vect){ // timer do pomiaru silnika i oblugi silnika
    cnt++;
    static uint16_t i = 0;
    if(i < 30 ){
        i++; return;
    }
    i = 0;
    //pomiar na silniku
    ADMUX |= _BV(MUX0);
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t v = ADC;
    sv = 1023 - v;
    ADMUX &= ~_BV(MUX0);
}

void timer2_init() //timer do pomiarow na pid
{
    TCCR2B = _BV(CS22) ;
    TIMSK2 = _BV(TOIE2);
}

ISR(TIMER2_OVF_vect){
 //pomiar na potencjometrze
    cnt2++;
    ADCSRA |= _BV(ADSC); // wykonaj konwersję
    while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
    ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
    uint16_t v2 = ADC;
   // printf("POTENCJA %d\r\n",v2);
    int16_t dif = (int16_t)v2 - tv;
    if(dif<0) dif = -dif;
    if(dif > 8){
        tv = v2;
        int32_t inp = pid_Controller(tv, sv, &pidData);
        ol = inp;
        sv2 = sv;
        // inp += (int32_t)OCR1A;
        if(inp < 0) OCR1A = 0;
        else if(inp > ICR1) OCR1A = ICR1;
        else OCR1A = inp;
    }
}

int main(){
     // zainicjalizuj ADC
    uart_init();
    timer1_init();
    timer2_init();
    pid_Init(kp * SCALING_FACTOR, ki * SCALING_FACTOR , kd* SCALING_FACTOR , &pidData);
  // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    adc_init();
    sei();
    uint16_t j = 0;
    while(1){
        if(j < 2000){
            j++;
        }
        else{
            printf("sv %d sv2: %d tv: %d  ol: %ld cnt: %d cnt2: %d \r\n", sv,sv2, tv,ol, cnt,cnt2);
            _delay_ms(10);
            j = 0;
        }
    }
}
