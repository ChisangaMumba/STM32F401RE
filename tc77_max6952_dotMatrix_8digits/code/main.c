//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tc77/tc77_c.h"
#include "./assets/max6952/max6952_c.h"
//------------------------------------------------------------------------------
char str[12];
float temp = 0.0f;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				// Set Clock to 16Mhz	
	max6952_init(2);	// Number of chips in daisy chain
	tc77_init();

	while(1)
	{
		temp = tc77_getTemp(); 
		
		sprintf(str, "%6.1f°C", temp); 
		max6952_displayText(str);

		delay_ms(500);
	}
}
//------------------------------------------------------------------------------

