//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/sht7x/sht7x_c.h"
#include "./assets/sed1565/sed1565_c.h"
//------------------------------------------------------------------------------
char str[35];
float temp = 0.0f;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	sed1565_init();
	sht7x_init();			 // Internal pull-up is enabled within the gpio configurations, hence no external resistor 
	
	sed1565_print(0, 25, "SED1565 display");
	sed1565_print(2, 32,  "SHT71 Sensor");
	
	while(1)
	{
		temp = sht7x_getTemp();
		
	 	sprintf(str, "Humidity:%6.2f%c", sht7x_getHumd(temp), '%');
		sed1565_print(5, 0, str); 
		
		sprintf(str, "Temper:%6.2f°C", temp);
		sed1565_print(7, 0, str);
		
		delay_ms(500);
	}
}
//------------------------------------------------------------------------------


