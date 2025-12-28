//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tc77/tc77_c.h"
#include "./assets/sevenSeg/sevenSeg_c.h"
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	sevenSeg_init();
	tc77_init();
	
	while(1)
	{ 				
		sevenSeg_print("%5.1f", tc77_getTemp());
	}
}
//------------------------------------------------------------------------------
