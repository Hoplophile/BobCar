/*
 * BobCar.c
 *
 * Created: 14.04.2020 22:55:20
 * Author : piotr
 */ 

#include "controller.h"
#include "powertrain.h"
#include <avr/io.h>

int main(void)
{
	DDRC = 0xFF;
	PORTC = (0 << PC0);
	
	UART_init(9600, true, true);
	enum commands command;
	
	POWTR_Init();
	
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
