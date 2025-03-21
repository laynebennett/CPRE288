/*
 * movement.h
 *
 *  Created on: Feb 7, 2025
 *      Author: layneben
 */

#ifndef MOVEMENT_H_
#define MOVEMENT_H_
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inc/tm4c123gh6pm.h>
#include "Timer.h"
#include "open_interface.h"
#include "Timer.h"
#include "lcd.h"

double move_forward(oi_t *sensor_data, double distance_mm);

double move_forward_bump(oi_t *sensor_data, double distance_mm);

double move_backward(oi_t *sensor_data, double distance_mm);

void turn_left(oi_t *sensor_data, double degrees);

void turn_right(oi_t *sensor_data, double degrees);

#endif /* MOVEMENT_H_ */


