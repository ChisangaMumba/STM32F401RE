//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/sht2x/sht2x_c.h"
#include "./assets/sixteenSeg/sixteenSeg_c.h"
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	sixteenSeg_init();
	sht2x_init();
	
	while(1)
	{ 				
		sixteenSeg_print("%7.2f°C", sht2x_getTemp());
	}
}
//------------------------------------------------------------------------------
