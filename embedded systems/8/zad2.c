#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>
#define mainLED_TASK_PRIORITY   2
#define mainSERIAL_TASK_PRIORITY 1

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#include <util/setbaud.h>

static void vLed(void* pvParameters);
static void vSerial(void* pvParameters);

int uart_transmit(char c, FILE *stream);
int uart_receive(FILE *stream);
void uart_init(void);

FILE uart_file = FDEV_SETUP_STREAM(uart_transmit, uart_receive, _FDEV_SETUP_RW);

// inicjalizacja UART
void uart_init(void)
{
  UBRR0H = UBRRH_VALUE;
  UBRR0L = UBRRL_VALUE;
#if USE_2X
  UCSR0A |= _BV(U2X0);
#else
  UCSR0A &= ~(_BV(U2X0));
#endif
  UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
  UCSR0B = _BV(RXEN0) | _BV(TXEN0); /* Enable RX and TX */
}

int uart_transmit(char c, FILE *stream) {
  while (!(UCSR0A & _BV(UDRE0))) taskYIELD();
  UDR0 = c;
  return 0;
}

int uart_receive(FILE *stream) {
  while (!(UCSR0A & _BV(RXC0))) taskYIELD();
  return UDR0;
}

QueueHandle_t xQueue1;

int main(void)
{
    //UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    uart_init();
    stdin = stdout = stderr = &uart_file;
    // Create task.
    xTaskHandle serial_handle;
    xTaskHandle dioda_handle;
    xQueue1 = xQueueCreate( 10, sizeof( uint16_t ) );


    xTaskCreate
        (
         vSerial,
         "serial",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainSERIAL_TASK_PRIORITY,
         &serial_handle
        );
    xTaskCreate
        (
         vLed,
         "dioda",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainSERIAL_TASK_PRIORITY,
         &dioda_handle
        );

    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}



/**************************************************************************//**
 * \fn static void vLed(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

int8_t buf[101];

static void vLed(void* pvParameters)
{
    LED_DDR |= _BV(LED);
    DDRB |= _BV(PB5);

   // printf("eh1\r\n");
    for ( ;; )
    {
        uint16_t val;
     //   printf("eh2\r\n");
       // putchar('a');
        if(xQueueReceive( xQueue1, &( val ),0 ) == pdPASS ) {
      //  printf("eeee macarena\r\n");
          printf("wzieto: %d\r\n",val);
          LED_PORT |= _BV(LED);
          vTaskDelay(val);
          LED_PORT &= ~_BV(LED);
          vTaskDelay(100);
        }
    }
}

void vApplicationIdleHook(void)
{

}


static void vSerial(void* pvParameters)
{

    //char input;
    uint16_t input;
    for ( ;; )
    {
        //puts("Hello World\r\n");
        scanf("%"SCNu16,&input);
    //    printf("ssa\r\n");
        printf("You wrote %d\r\n", input);
        xQueueSend( xQueue1, ( void * )&input, ( TickType_t ) 10 );
       // taskYIELD();

    }
}
