/* ###################################################################
**     Filename    : adc.c
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
** @file adc.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/

/* READMEE
 * simple barebone ADC on pins DAC0_out, B2 , B3
 * does not use processor expert component
 * only components are the debug and WAIT components, the rest came with default processor expet setting
 * */


/* MODULE adc */

#include "adc.h"

#include "MK64F12.h"

adc_result adc;

unsigned short threshold0 = 5000;
unsigned short threshold1 = 57000;
unsigned short threshold2 = 65000;

bool ADC_read16b0(void)
{
	ADC0_SC1A = 12 & ADC_SC1_ADCH_MASK; 	//Write to SC1A to start conversion
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  			//Conversion in progress
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));			//Until conversion complete

	if (ADC0_RA > threshold0)
	{return 1;}
	else
	{return 0;}
}

bool ADC_read16b1(void)
{
	ADC0_SC1A = 13 & ADC_SC1_ADCH_MASK; 	//Write to SC1A to start conversion
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  			//Conversion in progress
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));			//Until conversion complete

	if (ADC0_RA > threshold1)
	{return 1;}
	else
	{return 0;}
}

bool ADC_read16b2(void)
{
	ADC0_SC1A = 23 & ADC_SC1_ADCH_MASK; 	//Write to SC1A to start conversion
	while(ADC0_SC2 & ADC_SC2_ADACT_MASK);  			//Conversion in progress
	while(!(ADC0_SC1A & ADC_SC1_COCO_MASK));			//Until conversion complete

	if (ADC0_RA > threshold2)
	{return 1;}
	else
	{return 0;}
}

void adc_init(void)
{
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;		/*Enable the ADC0 Clock*/
	SIM_SCGC6 |= SIM_SCGC6_ADC0_MASK;

	ADC0_CFG1 |= ADC_CFG1_MODE(3);			/*16bits ADC*/
	ADC0_SC1A |= ADC_SC1_ADCH(31);			/*Disable the module, ADCH = 1111 */

	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;		/*Enable the PORTB clock*/
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;

	PORTB_PCR16 |= PORT_PCR_MUX(3);
	PORTB_PCR17 |= PORT_PCR_MUX(3);
}

void adc_read(void)
{
	adc.result = ADC_read16b0();
	adc.result2 = ADC_read16b1();
	adc.result3 = ADC_read16b2();
	PRINTF("value is %d   ,   %d   , %d    \r\n" , adc.result , adc.result2 , adc.result3);
	WAIT1_Waitms(500);
}