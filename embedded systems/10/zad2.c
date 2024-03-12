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

uint8_t tab[5]={0b10000,0b11000,0b11100,0b11110,0b11111};
int main(){
  // skonfiguruj wyświetlacz
  LCD_Initialize();
  LCD_Clear();
  uart_init();
  // skonfiguruj strumienie wyjściowe
  fdev_setup_stream(&hd44780_file, hd44780_transmit, uart_receive, _FDEV_SETUP_RW);
  stdout = stderr = &hd44780_file;
  stdin = &hd44780_file;

  LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON );
  // program testowy

  for(uint8_t i =0; i<5;i++){
    LCD_WriteCommand(HD44780_CGRAM_SET | (i<<3));
    for(uint8_t j=0;j<8;j++){
        LCD_WriteData(tab[i]);
    }
  }
  while(1){
    for(uint8_t i=0;i<16;i++){
      for(uint8_t j = 0; j<5;j++){
        LCD_GoTo(i, 1);
        printf("%c",j);
        _delay_ms(100);
      }
    }
  }
}

