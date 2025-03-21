/*
 * movement.c
 *
 *  Created on: Feb 7, 2025
 *      Author: layneben
 */

#include "movement.h"
#include "open_interface.h"
#include "Timer.h"
#include "lcd.h"


void turn_right(oi_t *sensor_data, double degrees){



    double degreeSum = 0;


    oi_setWheels(-250, 250);

    while(degreeSum >-degrees*.8){



        oi_update(sensor_data); //take sensor data
        degreeSum += sensor_data -> angle; //add sensor data to degree sum

        lcd_clear();
        lcd_printf("Degrees: %lf", degreeSum);


    }

    oi_setWheels(0,0); //stop
}

void turn_left(oi_t *sensor_data, double degrees){



    double degreeSum = 0;


    oi_setWheels(250, -250);

    while(degreeSum <degrees*.8){

        oi_update(sensor_data); //take sensor data
        degreeSum += sensor_data -> angle; //add sensor data to degree sum

        lcd_clear();
        lcd_printf("Degrees: %lf", degreeSum);

    }

    oi_setWheels(0,0); //stop
}

double move_forward(oi_t *sensor_data, double distance_mm){



    oi_setWheels(250, 250); //full speed

    double sum = 0; //reset distance sum

    while(sum < distance_mm){
        oi_update(sensor_data); //take sensor data
        sum += sensor_data -> distance; //add sensor datat to distance sum

        //updating lcd display with distance
        lcd_clear();
        lcd_printf("Distance: %lf", sum);


    }

    oi_setWheels(0,0); //stop

    return 0;
}

double move_forward_bump(oi_t *sensor_data, double distance_mm){//test for 2m



    oi_setWheels(250, 250); //full speed

    double sum = 0; //reset distance sum

    while(sum < distance_mm){



        oi_update(sensor_data); //take sensor data
        sum += sensor_data -> distance; //add sensor datat to distance sum

        lcd_clear();
        lcd_printf("Distance: %lf\n", sum);
        

        if(sensor_data -> bumpLeft){//if left bumper hit
            lcd_printf("Bump Left");//print bump strength

            move_backward(sensor_data, 150);
            sum -= 150;

            turn_right(sensor_data, 90); //move arounf=d
            move_forward(sensor_data, 250);
            turn_left(sensor_data, 90);
        }else if(sensor_data -> bumpRight){//if right bumper hit
            lcd_printf("Bump Right");//print bump strength

            move_backward(sensor_data, 150);
            sum -= 150;

            turn_left(sensor_data, 90); //move around
            move_forward(sensor_data, 250);
            turn_right(sensor_data, 90);
        }
        
        

        oi_setWheels(250, 250); //full speed


    }

    oi_setWheels(0,0); //stop

    return 0;
}

double move_backward(oi_t *sensor_data, double distance_mm){


    oi_setWheels(-250, -250); //full speed

    double sum = 0; //reset distance sum

    while(sum < distance_mm){
        oi_update(sensor_data); //take sensor data
        sum -= sensor_data -> distance; //add sensor datat to distance sum

        //updating lcd display with distance
        lcd_clear();
        lcd_printf("Distance: %lf", sum);


    }

    oi_setWheels(0,0); //stop

    return 0;
}

