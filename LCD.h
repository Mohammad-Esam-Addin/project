/*
 * LCD.h
 *
 * Created: 15/02/2020 01:49:51 م
 *  Author: Mohammad
 */ 
#include "bit_level.h"
#include "std_types.h"
#include "DIO.h"
#include <avr/io.h>

#define CURSOR_OFF 0
#define SET_CURSOR 1
#define	BLINKING_CURSOR 2

#define SHIFT_LEFT 0
#define SHIFT_RIGHT 1


void LCD_voidInit();

void LCD_voidSendCommand(uint8 command);

void LCD_voidSendData(uint8 data);

void LCD_voidClear();

void LCD_voidCursorDisplay(uint8 state);

void LCD_voidShiftCursor(uint8 shift, uint8 number);

void LCD_voidShiftDisplay(uint8 shift);

void LCD_voidPrintString(uint8 ch[]);

void LCD_voidPrintInt(uint32 number);

void LCD_voidPrintFloat(f32 number);

void LCD_voidPrintInTheFirst();

void LCD_voidPrintInTheSecond();