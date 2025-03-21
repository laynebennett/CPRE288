/**
 * lab5_template.c
 *
 * Template file for CprE 288 Lab 5
 *
 * @author Zhao Zhang, Chad Nelson, Zachary Glanz
 * @date 08/14/2016
 *
 * @author Phillip Jones, updated 6/4/2019
 * @author Diane Rover, updated 2/25/2021, 2/17/2022
 */

#include "button.h"
#include "timer.h"
#include "lcd.h"
#include "uart.h"

#include "cyBot_uart.h"  // Functions for communicating between CyBot and Putty (via UART1)
                         // PuTTy: Baud=115200, 8 data bits, No Flow Control, No Parity, COM1

#include "cyBot_Scan.h"  // Scan using CyBot servo and sensors


//#define REPLACEME 0


void sendString(char c, char puttyString[]);

void printWholeString(char puttyString[]);


int main(void) {
	button_init();
	timer_init(); // Must be called before lcd_init(), which uses timer functions
	lcd_init();


  // initialize the cyBot UART1 before trying to use it

  
	//cyBot_uart_init_clean();  // Clean UART1 initialization, before running your UART1 GPIO init code
	uart_init();
	// Complete this code for configuring the GPIO PORTB part of UART1 initialization (your UART1 GPIO init code)
  /*   SYSCTL_RCGCGPIO_R |= 0b10;
	    while ((SYSCTL_PRGPIO_R & 0b10) == 0) {};
		  GPIO_PORTB_DEN_R |= 0b11;
		  GPIO_PORTB_AFSEL_R |= 0b11;
		  GPIO_PORTB_PCTL_R &= ~0xFF;     // Force 0's in the desired locations
          GPIO_PORTB_PCTL_R |= 0x011;     // Force 1's in the desired locations
          */
		 // Or see the notes for a coding alternative to assign a value to the PCTL field

    
		//cyBot_uart_init_last_half();  // Complete the UART device configuration

		// Initialize the scan
	   //cyBOT_init_Scan();
		// Remember servo calibration function and variables from Lab 3

	
for(;;){
		 char puttyString[50]={'\0'}; //initializes empty string for printing on putty and lcd
		 char lcdString[50]={'\0'}; 
		     char button;
		     lcd_home();
		     int i;
		     for(i=0; i<20; i++){ //reciece 20 chars from UART

		         button = uart_receive();


		         if(button==13){ //if enter pressed, break
		             break;
		         }
		         sprintf(puttyString, "%c", button);
		         sprintf(lcdString, "%s%c", lcdString, button); //adds characters to final printed string
		         
		         printWholeString(puttyString); //prints to putty


		     }
		     sprintf(puttyString, "\n"); //prints to lcd
		     printWholeString(puttyString);
		     lcd_clear();
		     lcd_puts(lcdString);
		     lcd_gotoLine(2);
		     sprintf(lcdString, "%i", i);
		     lcd_puts(lcdString);


    }
}

void sendString(char c, char puttyString[]){ //Sends full string to print on the LCD

    sprintf(puttyString, "%s%c", puttyString, c);
    lcd_printf("Got %s\n", puttyString);

}

void printWholeString(char puttyString[]){ //Sends full string to print on putty interface
    int i;
    for(i=0;i<strlen(puttyString);i++){
        uart_sendChar(puttyString[i]);
    }

}

