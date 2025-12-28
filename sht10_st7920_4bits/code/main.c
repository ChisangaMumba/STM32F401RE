//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/sht1x/sht1x_c.h"
#include "./assets/st7920/st7920_c.h"
//------------------------------------------------------------------------------
char str[30];
sht1x_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	st7920_init();
	sht1x_init();			 // Internal pull-up is enabled within the gpio configurations, hence no external resistor
	
	st7920_print(0, 1, "SHT10 Sensor");
	
	while(1)
	{
		sht1x_setSensor(&sensor);
	
		st7920_print(2, 0, "Humd:%6.2f%c", sensor.humidity, '%');
		st7920_print(3, 0, "Temp:%6.2f°C", sensor.temperature);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------


