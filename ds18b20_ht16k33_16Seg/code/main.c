//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ds18b20/ds18b20_c.h"
#include "./assets/ht16k33/ht16k33_c.h"
//------------------------------------------------------------------------------
char str[15];
float temp = 0.0f;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 	// Set Clock to 16Mhz	
	ht16k33_init(15);   // Initialize HT16K33 with brightness level 15 
	ds18b20_init();

	while(1)
	{ 
		temp = ds18b20_readTemp(); 
		
		sprintf(str, "%6.1f°C", temp); 
		ht16k33_displayText(str);
		
		delay_ms(500);
	}
}
//------------------------------------------------------------------------------

