#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include <math.h>

#define LED PB5
#define LED_PORT PORTB
#define LED_DDR DDRB

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

void adc_init()
{
  ADMUX   = _BV(REFS0); // referencja AVcc, wejście ADC0
 // ADMUX |= 0b1110;
  DIDR0   = _BV(ADC0D); // wyłącz wejście cyfrowe na ADC0
  // częstotliwość zegara ADC 125 kHz (16 MHz / 128)
  ADCSRA  = _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2); // preskaler 128
  ADCSRA |= _BV(ADEN); // włącz ADC
}

const uint16_t sub=388;
FILE uart_file;
int main(){
     DDRB |= _BV(LED);
    // zainicjalizuj ADC
      uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;
    adc_init();
    printf("start\n\r");
    while(1){

        LED_PORT ^= _BV(LED);
        ADCSRA |= _BV(ADSC); // wykonaj konwersję
        while (!(ADCSRA & _BV(ADIF))); // czekaj na wynik
        ADCSRA |= _BV(ADIF); // wyczyść bit ADIF (pisząc 1!)
        uint16_t v = ADC; // weź zmierzoną wartość (0..1023)
    //    uint16_t vol = (11264/v);
        // vout = vin * (R1/(R1 + R2))
        printf("Odczytano: %u" "\r\n", v);
        // v = vin * (R1/(R1 + R2))
        // v = vin * (10000/(10000 + R2))
        // v*(10000 + R2) = vin * 10000
        // v*10000 + R2*v = 10000vin
        // R2*v = 10000vin - v*10000
        // R2*v = 10000(vin - v)
        // R2 = 10000(vin - v) / v
        // R2 = 10000*(vin/v - 1)

        // R2 = 10000(1024/v - 1)
        // R2 = 10240000/v - 10000

        double R2 = (10240000/v - 10000);

        double R0 = 4700.0; double B= 2613.7; double T0= 298.15;
        float T = ((R0*T0)/(T0*log((R2/R0)) +B))  - 273.15;

        int t2 = (int)T;
        printf("Tmp= %d.%d \n\r",t2/10,t2%10);

        _delay_ms(1000);
    }
}
