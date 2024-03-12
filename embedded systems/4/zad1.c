#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>
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

void timer1_init()
{
  // ustaw tryb licznika
  // WGM1  = 0000 -- normal
  // CS1   = 001  -- prescaler 1
  TCCR1B = _BV(CS10);
}

FILE uart_file;

void i8(){
    //int8_t
    int8_t a8 = rand();
    int8_t b8 = rand();

  //  scanf("%"SCNd8, &a8);
   // scanf("%"SCNd8, &b8);

    uint16_t a = TCNT1; // wartość licznika przed czekaniem
    volatile int8_t pom8 = a8+b8;
    uint16_t b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("a8+b8 = %"PRId8"\r\n", pom8);

    a = TCNT1; // wartość licznika przed czekaniem
    pom8 = a8*b8;
    b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("a8*b8 = %"PRId8"\r\n", pom8);

    a = TCNT1; // wartość licznika przed czekaniem
    pom8 = a8/b8;
    b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("a8/b8 = %"PRId8"\r\n", pom8);
}

void i16(){
    //int16_t
    int16_t a16 = rand();
    int16_t b16 = rand();

    uint16_t a = TCNT1; // wartość licznika przed czekaniem
    volatile int16_t pom16 = a16+b16;
    uint16_t b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("a16+b16 = %"PRId16"\r\n", pom16);

    a = TCNT1; // wartość licznika przed czekaniem
    pom16 = a16*b16;
    b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("a16*b16 = %"PRId16"\r\n", pom16);

    a = TCNT1; // wartość licznika przed czekaniem
    pom16 = a16/b16;
    b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("a16/b16 = %d""\r\n", pom16);
}


void i32(){
    //int32_t
    int32_t a32 = rand();
    int32_t b32 = rand();

    uint16_t a = TCNT1; // wartość licznika przed czekaniem
    volatile int32_t pom32 = a32+b32;
    uint16_t b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("a32+b32 = %"PRId32"\r\n", pom32);

    a = TCNT1; // wartość licznika przed czekaniem
    pom32 = a32*b32;
    b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("a32*b32 = %"PRId32"\r\n", pom32);

    a = TCNT1; // wartość licznika przed czekaniem
    pom32 = a32/b32;
    b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("a32/b32 = %"PRId32"\r\n", pom32);
}


void i64(){
    //int64_t
    int64_t a64 = rand();
    int64_t b64 = rand();

    uint16_t a = TCNT1; // wartość licznika przed czekaniem
    volatile int64_t pom64 = a64+b64;
    uint16_t b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony as: %"PRIu16" cykli\r\n", b - a);
    printf("a64+b64 = %d""\r\n", (int)pom64);

    a = TCNT1; // wartość licznika przed czekaniem
    pom64 = a64*b64;
    b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("a64*b64 = %d""\r\n", (int)pom64);

    a = TCNT1; // wartość licznika przed czekaniem
    pom64 = a64/b64;
    b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("a64/b64 = %d""\r\n", (int)pom64);
}

void f(){
    //float
    float af = rand();
    float bf = rand();

    uint16_t a = TCNT1; // wartość licznika przed czekaniem
    volatile float pomf = af+bf;
    uint16_t b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("af+bf = %f""\r\n", pomf);

    a = TCNT1;
    pomf = af*bf;
    b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("af*bf = %f""\r\n", pomf);

    a = TCNT1;
    pomf = af/bf;
    b = TCNT1; // wartość licznika po czekaniu
    printf("Zmierzony czas: %"PRIu16" cykli\r\n", b - a);
    printf("af/bf = %f""\r\n", pomf);
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  timer1_init();
  srand(10);
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // program testowy
  printf("Hello world!\r\n");
  while(1) {
    i8();
    _delay_ms(1000);
    i16();
    _delay_ms(1000);
    i32();
    _delay_ms(1000);
    i64();
    _delay_ms(1000);
    f();
    _delay_ms(3000);
  }
}
