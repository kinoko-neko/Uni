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
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    while (1){
        for(short i=0;i<10;i++){
            PORTD=liczby[i];
            _delay_ms(1000);
        }
    }
}
