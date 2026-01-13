//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/th02/th02_c.h"
#include "./assets/fourteenSeg/fourteenSeg_c.h"
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	fourteenSeg_init();
	th02_init();	
		
	while(1)
	{ 	
		fourteenSeg_print("%8.1f°C", th02_getTemp());
		
		//delay_us(50);
	}
}
//------------------------------------------------------------------------------
