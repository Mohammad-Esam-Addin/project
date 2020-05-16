/*
 * keypad.c
 *
 * Created: 21/02/2020 01:26:58 م
 *  Author: Mohammad
 */ 
#include "std_types.h"
#include "bit_level.h"
#include "DIO.h"
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

void KEYPAD_voidInit(void)
{
	//rows
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN_0, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN_1, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN_2, DIO_OUTPUT);
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN_3, DIO_OUTPUT);
	
	//columns
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN_4, DIO_INPUT);
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN_5, DIO_INPUT);
	DIO_voidSetPinDirection(DIO_PORTC, DIO_PIN_6, DIO_INPUT);
	
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN_4, PULL_UP);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN_5, PULL_UP);
	DIO_voidSetPinValue(DIO_PORTC,DIO_PIN_6, PULL_UP);
}

uint8 KEYPAD_uint8GetKey(void)
{
	uint8 buffer;
	
	//first row
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_0, DIO_LOW);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_1, DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_2, DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_3, DIO_HIGH);
	
	buffer = 0;
	for(int i = 0; i < 3; i ++)
	{
		
		buffer |= (DIO_uint8GetPinValue(DIO_PORTC, DIO_PIN_4 + i) << i);
	}
	
	switch(buffer)
	{
		case 14:
		_delay_ms(500);
		return 1;
		break;
		
		case 13:
		_delay_ms(500);
		return 2;
 		break;
		
		case 11:
		_delay_ms(500);
		return 3;
		break;
	}
	
	
	
	//second row
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_0, DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_1, DIO_LOW);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_2, DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_3, DIO_HIGH);
	
	buffer = 0;
	for(uint8 i = 0; i < 3; i ++)
	{
		buffer |= (DIO_uint8GetPinValue(DIO_PORTC, DIO_PIN_4 + i) << i);
	}
	
	switch(buffer)
	{
		case 14:
			_delay_ms(500);
			return 4;
			break;
		
		case 13:
			_delay_ms(500);
			return 5;
			break;
		
		case 11:
			_delay_ms(500);
			return 6;
			break;
	}
	
	//third row
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_0, DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_1, DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_2, DIO_LOW);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_3, DIO_HIGH);
	
	buffer = 0;
	for(uint8 i = 0; i < 3; i ++)
	{
		buffer |= (DIO_uint8GetPinValue(DIO_PORTC, DIO_PIN_4 + i) << i);
	}
	
	switch(buffer)
	{
		case 14:
		_delay_ms(500);
		return 7;
		break;
		
		case 13:
		_delay_ms(500);
		return 8;
		break;
		
		case 11:
		_delay_ms(500);
		return 9;
		break;
	}
	
	//fourth row
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_0, DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_1, DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_2, DIO_HIGH);
	DIO_voidSetPinValue(DIO_PORTC, DIO_PIN_3, DIO_LOW);
	
	buffer = 0;
	for(uint8 i = 0; i < 3; i ++)
	{
		buffer |= (DIO_uint8GetPinValue(DIO_PORTC, DIO_PIN_4 + i) << i);
	}
	
	switch(buffer)
	{
		case 14:
			_delay_ms(500);
			return '#';
			break;
		
		case 13:
			_delay_ms(500);
			return 0;
			break;
		
		case 11:
			_delay_ms(500);
			return '*';
			break;
	}
	return 0XFF;
}