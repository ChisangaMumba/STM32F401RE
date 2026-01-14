//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/adc/adc_c.h"
#include "./assets/usart/usart_c.h"
//------------------------------------------------------------------------------
int main(void)
{	  
	clock_init();				 			// Set Clock to 16Mhz	
	usart_init(usart2, 9600);	// USARTn, Baudrate = 9600
	internalTempSensor_init();
	printf("Please press 'T' or 't' to start\r\n");
	
	while(1)
	{ 
		if(is_TReceived == true)
			printf("Temperature: %5.1f'c\r\n", internalTempSensor_calcTemp());
		delay_ms(1000);	
	}
}
//------------------------------------------------------------------------------

