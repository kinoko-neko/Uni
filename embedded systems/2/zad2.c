#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

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
char *mors[]= { ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};

char t[4]={'a','a','a','a'};
int8_t ind=0;

char znak(){
   // for(int i=0;i<ind;i++)
     //   printf("%c",t[i]);
    //printf("%d\r\n",ind);

    for(int i=0;i<26;i++){
        int8_t fail=0;
    //    printf("\n\r%c",(char)(i+'a'));
        for(int j=0;j<ind;j++){
            if(mors[i][j]!=t[j]){
                fail=1;
                break;
            }
     //       printf("mors:%c|t:%c|",mors[i][j],t[j]);
        }
        if(fail==0){
            if(mors[i][ind]=='.' || mors[i][ind]=='-')
                continue;

            for(int i=0;i<4;i++)
                t[i]='a';
            return (char)(i+'a');
        }
    }
    for(int i=0;i<4;i++)
        t[i]='a';

    return 0;
}

int main() {
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);

    uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    int8_t last=1;
    int8_t pom;
    uint32_t cnt=0;
    while (1) {
        pom = BTN_PIN & _BV(BTN);
        LED_PORT &= ~_BV(LED);
        if((pom>0) == (last>0)){
            cnt+=1;
            if(cnt == 80){
                if(pom>0){
                    if(ind!=0){
                        printf("%c",znak());
                        ind=0;
                        cnt=0;
                    }
                }
                else{
              //      printf("granica");
                    LED_PORT |= _BV(LED);
                }
            }
        }
        else{
            if(last==0){
                if(cnt>80){
                    t[ind]='-';
                  //  printf("%d-",ind);
                }
                else{
                    t[ind]='.';
                 //   printf(".");
                }
                ind+=1;
            }
            else{
                if(cnt>100){
                    printf(" ");
                }
            }
            cnt=0;
        }
        last=pom;
        _delay_ms(10);
    }
}
