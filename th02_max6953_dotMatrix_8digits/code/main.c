//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/th02/th02_c.h"
#include "./assets/max6953/max6953_c.h"
//------------------------------------------------------------------------------
char str[12];
float temp = 0.0f;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				// Set Clock to 16Mhz	
	max6953_init(2);	// Number of chips in daisy chain
	th02_init();
	
	while(1)
	{
		temp = th02_getTemp(); 
		
		sprintf(str, "%6.1f°C", temp); 
		max6953_displayText(str);
		
		//delay_ms(500);
	}
}
//------------------------------------------------------------------------------

