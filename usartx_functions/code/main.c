//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/usart/usart_c.h"
//------------------------------------------------------------------------------
char str[80];
int num;
//------------------------------------------------------------------------------
int main(void)
{	  
	clock_init();				 			// Set internal Clock to 16Mhz	
	usart_init(usart1, 9600);	// USARTn, Baudrate = 9600
	
	printf("Test stdio library console I/O functions\r\n");
	fprintf(stdout, "Test for stdout\r\n"); 
	fprintf(stderr, "Test for stderr\r\n");	
	
	while(1)
	{ 
		// Numeric entry and feedback
		printf("Please enter a number: "); 
		scanf("%d", &num); 
		printf("The number entered is: %d\r\n", num); 
		
		// String entry and feedback
		printf("Please type a character string: "); 
		gets(str); 
		printf("The character string entered is: "); 
		puts(str); 
		printf("\r\n");	
	}
}
//------------------------------------------------------------------------------

