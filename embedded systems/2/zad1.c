#include <avr/io.h>
#include <util/delay.h>

#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

int8_t buf[13];

int8_t read_bit(int8_t x){
    int8_t poz=x/8;
    int8_t shift=x&0b00000111;

    if(buf[poz] & (1<<shift))
        return 1;
    return 0;
}

void write_bit(int8_t x,int8_t val){
    int8_t poz=x/8;
    int8_t shift=x&0b00000111;

    if(val){
        buf[poz] |= (1<<shift);
    }
    else{
        buf[poz] &= (0xFF ^ (1<<shift));
    }
}

int main() {
  BTN_PORT |= _BV(BTN);
  LED_DDR |= _BV(LED);

//  LED_DDR |= _BV(BTN);

  int8_t cnt=0;
  while (1) {
    //odczyt
    //ustaw diode

    LED_PORT = read_bit(cnt)<<LED;
    //zapis
    write_bit(cnt,BTN_PIN & _BV(BTN) );

    //delay
    _delay_ms(10);
    cnt++;
    if(cnt>100) cnt=0;
  }
}


