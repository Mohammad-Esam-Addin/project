/*
 * EEPROM.c
 *
 * Created: 13/05/2020 05:44:47 م
 *  Author: Mohammad
 */ 


#include "std_types.h"
#include "bit_level.h"
#include "DIO.h"
#include <avr/io.h>

void EEPROM_voidWrite(uint16 address, uint8 data)
{
	//disable interrupt
	CLR_BIT(EECR, 3);
	
	while(GET_BIT(EECR, 1) == 1);				//wait until EEWE becomes zero
	
	while (GET_BIT(SPMCR, 0) == 1);				//wait until SPMEN in SPMCR becomes zero
	
	//registering the address that we need to do process in the register
	for (uint8 i = 0; i < 2; i ++)
	{
		if (GET_BIT(address, (8 + i)) == 1)
		{
			SET_BIT(EEARH, (i));
		}
		else
		{
			CLR_BIT(EEARH, (i));
		}
	}
	EEARL = (uint8) address;
	
	//setting data in the register
	EEDR = data;
	
	//Write a logical one to the EEMWE bit while writing a zero to EEWE in EECR
	EECR = (1 << 2)|(0 << 1);
	
	//enable writing
	SET_BIT(EECR, 1);
}
//----------------------------------------------------------------------------------------------
uint8 EEPROM_uint8Read(uint16 address)
{
	while(GET_BIT(EECR, 1) == 1);
	
	//disable interrupt
	CLR_BIT(EECR, 3);
	
	//registering the address that we need to do process in the register
	for (uint8 i = 0; i < 2; i ++)
	{
		if (GET_BIT(address, (8 + i)) == 1)
		{
			SET_BIT(EEARH, (i));
		}
		else
		{
			CLR_BIT(EEARH, (i));
		}
	}
	EEARL = (uint8) address;
	
	//enable reading
	SET_BIT(EECR, 0);
	
	return EEDR;
}
//--------------------------------------------------
void EEPROM_voidEnableInt()
{
	SET_BIT(EECR, 3);
	SET_BIT(SREG, 7);
}