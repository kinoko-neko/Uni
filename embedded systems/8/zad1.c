#include "FreeRTOS.h"
#include "task.h"
#include <avr/io.h>
#include <stdio.h>

#define mainLED_TASK_PRIORITY   2
#define mainSERIAL_TASK_PRIORITY 1

#define BAUD 9600                          // baudrate
#define UBRR_VALUE ((F_CPU)/16/(BAUD)-1)   // zgodnie ze wzorem

static void vLinikaLed(void* pvParameters);
static void vLed(void* pvParameters);/*
static void vSerial(void* pvParameters);

int uart_transmit(char c, FILE *stream);
int uart_receive(FILE *stream);
void uart_init(void);

FILE uart_file = FDEV_SETUP_STREAM(uart_transmit, uart_receive, _FDEV_SETUP_RW);

// inicjalizacja UART
void uart_init(void)
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

int uart_transmit(char c, FILE *stream) {
  while (!(UCSR0A & _BV(UDRE0))) taskYIELD();
  UDR0 = c;
  return 0;
}

int uart_receive(FILE *stream) {
  while (!(UCSR0A & _BV(RXC0))) taskYIELD();
  return UDR0;
}
*/
int main(void)
{
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    // Create task.
    xTaskHandle linika_handle;
 //   xTaskHandle serial_handle;
    xTaskHandle dioda_handle;

    xTaskCreate
        (
         vLinikaLed,
         "linka",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainLED_TASK_PRIORITY +1,
         &linika_handle
        );
    xTaskCreate
        (
         vLed,
         "dioda",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainLED_TASK_PRIORITY,
         &dioda_handle
        );/*
    xTaskCreate
        (
         vSerial,
         "serial",
         configMINIMAL_STACK_SIZE,
         NULL,
         mainSERIAL_TASK_PRIORITY,
         &serial_handle
        );
*/
    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}

/**************************************************************************//**
 * \fn static void vLinikaLed(void* pvParameters)
 *
 * \brief
 *
 * \param[in]   pvParameters
 ******************************************************************************/
static void vLinikaLed(void* pvParameters)
{
    DDRD=0xFF;
    short a=0b00000001;

    for ( ;; )
    {
        PORTD=a;
       // _delay_ms(10);
        a<<=1;
        if(a == 0) {a = 1;}
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
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

#define BTN PB4
#define BTN_PIN PINB
#define BTN_PORT PORTB

int8_t buf[101];

static void vLed(void* pvParameters)
{
    BTN_PORT |= _BV(BTN);
    LED_DDR |= _BV(LED);
    DDRB |= _BV(PB5);
    int8_t cnt=0;
    for ( ;; )
    {
        if (buf[cnt] == 0) LED_PORT |= _BV(LED);
        else LED_PORT &= ~_BV(LED);
        buf[cnt] = BTN_PIN & _BV(BTN);
        vTaskDelay(20);
        cnt++;
        if(cnt>100) {cnt=0; }
    }
}

void vApplicationIdleHook(void)
{

}


/*
static void vSerial(void* pvParameters)
{
    uart_init();
    stdin = stdout = stderr = &uart_file;

    char input;

    for ( ;; )
    {
        puts("Hello World\r\n");
        input = getchar();
        printf("You wrote %c\r\n", input);
    }
}
*/
