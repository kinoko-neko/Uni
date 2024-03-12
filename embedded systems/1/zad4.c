#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>

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

void i8(){
    //int8_t
    int8_t a8 = 1;
    int8_t b8 = 1;

    scanf("%"SCNd8, &a8);
    scanf("%"SCNd8, &b8);

    int8_t pom8 = a8+b8;
    printf("a8+b8 = %"PRId8"\r\n", pom8);
    pom8 = a8*b8;
    printf("a8*b8 = %"PRId8"\r\n", pom8);
    pom8 = a8/b8;
    printf("a8/b8 = %"PRId8"\r\n", pom8);
}

void i16(){
    //int16_t
    int16_t a1 = 1;
    int16_t b1 = 1;

    scanf("%"SCNd16, &a1);
    scanf("%"SCNd16, &b1);

    int8_t pom1 = a1+b1;
    printf("a1+b1 = %"PRId16"\r\n", pom1);
    pom1 = a1*b1;
    printf("a1*b1 = %"PRId16"\r\n", pom1);
    pom1 = a1/b1;
    printf("a1/b1 = %"PRId16"\r\n", pom1);
}


void i32(){
    //int32_t
    int32_t a3 = 1;
    int32_t b3 = 1;

    scanf("%"SCNd32, &a3);
    scanf("%"SCNd32, &b3);

    int32_t pom3 = a3+b3;
    printf("a3+b3 = %"PRId32"\r\n", pom3);
    pom3 = a3*b3;
    printf("a3*b3 = %"PRId32"\r\n", pom3);
    pom3 = a3/b3;
    printf("a3/b3 = %"PRId32"\r\n", pom3);
}


void i64(){
    //int64_t
    int64_t a6 = 1;
    int64_t b6 = 1;

    scanf("%"SCNd32, &a6);
    scanf("%"SCNd32, &b6);

    int64_t pom6 = a6+b6;
    printf("a6+b6 = %"PRId32"\r\n", pom6);
    pom6 = a6*b6;
    printf("a6*b6 = %"PRId32"\r\n", pom6);
    pom6 = a6/b6;
    printf("a6/b6 = %"PRId32"\r\n", pom6);
}

void f(){
    //float
    float af = 1;
    float bf = 1;

    scanf("%f", &af);
    scanf("%f", &bf);

    int64_t pomf = af+bf;
    printf("af+bf = %f""\r\n", pomf);
    pomf = af*bf;
    printf("af*bf = %f""\r\n", pomf);
    pomf = af/bf;
    printf("af/bf = %f""\r\n", pomf);
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy
  printf("Hello world!\r\n");
  while(1) {
    i8();
    i16();
    i32();
    i64();
    f();
  }
}
