#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>
#include "hd44780.c"

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

// inicjalizacja UART
void uart_init()
{
  // ustaw baudrate
  UBRR0 = UBRR_VALUE;
  // wyczyść rejestr UCSR0A
  UCSR0A = 0;
  // włącz odbiornik i nadajnik
  UCSR0B = _BV(RXEN0) | _BV(TXEN0);
  // ustaw format 8n1
  UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)));
  return UDR0;
}

int hd44780_transmit(char data, FILE *stream)
{
  LCD_WriteData(data);
  return 0;
}


FILE hd44780_file;

char tab[17]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
int main()
{
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  uart_init();
  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, uart_receive, _FDEV_SETUP_RW);
  stdout = stderr = &hd44780_file;
  stdin = &hd44780_file;

  LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_ON | HD44780_CURSOR_BLINK);
  // program testowy
  printf("Hello world!");
  uint8_t x = 0;
  LCD_GoTo(0, 1);
  while(1) {
    char c;
    scanf("%c",&c);
    if(c == '\r'){
        LCD_GoTo(0, 0);
        printf("%s",tab);
        for(uint8_t i =0;i<16;i++){
            tab[i]= ' ';
        }
        LCD_GoTo(0, 1);
        printf("                ");
        LCD_GoTo(0, 1);
        x=0;
    }
    else{
        printf("%c",c);
        tab[x] = c;
        x++;
        if(x>=16) x=0;
        LCD_GoTo(x,1);
    }
   // _delay_ms(1000);
  }
}

