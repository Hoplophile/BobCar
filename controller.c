/*
 * controller.c
 *
 * Created: 02.05.2020 11:19:27
 *  Author: piotr
 */ 

#include "controller.h"

extern int power;

void CTRL_SendDistance(unsigned long distance_left, unsigned long distance_right){
	char message[20];
	sprintf(message, "DL:%lu cm R:%lu\n", distance_left, distance_right);
	UART_putstring(&message[0]);
}

void CTRL_SendTemp(unsigned int temperature){
	char message[15];
	sprintf(message, "T%u\n", temperature);
	UART_putstring(&message[0]);
}

void CTRL_GetPower(void){
	if(UART_available()){
		power = 10*(int)(UART_read()-'0');
	}
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
		case 'M':
			return LIGHTS_ON;
			break;
		case 'm':
			return LIGHTS_OFF;
			break;
		case 'X':
			return BEEP;
			break;
		case 'J':
			CTRL_GetPower();
			return POWER;
			break;
		default:
			return UNKNOWN;
			break;
	}
}
