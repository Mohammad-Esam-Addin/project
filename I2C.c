/*
 * I2C.c
 *
 * Created: 11/05/2020 06:23:28 ص
 *  Author: Mohammad
 */ 
#include "std_types.h"
#include "bit_level.h"
#include "DIO.h"
#include "I2C_Config.h"
#include <avr/io.h>
#define F_CPU 8000000

void I2C_voidTWIInt()
{
	#if TWI_INT == INTERRUPT_ON
	{
		SET_BIT(TWCR, 0);
		SET_BIT(SREG, 7);
	}
	#else
	{
		CLR_BIT(TWCR, 0);
	}
	#endif
}
//-----------------------------------------------------------------
void I2C_voidInit()
{
	SET_BIT(TWCR, 2);				//enable the TWI connection
	
	//prescaling the TWPS
	#if PRESCALE == PRESCALE_1
	{
		CLR_BIT(TWSR, 1);
		CLR_BIT(TWSR, 0);
	}
	#elif PRESCALE == PRESCALE_4
	{
		CLR_BIT(TWSR, 1);
		SET_BIT(TWSR, 0);
	}
	#elif PRESCALE == PRESCALE_16
	{
		SET_BIT(TWSR, 1);
		CLR_BIT(TWSR, 0);
	}
	#else
	{
		TWSR = (1<<1)|(1<<0);
	}
	#endif
	
	//defining the address of the ECU 0x79
	TWAR = ADDRESS;
	TWAR = TWAR << 1;
	
	
	//define the data bit rate
	TWBR = 1;
	
	//enable the TWI bit
	SET_BIT(TWCR, 2);
}
//---------------------------------------------------------------------------------------
void I2C_voidStart()
{
	TWCR = (1 << 7)|(1 << 5)|(1 << 2);
	while(GET_BIT(TWCR, 7) == 0);
}
//---------------------------------------------------------------------------------------
void I2C_voidSlaveWrite(uint8 slave)
{
	TWCR = (1 << 7)|(1 << 2);
	TWDR = (slave << 1);
	while(GET_BIT(TWCR, 7) == 0);
}
//---------------------------------------------------------------------------------------
void I2C_voidSlaveRead(uint8 slave)
{
	TWCR = (1 << 7)|(1 << 2);
	TWDR = (slave << 1)|1;
	while(GET_BIT(TWCR, 7) == 0);
}
//----------------------------------------------------------------------------------------
void I2C_voidSendData(uint8 data)
{
	TWDR = data;
	TWCR = (1 << 7)|(1 << 2);
	while(GET_BIT(TWCR, 7) == 0);
}
//-----------------------------------------------------------------------------------------
uint8 I2C_uint8ReceiveWithACK()
{
	TWCR = (1 << 7)|(1 << 2);
	while(GET_BIT(TWDR, 7) == 0);
	SET_BIT(TWCR, 6);
	return TWDR;
}
//------------------------------------------------------------------------------------------
uint8 I2C_uint8ReceiveWithNoACK()
{
	TWCR = (1 << 7)|(1 << 2);
	while(GET_BIT(TWDR, 7) == 0);
	return TWDR;
}
//------------------------------------------------------------------------------------------
void I2C_voidStop()
{
	TWCR = (1 << 7)|(1 << 4)|(1 << 2);
}
//------------------------------------------------------------------------------------------
uint8 I2C_uint8Status(uint8 status)
{
	if ((TWSR & 0xf8) == status)
		return 1;
	else
		return 0;
}
