//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tc77/tc77_c.h"
#include "./assets/bargraph/bargraph_c.h"
#include "./assets/max7219/max7219_c.h"
//------------------------------------------------------------------------------
float temp = 0.0f;
//------------------------------------------------------------------------------
int main(void)
{	  
	clock_init();				// Set Clock to 16Mhz	
	max7219_init(1);		// Number of chips connected in daisy chain
	tc77_init();
	bargraph_init();

	while(1)
	{
		temp = tc77_getTemp();
		
		max7219_print( "%7.2f°C", temp);
		bargraph_write((uint16_t) temp);
	}
}
//------------------------------------------------------------------------------
