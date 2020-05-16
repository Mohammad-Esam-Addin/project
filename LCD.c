/*
 * LCD.c
 *
 * Created: 15/02/2020 01:49:33 م
 *  Author: Mohammad
 */
#include "std_types.h"
#include "bit_level.h" 
#include "DIO.h"


#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <math.h>

//for sending commands in LCD

void LCD_voidSendCommand(uint8 command)
{
	uint8 upper = command >> 4;
	uint8 lower = command & 0x0f;
	
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_1, DIO_LOW);		//low for RS
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);		//low for E
	
	
	//reading upper
	for(uint8 i = 0; i < 4; i ++)
	{
		if(((upper >> i) & (0x01)) == 1)
			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN_4 + i, DIO_HIGH);
		else
			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN_4 + i, DIO_LOW);
	}
	
	//printing upper	
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_3, DIO_HIGH);	//high for E
	_delay_ms(2);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);		//low for E
	
	
	//reading lower
	for(uint8 i = 0; i < 4; i ++)
	{
		if(((lower >> i) & (0x01)) == 1)
			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN_4 + i, DIO_HIGH);
		else
			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN_4 + i, DIO_LOW);
	}
	
	//printing lower	
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_3, DIO_HIGH);	//high for E
	_delay_ms(2);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);		//low for E
}
//-----------------------------------------------------------------------

//sending data to print
void LCD_voidSendData(uint8 data)
{
	uint8 upper = data >> 4;
	uint8 lower = data & 0x0f;
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_1, DIO_HIGH);	//RS is high for writing data
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);		//E is low
	
	//for reading upper
	for(uint8 i = 0; i < 4; i ++)
	{
		if(((upper >> i) & (0x01)) == 1)
			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN_4 + i, DIO_HIGH);
		else
			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN_4 + i, DIO_LOW);
	}

	//for scanning upper	
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_3, DIO_HIGH);	//high for E
	_delay_ms(2);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);		//low for E
	
	
	//for reading lower
	for(uint8 i = 0; i < 4; i ++)
	{
		if(((lower >> i) & (0x01)) == 1)
			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN_4 + i, DIO_HIGH);
		else
			DIO_voidSetPinValue(DIO_PORTA, DIO_PIN_4 + i, DIO_LOW);
	}
	
	
	//for scanning lower	
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_3, DIO_HIGH);	//high for E
	_delay_ms(2);
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);		//low for E
}
//-----------------------------------------------------------------------

//initializations for the pins of LCD in MC
void LCD_voidInit()
{
	_delay_ms(50);
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN_4, DIO_OUTPUT);	//D4
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN_5, DIO_OUTPUT);	//D5
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN_6, DIO_OUTPUT);	//D6
	DIO_voidSetPinDirection(DIO_PORTA, DIO_PIN_7, DIO_OUTPUT);	//D7
	
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN_1, DIO_OUTPUT);	//RS
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN_2, DIO_OUTPUT);	//RW
	DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN_3, DIO_OUTPUT);	//E
	
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_1, DIO_LOW);			//RS	low
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_2, DIO_LOW);			//RW	low
	DIO_voidSetPinValue(DIO_PORTB, DIO_PIN_3, DIO_LOW);			//E		low
	
	LCD_voidSendCommand(0x02);		//return home
	_delay_ms(2);
	LCD_voidSendCommand(0x28);		//set function sets: 4-bit line, 2-line display, 5x8 for a character
	_delay_ms(2);
	LCD_voidSendCommand(0x0c);		//display function: display on, cursor off, blinking cursor off
	_delay_ms(2);
	LCD_voidSendCommand(0x01);		//clear display
	_delay_ms(2);
}
//-----------------------------------------------------------------------------------------------------------
//clear display
void LCD_voidClear()
{
	LCD_voidSendCommand(0x01);
}
//-----------------------------------------------------------------------------------------------------------
//set cursor
void LCD_voidCursorDisplay(uint8 state)
{
	switch(state)
	{
		case 0:
			LCD_voidSendCommand(0x0c);	//cursor off
			break;
			
		case 1:
			LCD_voidSendCommand(0x0e);	//set the cursor without blinking
			break;
			
		case 2:
			LCD_voidSendCommand(0x0f);		//set the cursor with blinking
	}
}
//-------------------------------------------------------------------------------------------------------------------
//shift cursor
void LCD_voidShiftCursor(uint8 shift, uint8 number)
{
	switch(shift)
	{
		case 0:
			for(uint8 i = 0; i < number; i ++)
			{
				LCD_voidSendCommand(0x10); //shift cursor to left
			}
			break;
			
		case 1:
			for(uint8 i = 0; i < number; i ++)
			{
				LCD_voidSendCommand(0x14);	//shift cursor to right
			}
			break;
	}
}
//------------------------------------------------------------------------------------------------------------------
//shift display
void LCD_voidShiftDisplay(uint8 shift)
{
	switch(shift)
	{
		case 0:
			LCD_voidSendCommand(0x18); //shift display to left
			break;
			
		case 1:
			LCD_voidSendCommand(0x1c);	//shift display to right
	}
}
//-------------------------------------------------------------------------------------------------------------------
//start printing in the first line
void LCD_voidPrintInTheFirst()
{
	LCD_voidSendCommand(0x80);
}

//-------------------------------------------------------------------------------------------------------------------
//start printing in the second line
void LCD_voidPrintInTheSecond()
{
	LCD_voidSendCommand(0x0c);
}
//-------------------------------------------------------------------------------------------------------------------
//print string
void LCD_voidPrintString(uint8 ch[])
{
	uint8* letter = ch;
	while((*letter) != '\0')
	{
		LCD_voidSendData(*letter);
		letter ++;
	}
	
}
//-----------------------------------------------------
//print integer
void LCD_voidPrintInt(uint32 number)
{
	uint8 count = 0;
	uint32 pack = number;
	uint32 mirror = number;
	uint8 digit = 0;
	
	if(number == 0)
		LCD_voidSendData('0');		//to avoid dividing zero by zero
	else
	{
		while(pack != 0)   // counting the number of digits
		{
			pack /= 10;
			count ++;
		}
		
		
		//printing digit by digit
		pack = number;
		for(uint8 i = 0; i < count; i ++)
		{
			pack /= pow(10, count - i - 1);
			digit = (uint8)pack;
			LCD_voidSendData(digit + '0');
			mirror = mirror - (pack * pow(10, count - i - 1));
			pack = mirror;
		}
	}
	
}
//-----------------------------------------------------------------------------------
//print float number
//five numbers after digit
void LCD_voidPrintFloat(f32 number)
{
	f32 pack = number;
	uint32 correct_part;							//carry the correct part
	f32 fraction_part;								//carry the fraction part
	uint8 digit;
	
	correct_part = (uint32) pack;					//calculate the correct part
	fraction_part = pack - correct_part;			//calculate the fraction part
	
	LCD_voidPrintInt(correct_part);					//print the correct part
	
	LCD_voidSendData('.');							//print the decimal point
	
	
	for(uint8 i = 1; i <= 2; i ++)					//print the fraction part, 2 digits after the decimal point
	{
		fraction_part *= 10;
		digit = (uint8)fraction_part;
		LCD_voidSendData(digit + '0');
		fraction_part = fraction_part - digit;
	}
}
