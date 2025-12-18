//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tc77/tc77_c.h"
#include "./assets/max6950/max6950_c.h"
//------------------------------------------------------------------------------
char str[20];
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				// Set Clock to 16Mhz	
	max6950_init(2);	// Number of chips connected in parallel
	tc77_init();

	while(1)
	{		 
		sprintf(str, "%7.1f°C", tc77_getTemp()); 
		max6950_displayText(str);
		
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------

