#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <errno.h>
#include <stdint.h>
#include <util/delay.h>

void spi_init(){
    // ustaw piny MOSI i SCK jako wyjścia
    DDRA = _BV(DDA4) | _BV(DDA5);
    // ustaw USI w trybie trzyprzewodowym (SPI)
    USICR = _BV(USIWM0);
}

uint8_t spi_transfer(uint8_t data){
    // załaduj dane do przesłania
    USIDR = data;
    // wyczyść flagę przerwania USI
    USISR = _BV(USIOIF);
    // póki transmisja nie została ukończona, wysyłaj impulsy zegara
    while (!(USISR & _BV(USIOIF))) {
        // wygeneruj pojedyncze zbocze zegarowe
        // zostanie wykonane 16 razy
        USICR = _BV(USIWM0) | _BV(USICS1) | _BV(USICLK) | _BV(USITC);
    }
    // zwróć otrzymane dane
    return USIDR;
}

#define BTN PA7
#define BTN_PIN PINA
#define BTN_PORT PORTA

#define LED PB2
#define LED_DDR DDRB
#define LED_PORT PORTB

int main()
{
    spi_init();
    LED_DDR |= _BV(LED);
    BTN_PORT |= _BV(BTN);
    while(1) {
        uint8_t rec = spi_transfer(( BTN_PIN & _BV(BTN) )>>4);
        if( rec ){
            LED_PORT &= ~_BV(LED);
        }
        else{
            LED_PORT |= _BV(LED);
        }
        _delay_ms(100);
    }
}
