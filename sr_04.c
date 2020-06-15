#include "sr_04.h"

#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

sr_04 *sensor_new (uint8_t measure_iter,
                   uint8_t *trig_DDRX,
                   uint8_t trig_DDXY,
                   uint8_t *trig_PORTX,
                   uint8_t trig_PORTXY,
                   uint8_t *echo_DDRX,
                   uint8_t echo_DDXY,
                   uint8_t *echo_PINX,
                   uint8_t echo_PINXY) {
					   
    sr_04 *new_struct = malloc(sizeof(sr_04));
	
    // set trig as output
    DDRB |= (1 << PB1);
	
	// set trig to 0
    PORTB &= ~(1 << PB1);

    // set echo as input
    DDRB &= ~(1 << PB2);
	
	//TIMSK1 = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A &= !((1 << WGM11) | (1 << WGM10));		/* Set timer1 Normal operation */

    // set measure repeats
    new_struct->_measure_iter 	= measure_iter;
    new_struct->_trig_DDRX 	= DDRB;
    new_struct->_trig_DDXY 	= trig_DDXY;
    new_struct->_trig_PORTX 	= PORTB;
    new_struct->_trig_PORTXY 	= trig_PORTXY;
    new_struct->_echo_DDRX 	= DDRB;
    new_struct->_echo_DDXY 	= echo_DDXY;
    new_struct->_echo_PINX 	= DDB5;
    new_struct->_echo_PINXY 	= echo_PINXY;
    new_struct->_last_duration = 0;
    new_struct->_last_distance_cm = 0;
    return new_struct;
}	

void set_trig_high(sr_04 *sensor) {
    PORTB |= (1 << PB1);
}

void set_trig_low(sr_04 *sensor) {
    PORTB &= ~(1 << PB1);
}

bool read_echo(sr_04 *sensor) {
    return (bool)(PINB & (1 << PB2));
}

void measure_duration(sr_04 *sensor) {
	
	PORTB &= ~(1 << PB1);
	_delay_us(2);
    /* Give 10us trigger pulse on trig. pin to HC-SR04 */
    PORTB |= (1 << PB1);
    _delay_us(10);
    PORTB &= ~(1 << PB1);
    
	while(!(PINB & (1 << PB2))) {}
		
    TCNT1 = 0;				/* Clear timer counter */
    TCCR1B |= (1 << CS11);	/* Normal Mode, prescaler 8 */
    TIFR1 |= (1 << TOV1);	/* Clear Timer Overflow flag */
	
	while((PINB & (1 << PB2))) {} //&& (TIFR1 & (1 << TOV1))) {}
		
	// stop timer
	TCCR1B &= !(1 << CS11);
	
	// read counter value
    //int count = TCNT1;
	
	//if(!(TIFR1 & (1 << TOV1)))
		//sensor->_last_duration = 0xff;
	//else
		sensor->_last_duration = TCNT1;
	
}

int calculate_distance_cm(uint8_t duration) {
    return (int)(duration / 200);	// jakieœ robocze wartoœci
}

int get_dist_cm(sr_04 *sensor) {
    measure_duration(sensor);
    sensor->_last_distance_cm = calculate_distance_cm(sensor->_last_duration);

    return sensor->_last_distance_cm;
}
