#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <stdint.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

int8_t buf[100];

// inicjalizacja licznika 1
void timer1_init()
{
 TCCR1B = _BV(CS11) | _BV(WGM12);
    OCR1A = 19999;
    TIMSK1 = _BV(OCIE1A);
}

int8_t cnt=0;

ISR(TIMER1_COMPA_vect) {

    if (buf[cnt] == 0) LED_PORT |= _BV(LED);
    else LED_PORT &= ~_BV(LED);
    //zapis
    if(BTN_PIN & _BV(BTN))
      buf[cnt] = 0;
    else
      buf[cnt] = 1;
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


