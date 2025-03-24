/*
 * button.c
 *
 *  Created on: Jul 18, 2016
 *      Author: Eric Middleton, Zhao Zhang, Chad Nelson, & Zachary Glanz.
 *
 *  @edit: Lindsey Sleeth and Sam Stifter on 02/04/2019
 *  @edit: Phillip Jones 05/30/2019: Merged Spring 2019 version with Fall 2018
 *  @edit: Diane Rover 02/01/20: Corrected comments about ordering of switches for new LCD board and added busy-wait on PRGPIO
 */



//The buttons are on PORTE 3:0
// GPIO_PORTE_DATA_R -- Name of the memory mapped register for GPIO Port E,
// which is connected to the push buttons
#include "button.h"


/**
 * Initialize PORTE and configure bits 0-3 to be used as inputs for the buttons.
 */
void button_init() {
	static uint8_t initialized = 0;

	//Check if already initialized
	if(initialized){
		return;
	}

	
	SYSCTL_RCGCGPIO_R |= 0b10000; //0x10 start register clock
	while ((SYSCTL_PRGPIO_R & 0b10000) == 0) {};
	GPIO_PORTE_DIR_R &= 0b11110000; //set direction of buttons
	GPIO_PORTE_DEN_R |= 0b00001111; //enable register

	initialized = 1;
}



/**
 * Returns the position of the rightmost button being pushed.
 * @return the position of the rightmost button being pushed. 1 is the leftmost button, 4 is the rightmost button.  0 indicates no button being pressed
 */
uint8_t button_getButton() {



    if((GPIO_PORTE_DATA_R & 0b00001000) == 0x0){ //returns 1 2 3 and 4 for each button pressed
        return 0b00000100;
    }else if((GPIO_PORTE_DATA_R & 0b00000100) == 0x0){
        return 0b00000011;
    }else if((GPIO_PORTE_DATA_R & 0b00000010) == 0x0){
        return 0b00000010;
    }else if((GPIO_PORTE_DATA_R & 0b00000001) == 0x0){
        return 0b00000001;
    }else{
        return 0;
    }
}
