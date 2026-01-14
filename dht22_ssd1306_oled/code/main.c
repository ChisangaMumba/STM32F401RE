//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/dht22/dht22_c.h"
#include "./assets/ssd1306/ssd1306_c.h"
//------------------------------------------------------------------------------
dht22_t sensor;
//------------------------------------------------------------------------------
int main(void)
{			
	clock_init();				// Set Clock to 16Mhz	
	ssd1306_init(); 
	
	ssd1306_print(0, 10, font2, "DHT22 sensor");
	ssd1306_print(1,  0, font1, "Readings:");
	
	while(1)
	{ 	
		if(dht22_getSensorData(&sensor))
		{
			ssd1306_print(2, 0, font1, "Humd:%7.1f%c", sensor.humidity, '%');
			ssd1306_print(3, 0, font1, "Temp:%7.1f°C", sensor.temperature);
		}
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
