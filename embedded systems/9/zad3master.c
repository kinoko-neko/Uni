#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DDR_USI DDRA
#define PORT_USI PORTA
#define PIN_USI PINA

#include "USI_TWI_Master.c"

#define SLAVE_ADDR  0x7f

#define MESSAGEBUF_SIZE       4

#define TWI_GEN_CALL         0x00  // The General Call address is 0

// Sample TWI transmission commands
#define TWI_CMD_MASTER_WRITE 0x10
#define TWI_CMD_MASTER_READ  0x20

// Sample TWI transmission states, used in the main application.
#define SEND_DATA             0x01
#define REQUEST_DATA          0x02
#define READ_DATA_FROM_BUFFER 0x03



int main( void )
{
  unsigned char messageBuf[MESSAGEBUF_SIZE];
  unsigned char TWI_targetSlaveAddress, temp;
  uint8_t myCounter=0;

  //LED feedback port - connect port B to the STK500 LEDS

  //Switch port - connect portD to the STK500 switches

  USI_TWI_Master_Initialise();

 //sei();

  TWI_targetSlaveAddress   = 0x7f;

  // This example is made to work together with the AVR311 TWI Slave application note and stk500.
  // In adition to connecting the TWI pins, also connect PORTB to the LEDS and PORTD to the switches.
  // The code reads the pins to trigger the action you request. There is an example sending a general call,
  // address call with Master Read and Master Write. The first byte in the transmission is used to send
  // commands to the TWI slave.

  // This is a stk500 demo example. The buttons on PORTD are used to control different TWI operations.
  sei();
  for(;;)
  {
    messageBuf[0] = (TWI_targetSlaveAddress<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT); // The first byte must always consit of General Call code or the TWI slave address.
    messageBuf[1] = TWI_CMD_MASTER_WRITE;             // The first byte is used for commands.
    messageBuf[2] = myCounter;                        // The second byte is used for the data.
    temp = USI_TWI_Start_Transceiver_With_Data( messageBuf, 3 );
    myCounter++;
    _delay_ms(1000);
  }
}

