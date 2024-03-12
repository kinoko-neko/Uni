#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/io.h>
#include <util/delay.h>
//#include <avr/pgmspace.h>
#include "lieblingsfach.h"
// lieblingsfach https://www.youtube.com/watch?v=39UDZMgPg5k

void spi_init(){

    // ustaw piny MOSI, SCK i ~SS jako wyjścia
  DDRB |= _BV(DDB3) | _BV(DDB5) | _BV(DDB2);
    // włącz SPI w trybie master z zegarem 250 kHz
  SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1) | _BV(SPR0);

}
// transfer jednego bajtu
void spi_transfer(uint8_t data)
{
    PORTB &= ~_BV(PB2);
    // rozpocznij transmisję

    SPDR = 0b00110000 | (data >> 4);
    while (!(SPSR & _BV(SPIF)));
    SPSR |= _BV(SPIF);
    SPDR = (data<<4);
    while (!(SPSR & _BV(SPIF)));
    SPSR |= _BV(SPIF);
    PORTB |= _BV(PB2);
}

int main()
{
  spi_init();

  uint64_t i = 0;
  uint8_t data;

  while (1)
  {
    data = pgm_read_byte(&lieblingsfach_raw[i++]);
    spi_transfer(data);
    if(i >= lieblingsfach_raw_len){
      i = 0;
    }

}
}
