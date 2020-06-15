#ifndef SR_04_H
#define SR_04_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    int  _last_distance_cm;	// min=0, max=17.34
    uint16_t _last_duration;	// 1 = 4us
    uint8_t _measure_iter;

    uint8_t *_trig_DDRX;
    uint8_t _trig_DDXY;
    uint8_t *_trig_PORTX;
    uint8_t _trig_PORTXY;

    uint8_t *_echo_DDRX;
    uint8_t _echo_DDXY;
    uint8_t *_echo_PINX;
    uint8_t _echo_PINXY;
} sr_04;

sr_04 *sensor_new (uint8_t measure_iter,
                   uint8_t *trig_DDRX,
                   uint8_t trig_DDXY,
                   uint8_t *trig_PORTX,
                   uint8_t trig_PORTXY,
                   uint8_t *echo_DDRX,
                   uint8_t echo_DDXY,
                   uint8_t *echo_PINX,
                   uint8_t echo_PINXY);

void measure_duration(sr_04 *sensor);
int calculate_distance_cm(uint8_t duration);
int get_dist_cm(sr_04 *sensor);

#endif
