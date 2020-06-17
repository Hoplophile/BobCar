/*
 * BobCar.c
 *
 * Created: 14.04.2020 22:55:20
 * Author : piotr
 */ 

#include "powertrain.h"
#include "sr_04.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{	
	UART_init(9600, true, true);
	set_led(true);
	enum commands command;
	sr_04 *mysensor = sensor_new(4, &DDRB, DDB1, &PORTB, PORTB1, &DDRB, DDB2, &PINB, PINB2);
	POWTR_Init();
	//LnS_Init();
	
	
	while (1)
	{
		
		// read sensors
		
		//if(mysensor->_last_distance_mm < 9.0) {
			//LnS_BuzzerSwitch(ON);
			//} else {
			//LnS_BuzzerSwitch(OFF);
		//}
		get_dist_cm(mysensor);

		//_delay_ms(500);
		CTRL_SendDistance(mysensor->_last_distance_mm);
		//_delay_ms(500);
		// CTRL_SendTemp(mysensor->_last_duration);
		
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
		_delay_ms(800);
		
	}
	return 0;
}
