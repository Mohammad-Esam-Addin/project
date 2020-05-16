/*
 * connection_frame.h
 *
 * Created: 13/05/2020 12:57:34 ص
 *  Author: Mohammad
 */ 

#include "std_types.h"


#ifndef CONNECTION_FRAME_H_
#define CONNECTION_FRAME_H_

uint8 rec_data[10];				//data for UART

uint8 recei_data[10];			//data for i2c
void SendingFrame(uint8 type, uint8 bytes, uint8 data[]);

uint8 ReceiveFrame();

void I2C_SendingFrame(uint8 type,uint8 address, uint8 bytes, uint8 data[]);

void I2C_ReceivingFrame();

#endif /* CONNECTION_FRAME_H_ */