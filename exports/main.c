/* ###################################################################
 **     Filename    : main.c
 **     Project     : sonar_baremetal3
 **     Processor   : MK64FN1M0VLL12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2016-11-19, 22:00, # CodeGen: 0
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
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "clockMan1.h"
#include "pin_init.h"
#include "osa1.h"
#include "WAIT1.h"
#include "DbgCs1.h"
#if CPU_INIT_CONFIG
#include "Init_Config.h"
#endif
/* User includes (#include below this line is not maintained by Processor Expert) */



int ping_sonar(uint32_t pin_send , uint32_t pin_receive , uint32_t threshold )
{
	uint32_t count = 0;

	GPIOC_PDOR = (0<<pin_send);
	WAIT1_Waitus(20);
	GPIOC_PDOR = (1<<pin_send);
	WAIT1_Waitus(10);
	GPIOC_PDOR = (0<<pin_send);
	WAIT1_Waitus(250);

	while(((PTC->PDIR >> pin_receive) & 0x01U) && count < threshold){
		count++;
	}

	GPIOC_PDOR |= (0<<pin_send);
	WAIT1_Waitms(18);

	PRINTF("%d   " , count);    /*Print the text*/
	return count;

}

void three_ping_sonar()
{

	ping_sonar(0,1,40000);
	WAIT1_Waitms(8);
	ping_sonar(7,8,40000);
	WAIT1_Waitms(8);
	ping_sonar(5,9,40000);
	WAIT1_Waitms(8);
}

void init_sonar()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;		/*Enable Port C Clock Gate Control*/
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;

	PORTC_PCR0  = 0X100;		/*sendpin */
	PORTC_PCR5  = 0X100;
	PORTC_PCR7  = 0X100;

	PORTA_PCR4  = 0x100;
	GPIOA_PDDR |= (0 << 4);

	GPIOC_PDDR |= (1 << 0);
	GPIOC_PDDR |= (1 << 5);
	GPIOC_PDDR |= (1 << 7);

	GPIOC_PDOR |= (0 << 0);
	GPIOC_PDOR |= (0 << 5);
	GPIOC_PDOR |= (0 << 7);

	//////////////////////

	PORTC_PCR1  = 0X100;		/*receive pin*/
	PORTC_PCR8  = 0X100;
	PORTC_PCR9  = 0X100;

	GPIOC_PDDR |= (0 << 1);
	GPIOC_PDDR |= (0 << 8);
	GPIOC_PDDR |= (0 << 9);

	///////////////////////

	PORTC_PCR6  = 0X100;
	GPIOC_PDDR |= (0 << 6);

}


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	/* For example: for(;;) { } */


	init_sonar();

	for(;;)
	{

		three_ping_sonar();
		WAIT1_Waitms(100);
		PRINTF("\r\n loopessss\r\n");
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
