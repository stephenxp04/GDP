/* ###################################################################
**     Filename    : main.c
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
** @file main.c
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


/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "clockMan1.h"
#include "pin_init.h"
#include "osa1.h"
#include "DbgCs1.h"
#include "adConv1.h"
#include "WAIT1.h"
#if CPU_INIT_CONFIG
  #include "Init_Config.h"
#endif
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "board.h"
#include "fsl_pmc_hal.h"
#include "fsl_debug_console.h"
#include <string.h>
#include <stdio.h>
#include "MK64F12.h"

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


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  hardware_init();
  /* Write your code here */
  /* For example: for(;;) { } */

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
PRINTF("testing\r\n");


uint16_t result=0;
uint16_t result2=0;
uint16_t result3=0;
adc_init();

uint8_t ch;
unsigned short bADCData;


  for(;;){

	  	result = ADC_read16b0();
	  	result2 = ADC_read16b1();
	  	result3 = ADC_read16b2();

	  	PRINTF("value is %d   ,   %d   , %d    \r\n" , result , result2 ,result3 );
	  	WAIT1_Waitms(500);

  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
