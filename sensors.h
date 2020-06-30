/*
 * sensors.h
 *
 * Created: 20.06.2020 11:49:20
 *  Author: piotr
 */ 


#ifndef SENSORS_H_
#define SENSORS_H_

#include "sr_04.h"
#include "powertrain.h"
#include "lights_and_sound.h"
#include <avr/io.h>

#define TWILIGHT_SENSOR PD2

void SENS_Init(void);
void SENS_CheckLight(void);
void SENS_CheckForObstacles(int warn, int critical);

#endif /* SENSORS_H_ */