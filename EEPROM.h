/*
 * EEPROM.h
 *
 * Created: 13/05/2020 05:45:07 م
 *  Author: Mohammad
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_


void EEPROM_voidWrite(uint16 address, uint8 data);

uint8 EEPROM_uint8Read(uint16 address);

void EEPROM_voidEnableInt();




#endif /* EEPROM_H_ */