//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tc72/tc72_c.h"
#include "./assets/max6954/max6954_c.h"
//------------------------------------------------------------------------------
char str[15];
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 // Set Clock to 16Mhz	
	max6954_init();
	tc72_init();

	while(1)
	{		 
		sprintf(str, "%7.1f°C", tc72_getTempr2()); 
		max6954_displayText(str);
	}
}
//------------------------------------------------------------------------------

