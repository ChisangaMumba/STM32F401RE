//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tc72/tc72_c.h"
#include "./assets/max6950/max6950_c.h"
//------------------------------------------------------------------------------
char str[12];
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 // Set Clock to 16Mhz	
	max6950_init(SCAN_ALL_DIGITS);
	tc72_init();

	while(1)
	{		 
		sprintf(str, "%5.1fC", tc72_getTempr2()); 
		max6950_displayText(str);
	}
}
//------------------------------------------------------------------------------

