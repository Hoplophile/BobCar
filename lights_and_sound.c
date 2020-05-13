/*
 * lights_and_sound.c
 *
 * Created: 08.05.2020 11:10:45
 *  Author: piotr
 */ 

#include "lights_and_sound.h"


/* Init_Timer0
*  Initialize Timer0 for Fast PWM on pin 5 (BUZZER)
*/
void Init_Timer0() {
	//		  tmr 8-bit					  | use pin 5
	TCCR0A |= (1 << WGM01) | (1 << WGM00) | (1 << COM0A1);
	
	//		  prescaler 8
	TCCR0B |= (1 << CS01);						//16Mhz / (8 * 255) = 7.8kHz
}

void LnS_Init(){
	PORTC |= (1 << PIN_MAIN_LIGHTS);
	PORTC |= (1 << PIN_BACKWARD_LIGHTS);
	PORTC |= (1 << PIN_BREAK_LIGHTS); 
}

void LnS_SendCommand(enum commands command){
	switch(command){
		case LIGHTS_ON:
			break;
		case LIGHTS_OFF:
			break;
		case BEEP:
			break;
		default:
			break;
	}
}