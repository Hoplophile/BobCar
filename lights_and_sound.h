/*
 * lights_and_sound.h
 *
 * Created: 08.05.2020 11:11:45
 *  Author: piotr
 */ 

#ifndef LIGHTS_AND_SOUND_H_
#define LIGHTS_AND_SOUND_H_

#include <avr/io.h>
#include "controller.h"

#define PIN_MAIN_LIGHTS		PC0
#define PIN_BACKWARD_LIGHTS	PC1
#define PIN_BREAK_LIGHTS	PC2

void LnS_Init(void);
void LnS_SendCommand(enum commands);

#endif /* LIGHTS_AND_SOUND_H_ */