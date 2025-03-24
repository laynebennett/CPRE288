/// Simple 'Hello, world' program
/**
 * This program prints "Hello, world" to the LCD screen
 * @author Chad Nelson
 * @date 06/26/2012
 *
 * updated: phjones 9/3/2019
 * Description: Added timer_init call, and including Timer.h
 */

#include "Timer.h"
#include "lcd.h"



int lcd_rotatingBanner(int i){

    char str[] = "                    :)                    "; //':)' is test case phrase with white space padding



    int j; //represents the x position of word: "    |:)                 "
//                                                   ^
    for(j=0;j<20;j++){

        lcd_putc(str[j+i]);
    }



    i++; //iterate through chars of the phrase

    if(str[j+i+1]=='\0'){ //if at end of phrase, start again at 0
        i=0;
    }


return i;
}


int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen. 

	int i = 0;

	for(;;){

	    lcd_setCursorPos(0, 0); //resets cursor
	    timer_waitMillis(300);
	    lcd_init();
	    i = lcd_rotatingBanner(i); 


	}
	return;
}


