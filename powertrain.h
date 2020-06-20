/*
 * powertrain.h
 *
 * Created: 02.05.2020 11:51:17
 *  Author: piotr
 */ 

#ifndef POWERTRAIN_H_
#define POWERTRAIN_H_

#include "lights_and_sound.h"
#include "controller.h"
#include <stdbool.h>
#include <avr/io.h>

#define PIN_FWD		PC5
#define PIN_BWD		PD4
#define PIN_POWER	PB3
#define PIN_TURN_L	PD7
#define PIN_TURN_R	PB0

enum car_states{
	STOPPED,
	DRV_FWD,
	DRV_FWD_L,
	DRV_FWD_R,
	DRV_BWD,
	DRV_BWD_L,
	DRV_BWD_R
	} car_state;

void POWTR_Init(void);
void POWTR_BlockDrivingForward(void);
void POWTR_BlockDrivingBackward(void);
void POWTR_UnblockDrivingForward(void);
void POWTR_UnblockDrivingBackward(void);
void POWTR_SendCommand(enum commands);
 
#endif /* POWERTRAIN_H_ */