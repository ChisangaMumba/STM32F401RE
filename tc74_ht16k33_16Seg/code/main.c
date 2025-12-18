//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tc74/tc74_c.h"
#include "./assets/ht16k33/ht16k33_c.h"
//------------------------------------------------------------------------------
char str[15];
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 	// Set Clock to 16Mhz	
	ht16k33_init(15);   // Initialize HT16K33 with brightness level 15 
	tc74_init(NORMAL_MODE);  // Initialize TC74 with normal mode.

	while(1)
	{ 		
		sprintf(str, "%6i°C", tc74_readTemp()); 
		ht16k33_displayText(str);
		
		delay_ms(500);
	}
}
//------------------------------------------------------------------------------

