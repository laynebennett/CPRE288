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
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include <string.h>

#define TOTAL_DEG_TURN 180
#define DEGREE_INCREMENT 2

int lcd_rotatingBanner(int i);

void sendString(char c, char puttyString[]);

void printString(char c);

void printWholeString(char puttyString[]);

int main (void) {

    oi_t *sensor_data = oi_alloc();

    oi_init(sensor_data);


    timer_init(); // Initialize Timer, needed before any LCD screen functions can be called
                  // and enables time functions (e.g. timer_waitMillis)

    lcd_init();   // Initialize the LCD screen.  This also clears the screen.

    
    right_calibration_value = 343000;
    left_calibration_value = 1324750;


    cyBOT_init_Scan(0b0111);


    //cyBOT_SERVO_cal();

    cyBot_uart_init();

    char puttyString[50];


    /*for(;;){
        c = cyBot_getByte();
        sendString(c, puttyString);
        printString(c);

    }*/

    cyBOT_Scan_t scan;


    for(;;){
       if(cyBot_getByte()=='m'){//if m pressed
            float scanDist[4] = {50}; //array used to average the scan distances
            float distSum; //sum used to average
            float distAvg; //final avg
            bool objDetect=false; //false if no object in front, true if
            int objCount = 0; //number of objects found
            int objWidth[10] = {0};
            int objAngle[10] = {0};
            float avgObjDist = 0;
            float objDist;

            sprintf(puttyString, "\n");
            printWholeString(puttyString);

            int i;
            for(i=0; i<=TOTAL_DEG_TURN; i+= DEGREE_INCREMENT ){//scan 180 deg
                    cyBOT_Scan(i, &scan);
                    scanDist[3] = scan.sound_dist;//distance after scan
                    int j;
                    distSum = 0;
                    for(j=1; j<4;j++){//loop averages out the distances by groups of 3 (scanDist[0] is ignored)
                        distSum+=scanDist[j];
                        scanDist[j-1]=scanDist[j];
                    }
                    distAvg=distSum/3;//get avg

                    //sprintf(puttyString, "scanDist = %f distAvg = %f\n", scanDist[3], distAvg);
                    //printWholeString(puttyString);

                    if(distAvg<50){//if object detected


                        if(objDetect== false){//if new object, update count

                            objCount++;
                            objWidth[objCount]=0;
                            objAngle[objCount]=i;
                            }
                        objDetect = true;
                        //sprintf(puttyString, "found an object\n");
                        sprintf(puttyString, "|");

                        objWidth[objCount] += DEGREE_INCREMENT;

                    }else{//if no object detected
                        if((objWidth[objCount]<=8)&&(objDetect==true)){
                            objCount--;
                        }
                        objDetect = false;
                        sprintf(puttyString, " ");
                    }
                    printWholeString(puttyString);
                }
            sprintf(puttyString, "\nobjCount: %i\n", objCount);
            printWholeString(puttyString);
            int q;
            int minWidth = objWidth[1];
            int minAngle = objAngle[1];

            sprintf(puttyString, "\n");
            printWholeString(puttyString);

            for(q=1;q<=objCount;q++){ //scan each object and calculate the distance, taking an average from 5 readings
                avgObjDist = 0;
                for(i = 0; i < 5; i++) {
                    cyBOT_Scan(objAngle[q]+(objWidth[q]/2), &scan);
                    //timer_waitMillis(200);
                    objDist = scan.sound_dist;
                    avgObjDist += objDist;
                }
                avgObjDist /= 5;


                sprintf(puttyString, "Object %i: Angle = %i, Distance = %f, Width = %i\n", q, objAngle[q]+(objWidth[q]/2), avgObjDist, objWidth[q]); //prints all object information to putty
                printWholeString(puttyString);

                if(objWidth[q]<minWidth){ //find smallest width object
                    minWidth = objWidth[q];
                    minAngle = objAngle[q]+(((double)objWidth[q])/2.0);
                }

            }
            cyBOT_Scan(minAngle-(minAngle-90)*.2, &scan); //point to smallest width object
		objDist = scan.sound_dist*.9;
/*
		double z = 10; //CHANGE

		double x;
		double a;
		double minAngleRad = minAngle*(3.14159/180);
		


	if(minAngle>90){
		x=sqrt((objDist*objDist)+(z*z)-2*objDist*z*cos(4.71239-minAngleRad));
		a=asin(sin(4.71239-minAngleRad)*(objDist)/x);
                turn_left(sensor_data, a*(57.29577));
            }else{
		x=sqrt((objDist*objDist)+(z*z)-2*objDist*z*cos(1.5708+minAngleRad));
		a=asin(sin(1.5708+minAngleRad)*(objDist)/x);
                turn_right(sensor_data, a*(57.29577));
            }

        move_forward(sensor_data, objDist*10);

*/
            break;
        }

    }







    return 0;
}


void sendString(char c, char puttyString[]){

    sprintf(puttyString, "%s%c", puttyString, c);
    lcd_printf("Got %s\n", puttyString);

}

void printWholeString(char puttyString[]){
    int i;
    for(i=0;i<strlen(puttyString);i++){
        printString(puttyString[i]);
    }

}

void printString(char c){
    cyBot_sendByte(c);
}

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


return i;
}

