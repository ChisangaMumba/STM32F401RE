//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/ads111x/ads111x_c.h"
#include "./assets/ssd1306/ssd1306_c.h"
//------------------------------------------------------------------------------
char str[20];
uint16_t rawData;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				// Set Clock to 16Mhz	
	ssd1306_init();
	ads111x_init(); 
	
	ssd1306_print(0, 10, font2, "ADS1115 sensor");
	ssd1306_print(2,  0, font1, "Single Mode:");
	
	while(1)
	{ 	
		ssd1306_print(4, 0, font1, "CH0:%7.2f°C", ads111x_getVoltage(SINGLE_MODE, 0) * 100);
		ssd1306_print(5, 0, font1, "CH1:%7.2f°C", ads111x_getVoltage(SINGLE_MODE, 1) * 100);
		ssd1306_print(6, 0, font1, "CH2:%7.2f°C", ads111x_getVoltage(SINGLE_MODE, 2) * 100);
		ssd1306_print(7, 0, font1, "CH3:%7.2f°C", ads111x_getVoltage(SINGLE_MODE, 3) * 100);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
