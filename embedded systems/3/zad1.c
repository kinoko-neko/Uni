#include <avr/pgmspace.h>
#include <avr/io.h>
#include<inttypes.h>
#include <util/delay.h>

// Definicje dźwięków i ich częstotliwości

#define C4 261.63
#define D4 293.66
#define E4 329.63
#define F4 349.23
#define G4 392.00
#define A4 440.00
#define B4 493.88
#define C2 523.25
#define D2 587.33

#define C 64
#define D 72
#define E 82
#define F 86
#define G 98
#define A 110
#define B 122
#define CC 130
#define DD 146
/*
#define C 32
#define D 36
#define E 41
#define F 43
#define G 49
#define A 55
#define B 61
#define CC 65
#define DD 73
*/
/*
#define C 16
#define D 18
#define E 20
#define F 21
#define G 24
#define A 27
#define B 30
#define CC 32
#define DD 36
*/
// Definicje długości nut
#define WHOLE 8
#define HALF 4
#define QUARTER 2
#define EIGHTH 1

// Tablica nut (uproszczona wersja melodii "Bad Apple!!")

static const uint16_t melody[] PROGMEM = {
    D, E, F, G, A, DD, CC, A, D, A, G, F, E,
    D, E, F, G, A, G, F, E, D, E, F, E, C,
    E, D, E, F, G, A, DD, CC, A, D, A, G, F, E,
    D, E, F, G, A, G, F, D, E, F, G,
    D, E, F, G, A, DD, CC, A, D, A, G, F, E,
    D, E, F, G, A, G, F, E, D, E, F, E, C,
    E, D, E, F, G, A, DD, CC, A, D, A, G, F, E,
    D, E, F, G, A, G, F, D, E, F, G

};
//53
// Tablica długości nut (ćwierćnuty)
static const uint16_t noteLengths[] PROGMEM = {
    QUARTER, QUARTER, QUARTER, QUARTER, HALF, QUARTER, QUARTER, HALF, HALF, QUARTER, QUARTER, QUARTER, QUARTER,
    QUARTER, QUARTER, QUARTER, QUARTER, HALF, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER,
    QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, HALF, QUARTER, QUARTER, HALF, HALF, QUARTER, QUARTER, QUARTER, QUARTER,
    QUARTER, QUARTER, QUARTER, QUARTER, HALF, QUARTER, QUARTER, HALF, HALF, HALF, HALF,
    QUARTER, QUARTER, QUARTER, QUARTER, HALF, QUARTER, QUARTER, HALF, HALF, QUARTER, QUARTER, QUARTER, QUARTER,
    QUARTER, QUARTER, QUARTER, QUARTER, HALF, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, QUARTER,
    QUARTER, QUARTER, QUARTER, QUARTER, QUARTER, HALF, QUARTER, QUARTER, HALF, HALF, QUARTER, QUARTER, QUARTER, QUARTER,
    QUARTER, QUARTER, QUARTER, QUARTER, HALF, QUARTER, QUARTER, HALF, HALF, HALF, HALF
};

#define BZ PB4
#define BZPORT PORTB


int main(){
    DDRB |= _BV(BZ);

   // while (1){
         for(int8_t i=0;i<106;i++){
             int8_t czas=pgm_read_byte(&noteLengths[i])*2;
             for(int8_t j=0; j<czas;j++){
                 for(int16_t k=0; k<pgm_read_byte(&melody[i])  ;k++){
                     switch (pgm_read_byte(&melody[i])){
                        case C:
                            BZPORT |= _BV(BZ);
                            _delay_ms(125.0/C4);
                            BZPORT &= ~_BV(BZ);
                            _delay_ms(125.0/C4); continue;
                        case D:
                            BZPORT |= _BV(BZ);
                            _delay_ms(125.0/D4);
                            BZPORT &= ~_BV(BZ);
                            _delay_ms(125.0/D4); continue;
                        case E:
                            BZPORT |= _BV(BZ);
                            _delay_ms(125.0/E4);
                            BZPORT &= ~_BV(BZ);
                            _delay_ms(125.0/E4); continue;
                        case F:
                            BZPORT |= _BV(BZ);
                            _delay_ms(125.0/F4);
                            BZPORT &= ~_BV(BZ);
                            _delay_ms(125.0/F4); continue;
                        case G:
                            BZPORT |= _BV(BZ);
                            _delay_ms(125.0/G4);
                            BZPORT &= ~_BV(BZ);
                            _delay_ms(125.0/G4); continue;
                        case A:
                            BZPORT |= _BV(BZ);
                            _delay_ms(125.0/A4);
                            BZPORT &= ~_BV(BZ);
                            _delay_ms(125.0/A4); continue;
                        case B:
                            BZPORT |= _BV(BZ);
                            _delay_ms(125.0/B4);
                            BZPORT &= ~_BV(BZ);
                            _delay_ms(125.0/B4); continue;
                        case CC:
                            BZPORT |= _BV(BZ);
                            _delay_ms(125.0/C2);
                            BZPORT &= ~_BV(BZ);
                            _delay_ms(125.0/C2); continue;
                        case DD:
                            BZPORT |= _BV(BZ);
                            _delay_ms(125.0/D2);
                            BZPORT &= ~_BV(BZ);
                            _delay_ms(125.0/D2); continue;
                    }

                }
            }
         }

     //}
}
