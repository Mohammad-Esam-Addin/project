/*
 * UART_Config.h
 *
 * Created: 08/05/2020 11:26:03 م
 *  Author: Mohammad
 */ 

#include "UART.h"


#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define SIZE BITS_8

#define SENDING_MODE ASYNCHRONOUS_MODE

#define PARITY_MODE DISABLED_PARITY

#define STOP_BIT ONE_BIT

#define CLK_EDGE FALLING_EDGE

#define REGISTER UBRR_SELECT

#define BAUD BAUD_9600

#define RX_INT INTERRUPT_ON

#define TX_INT INTERRUPT_OFF

#define REG_INT INTERRUPT_OFF


#endif /* UART_CONFIG_H_ */