/* ###################################################################
**     Filename    : adc.h
**     Project     : adc_test
**     Processor   : MK64FN1M0VLL12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-11-07, 21:48, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!

/* READMEE
 * simple barebone ADC on pins DAC0_out, B2 , B3
 * does not use processor expert component
 * only components are the debug and WAIT components, the rest came with default processor expet setting
 * */


#ifndef ADC_H_
#define ADC_H_

/*! @ ADC results */
typedef struct
{
	uint16_t result;
	uint16_t result2;
	uint16_t result3;
} adc_result;

bool ADC_read16b0(void);
//For ADC0
bool ADC_read16b1(void);
//For ADC1
bool ADC_read16b2(void);
//For ADC2
void adc_init(void);
//Initialising the ADC
void adc_read(void);
//Reading and sending data from ADC

#endif //ADC_H_