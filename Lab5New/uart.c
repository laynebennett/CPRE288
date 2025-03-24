/*
*
*   uart.c
*
*
*
*   @author
*   @date
*/

#include <inc/tm4c123gh6pm.h>
#include <stdint.h>
#include "uart.h"
#include "lcd.h"

void uart_init(void){
	//TODO
  //enable clock to GPIO port B
  SYSCTL_RCGCGPIO_R |= 0b10;

  //enable clock to UART1
  SYSCTL_RCGCUART_R |= 0b10;

  //wait for GPIOB and UART1 peripherals to be ready
  while ((SYSCTL_PRGPIO_R & 0b10) == 0) {};
  while ((SYSCTL_PRUART_R & 0b10) == 0) {};

  //enable alternate functions on port B pins
  GPIO_PORTB_AFSEL_R |= 0b11;

  //enable digital functionality on port B pins
  GPIO_PORTB_DEN_R |= 0b11;

  //enable UART1 Rx and Tx on port B pins
  GPIO_PORTB_PCTL_R &= ~0xFF;     // Force 0's in the desired locations
  GPIO_PORTB_PCTL_R |= 0x011;     // Force 1's in the desired locations

  //calculate baud rate
  uint16_t iBRD = 8; //use equations
  uint16_t fBRD = 44; //use equations

  //turn off UART1 while setting it up
  UART1_CTL_R &= ~0x1;

  //set baud rate
  UART1_IBRD_R = iBRD;
  UART1_FBRD_R = fBRD;

  UART1_LCRH_R = 0b01100000;

  //use system clock as source
  UART1_CC_R = 0x0;

  //re-enable UART1 and also enable RX, TX (three bits)
  //RX and TX are enabled by default on reset
  UART1_CTL_R |= 0x1;

}

void uart_sendChar(char data){
	UART1_DR_R = data;
}

char uart_receive(void){
    while (UART1_FR_R & 0x10) { // Check the Receive FIFO Empty flag
            // Wait until there is data to read
        }
        return (char)(UART1_DR_R & 0xFF);
}

void uart_sendStr(const char *data){

    while(*data != '\0')
        {
            lcd_putc(*data);
            data++;
        }
}
