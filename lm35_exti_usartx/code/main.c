//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/exti/extInterrupt_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/adc/adc_c.h"
#include "./assets/usart/usart_c.h"
#define	 adcPin  PA0
//------------------------------------------------------------------------------
int main(void)
{	  
	clock_init();				 			// Set internal Clock to 16Mhz	
	usart_init(usart1, 9600);	// USARTn, Baudrate = 9600
	adc_init(adc1, adcPin);
	extInt_init(PB0, RISING_EDGE);
	
	printf("Please press 'T' or 't' to start\r\n");
	
	while(1)
	{ 
		if((is_TReceived == true) && (isPaused == false))
			printf("Temperature: %5.1f'c\r\n", adc_getVoltage(adc1, adcPin));
		delay_ms(1000);	
	}
}
//------------------------------------------------------------------------------

