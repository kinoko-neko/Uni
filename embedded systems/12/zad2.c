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

#define kp     1.5
#define ki     0.400
#define kd     0.20
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


// inicjalizacja ADC

void adc_init(){
  ADMUX   = _BV(REFS0) | _BV(REFS1); // referencja AVcc, wejście ADC0
 // ADMUX |= 0b1110;
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

void timer1_init(){
    TCCR1A = _BV(COM1A1) | _BV(WGM11);
    TCCR1B = _BV(CS10) | _BV(WGM12) | _BV(WGM13);
    ICR1 = 32767;
    OCR1A = 0;
    DDRB |= _BV(PB1);
}

FILE uart_file;

volatile int16_t T;
volatile int16_t ta;
volatile int16_t tv;
volatile uint16_t vl;
volatile int32_t inpl;
volatile uint16_t ocl;
volatile uint16_t cnt=0;
int16_t tc = 10;
int16_t v0 = 500;

#define TIME_INTERVAL   157

ISR(ADC_vect){
    uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
    cnt++;
    vl = v*30;
    // printf("adc %d\r\n",cnt);
    int16_t referenceValue, measurementValue;

    referenceValue = tv;
    measurementValue = v*30;
    int32_t inp = pid_Controller(referenceValue, measurementValue, &pidData);
    inpl = inp;
    if(inp < 0) OCR1A = 0;
    else if(inp > ICR1) OCR1A = ICR1;
    else OCR1A = inp;
    ocl = OCR1A;
}


void timer2_init()
{
    TCCR2A = _BV(WGM21);
    TCCR2B = _BV(CS20) | _BV(CS21) | _BV(CS22);
    TIMSK2 = _BV(OCIE2A);
}

//16tys

//16000 / x = 10
//1600/x = 1
// x = 1600
volatile uint16_t pomiar =0;
ISR(TIMER2_COMPA_vect)
{
    pomiar++;
    if(pomiar ==1600){
      ADCSRA |= _BV(ADSC); // wykonaj konwersję
      pomiar = 0;
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
    DDRB |= _BV(PB5);

    ADCSRA |= _BV(ADIE);
    ADCSRA |= _BV(ADSC);
    sei();
  //  uint8_t cnt = 0;
    while(1){

      //jesli znak dostepny
      if(UCSR0A & _BV(RXC0)){
        scanf("%d", &T);
        // v_o = tc * ta + v_0
        // v_o = 10 * ta + 500 [mv]
        // (v_0 / 1100 )* 1023 = adc
        int64_t pomi = T;
        pomi = pomi*10 +500;
        pomi = (pomi*1023)/1100; //ile na adc (troche obcięte)
        tv = pomi *30; // raz policz ile potrzeba

        printf("TARGET V: %d pomi: %u TEMPERATURA: %d\r\n",tv,(uint16_t)pomi,T);
        pid_Reset_Integrator(&pidData);
      }
      else{
          printf("tv: %d vl: %d inpl: %ld ocl: %u cnt: %d cnt2: %d  TTTTTT: %d\r\n",tv,vl,inpl,ocl,cnt,pomiar,T);
          _delay_ms(100);
      }

    }
}
