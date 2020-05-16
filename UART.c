/*
 * UART.c
 *
 * Created: 20/04/2020 11:12:30 م
 *  Author: Mohammad
 */ 

#include "std_types.h"
#include "DIO.h"
#include "bit_level.h"

#include "UART_Config.h"
#include <avr/io.h>
#define F_CPU 8000000


void UART_voidInit()
{
	SET_BIT(UCSRC, 7);
	
	//selecting the data size: 5, 6, 7, 8, or 9 bits
	#if SIZE == BITS_5
	{
		CLR_BIT(UCSRB, 2);
		CLR_BIT(UCSRC, 2);
		CLR_BIT(UCSRC, 1);
	}
	#elif SIZE == BITS_6
	{
		CLR_BIT(UCSRB, 2);
		CLR_BIT(UCSRC, 2);
		SET_BIT(UCSRC, 1);
	}
	#elif SIZE == BITS_7
	{
		CLR_BIT(UCSRB, 2);
		SET_BIT(UCSRC, 2);
		CLR_BIT(UCSRC, 1);
	}
	#elif SIZE == BITS_8
	{
		CLR_BIT(UCSRB, 2);
		SET_BIT(UCSRC, 2);
		SET_BIT(UCSRC, 1);
	}
	#elif SIZE == BITS_9
	{
		SET_BIT(UCSRB, 2);
		SET_BIT(UCSRC, 2);
		SET_BIT(UCSRC, 1);
	}
	#endif
	
	//select mode of sending, Synchronous or Asynchronous
	#if SENDING_MODE == ASYNCHRONOUS_MODE
	CLR_BIT(UCSRC, 6);
	#else
	SET_BIT(UCSRC, 6);
	#endif
	
	//define the stop bits: one bit or two bits
	#if STOP_BIT == ONE_BIT
	CLR_BIT(UCSRC, 3);
	#else
	SET_BIT(UCSRC, 3);
	#endif
	
	//choose the clock polarization: rising or falling
	#if CLK_EDGE == FALLING_EDGE
	CLR_BIT(UCSRC, 0);
	#else
	SET_BIT(UCSRC, 0);
	#endif
	
	//define the parity mode
	#if PARITY_MODE == DISABLED_PARITY
	{
		CLR_BIT(UCSRC, 5);
		CLR_BIT(UCSRC, 4);
	}
	#elif PARITY_MODE == EVEN_PARITY
	{
		SET_BIT(UCSRC, 5);
		CLR_BIT(UCSRC, 4);
	}
	#else
	{
		SET_BIT(UCSRC, 5);
		SET_BIT(UCSRC, 4);
	}
	#endif
	
	UART_voidRxCompleteInt();
	
	UART_voidTxCompleteInt();
	
	UART_voidRegisterEmptyInt();
	
	UART_voidSelectBaudRate();
	
	UCSRB = (1<< 3)|(1 << 4);
}
//------------------------------------------------------------------------------------------------
void UART_voidSendData(uint8 data)
{
	while(GET_BIT(UCSRA, 5) == 0);
	UDR = data;
}
//---------------------------------------------------------------------------------------
void UART_voidSendString(uint8 array[])
{
	uint8 counter = 0;
	uint8* ptr = array;
	while (*(ptr) != '\0')
	{
		counter ++;
		ptr ++;
	}
	ptr = array;
	while(GET_BIT(UCSRA, 5) == 0);
	for (uint8 i = 0; i < counter; i ++)
	{
		UART_voidSendData(*(ptr));
		ptr ++;
	}
}
//-----------------------------------------------------------------------------------------
void UART_voidRxCompleteInt()
{
	#if RX_INT == INTERRUPT_ON
	{
		SET_BIT(UCSRB, 7);
		SET_BIT(SREG, 7);
	}
	#else
	{
		CLR_BIT(UCSRB, 7);
	}
	#endif
}
//------------------------------------------------------------------------------------------
void UART_voidTxCompleteInt()
{
	#if TX_INT == INTERRUPT_ON
	{
		SET_BIT(UCSRB, 6);
		SET_BIT(SREG, 7);
	}
	#else
		CLR_BIT(UCSRB, 6);
	#endif
	
}
//-----------------------------------------------------------------------------------------
void UART_voidRegisterEmptyInt()
{
	#if REG_INT == INTERRUPT_ON
	{
		SET_BIT(UCSRB, 5);
		SET_BIT(SREG, 7);
	}
	#else
		CLR_BIT(UCSRB, 5);
	#endif
}
//-----------------------------------------------------------------------------------------
uint8 UART_uint8ReceiveData()
{
	while(GET_BIT(UCSRA, 7) == 0);
	return UDR;
}
//--------------------------------------------------------------------------------------------
void UART_voidSelectBaudRate()
{
	CLR_BIT(UBRRH, 7);
	
	uint64 buff;
	buff = (F_CPU/(16UL * BAUD)) - 1;
	
	for (uint8 i = 0; i < 4; i ++)
	{
		if(GET_BIT(buff, (8 + i)) == 1)
			SET_BIT(UBRRH, (0 + i));
		else
			CLR_BIT(UBRRH, (0 + i));
	}	
	UBRRL = (uint8)buff;
}
//------------------------------------------------------------------------------------------
