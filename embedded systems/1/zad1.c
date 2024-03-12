#include <avr/io.h>
#include <inttypes.h>
#include <stdio.h>
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

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

char *mors[]= { ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy
  char a;
  LED_DDR |= _BV(LED);
  while(1) {
    scanf("%c", &a);
    printf("Odczytano: %c""\r\n", a);
    if(a>='a' && a<='z'){
        int i=0;
        a=a-'a';
        while(mors[a][i]=='.' || mors[a][i]=='-'){
          LED_PORT |= _BV(LED);
          if(mors[a][i]=='-'){
              _delay_ms(1000);
          }
          else{
            _delay_ms(500);
          }
          LED_PORT &= ~_BV(LED);
          _delay_ms(100);
          i++;
        }
    }
    LED_PORT &= ~_BV(LED);
    _delay_ms(50);
  }
}

