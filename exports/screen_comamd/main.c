/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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

uint8_t uart_getchar ();
void put(char *ptr_str);
void uart_putchar (char ch);
void init_uart3();


uint8_t uart_getchar ()
{
/* Wait until character has been received */
while (!(UART3_S1 & UART_S1_RDRF_MASK));
/* Return the 8-bit data from the receiver */
return UART3_D;
}

void uart_putchar (char ch)
{
/* Wait until space is available in the FIFO */
while(!(UART3_S1 & UART_S1_TDRE_MASK));
/* Send the character */
UART3_D = (uint8_t)ch;
}

void put(char *ptr_str)
{
	while(*ptr_str)
		uart_putchar(*ptr_str++);
}

void init_uart3()
{

	uint16_t ubd;					/*Variable to save the baud rate*/
	uint8_t temp;
	SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;      /*Enable the UART clock*/
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;		/*Enable the PORTB clock*/
	PORTC_PCR16 |= PORT_PCR_MUX(3);
	PORTC_PCR17 |= PORT_PCR_MUX(3);

	UART3_C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK );  /*Disable Tx and Rx*/
	UART3_C1 = 0; 		/*Dafault settings of the register*/

	ubd = (uint16_t)((21000*1000)/(9600 * 16));  /* Calculate baud settings */

	temp = UART3_BDH & ~(UART_BDH_SBR(0x1F));   /*Save the value of UART0_BDH except SBR*/
	UART3_BDH = temp | (((ubd & 0x1F00) >> 8));
	UART3_BDL = (uint8_t)(ubd & UART_BDL_SBR_MASK);

	UART3_C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK );    /* Enable receiver and transmitter */


}


const uint8_t splash_screen = 117;
const uint8_t sensors_check = 118;
const uint8_t sensor_report = 119;
const uint8_t warning = 120;
const uint8_t shutdown_engine = 121;
const uint8_t restart_engine = 122;
const uint8_t screen_one = 49;
const uint8_t screen_zero = 48;

void screen_splash_screen(){
	uart_putchar (splash_screen);
	uart_putchar (splash_screen);
	uart_putchar (splash_screen);
	uart_putchar (splash_screen);
	uart_putchar (splash_screen);
}
void screen_sensors_check(uint8_t arg1, uint8_t arg2, uint8_t arg3, uint8_t arg4)
{

    uart_putchar (sensors_check);
	uart_putchar (arg1);
	uart_putchar (arg2);
	uart_putchar (arg3);
	uart_putchar (arg4);

}

void screen_sensor_report(uint8_t arg1, uint8_t arg2, uint8_t arg3, uint8_t arg4)
{
	uart_putchar (sensor_report);
	uart_putchar (arg1);
	uart_putchar (arg2);
	uart_putchar (arg3);
	uart_putchar (arg4);
}

void screen_warning()
{
	uart_putchar (warning);
	uart_putchar (warning);
	uart_putchar (warning);
	uart_putchar (warning);
	uart_putchar (warning);
}

void screen_shutdown_engine()
{
	uart_putchar (shutdown_engine);
	uart_putchar (shutdown_engine);
	uart_putchar (shutdown_engine);
	uart_putchar (shutdown_engine);
	uart_putchar (shutdown_engine);
}

void screen_restart_engine()
{
	uart_putchar (restart_engine);
	uart_putchar (restart_engine);
	uart_putchar (restart_engine);
	uart_putchar (restart_engine);
	uart_putchar (restart_engine);
}

static int i = 0;

int main(void)
{

    /* Write your code here */
	init_uart3();
    /* This for loop should be replaced. By default this loop allows a single stepping. */
    for (;;) {

    	for(int i = 0 ; i < 2000000 ; i++){}
    	screen_splash_screen();
    	for(int i = 0 ; i < 2000000 ; i++){}
    	screen_sensors_check(screen_one,screen_one,screen_one,screen_one);
    	for(int i = 0 ; i < 2000000 ; i++){}
    	screen_warning();

    }
    /* Never leave main */
    return 0;
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
