#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <errno.h>
#include <stdint.h>
#include <util/delay.h>

#define LED PB2
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PA7
#define BTN_PIN PINA
#define BTN_PORT PORTA

int8_t buf[100];

// inicjalizacja licznika 1
void timer1_init()
{
    TCCR1B = _BV(CS10) | _BV(WGM12);
    OCR1A = 9999;
    TIMSK1 = _BV(OCIE1A);
}

int8_t cnt=0;

ISR(TIM1_COMPA_vect) {

    if (buf[cnt] == 0) LED_PORT |= _BV(LED);
    else LED_PORT &= ~_BV(LED);
    //zapis
    if(BTN_PIN & _BV(BTN))
      buf[cnt] = 1;
    else
      buf[cnt] = 0;
    cnt++;
    if(cnt>100) cnt=0;

}


int main() {
  timer1_init();
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);

   sei();
   set_sleep_mode(SLEEP_MODE_IDLE);


    while (1) {
        sleep_mode();
    }
}


