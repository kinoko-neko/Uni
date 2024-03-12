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


void timer_init(){
    TCCR1B = _BV(CS12) | _BV(CS10); //1024
}

volatile uint16_t last = 0;

volatile int8_t t[100];
volatile int8_t i;

ISR(TIMER1_CAPT_vect)
{
    uint16_t temp = ICR1;
    uint16_t l = temp - last;
//    printf("eh = %u\r\n",temp);
    t[i]=l;
    last = temp;
}

FILE uart_file;

int main(){
    timer_init();
    uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    set_sleep_mode(SLEEP_MODE_IDLE);
    sei();

    //printf("start\n\r");
    while(1){
        TIMSK1 = _BV(ICIE1);
        for(i = 0; i<100; i++){
            sleep_mode();
        }
        TIMSK1 &= ~_BV(ICIE1);
        for(int8_t i = 0; i<100; i++){
            printf("a = %d\n\r",t[i]);
            printf("b = %d\n\r", 15625/((int)t[i]));
        }
        printf("saddsadsadsa\n\r");
        _delay_ms(1000);
    }

}
