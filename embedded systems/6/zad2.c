#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

#define buf_siz 32
volatile char nadawanie[buf_siz];
volatile char odbieranie[buf_siz];
volatile uint8_t head_n = 0;
volatile uint8_t tail_n = 0;
volatile uint8_t head_o = 0;
volatile uint8_t tail_o = 0;

ISR(USART_RX_vect){ // odbior
    uint8_t next = (head_o +1)%buf_siz;
    //jak bufor przepelniony to nie czekam tylko udaje ze znaku nie bylo
    if(next != tail_o){
        odbieranie[head_o]=UDR0;
        head_o=next;
    }
 //   printf("yyyyyyy %"SCNu8 " odb= %c" "\n\r",head_o,odbieranie[next]);
   // send = UDR0;
   // UDR0 = send;
    //UCSR0B |= _BV(TXCIE0);
}

ISR(USART_UDRE_vect){// wysyłanie
    //jak bufor pusty to zamykam przerwania bo wszystko zostalo wyslane
    if(tail_n==head_n){
        UCSR0B &= ~_BV(UDRIE0);
    }
    else{
        UDR0 = nadawanie[tail_n];
        tail_n = (tail_n+1) % buf_siz;
    }
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
    uint8_t next = (head_n + 1)%buf_siz;
    while(next == tail_n); //zajety bufor nadawania
    nadawanie[head_n] = data;
    head_n = next;
    UCSR0B |= _BV(UDRIE0); // wlacz przerwania na gotowe do nadania nowego znaku
 // while(!(UCSR0A & _BV(UDRE0)));
 // UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (head_o==tail_o); //bufor odbierania pusty
  uint8_t data=odbieranie[tail_o];
//  printf("eeeee %c" " %"SCNu8 "\n\r",(char)data,tail_o);
  tail_o = (tail_o+1) %buf_siz;

  return data;
}

FILE uart_file;

int main()
{
  // zainicjalizuj UART
  uart_init();
 // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  set_sleep_mode(SLEEP_MODE_IDLE);
  // program testujący połączenie
  UCSR0B |= _BV(RXCIE0);
  sei();
  printf("hello world! 123456789");
  char y;
  scanf("%c",&y);
  //printf("hello world!");
 // printf("odczytano: %c yh",y);
  while(1) {
      sleep_mode();
   //   printf("%d %d\r\n",send,f2);
     // _delay_ms(100);
  }
}

