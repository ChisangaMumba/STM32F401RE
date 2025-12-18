//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/dht11/dht11_c.h"
#include "./assets/max6953/max6953_c.h"
//------------------------------------------------------------------------------
char str[12];
dht11_t sensor;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				// Set Clock to 16Mhz	
	max6953_init();	
	
	while(1)
	{
		if(dht11_getSensorData(&sensor))
		{
			sprintf(str, "%2i°C", sensor.temperature);
			max6953_displayText(str);
		}
		else
				max6953_displayText(" Err");
		//delay_ms(1000);
	}
}
//------------------------------------------------------------------------------
