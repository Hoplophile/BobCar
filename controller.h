/*
 * controller.h
 *
 * Created: 02.05.2020 11:19:49
 *  Author: piotr
 */ 

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "uart.h"
#include <stdio.h>

enum commands{
	FORWARD,
	FORWARD_LEFT,
	FORWARD_RIGHT,
	BACKWARDS,
	BACKWARDS_LEFT,
	BACKWARDS_RIGHT,
	NEUTRAL,
	POWER,
	LIGHTS_ON,
	LIGHTS_OFF,
	BEEP,
	UNKNOWN
	} command;

void CTRL_SendDistance(unsigned long, unsigned long); 
void CTRL_SendTemp(unsigned int);
enum commands CTRL_GetCommand(void);

#endif /* CONTROLLER_H_ */
