/*
 * BobCar.c
 *
 * Created: 14.04.2020 22:55:20
 * Author : piotr
 */ 

#define F_CPU 16000000UL

#include "powertrain.h"
#include "sensors.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{	
	UART_init(9600, true, true);

	POWTR_Init();
	LnS_Init();
	SENS_Init();
	
	LnS_BuzzerSwitch(ON);
	_delay_ms(150);
	LnS_BuzzerSwitch(OFF);
	
	while (1)
	{		
		// read sensors
		SENS_CheckForObstacles(200, 50);
		SENS_CheckLight();
		
		// read commands from controller
		if(UART_available()){
			command = CTRL_GetCommand();
			if((int)command <= 7){
				POWTR_SendCommand(command);
				// powertrain command
			} else{
				// lightandsound command
			}
		}
		_delay_ms(20);
	}
	return 0;
}
