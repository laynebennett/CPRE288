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

    char str[] = "                    ;)                    ";



    int j;
    for(j=0;j<20;j++){

        lcd_putc(str[j+i]);
    }



    i++;

    if(str[j+i+1]=='\0'){
        i=0;
    }


    /*
    if (str[i] == '\0') {
        lcd_printf('\0')
    }
    else if (i > 20) {
        lcd_printf(str[i])
    }
    else {

    }
*/
 //   lcd_printf("%-19s", str[i]);
  //  i++;


return i;
}


int main (void) {

	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen. 

	// Print "Hello, world" on the LCD
	//lcd_printf("Hello, world");

	//lcd_puts("Hello, world"); // Replace lcd_printf with lcd_puts
        // step through in debug mode and explain to TA how it works
    
	// NOTE: It is recommended that you use only lcd_init(), lcd_printf(), lcd_putc, and lcd_puts from lcd.h.
       // NOTE: For time functions, see Timer.h

	int i = 0;

	for(;;){

	    lcd_setCursorPos(0, 0);
	    timer_waitMillis(300);
	    lcd_init();
	    i = lcd_rotatingBanner(i);


	}
	return;
}


