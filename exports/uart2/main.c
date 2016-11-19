/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "MK64F12.h"


uint8_t uart_getchar ()
{
/* Wait until character has been received */
while (!(UART2_S1 & UART_S1_RDRF_MASK));
/* Return the 8-bit data from the receiver */
return UART2_D;
}

void uart_putchar (char ch)
{
/* Wait until space is available in the FIFO */
while(!(UART2_S1 & UART_S1_TDRE_MASK));
/* Send the character */
UART2_D = (uint8_t)ch;
}

void put(char *ptr_str)
{
	while(*ptr_str)
		uart_putchar(*ptr_str++);

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

void DelayFunction(void)
{
	int cnt;
	for(cnt=0; cnt<100000; cnt++){}

}

int main(void)
{

	uint16_t ubd;					/*Variable to save the baud rate*/
	uint8_t temp;

	SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;      /*Enable the UART clock*/
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;		/*Enable the PORTB clock*/
	PORTD_PCR2 |= PORT_PCR_MUX(3)|PORT_PCR_ISF(0)|PORT_PCR_IRQC(10);//|PORT_PCR_ISF(0);			//this is the RX
	PORTD_PCR3 |= PORT_PCR_MUX(3)|PORT_PCR_ISF(0);

	UART2_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );  /*Disable Tx and Rx*/
	UART2_C1 = 0; 		/*Dafault settings of the register*/

	ubd = (uint16_t)((21000*1000)/(9600 * 16));  /* Calculate baud settings */

	temp = UART2_BDH & ~(UART_BDH_SBR(0x1F));   /*Save the value of UART0_BDH except SBR*/
	UART2_BDH = temp | (((ubd & 0x1F00) >> 8));
	UART2_BDL = (uint8_t)(ubd & UART_BDL_SBR_MASK);

	UART2_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);    /* Enable receiver and transmitter */

	uint8_t ch;

	//PORTD_PCR2  = 0x80300; 		/*PORTD_PCR6: ISF=0,IRQC=8,MUX=1 */
	PORTD_ISFR = PORT_ISFR_ISF(0x00000004); 	  /* Clear interrupt status flag */
	//NVIC_EnableIRQ(UART2_RX_TX_IRQn);
	NVIC_EnableIRQ(PORTD_IRQn);
	//////////////////////////////////////////
	//ISR

	/////////////////////////////////////////

		put("\r\nSerial code example\r\n");    /*Print the text*/

		while(1)
		{
			put("\r\nSerial yolo\r\n");
			for(int i = 0 ; i< 1000 ; i++){}
		}
	    return 0;

}


