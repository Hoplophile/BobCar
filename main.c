/*
 * BobCar.c
 *
 * Created: 14.04.2020 22:55:20
 * Author : piotr
 */ 

#include "powertrain.h"
#include <avr/io.h>

int main(void)
{	
	UART_init(9600, true, true);
	enum commands command;
	
	POWTR_Init();
	LnS_Init();
	
	LnS_BuzzerSwitch(ON);
	
	while (1)
	{
		// read sensors
		
		
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
	}
	return 0;
}
