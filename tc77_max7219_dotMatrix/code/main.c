//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tc77/tc77_c.h"
#include "./assets/max7219/max7219_c.h"
//------------------------------------------------------------------------------
char str[12];
float temp = 0.0f;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				// Set Clock to 16Mhz	
	max7219_init(5);	// Number of chips in daisy chain
	tc77_init();

	while(1)
	{
		temp = tc77_getTemp(); 
		
		sprintf(str, "%5.1f°C", temp); 
		max7219_displayText(str);

		delay_ms(2000);
	}
}
//------------------------------------------------------------------------------

