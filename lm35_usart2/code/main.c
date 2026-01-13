//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/adc/adc_c.h"
#include "./assets/usart2/usart2_c.h"
#define	 pin  PA0
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 // Set Clock to 16Mhz	
	usart2_init(9600); // Baudrate = 9600
	adc_init(adc1, pin);
	printf("Please press 'T' or 't' to start\r\n");
	
	while(1)
	{ 
		if(is_TReceived == true)
			printf("Temperature: %5.1f'c\r\n", adc_getVoltage(adc1, pin));
		delay_ms(1000);
	}
}
//------------------------------------------------------------------------------

