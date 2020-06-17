/*
 * controller.c
 *
 * Created: 02.05.2020 11:19:27
 *  Author: piotr
 */ 

#include "controller.h"

void CTRL_SendDistance(unsigned long distance){
	char message[15];
	sprintf(message, "D = %lu  \n", distance);
	UART_putstring(&message[0]);
}

void CTRL_SendTemp(unsigned int temperature){
	char message[15];
	sprintf(message, "T = %u  \n", temperature);
	UART_putstring(&message[0]);
}

enum commands CTRL_GetCommand(){
	char received_char;
	received_char = UART_read();
	
	switch(received_char){
		case 'F':
			return FORWARD;
			break;
		case 'Q':
			return FORWARD_LEFT;
			break;
		case 'E':
			return FORWARD_RIGHT;
			break;
		case 'G':
			return BACKWARDS;
			break;
		case 'Z':
			return BACKWARDS_LEFT;
			break;
		case 'C':
			return BACKWARDS_RIGHT;
			break;
		case 'S':
			return NEUTRAL;
			break;
		case 'J':
			return POWER;
			break;
		case 'M':
			return LIGHTS_ON;
			break;
		case 'm':
			return LIGHTS_OFF;
			break;
		case 'X':
			return BEEP;
			break;
		default:
			return UNKNOWN;
			break;
	}
}
