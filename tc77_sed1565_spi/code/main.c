//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/tc77/tc77_c.h"
#include "./assets/sed1565/sed1565_c.h"
//------------------------------------------------------------------------------
char str[35];
float temp = 0.0f;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	sed1565_init();
	tc77_init();
	
	sed1565_print(0, 25, "SED1565 display");
	sed1565_print(2, 32,  "TC77 Sensor");
	
	while(1)
	{
		temp = tc77_getTemp();
		
		sprintf(str, "Temper:%6.2f°C", temp);
		sed1565_print(4, 0, str);
		
		delay_ms(500);
	}
}
//------------------------------------------------------------------------------


