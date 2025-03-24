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
#include "open_interface.h"
#include "movement.h"


int lcd_rotatingBanner(int i){ //creates rotating banner display on 20-wide lcd display on the CyBOT

    char str[] = "                    :)                    "; //using smiley face as test case with white space padding



    int j;
    for(j=0;j<20;j++){ //shift string to left in increments of 1

        lcd_putc(str[j+i]);
    }



    i++;

    if(str[j+i+1]=='\0'){ //if at the end of the string, start at beginning
        i=0;
    }


return i;
}





int main (void) {

    oi_t *sensor_data = oi_alloc();

    oi_init(sensor_data);











	timer_init(); // Initialize Timer, needed before any LCD screen functions can be called 
	              // and enables time functions (e.g. timer_waitMillis)

	lcd_init();   // Initialize the LCD screen.  This also clears the screen. 

	/*
    //SQUARE MOVEMENT
	move_forward(sensor_data, 500);

	turn_right(sensor_data, 90);

    move_forward(sensor_data, 500);

    turn_right(sensor_data, 90);

    move_forward(sensor_data, 500);

    turn_right(sensor_data, 90);

    move_forward(sensor_data, 500);

    turn_right(sensor_data, 90);
    */


    //BUMP DETECTION
    move_forward_bump(sensor_data, 2000); //detects bump and moves around objects to the right, moving forward 2 meters total

	/*int i = 0;

	for(;;){

	    lcd_setCursorPos(0, 0);
	    timer_waitMillis(300);
	    lcd_init();
	    i = lcd_rotatingBanner(i);


	}

	*/

	oi_free(sensor_data);

	return;
}


