/*
 * I2C.h
 *
 * Created: 11/05/2020 06:24:05 ص
 *  Author: Mohammad
 */ 

#include "std_types.h"
#include "DIO.h"
#include "bit_level.h"
#include <avr/io.h>


#ifndef I2C_H_
#define I2C_H_

#define PRESCALE_1 0
#define PRESCALE_4 1
#define PRESCALE_16 2
#define PRESCALE_64 3

#define INTERRUPT_OFF 0
#define INTERRUPT_ON 1

void I2C_voidInit();

void I2C_voidStart();

void I2C_voidSlaveWrite(uint8 slave);

void I2C_voidSlaveRead(uint8 slave);

void I2C_voidSendData(uint8 data);

uint8 I2C_uint8ReceiveWithACK();

uint8 I2C_uint8ReceiveWithNoACK();

void I2C_voidStop();

uint8 I2C_uint8Status(uint8 status);

void I2C_voidTWPS();



#endif /* I2C_H_ */