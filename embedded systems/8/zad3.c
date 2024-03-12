#include "FreeRTOS.h"
#include "portmacro.h"
#include "task.h"
#include "queue.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#define mainLED_TASK_PRIORITY   1
#define mainSERIAL_TASK_PRIORITY 2

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem
#include <util/setbaud.h>

static void vLed(void* pvParameters);
static void vSerial(void* pvParameters);

int uart_transmit(char c, FILE *stream);
int uart_receive(FILE *stream);
void uart_init(void);

FILE uart_file = FDEV_SETUP_STREAM(uart_transmit, uart_receive, _FDEV_SETUP_RW);

QueueHandle_t xQueuein, xQueueout;
//1-odbieranie
//2-nadawanie
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
  UCSR0B = _BV(RXEN0) | _BV(TXEN0) | _BV(RXCIE0); /* Enable RX and TX */
}


ISR(USART_UDRE_vect){
    uint8_t a;
    if (xQueueReceiveFromISR(xQueuein, &a, 0) == pdPASS){
        UDR0 = a;
    }
    else{
        UCSR0B &= ~_BV(UDRIE0);
    }
}


ISR(USART_RX_vect) {
    char received = UDR0;
    if (uxQueueMessagesWaitingFromISR(xQueueout)<99) xQueueSendToBackFromISR(xQueueout, &received, NULL);
}

int uart_transmit(char c, FILE *stream) {
    xQueueSendToBack(xQueuein, &c, portMAX_DELAY);
    UCSR0B |= _BV(UDRIE0);
    return 0;
}

int uart_receive(FILE *stream) {
    uint8_t data;
    if (xQueueReceive(xQueueout, &data, portMAX_DELAY) == pdPASS) {
        // Wait until data is available in the receive buffer
        return data;
    }
    return _FDEV_EOF;
}
int main(void)
{
    //UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);

    uart_init();
    stdin = stdout = stderr = &uart_file;
    // Create task.
    xTaskHandle serial_handle;
    xTaskHandle dioda_handle;
    xQueuein = xQueueCreate( 100, sizeof( char ) );
    xQueueout = xQueueCreate( 100, sizeof( char ) );

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
         mainLED_TASK_PRIORITY,
         &dioda_handle
        );


    // Start scheduler.
    vTaskStartScheduler();
     UCSR0B |= _BV(RXCIE0);
    sei();
    return 0;
}



void vApplicationIdleHook(void)
{

}
#define LED PB5
#define LED_DDR DDRB
#define LED_PORT PORTB

static void vLed(void* pvParameters)
{
    LED_DDR |= _BV(LED);
    DDRB |= _BV(PB5);

    while(1)
    {
        PORTB ^= _BV(PB5);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

static void vSerial(void* pvParameters)
{

    //char input;
    char input;
    while(1)
    {
        //puts("Hello World\r\n");
      //  scanf("%"SCNu16,&input);
    //    printf("ssa\r\n");
       // uint8_t eh;
        printf("wpisz:\r\n");
        scanf("%c",&input);
        printf("odczytano %c\r\n\n", input);
        vTaskDelay(100);
   //     xQueueSend( xQueue1, ( void * )&input, ( TickType_t ) 0 );
       // taskYIELD();

    }
}
