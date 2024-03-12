#include <avr/io.h>
#include <util/delay.h>

void spi_init(){

    // ustaw piny MOSI, SCK i ~SS jako wyjścia
  DDRB |= _BV(DDB3) | _BV(DDB5) | _BV(DDB2) | _BV(DDB1) ;
    // włącz SPI w trybie master z zegarem 250 kHz
  SPCR = _BV(SPE) | _BV(MSTR) | _BV(SPR1) | _BV(SPR0) | _BV(DORD);

}
// transfer jednego bajtu
void spi_transfer(uint8_t data)
{
    PORTB &= ~_BV(PB1);
    // rozpocznij transmisję

    SPDR = data;
    while (!(SPSR & _BV(SPIF)));
 //   SPSR |= _BV(SPIF);

    PORTB |= _BV(PB1);
}

const uint8_t digits[] = {
  0b11111100,
  0b01100000,
  0b11011010,
  0b11110010,
  0b01100110,
  0b10110110,
  0b10111110,
  0b11100000,
  0b11111110,
  0b11110110,
};

int main()
{
  spi_init();

  uint8_t i = 0;
  uint8_t data;

  while (1)
  {
    data = digits[i];
    spi_transfer(data);
    _delay_ms(1000);
    i++;
    i *= i < 10;
  }
}
