/*
 * BobCar.c
 *
 * Created: 14.04.2020 22:55:20
 * Author : piotr
 */ 

#define F_CPU 16000000UL

#include "powertrain.h"
#include "sr_04.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{	
	UART_init(9600, true, true);
	enum commands command;
	
	sr_04 *mysensor = sensor_new(4, &DDRB, DDB1, &PORTB, PORTB1, &DDRB, DDB2, &PINB, PINB2);
	
	POWTR_Init();
	LnS_Init();
	
	//LnS_BuzzerSwitch(ON);
	_delay_ms(250);
	
	while (1)
	{		
		// read sensors
		
		get_dist_cm(mysensor);
		//CTRL_SendDistance(mysensor->_last_distance_mm);
		
		//if(mysensor->_last_distance_mm < 15) {
			//LnS_BuzzerSwitch(ON);
		//} else {
			//LnS_BuzzerSwitch(OFF);
		//}
		
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
		_delay_ms(250);
	}
	return 0;
}
