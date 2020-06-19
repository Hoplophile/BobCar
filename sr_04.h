#ifndef SR_04_H
#define SR_04_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  unsigned long _last_distance_mm;    // min=0, max=~400
  uint16_t _last_duration;  // 1 = 4us
  uint8_t _measure_iter;

  volatile uint8_t *_trig_DDRX;
  uint8_t _trig_DDXY;
  volatile uint8_t *_trig_PORTX;
  uint8_t _trig_PORTXY;

  volatile uint8_t *_echo_DDRX;
  uint8_t _echo_DDXY;
  volatile uint8_t *_echo_PINX;
  uint8_t _echo_PINXY;
} sr_04;

sr_04 *sensor_new(uint8_t measure_iter,
                  volatile uint8_t *trig_DDRX,
                  uint8_t trig_DDXY,
                  volatile uint8_t *trig_PORTX,
                  uint8_t trig_PORTXY,
                  volatile uint8_t *echo_DDRX,
                  uint8_t echo_DDXY,
                  volatile uint8_t *echo_PINX,
                  uint8_t echo_PINXY);

void measure_duration(sr_04 *sensor);
int calculate_distance_mm(uint16_t duration);
int get_dist_cm(sr_04 *sensor);

#endif
