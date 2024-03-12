#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
#include "i2c.c"

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

const uint8_t eeprom_addr = 0xa0; // 1010 0000

uint8_t read1(uint8_t addr){
    i2cStart();
    i2cSend(eeprom_addr | ((addr & 0x100) >> 7) );
    i2cSend(addr & 0xFF);
    i2cStart();
    i2cSend(eeprom_addr | ((addr & 0x100) >> 7) | 1);
    uint8_t data = i2cReadNoAck();
    i2cStop();
    return data;
}

void write1(uint8_t addr, uint8_t value){
    i2cStart();
    i2cSend(eeprom_addr | ((addr & 0x100) >> 7) );
    i2cSend(addr & 0xFF);
    i2cSend(value);
    i2cStop();
    _delay_ms(10);
}

//adress 0b1010 00
int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj I2C


  i2cInit();
  // program testowy
  uint16_t addr;
  uint8_t val;
 // write1(addr, 32);
  //uint8_t val=read1(addr);
 // printf("val = %d",val);
  char typ;

  while (1) {

    scanf("%c %d",&typ,&addr);
    if( typ == 'w'){
      scanf("%2" SCNu8,&val);
      write1(addr, val);
      printf("zapisano: %d w %d\r\n",val,addr);
    }
    else if(typ == 'r'){
      printf("oczytano: %d z %d\r\n",read1(addr),addr);
    }
    else{
      printf("zly input\r\n");
    }
  }
}

