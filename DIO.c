/*
 * DIO.c
 *
 * Created: 14/02/2020 11:25:58 ص
 *  Author: Mohammad
 */ 
#include "bit_level.h"
#include "std_types.h"
#include <avr/io.h>
#include "DIO.h"

//define if the port is input or output
void DIO_voidSetPinDirection(uint8 port, uint8 pin, uint8 dir)
{
	switch(port)
	{
		case 0:
			if(dir == 0)
				CLR_BIT(DDRA, pin);
			else
				SET_BIT(DDRA, pin);
			break;
		case 1:
			if(dir == 0)
				CLR_BIT(DDRB, pin);
			else
				SET_BIT(DDRB, pin);
			break;
		case 2:
			if(dir == 0)
				CLR_BIT(DDRC, pin);
			else
				SET_BIT(DDRC, pin);
			break;
		case 3:
			if(dir == 0)
				CLR_BIT(DDRD, pin);
			else
				SET_BIT(DDRD, pin);
			break;
	}
}
//-----------------------------------------------------------------------
//define if the output is high or low
void DIO_voidSetPinValue(uint8 port, uint8 pin, uint8 value)
{
	switch(port)
	{
		case 0:
			if(value == 0)
				CLR_BIT(PORTA, pin);
			else
				SET_BIT(PORTA, pin);
			break;
		case 1:
			if(value == 0)
				CLR_BIT(PORTB, pin);
			else
				SET_BIT(PORTB, pin);
			break;
		case 2:
			if(value == 0)
				CLR_BIT(PORTC, pin);
			else
				SET_BIT(PORTC, pin);
			break;
		case 3:
			if(value == 0)
				CLR_BIT(PORTD, pin);
			else
				SET_BIT(PORTD, pin);
			break;
	}
}
//----------------------------------------------------------------------
//to get the value in the pin
uint8 DIO_uint8GetPinValue(uint8 port, uint8 pin)
{
	switch(port)
	{
		case 0:
			return GET_BIT(PINA, pin);
			break;
			
		case 1:
			return GET_BIT(PINB, pin);
			break;
			
		case 2:
			return GET_BIT(PINC, pin);
			break;
			
		case 3:
			return GET_BIT(PIND, pin);
			break;
	}
	return 0;
}
//--------------------------------------------------------
// to toggle the port
void DIO_voidTogglePin(uint8 port, uint8 pin)
{
	switch(port)
	{
		case 0:
			TOGGLE_BIT(PORTA, pin);
			break;
		case 1:
			TOGGLE_BIT(PORTB, pin);
			break;
			
		case 2:
			TOGGLE_BIT(PORTC, pin);
			break;
			
		case 3:
			TOGGLE_BIT(PORTD, pin);
			break;	
	}
}