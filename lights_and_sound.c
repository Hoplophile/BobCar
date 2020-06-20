/*
 * lights_and_sound.c
 *
 * Created: 08.05.2020 11:10:45
 *  Author: piotr
 */ 

#include "lights_and_sound.h"
#include <avr/interrupt.h>

uint8_t buzzer_timer_compare_value;
//uint8_t timer_overflow_counter;
//
//ISR(TIMER1_OVF_vect)
//{
	//timer_overflow_counter++;	/* Increment Timer Overflow count */
	//if(timer_overflow_counter > 100){
		//LnS_BuzzerSwitch(OFF);
		////TCCR0A &= !(1 << COM0B1);
	//}
//}

/* Init_Timer0
*  Initialize Timer0 for Fast PWM on pin 5 (BUZZER)
*/
void Init_Timer0() {
	
	sei();
	
	//		  tmr 8-bit									 | toggle pin 5
	TCCR0A |= (1 << WGM02) | (1 << WGM01) | (1 << WGM00) | (1 << COM0B1);
	
	//TIMSK0 |= (1 << TOIE0);
		
	OCR0A = 0xF0;
}

/* LnS_Init
 * initialize lights and buzzer pins as outputs and set to 0
 */
void LnS_Init(){
	DDRC |= (1 << PIN_MAIN_LIGHTS);
	DDRC |= (1 << PIN_BACKWARD_LIGHTS);
	DDRC |= (1 << PIN_BREAK_LIGHTS);
	DDRD |= (1 << PIN_BUZZER);
	PORTC &= ~(1 << PIN_MAIN_LIGHTS);
	PORTC &= ~(1 << PIN_BACKWARD_LIGHTS);
	PORTC &= ~(1 << PIN_BREAK_LIGHTS);
	PORTD &= ~(1 << PIN_BUZZER);
	Init_Timer0();
	LnS_BuzzerSwitch(OFF);
}

/* LnS_BuzzerSwitch
 * Switch buzzer ON/OFF
 *	state: ON/OFF defined in .h
 */
void LnS_BuzzerSwitch(int state){
	if(state == OFF)
		TCCR0B &= (0 << CS02);		//timer 0 off
	else
		TCCR0B |= (1 << CS02);		//16Mhz / (1 * 255) = 62kHz}
}

/* LnS_MainLightsSwitch
 * Switch main lights ON/OFF
 *	state: ON/OFF defined in .h
 */
void LnS_MainLightsSwitch(int state){
	if(state == OFF)
		PORTC &= ~(1 << PIN_MAIN_LIGHTS);
	else
		PORTC |= (1 << PIN_MAIN_LIGHTS);
}

/* LnS_BackwardLightsSwitch
 * Switch backward lights ON/OFF
 *	state: ON/OFF defined in .h
 */
void LnS_BackwardLightsSwitch(int state){
	if(state == OFF)
		PORTC &= ~(1 << PIN_BACKWARD_LIGHTS);
	else
		PORTC |= (1 << PIN_BACKWARD_LIGHTS);
}

/* LnS_BreakLightsSwitch
 * Switch break lights ON/OFF
 *	state: ON/OFF defined in .h
 */
void LnS_BreakLightsSwitch(int state){
	if(state == OFF)
		PORTC &= ~(1 << PIN_BREAK_LIGHTS);
	else
		PORTC |= (1 << PIN_BREAK_LIGHTS);
}

/* LnS_SendCommand
 * Pass command to lights and sound module to perform
 * action related to lights or buzzer
 * Params:
 *	command:	command from bluetooth module (of type enum command)
 *				related to lights or buzzer
 */
void LnS_SendCommand(enum commands command){
	switch(command){
		case LIGHTS_ON:
			LnS_MainLightsSwitch(ON);
			break;
		case LIGHTS_OFF:
			LnS_MainLightsSwitch(OFF);
			break;
		case BEEP:
			break;
		default:
			break;
	}
}