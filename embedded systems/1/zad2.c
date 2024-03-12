#include <avr/io.h>
#include <util/delay.h>

int main(){
    DDRD=0xFF;
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);

    while (1){
        short a=0b00000001;

        for(short i=0;i<8;i++){
            PORTD=a;
            _delay_ms(10);
            a<<=1;
        }

    }
}
