//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/sht1x/sht1x_c.h"
#include "./assets/lcd4/lcd4_c.h"
//------------------------------------------------------------------------------
char str[30];
float temp = 0.0f;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	lcd_init();
	sht1x_init();			 // Internal pull-up is enabled within the gpio configurations, hence no external resistor 
	
	while(1)
	{
		temp = sht1x_getTemp();
		
	 	sprintf(str, "Humd:%6.2f%c", sht1x_getHumd(temp), '%');
		lcd_string(0, 0, str); 
		
		sprintf(str, "Temp:%6.2f°C", temp);
		lcd_string(1, 0, str);
		
		delay_ms(500);
	}
}
//------------------------------------------------------------------------------


