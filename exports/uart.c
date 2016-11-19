/* ###################################################################
**     Filename    : uart.c
**     Project     : uart
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
** @file uart.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/

#include "uart.h"
#include "MK64F12.h"

uart uart2, uart3;

void uart2_init(void)
{
	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;      /*Enable the UART clock*/
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;		/*Enable the PORTB clock*/
	PORTD_PCR2 |= PORT_PCR_MUX(3)|PORT_PCR_ISF(0)|PORT_PCR_IRQC(10);//|PORT_PCR_ISF(0);			//this is the RX
	PORTD_PCR3 |= PORT_PCR_MUX(3)|PORT_PCR_ISF(0);

	UART2_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );  /*Disable Tx and Rx*/
	UART2_C1 = 0; 		/*Dafault settings of the register*/

	uart2.ubd = (uint16_t)((21000*1000)/(9600 * 16));  /* Calculate baud settings */

	uart2.temp = UART2_BDH & ~(UART_BDH_SBR(0x1F));   /*Save the value of UART0_BDH except SBR*/
	UART2_BDH = temp | (((ubd & 0x1F00) >> 8));
	UART2_BDL = (uint8_t)(ubd & UART_BDL_SBR_MASK);

	UART2_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);    /* Enable receiver and transmitter */
	
	PORTD_ISFR = PORT_ISFR_ISF(0x00000004); 	  /* Clear interrupt status flag */
	
	NVIC_EnableIRQ(PORTD_IRQn);
}

void uart3_init(void)
{
	SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;      /*Enable the UART clock*/
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;		/*Enable the PORTB clock*/
	PORTC_PCR16 |= PORT_PCR_MUX(3);
	PORTC_PCR17 |= PORT_PCR_MUX(3);

	UART3_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );  /*Disable Tx and Rx*/
	UART3_C1 = 0; 		/*Dafault settings of the register*/

	uart3.ubd = (uint16_t)((21000*1000)/(9600 * 16));  /* Calculate baud settings */

	uart3.temp = UART3_BDH & ~(UART_BDH_SBR(0x1F));   /*Save the value of UART0_BDH except SBR*/
	UART3_BDH = temp | (((ubd & 0x1F00) >> 8));
	UART3_BDL = (uint8_t)(ubd & UART_BDL_SBR_MASK);

	UART3_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK );    /* Enable receiver and transmitter */
}

uint8_t uart2_getchar ()
{
	/* Wait until character has been received */
	while (!(UART2_S1 & UART_S1_RDRF_MASK));
	/* Return the 8-bit data from the receiver */
	return UART2_D;
}

uint8_t uart3_getchar ()
{
	/* Wait until character has been received */
	while (!(UART3_S1 & UART_S1_RDRF_MASK));
	/* Return the 8-bit data from the receiver */
	return UART3_D;
}

void uart2_putchar (char ch)
{
	/* Wait until space is available in the FIFO */
	while(!(UART2_S1 & UART_S1_TDRE_MASK));
	/* Send the character */
	UART2_D = (uint8_t)ch;
}

void uart3_putchar (char ch)
{
	/* Wait until space is available in the FIFO */
	while(!(UART3_S1 & UART_S1_TDRE_MASK));
	/* Send the character */
	UART3_D = (uint8_t)ch;
}

void put2(char *ptr_str)
{
	while(*ptr_str)
		uart2_putchar(*ptr_str++);
}

void put3(char *ptr_str)
{
	while(*ptr_str)
		uart3_putchar(*ptr_str++);
}

void DelayFunction(void)
{
	int cnt;
	for(cnt=0; cnt<100000; cnt++){}	
}
void UART2_IRQHandler(void)
{
	DelayFunction();
	put("interruptedxxx");

	PORTD_ISFR = PORT_ISFR_ISF(0x00000004);
}

void PORTD_IRQHandler(void)
{
	DelayFunction();
	put("interrupted");

	PORTD_ISFR = PORT_ISFR_ISF(0x00000004);		/* Clear interrupt status flag */
}

