//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/htu21/htu21_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
char str[20];
uint16_t rawHumd, rawTemp;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	lcd_init();
	htu21_init(RES_3);
	
	while(1)
	{ 
		rawHumd = htu21_readConv(HUMD_NO_HOLD_CMD);
		rawTemp = htu21_readConv(TEMP_NO_HOLD_CMD);
		
		if(rawHumd != 0xFFFF)
		{
			sprintf(str, "Humd:%7.2f%c", htu21_calcHumd(rawHumd), '%');
			lcd_string(0, 0, str);
		}
			
		if(rawTemp != 0xFFFF)
		{
			sprintf(str, "Temp:%7.2f°C", htu21_calcTemp(rawTemp));
			lcd_string(1, 0, str);
		}		
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
