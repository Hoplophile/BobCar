/*
 * UART.h
 *
 * Created: 04.02.2020 22:54:39
 *  Author: piotr
 */ 

#ifndef UART_H_
#define UART_H_

#include <stdbool.h>

void UART_init(unsigned int, bool, bool);
void UART_send(unsigned char);
void UART_putstring(char*);
bool UART_available(void);
unsigned char UART_read(void);

#endif /* UART_H_ */