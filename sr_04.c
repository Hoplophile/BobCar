#include "sr_04.h"

#define F_CPU 16000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

/* sensor_new
 * Creates and initializes a new structure representing a particular HC-SR04 proximity sensor
 * Params:
 *   measure_iter: number of measurements to execute for an averaged distance
 *   trig_DDRX: trig port direction register
 *   trig_DDXY: trig port direction bit mask
 *   trig_PORTX: trig port register
 *   trig_PORTXY: trig port bit mask
 *   echo_DDRX: echo port direction register
 *   echo_DDXY: echo port direction bit mask
 *   echo_PINX: echo pin register
 *   echo_PINXY: echo pin bit mask
 */
sr_04 *sensor_new(uint8_t measure_iter,
                  volatile uint8_t *trig_DDRX,
                  uint8_t trig_DDXY,
                  volatile uint8_t *trig_PORTX,
                  uint8_t trig_PORTXY,
                  volatile uint8_t *echo_DDRX,
                  uint8_t echo_DDXY,
                  volatile uint8_t *echo_PINX,
                  uint8_t echo_PINXY) {
  sr_04 *new_struct = malloc(sizeof(sr_04));

  // set trig as output
  *trig_DDRX |= (1 << trig_DDXY);
  // set trig to 0
  *trig_PORTX &= (1 << trig_PORTXY);
  // set echo as input
  *echo_DDRX &= ~(1 << echo_DDXY);

  // TIMSK1 = (1 << TOIE1);	// Enable Timer1 overflow interrupts 
  TCCR1A &= !((1 << WGM11) | (1 << WGM10)); /* Set timer1 Normal operation */

  // set measure repeats
  new_struct->_measure_iter     = measure_iter;
  new_struct->_trig_DDRX        = trig_DDRX;
  new_struct->_trig_DDXY        = trig_DDXY;
  new_struct->_trig_PORTX       = trig_PORTX;
  new_struct->_trig_PORTXY      = trig_PORTXY;
  new_struct->_echo_DDRX        = echo_DDRX;
  new_struct->_echo_DDXY        = echo_DDXY;
  new_struct->_echo_PINX        = echo_PINX;
  new_struct->_echo_PINXY       = echo_PINXY;
  new_struct->_last_duration    = 0;
  new_struct->_last_distance_mm = 0;
  return new_struct;
}

void set_trig_high(sr_04 *sensor) { *(sensor->_trig_PORTX) |= (1 << sensor->_trig_PORTXY); }

void set_trig_low(sr_04 *sensor) { *(sensor->_trig_PORTX) &= ~(1 << sensor->_trig_PORTXY); }

bool read_echo(sr_04 *sensor) { return (bool)(*(sensor->_echo_PINX) & (1 << sensor->_echo_PINXY)); }

/* measure_duration
 * triggers the distance measurement using specified sensor and stores the measured echo pulse duration in sensor struct
 * Params:
 *   sensor: pointer to a structure describing the sensor
 */
void measure_duration(sr_04 *sensor) {
  set_trig_low(sensor);
  _delay_us(2);
  /* Give 10us trigger pulse on trig. pin to HC-SR04 */
  set_trig_high(sensor);
  _delay_us(10);
  set_trig_low(sensor);
  while ((*(sensor->_echo_PINX) & (1 << sensor->_echo_PINXY)) == 0) {
  }

  TCNT1 = 0;                             /* Clear timer counter */
  TCCR1B |= ((1 << CS11) | (1 << CS10)); /* Normal Mode, prescaler 64 */

  while (*(sensor->_echo_PINX) & (1 << sensor->_echo_PINXY)) {
  }
  // read counter value
  sensor->_last_duration = TCNT1;

  // stop timer
  TCCR1B &= ~((1 << CS12)|(1 << CS11)|(1 << CS10));
}

/* calculate_distance_mm
 * returns the distance in millimeters
 * Params:
 *   duration: sensor echo pulse duration measured using timer with prescaler 64
 */
int calculate_distance_mm(uint16_t duration) {
  return (unsigned long)((double)duration * 0.686);
}

/* get_dist_cm
 * triggers distance measurement, update duration and distance latest values in specified structure and return the distance in millimeters
 * Params:
 *   sensor: pointer to a structure describing the sensor
 */
int get_dist_mm(sr_04 *sensor) {
  measure_duration(sensor);
  sensor->_last_distance_mm = calculate_distance_mm(sensor->_last_duration);

  return sensor->_last_distance_mm;
}
