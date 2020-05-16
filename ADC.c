/*
 * ADC.c
 *
 * Created: 22/02/2020 02:29:08 م
 *  Author: Mohammad
 */ 
#include "std_types.h"
#include "bit_level.h"
#include "DIO.h"
#include "ADC.h"
#include "ADC_Config.h"
#include <avr/io.h>
#include <avr/interrupt.h>



//choosing channel
void ADC_voidChooseChannel(uint8 channel)
{
	switch(channel)
	{
		case 0:												//using	ADC0 at PORTA0
			CLR_BIT(ADMUX, 4);
			CLR_BIT(ADMUX, 3);
			CLR_BIT(ADMUX, 2);
			CLR_BIT(ADMUX, 1);
			CLR_BIT(ADMUX, 0);
			break;
			
		case 1:												//using ADC1 at PORTA1
			CLR_BIT(ADMUX, 4);
			CLR_BIT(ADMUX, 3);
			CLR_BIT(ADMUX, 2);
			CLR_BIT(ADMUX, 1);
			SET_BIT(ADMUX, 0);
			break;
			
		case 2:												//using ADC2 at PORTA2
			CLR_BIT(ADMUX, 4);
			CLR_BIT(ADMUX, 3);
			CLR_BIT(ADMUX, 2);
			SET_BIT(ADMUX, 1);
			CLR_BIT(ADMUX, 0);
			break;
			
		case 3:												//using ADC3 at PORTA3
			CLR_BIT(ADMUX, 4);
			CLR_BIT(ADMUX, 3);
			CLR_BIT(ADMUX, 2);
			SET_BIT(ADMUX, 1);
			SET_BIT(ADMUX, 0);
			break;
			
		case 4:												//using ADC4 at PORTA4
			CLR_BIT(ADMUX, 4);
			CLR_BIT(ADMUX, 3);
			SET_BIT(ADMUX, 2);
			CLR_BIT(ADMUX, 1);
			CLR_BIT(ADMUX, 0);
			break;
			
		case 5:												//using ADC5 at PORTA5
			CLR_BIT(ADMUX, 4);
			CLR_BIT(ADMUX, 3);
			SET_BIT(ADMUX, 2);
			CLR_BIT(ADMUX, 1);
			SET_BIT(ADMUX, 0);
			break;
			
		case 6:												//using ADC6 at PORTA6
			CLR_BIT(ADMUX, 4);
			CLR_BIT(ADMUX, 3);
			SET_BIT(ADMUX, 2);
			SET_BIT(ADMUX, 1);
			CLR_BIT(ADMUX, 0);
			break;
			
		case 7:												//using ADC7 at PORTA7
			CLR_BIT(ADMUX, 4);
			CLR_BIT(ADMUX, 3);
			SET_BIT(ADMUX, 2);
			SET_BIT(ADMUX, 1);
			SET_BIT(ADMUX, 0);
			break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//conversion analog to digital
uint8 ADC_uint8ConvertChannel()
{
	uint32 digital_value = 0;
	
	#if DIRECTION == LEFT_ADJUST
		SET_BIT(ADMUX, 5);
		
	#elif DIRECTION == RIGHT_ADJUST
		CLR_BIT(ADMUX, 5);
	#endif
		
	for(uint8 i = 0; i < 100; i ++)
	{
		SET_BIT(ADCSRA, 6);					//start conversion
		SET_BIT(ADCSRA, 4);					//reset flag
		
		//waiting for conversion
		while(GET_BIT(ADCSRA, 4) == 0);
		
		//clearing flag
		SET_BIT(ADCSRA, 4);
		
		//sum of samples
		if(ADLAR == 1)
			digital_value += ADCH;
		else
			digital_value += ADCL;
	}
	//taking average
	digital_value /= 100;
	return (uint8)digital_value;
}
//-------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//for the register ADCSRA
//for prescaling timer
void ADC_voidPrescalarTimer()
{
	#if prescale == 2
		CLR_BIT(ADCSRA, 0);
		CLR_BIT(ADCSRA, 1);
		CLR_BIT(ADCSRA, 2);
		
	#elif prescale == 4
		CLR_BIT(ADCSRA, 0);
		SET_BIT(ADCSRA, 1);
		CLR_BIT(ADCSRA, 2);
		
	#elif prescale == 8
		SET_BIT(ADCSRA, 0);
		SET_BIT(ADCSRA, 1);
		CLR_BIT(ADCSRA, 2);
		
	#elif prescale == 16
		CLR_BIT(ADCSRA, 0);
		CLR_BIT(ADCSRA, 1);
		SET_BIT(ADCSRA, 2);
		
	#elif prescale == 32
		SET_BIT(ADCSRA, 0);
		CLR_BIT(ADCSRA, 1);
		SET_BIT(ADCSRA, 2);
		
	#elif prescale == 64
		CLR_BIT(ADCSRA, 0);
		SET_BIT(ADCSRA, 1);
		SET_BIT(ADCSRA, 2);
		
	#elif prescale == 128
		SET_BIT(ADCSRA, 0);
		SET_BIT(ADCSRA, 1);
		SET_BIT(ADCSRA, 2);
		
	#endif
}
//-----------------------------------------------------------------------------
//for enabling ADC interrupt enable
void ADC_voidEnableInterrupt()
{
	#if INT_STATUS == ENABLE_INT
	{
		SET_BIT(ADCSRA, 3);
		SET_BIT(SREG, 7);
	}
	#else
	{
			CLR_BIT(ADCSRA, 3);
	}
	#endif
	
}
//------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//for the register SFIOR
//special function I/O register
void ADCvoidSpecialFunctionChoice()
{
	#if FUNCTION == FREE_RUNNING_MODE
		CLR_BIT(SFIOR, 7);
		CLR_BIT(SFIOR, 6);
		CLR_BIT(SFIOR, 5);
		
	#elif FUNCTION == ANALOG_COMPARATOR
		CLR_BIT(SFIOR, 7);
		CLR_BIT(SFIOR, 6);
		SET_BIT(SFIOR, 5);
		
	#elif FUNCTION == EXTERNAL_INTERRUPT
		CLR_BIT(SFIOR, 7);
		SET_BIT(SFIOR, 6);
		CLR_BIT(SFIOR, 5);
		
	#elif FUNCTION == TIMER0_COMPARE_MATCHA
		CLR_BIT(SFIOR, 7);
		SET_BIT(SFIOR, 6);
		SET_BIT(SFIOR, 5);
		
	#elif FUNCTION == TIMER0_OVERFLOW
		SET_BIT(SFIOR, 7);
		CLR_BIT(SFIOR, 6);
		CLR_BIT(SFIOR, 5);
		
	#elif FUNCTION == TIMER1_COMPARE_MATCHB
		SET_BIT(SFIOR, 7);
		CLR_BIT(SFIOR, 6);
		SET_BIT(SFIOR, 5);
		
	#elif FUNCTION == TIMER1_OVERFLOW
		SET_BIT(SFIOR, 7);
		SET_BIT(SFIOR, 6);
		CLR_BIT(SFIOR, 5);
		
	#elif FUNCTION == TIMER1_CAPTURE_EVENT
		SET_BIT(SFIOR, 7);
		SET_BIT(SFIOR, 6);
		SET_BIT(SFIOR, 5);

	#endif
	
	CLR_BIT(SFIOR, 4);
}
//--------------------------------------------------------------------------------------------------------------------
void ADC_voidInit()
{
	#if v_max == A_REF			//internal VREF is turned off
	CLR_BIT(ADMUX, 7);
	CLR_BIT(ADMUX, 6);
	
	#elif v_max == VCC			//using VCC with external capacitor at AREF pin
	CLR_BIT(ADMUX, 7);
	SET_BIT(ADMUX, 6);
	
	#elif v_max == half_vcc		//internal 2.56v voltage reference with external capacitor at AREF pin
	SET_BIT(ADMUX, 7);
	SET_BIT(ADMUX, 6);
	
	#endif
	
	
	ADC_voidPrescalarTimer();		//prescaling timer
	
	ADCvoidSpecialFunctionChoice();			//choosing the function of the ADC	
	
	SET_BIT(ADCSRA, 7);			//enable ADC
}
//--------------------------------------------------------------------------------------------------------------------------------