/*
 * connection_frame.c
 *
 * Created: 13/05/2020 04:47:32 ص
 *  Author: Mohammad
 */ 

#include "std_types.h"
#include "DIO.h"
#include "bit_level.h"

#include "I2C.h"
#include "I2C_Config.h"
#include <avr/io.h>

//extern uint8 rec_data[10];
extern uint8 recei_data[10];

/*void SendingFrame(uint8 type, uint8 bytes, uint8 data[])
{
	//send the frame header
	UART_voidInit();
	UART_voidSendData(0xaa);
	
	//send the frame type
	UART_voidSendData(type);
	
	//send size of data
	UART_voidSendData(bytes);
	
	//send data
	for (uint8 i = 0; i < bytes; i ++)
	{
		UART_voidSendData(data[i]);
	}
	
	//calculate the checksum
	uint8 checksum = 0xaa;
	for (uint8 i = 0; i < bytes; i ++)
	{
		checksum ^= data[i];
	}
	checksum ^= bytes;
	checksum ^= type;
	
	//sending the checksum
	UART_voidSendData(checksum);
	
	//sending the tail
	UART_voidSendData(0x55);
}
//-----------------------------------------------------------------------------
uint8 ReceiveFrame()
{
	UART_voidInit();
	if(UART_uint8ReceiveData() == 0xaa)
	{
		
		
		uint8 bytes = 0;
		uint8 checksum = 0xaa;
		uint8 rec_checksum = 0;
		rec_data[0] = UART_uint8ReceiveData();					//type of data
		
		bytes = UART_uint8ReceiveData();						//no. of bytes will be received
		
		for (uint8 i = 0; i < bytes; i ++)
		{
			rec_data[i + 1] = UART_uint8ReceiveData();
		}
		
		if (UART_uint8ReceiveData() == 0x55)					//check if the frame has ended
		{
			rec_checksum = UART_uint8ReceiveData();
			
			checksum ^= bytes;
			for (uint8 i = 0; i <= bytes; i ++)
			{
				checksum = rec_data[i];
			}
			if (checksum == rec_checksum)
			{
				return bytes;
			}
			else
			{
				return 0;
			}
		}
	}
	return 0;
}*/
//------------------------------------------------------------------------------------------------------------------------
void I2C_SendingFrame(uint8 type,uint8 address, uint8 bytes, uint8 data[])
{
	uint8 checksum = 0xaa;
	checksum ^= (type ^ bytes);
	
	for(uint8 i = 0; i < bytes; i ++)
	{
		checksum ^= data[i];
	}
	
	I2C_voidStart();
	
	I2C_voidSlaveWrite(address);
	
	while (I2C_uint8Status(0x18) == 0);
	
	I2C_voidSendData(0xaa);
	
	I2C_voidSendData(type);
	
	I2C_voidSendData(bytes);
	
	for (uint8 i = 0; i < bytes; i ++)
	{
		I2C_voidSendData(data[i]);
	}
	
	I2C_voidSendData(checksum);
	
	I2C_voidSendData(0x55);
	
	while(I2C_uint8Status(0x28) == 1);
	
	I2C_voidStop();
}
//-------------------------------------------------------------------------------------------------------------------------
void I2C_ReceivingFrame()
{
	uint8 count = 0;
	while ((I2C_uint8Status(0x60) == 0) || (I2C_uint8Status(0x70) == 1));
	
	if (I2C_uint8ReceiveWithACK() == 0xaa)
	{
		while((I2C_uint8Status(0x80) == 0)||(I2C_uint8Status(0x90) == 0))
		while (I2C_uint8ReceiveWithACK() != 0x55)
		{
			recei_data[count] = I2C_uint8ReceiveWithACK();
			count ++;
			while((I2C_uint8Status(0x80) == 0)||(I2C_uint8Status(0x90) == 0));
		}
	}
	count ++;
	
	recei_data[count] = I2C_uint8ReceiveWithNoACK();
}