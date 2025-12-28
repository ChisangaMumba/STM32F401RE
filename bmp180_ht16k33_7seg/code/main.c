//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ht16k33/ht16k33_c.h"
#include "./assets/bmp180/bmp180_c.h"
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();					// Set Clock to 16Mhz	
	ht16k33_init(15);		// Valid brightness values from 0 - 15
	bmp180_init();
	
	while(1)
	{ 				
		ht16k33_print("%7.1f°C", bmp180_getTemp());
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
