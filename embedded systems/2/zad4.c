#include <avr/io.h>
#include <util/delay.h>

const short liczby[10]={
    0b01000000,
    0b01111001,
    0b00100100,
    0b00110000,
    0b00011001,
    0b00010010,
    0b00000010,
    0b01111000,
    0b00000000,
    0b00010000
};

const short segmenty[8]={
    0b11111110,
    0b11111101,
    0b11111011,
    0b11110111,
    0b11101111,
    0b11011111,
    0b10111111,
    0b01111111
};


int main(){
    DDRD=0xFF;
    DDRC |= _BV(PC0);
    DDRC |= _BV(PC1);
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    while (1){
        for(short j=0;j<6;j++){
            for(short i=0;i<10;i++){
                for(short k=0;k<500;k++){

                    PORTC &= ~_BV(PC1);
                    PORTD = liczby[i];
                    PORTC |= _BV(PC0);
                    _delay_ms(1);
                    PORTC &= ~_BV(PC0);
                    PORTD = liczby[j];
                    PORTC |= _BV(PC1);
                    _delay_ms(1);
                }
            }
        }
    }
}
