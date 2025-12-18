//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/dht11/dht11_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
char str[20];
dht11_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set system Clock to 16Mhz	
	lcd_init();
	
	while(1)
	{ 	
		if(dht11_getSensorData(&sensor))
		{	
			sprintf(str, "Humd:%3i%c", sensor.humidity, '%');
			lcd_string(0, 0, str);
			
			sprintf(str, "Temp:%3i°C", sensor.temperature);
			lcd_string(1, 0, str);
		}
		else
				{
					lcd_string(0, 0, "Error");
				}
				
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------
