/*
 * powertrain.c
 *
 * Created: 02.05.2020 11:51:29
 *  Author: piotr
 */ 

#include "powertrain.h"

bool block_forward = false;
bool block_backward = false;

/* Timer2_Init
 * Initialize Timer2 for Fast PWM on pin 11
 */
void Timer2_Init() {
	//		  tmr 8-bit					  | use pin 11   
	TCCR2A |= (1 << WGM21) | (1 << WGM20) | (1 << COM2A1);
	
	//		  prescaler 8
	TCCR2B |= (1 << CS22);			//16Mhz / (8 * 255) = 7.8kHz
}

/* Timer2_SetCounter
 * Set compare value (PWM duty) for timer2
 * Params:
 *	compare_value: value to write to compare register (0-255)
 */
void Timer2_SetCounter(int compare_value){
	OCR2A = compare_value;
}

/* POWTR_init
 * Initialize motoros PWM, pins as outputs and set them to LOW
 */
void POWTR_Init(){
	// driving motor pins
	DDRD |= (1 << PIN_BWD);
	DDRC |= (1 << PIN_FWD);
	DDRB |= (1 << PIN_POWER);
	PORTD &= ~(1 << PIN_BWD);
	PORTC &= ~(1 << PIN_FWD);
	PORTB &= ~(1 << PIN_POWER);
	
	// turning motor pins
	DDRD |= (1 << PIN_TURN_L);
	DDRB |= (1 << PIN_TURN_R);
	PORTD &= ~(1 << PIN_TURN_L);
	PORTB &= ~(1 << PIN_TURN_R);
	
	Timer2_Init();
	
	power = 50;
	car_state = STOPPED;
}

/* POWTR_TurnLeft
 * Set motor driver inputs to rotate turning
 * motor left
 */
void POWTR_TurnLeft(){
	PORTD |= (1 << PIN_TURN_L);
	PORTB &= ~(1 << PIN_TURN_R);
}

/* POWTR_TurnRight
 * Set motor driver inputs to rotate turning
 * motor left
 */
void POWTR_TurnRight(){
	PORTD &= ~(1 << PIN_TURN_L);
	PORTB |= (1 << PIN_TURN_R);
}

/* POWTR_NoTurn
 * Set motor driver inputs to 0 to not turn the wheels
 */
void POWTR_NoTurn(){
	PORTD &= ~(1 << PIN_TURN_L);
	PORTB &= ~(1 << PIN_TURN_R);
}

/* POWTR_DriveForward
 * Set motor driver inputs to rotate 
 * driving motor forward
 */
void POWTR_DriveForward(){
	PORTC |= (1 << PIN_FWD);
	PORTD &= ~(1 << PIN_BWD);
	Timer2_SetCounter((2 * power) * 55);
}

/* POWTR_DriveBackward
 * Set motor driver inputs to rotate 
 * driving motor backward
 */
void POWTR_DriveBackward(){
	PORTC &= ~(1 << PIN_FWD);
	PORTD |= (1 << PIN_BWD);
	Timer2_SetCounter((2 * power) * 55);
}

/* POWTR_Stop
 * Set motor driver inputs and timer counter to 0
 */
void POWTR_Stop(){
	Timer2_SetCounter(0);
	PORTC &= ~(1 << PIN_FWD);
	PORTD &= ~(1 << PIN_BWD);
}

void POWTR_BlockDrivingForward(){
	block_forward = true;
	POWTR_Stop();
}

void POWTR_BlockDrivingBackward(){
	block_backward = true;
	POWTR_Stop();
}

void POWTR_UnblockDrivingForward(){
	block_forward = false;
}

void POWTR_UnblockDrivingBackward(){
	block_backward = false;
}

/* POWTR_SendCommand
 * Pass command to powertrain module to perform
 * action related to driving
 * Params:
 *	command:	command from bluetooth module (of type enum command)
 *				related to powertrain
 */
void POWTR_SendCommand(enum commands command){
	switch(command){
		case FORWARD:
			if(block_forward) break;
			car_state = DRV_FWD;
			POWTR_NoTurn();
			POWTR_DriveForward();
			break;
		case FORWARD_LEFT:
			if(block_forward) break;
			car_state = DRV_FWD_L;
			POWTR_TurnLeft();
			POWTR_DriveForward();
			break;
		case FORWARD_RIGHT:
			if(block_forward) break;
			car_state = DRV_FWD_R;
			POWTR_TurnRight();
			POWTR_DriveForward();
			break;
		case BACKWARDS:
			if(block_backward) break;
			car_state = DRV_BWD;
			POWTR_NoTurn();
			POWTR_DriveBackward();
			break;
		case BACKWARDS_LEFT:
			if(block_backward) break;
			car_state = DRV_BWD_L;
			POWTR_TurnLeft();
			POWTR_DriveBackward();
			break;
		case BACKWARDS_RIGHT:
			if(block_backward) break;
			car_state = DRV_BWD_R;
			POWTR_TurnRight();
			POWTR_DriveBackward();
			break;
		case NEUTRAL:
			car_state = STOPPED;
			POWTR_NoTurn();
			POWTR_Stop();
			break;	
		default:
			break;
	}
}