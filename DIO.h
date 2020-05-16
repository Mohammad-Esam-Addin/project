/*
 * DIO.h
 *
 * Created: 14/02/2020 11:26:25 ص
 *  Author: Mohammad
 */ 


#ifndef DIO_H_
#define DIO_H_
#endif /* DIO_H_ */

#define DIO_PORTA 0
#define DIO_PORTB 1
#define DIO_PORTC 2
#define DIO_PORTD 3

#define DIO_PIN_0 0
#define DIO_PIN_1 1
#define DIO_PIN_2 2
#define DIO_PIN_3 3
#define DIO_PIN_4 4
#define DIO_PIN_5 5
#define DIO_PIN_6 6
#define DIO_PIN_7 7

#define DIO_INPUT 0
#define DIO_OUTPUT 1

#define DIO_LOW 0
#define DIO_HIGH 1

#define PULL_UP 1
#define TRI_STATE 0


void DIO_voidSetPinDirection(uint8 port, uint8 pin, uint8 dir);

void DIO_voidSetPinValue(uint8 port, uint8 pin, uint8 value);

uint8 DIO_uint8GetPinValue(uint8 port, uint8 pin);

void DIO_voidTogglePin(uint8 port, uint8 pin);