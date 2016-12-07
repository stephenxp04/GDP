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


void rpi_output_init()
{
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;		/*Enable Port C Clock Gate Control*/
	PORTC_PCR2  = 0x0100; // mux 1
	PORTC_PCR3  = 0x0100; // mux 1
	GPIOC_PDDR |= (0 << 2);//set as input pin C2 (EN)
	GPIOC_PDDR |= (0 << 3);// set as input pin C3 (SIGNAL)
}

uint8_t uart_getchar ()
{
/* Wait until character has been received */
while (!(UART0_S1 & UART_S1_RDRF_MASK));
/* Return the 8-bit data from the receiver */
return UART0_D;
}

void uart_putchar (char ch)
{
/* Wait until space is available in the FIFO */
while(!(UART0_S1 & UART_S1_TDRE_MASK));
/* Send the character */
UART0_D = (uint8_t)ch;
}

void put(char *ptr_str)
{
	while(*ptr_str)
		uart_putchar(*ptr_str++);
}

void uart_init()
{
	uint16_t ubd;					/*Variable to save the baud rate*/
	uint8_t temp;

	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;      /*Enable the UART clock*/
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;		/*Enable the PORTB clock*/
	PORTB_PCR16 |= PORT_PCR_MUX(3);
	PORTB_PCR17 |= PORT_PCR_MUX(3);

	UART0_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );  /*Disable Tx and Rx*/
	UART0_C1 = 0; 		/*Dafault settings of the register*/

	ubd = (uint16_t)((21000*1000)/(9600 * 16));  /* Calculate baud settings */

	temp = UART0_BDH & ~(UART_BDH_SBR(0x1F));   /*Save the value of UART0_BDH except SBR*/
	UART0_BDH = temp | (((ubd & 0x1F00) >> 8));
	UART0_BDL = (uint8_t)(ubd & UART_BDL_SBR_MASK);

	UART0_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK );    /* Enable receiver and transmitter */

	uint8_t ch;

}

int rpi_output()
{
	if(((PTC->PDIR >> 0x02u) & 0x01U))			/*If the EN signal*/
		{
			if(((PTC->PDIR >> 0x03u) & 0x01U))		/* if the rpis signal is high also*/
			{
				put("rpi detected \r\n");
				return 1;
			}
			else
			{
				put("rpi not detected \r\n");
				return 0;
			}
		}
		else
		{   put("------------------------------- \r\n");
			return 0;
		}

}


int main(void)
{
	rpi_output_init();
	uart_init();
	unsigned long Counter = 0x100000;		/*Delay Value    1ms = 40ticks*/

	for(;;)
	{   put("================================ \r\n\n\n");
		rpi_output();
	}
	return 0;
}
