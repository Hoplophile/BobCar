/*
 * UART.c
 *
 * Created: 04.02.2020 22:54:25
 *  Author: piotr
 */ 

#include <avr/io.h>
#include <stdbool.h>

#define F_CPU 16000000UL

void UART_init(unsigned int baud, bool RX, bool TX)
{
	unsigned int baudrate;
	baudrate = (((F_CPU / (baud * 16UL))) - 1);
	UBRR0H = (unsigned char)(baudrate >> 8);
	UBRR0L = (unsigned char)baudrate;
	
	// parity bits
	//UCSR0C |= 1 << UPM01; // 1 parity bit
	
	// data bits
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	
	// 1 stopbit is default

	if(RX) {
		UCSR0B |= 1<<RXEN0;
	}
	
	if(TX) {
		UCSR0B |= 1<<TXEN0;
	}
}

void UART_send( unsigned char data){

	while(!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

void UART_putstring(char* StringPtr){

	while(*StringPtr != 0x00)
	{
		UART_send(*StringPtr);
		StringPtr++;
	}
}

bool UART_available()
{
	return (UCSR0A & (1<<RXC0));
}

unsigned char UART_read()
{
	return UDR0;
}