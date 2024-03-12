#include <avr/io.h>
#include <util/delay.h>

#define BTN1 PB4
#define BTN2 PB3
#define BTN3 PB2
#define BTN_PIN PINB
#define BTN_PORT PORTB

int main(){
    DDRD=0xFF;
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    BTN_PORT |= _BV(BTN1);
    BTN_PORT |= _BV(BTN2);
    BTN_PORT |= _BV(BTN3);

    uint8_t liczba=0;
    while (1){/*
        short disp=0b0000000;

        for(short i=0;i<8;i++){

            PORTD=gray;
        }*/
        int8_t but1 = BTN_PIN & _BV(BTN1);
        int8_t but2 = BTN_PIN & _BV(BTN2);
        int8_t but3 = BTN_PIN & _BV(BTN3);

        _delay_ms(30);

        if(but1==0 && (BTN_PIN & _BV(BTN1))){
            liczba += 1;
        }
        if(but2==0 && (BTN_PIN & _BV(BTN2))){
            liczba -= 1;
        }
        if(but3==0 && (BTN_PIN & _BV(BTN3))){
            liczba = 0;
        }
        PORTD = liczba ^ (liczba >> 1);
    }
}
