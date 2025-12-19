//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/htu21/htu21_c.h"
#include "./assets/pcd8544/pcd8544_c.h"
//------------------------------------------------------------------------------
char str[30];
uint16_t rawHumd, rawTemp;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();			// Set Clock to 16Mhz	
	pcd8544_init();
	htu21_init(RES_3);		// Internal pull-up is enabled within the gpio configurations, hence no external resistor
	
	pcd8544_print(0, 2, "Nokia 5510");
	pcd8544_print(1, 1, "HTU21 Sensor");
	
	while(1)
	{ 			
		rawHumd = htu21_readConv(HUMD_NO_HOLD_CMD);
		rawTemp = htu21_readConv(TEMP_NO_HOLD_CMD);
		
		if(rawHumd != 0xFFFF)
		{
			sprintf(str, "Humd:%6.2f%c", htu21_calcHumd(rawHumd), '%');
			pcd8544_print(3, 0, str); 
		}
		
		if(rawTemp != 0xFFFF)
		{
			sprintf(str, "Temp:%6.2f°C", htu21_calcTemp(rawTemp));
			pcd8544_print(5, 0, str);
		}
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
