//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/th02/th02_c.h"
#include "./assets/ssd1308/ssd1308_c.h"
//------------------------------------------------------------------------------
char str[30];
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	ssd1308_init();
	th02_init(); 
	
	ssd1308_print(0, 30, "TH02 sensor");
	ssd1308_print(4,  0, "Readings:");
	sprintf(str, "Device ID: 0x%x",  th02_readDevice(DEV_ID_REG));
	ssd1308_print(2, 0, str);
	
	while(1)
	{ 			
		sprintf(str, "Humd:%7.2f%c", th02_getHumd(), '%');
		ssd1308_print(5, 0, str);

		sprintf(str, "Temp:%7.2f°C", th02_getTemp());
		ssd1308_print(6, 0, str);

		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
