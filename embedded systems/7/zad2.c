#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <util/delay.h>
#include "i2c.c"
#include "i2c.h"

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
/*
void read2(uint8_t addr, uint8_t length) {
    i2cStart();
    i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
    i2cSend(addr & 0xFF);
    i2cStart();
    i2cSend((eeprom_addr | ((addr & 0x100) >> 7)) | 1);

    for (uint8_t i = 0; i < length; ++i) {
        if (i < length - 1) {
            printf("%c ", i2cReadAck());
        } else {
            printf("%c ", i2cReadNoAck());
        }
    }

    i2cStop();
}
*/

void read2(uint8_t addr, uint8_t length) {
    i2cStart();
    i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
    i2cSend(addr & 0xFF);
    i2cStart();
    i2cSend((eeprom_addr | ((addr & 0x100) >> 7)) | 1);

    uint8_t tab[30];
    for (uint8_t i = 0; i < length; ++i) {
        if (i < length - 1) {
            tab[i] = i2cReadAck();
          //  printf("%c ", i2cReadAck());
        } else {

            tab[i] = i2cReadAck();
           // printf("%c ", i2cReadNoAck());
        }
    }

    i2cStop();

    uint8_t wsk = 0;
    for (uint8_t i =0; i < (length/4) ; i++) {
        printf(":08%x00",addr);
        addr+=4;
        uint8_t sum = 0;
        for (uint8_t j =0;j<4 ;j++ ) {
            printf("%x",tab[wsk]);
            wsk++;
            sum+=tab[wsk];
        }
        printf("%x\r\n",sum);
    }
    if(wsk<length){
        printf(":%x%x00",(length-wsk)*2,addr);
        uint8_t sum = 0;
        while(wsk<length){
            printf("%x",tab[wsk]);
            wsk++;
            sum+=tab[wsk];
        }
        printf("%x\r\n",sum);
    }
    printf(":00000001FF");
}

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

void write_block(uint8_t addr,uint8_t length, uint8_t* data ) {

    printf("do wpisania ");
    for (uint8_t i = 0 ;i<length ; i++ ) {
        printf("%d,",data[i]);
    }
    printf(" tyle\n\r");
    uint8_t wsk = 0;
    for(uint8_t i = 0; i<(length/4);i++){
        i2cStart();
        i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
        i2cSend(addr & 0xFF);

        for(uint8_t j =0; j<4;j++){
            i2cSend(data[wsk]);
            printf("e = %c\r\n",data[wsk]);
            wsk++; addr++;
            _delay_ms(25);
        }
        i2cStop();
        _delay_ms(25);
    }

    if(length> wsk){
        i2cStart();
        i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
        i2cSend(addr & 0xFF);
        while(wsk<length){
            printf("e = %c\r\n",data[wsk]);
            i2cSend(data[wsk]);
            wsk++;
        }

        i2cStop();
        _delay_ms(20);
    }
}

uint8_t chartohex(char x){
    switch (x) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'A': return 10;
        case 'B': return 11;
        case 'C': return 12;
        case 'D': return 13;
        case 'E': return 14;
        case 'F': return 15;
    }
}


void write1(uint8_t addr, uint8_t value){
    i2cStart();
    i2cSend(eeprom_addr | ((addr & 0x100) >> 7) );
    i2cSend(addr & 0xFF);
    i2cSend(value);
    i2cStop();
    _delay_ms(10);
}


void zapis(uint8_t* tab, uint8_t len){

    printf("do konwersji ");
    for (uint8_t i = 0 ;i<len ; i++ ) {
        printf("%c",tab[i]);
    }
    printf(" tyle\n\r");

    uint8_t tab1[20];

    uint8_t siz;
    uint8_t wsk = 0;

    while(wsk<len){
        if(tab[wsk]==':'){
            printf("dwukopek\n\r");
            siz = chartohex(tab[wsk+1])*16+chartohex(tab[wsk+2]);
            siz*=2;

            wsk+=3;
            uint16_t addr =chartohex(tab[wsk])*16*16*16 + chartohex(tab[wsk+1])*16*16+chartohex(tab[wsk+2])*16+chartohex(tab[wsk+3]);
            wsk+=4;

            uint8_t typ = chartohex(tab[wsk])*16+chartohex(tab[wsk+1]);
            wsk+=2;

            printf("typ = %d siz = %d",typ,siz);
            if(typ == 1) return;
            for(uint16_t i=0;i<siz;i+=2){ //2znaki to jeden uint
                tab1[i/2] = chartohex(tab[wsk+i])*16 + chartohex(tab[wsk+i+1]);
            }
            wsk+=siz;
            write_block(addr,siz/2 ,tab1 );
        }
        wsk++;
    }

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
    char command;
    uint8_t buf[43];
   // uint8_t buf2[50];
    while(1) {
        printf("ready\r\n");
        scanf("%c",&command);
        if (command == 'r')
        {
            printf("read\r\n");
            uint16_t addr;
            scanf("%d",&addr);
            printf("odczytano: %d\r\n",addr);
            printf("odczytano %.3x: %c\r\n",addr,read1(addr));
        }
        else if (command == 'w')
        {
            printf("write\r\n");
            uint16_t addr;
            char data;
            scanf("%d %c",&addr, &data);
            printf("odczytano: %d, %d\r\n",addr, data);
            write1(addr, data);
        }
        else if (command == 't')
        {
            printf("sequential read\r\n");
            uint16_t addr;
            uint16_t len;
            scanf("%d %d",&addr, &len);
            if (len > 40) len = 40;
            printf("odczytano: %d %d\r\n",addr,len);
            read2(addr, len);
            printf("\r\n");
        }
        else if (command == 'e')
        {
            printf("sequential write\r\n");
            uint16_t len;
            scanf("%d",&len);
            if (len > 40) len = 40;
            scanf("%s",buf);

            printf("odczytano:%d\r\n",len);
            zapis(buf, len);
        }
        for(uint8_t i = 0; i<20; i++)
        {
            buf[i] = ' ';
        }
        printf("\r\n");
    }

}
//len = 19
//:0400000011111111 99
