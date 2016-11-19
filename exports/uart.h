/* ###################################################################
**     Filename    : uart.h
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

/* README
 * UART communications header file for RPI comms and screen comms
 * */
 
 #ifndef UART_H_
 #define UART_H_
 
 //UART body
 typedef struct
 {	
	uint16_t ubd;	//baud rate
	uint8_t temp;	//temp baud rate
	uint8_t ch;		//char for use in uart transmission
 }	uart; 
 
 //UART2 functions
void uart2_init(void);
uint8_t uart2_getchar ();
void uart2_putchar (char ch);
void UART2_IRQHandler(void);
void PORTD_IRQHandler(void);

//UART3 functions
void uart3_init(void);
uint8_t uart3_getchar ();
void uart3_putchar (char ch);

//Misc functions
void DelayFunction(void);
void put2(char *ptr_str);
void put3(char *ptr_str);

#endif //UART_H_