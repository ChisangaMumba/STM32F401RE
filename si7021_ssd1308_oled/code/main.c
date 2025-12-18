//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/si7021/si7021_c.h"
#include "./assets/ssd1308/ssd1308_c.h"
//------------------------------------------------------------------------------
char str[20];
uint16_t rawHum, rawTemp;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	ssd1308_init();
	si7021_init(RES_3); // RH:11bit, Temp:11bit
	
	ssd1308_print(0, 30, "SI7021 sensor");
	ssd1308_print(4,  0, "Readings:");
	sprintf(str, "Config: %04x",  si7021_readConfig());
	ssd1308_print(2, 0, str);
	
	while(1)
	{ 			
		rawHum = si7021_readConv(HUMD_NO_HOLD_CMD);
		rawTemp = si7021_readConv(TEMP_NO_HOLD_CMD);
		
		if(rawHum != 0xFFFF)
		{
			sprintf(str, "Humd:%7.2f%c", si7021_calcHumd(rawHum), '%');
			ssd1308_print(5, 0, str);
		}
		
		if(rawTemp != 0xFFFF)
		{
			sprintf(str, "Temp:%7.2f°C", si7021_calcTemp(rawTemp));
			ssd1308_print(6, 0, str);
		}
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
