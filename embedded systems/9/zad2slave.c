#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdio.h>

#define LED PD3
#define LED_DDR DDRD
#define LED_PORT PORTD

#define BTN PD4
#define BTN_PIN PIND
#define BTN_PORT PORTD

void spi_init()
{
   // ustaw pin MISO jako wyjście
    DDRB |= _BV(DDB4);

    SPCR = _BV(SPE) | _BV(SPIE);
}

ISR(SPI_STC_vect){
    uint8_t a = SPDR;
    if (a == 0) LED_PORT |= _BV(LED);
    else LED_PORT &= ~_BV(LED);

    SPDR = (BTN_PIN & _BV(BTN))!=0;
}

int main()
{
    spi_init();
    BTN_PORT |= _BV(BTN);
    LED_DDR |= _BV(LED);

    sei();
    while (1) {
        sleep_mode();
    }
}
