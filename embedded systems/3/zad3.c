#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>

#define LED PD4
#define LED_PORT PORTD

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



// inicjalizacja ADC

const uint8_t exp_table[] = {0, 1, 2, 4, 6, 9, 13, 18, 24, 32, 41, 53, 67, 84, 104, 128};

void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

const uint16_t sub=388;
FILE uart_file;
int main(){
    DDRD |= _BV(LED);
    // zainicjalizuj ADC
      uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    adc_init();
    printf("start\n\r");
    while(1){
        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        uint16_t v = ADC; // weź zmierzoną wartość (0..1023)

        uint16_t b=1;

        printf("Odczytano: %u %u %d" "\r\n", v,v-388,b);
    //    _delay_ms(10);
        if (v < 1024) {
        // Przelicz wartość pomiaru na jasność z wykorzystaniem tablicy wykładniczej
          b=exp_table[v>> 6]; // Przesunięcie bitowe o 6 to odpowiednik dzielenia przez 64
        } else {
            b=255; // Maksymalna jasność
        }
//

        for(uint8_t j=0; j<255;j++){
            LED_PORT |= _BV(LED);
            for(uint8_t p=0; p<b;p++){
                _delay_us(10);
            }
            LED_PORT &= ~_BV(LED);
            for(uint8_t p=b; p<255;p++){
                _delay_us(10);
            }
        }
    }
}
