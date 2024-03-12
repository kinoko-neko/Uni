#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while(!(UCSR0A & _BV(UDRE0)));
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}
FILE uart_file;

void timer_init()
{
  // Ustaw tryb licznika 0
  TCCR0A = _BV(COM0A1) | _BV(WGM01) | _BV(WGM00); // Tryb Fast PWM
  TCCR0B = _BV(CS00); // Brak prescalera

  // Ustaw tryb licznika 1
  ICR1 = 255;
  TCCR1A = _BV(COM1A1) | _BV(WGM11); // Tryb Fast PWM
  TCCR1B = _BV(WGM12) | _BV(WGM13) | _BV(CS10); // Brak prescalera

  // Ustaw tryb licznika 2
  TCCR2A = _BV(COM2A1) | _BV(WGM01) | _BV(WGM00); // Tryb Fast PWM
  TCCR2B = _BV(CS00); // Brak prescalera

  // Ustaw piny wyjściowe jako wyjścia PWM
  DDRD |= _BV(PD6);  // OC0A (Timer 0)
  DDRB |= _BV(PB1);  // OC1A (Timer 1)
  DDRB |= _BV(PB3);  // OC2A (Timer 2)
}

const uint8_t brightness_values[73] = {
    0,0,2,5,9,15,21,28,37,46,56,67,78,90,102,114,127,139,152,164,176,187,198,208,217,225,233,239,245,249,252,254,255,254,252,249,245,239,233,225,217,208,198,187,176,164,152,139,127,114,102,90,78,67,56,46,37,28,21,15,9,5,2,1,0
};

int main(){
      uart_init();
      timer_init();
  // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

  //  printf("start\n\r");
    while(1){
        //losuj h
        uint16_t h = rand()%360;
        uint16_t c = 255;
        uint16_t x = (c * (255 - abs((h / 60) % 2 * 255))) / 255;
        //policz rgb
        uint16_t r,g,b;
    //    printf("newkolor %u\n\r",h);
        if(h<60){
          r = c; g = x; b = 0;
        } else if (h<120){
          r = x; g = c; b = 0;
        } else if (h<180) {
          r = 0; g = c; b = x;
        } else if (h<240) {
          r = 0; g = x; b = c;
        } else if (h<300){
          r = x; g = 0; b = c;
        } else{
          r = c; g = 0; b = x;
        }

        //petla na oddech
        for (uint8_t br = 0; br< 73; br++){
          for(uint8_t j=0; j<220;j++){
            OCR0A = b;
            OCR1A = r;
            OCR2A = g;
            //ustpełnienia wpisz takie jak wynikna z rgb
            for(uint8_t p=0; p<brightness_values[br];p++){
                _delay_us(0.5);
            }
            //uzupełnienia na 0
            OCR0A = 255;
            OCR1A = 255;
            OCR2A = 255;
            for(uint8_t p=brightness_values[br]; p<255;p++){
                _delay_us(0.5);
            }
          }
        }
        _delay_ms(20);

    }

}
