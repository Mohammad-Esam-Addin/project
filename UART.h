/*
 * UART.h
 *
 * Created: 20/04/2020 11:13:31 م
 *  Author: Mohammad
 */ 


#include <avr/io.h>

#ifndef UART_H_
#define UART_H_

#define BITS_5 0
#define BITS_6 1
#define BITS_7 2
#define BITS_8 3
#define BITS_9 7

#define ASYNCHRONOUS_MODE 0
#define SYNCHRONOUS_MODE 1

#define DISABLED_PARITY 0
#define EVEN_PARITY 2
#define	ODD_PARITY 3

#define ONE_BIT 0
#define TWO_BIT 1

#define FALLING_EDGE 0
#define RISING_EDGE 1

#define UBRR_SELECT 0
#define UCSRC_SELECT 1

#define	BAUD_2400 2400
#define BAUD_4800 4800
#define BAUD_9600 9600
#define	BAUD_14400 14400
#define BAUD_19200 19200
#define BAUD_28800 28800
#define BAUD_38400 38400
#define BAUD_57600 57600
#define BAUD_76800 76800
#define BAUD_115200 115200
#define BAUD_230400 230400
#define BAUD_250000 250000

#define INTERRUPT_OFF 0
#define INTERRUPT_ON 1

void UART_voidInit();

void UART_voidSendData(uint8 data);

void UART_voidSendString(uint8 array[]);

void UART_voidRxCompleteInt();

void UART_voidTxCompleteInt();

void UART_voidRegisterEmptyInt();

uint8 UART_uint8ReceiveData();

void UART_voidSelectBaudRate();

#endif /* UART_H_ */