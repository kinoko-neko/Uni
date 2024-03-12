#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <avr/delay.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
//definiuje po tym co sie do nich dolacza. a nie port na ktorym to jest
#define SS DDD5
#define SCK DDD4
#define MISO DDD7
#define MOSI DDD6

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

void spi_init(){
    // ustaw pin MISO jako wyjście
    DDRB |= _BV(DDB4);

    SPCR = _BV(SPE);

    DDRD |= _BV(MOSI) | _BV(SCK) | _BV(SS); //ustaw piny na wyjscia
    PORTD |= _BV(SS);
}

uint8_t receive(){
    //ze spi transfer z przykładu
    // czekaj na ukończenie transmisji
    while (!(SPSR & _BV(SPIF)));
    // wyczyść flagę przerwania
    SPSR |= _BV(SPIF);
    // zwróć otrzymane dane
    return SPDR;
}

void send(uint8_t d){

    PORTD &= ~_BV(SS);
    PORTD &= ~_BV(SCK);
    for (int8_t i = 7; i >= 0; i--)
    {
        if ((d & (1 << i)) != 0)
        {
            PORTD |= _BV(MOSI);
        }
        else
        {
            PORTD &= ~_BV(MOSI);
        }
        PORTD |= _BV(SCK);
        PORTD &= ~_BV(SCK);
    }
    PORTD |= _BV(SCK);
    PORTD |= _BV(SS);
}

int main()
{
    // zainicjalizuj UART
    uart_init();
    // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    // zainicjalizuj SPI
    spi_init();
    // program testujący połączenie

    while(1) {
        for(uint8_t i = 0 ; i<10; i++){
            send(i);
            uint8_t rec = receive();
            printf("Wysłano: %"PRId8" Odczytano: %"PRId8"\r\n", i, rec);
            _delay_ms(10);
        }
    }
}
