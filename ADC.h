/*
 * ADC.h
 *
 * Created: 22/02/2020 02:29:25 م
 *  Author: Mohammad
 */ 


#ifndef ADC_H_
#define ADC_H_

#define	A_REF 0
#define VCC 1
#define half_vcc 2


#define FREE_RUNNING_MODE 0
#define ANALOG_COMPARATOR 1
#define	EXTERNAL_INTERRUPT 2
#define TIMER0_COMPARE_MATCHA 3
#define TIMER0_OVERFLOW 4
#define TIMER1_COMPARE_MATCHB 5
#define TIMER1_OVERFLOW 6
#define TIMER1_CAPTURE_EVENT 7

#define DISABLE_INT 0
#define ENABLE_INT 1

#define	LEFT_ADJUST 1
#define RIGHT_ADJUST 0

#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7

#endif /* ADC_H_ */

void ADC_voidInit();

void ADC_voidChooseChannel(uint8 channel);

uint8 ADC_uint8ConvertChannel();

void ADC_voidEnableInterrupt();

void ADC_voidPrescalarTimer();

void ADCvoidSpecialFunctionChoice();