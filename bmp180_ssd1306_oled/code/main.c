//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bmp180/bmp180_c.h"
#include "./assets/ssd1306/ssd1306_c.h"
//------------------------------------------------------------------------------
char str[30];
float press, temp;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	ssd1306_init();
	bmp180_init();
	
	ssd1306_print(0, 45, "BMP180");
	
	while(1)
	{ 
		temp = bmp180_getTemp();
		//press = bmp180_getPress(OSS_3);
		
		//sprintf(str, "Press:%6.1fhPa%c", press, '%');
		//ssd1306_print(2, 0, str);
		
		sprintf(str, "Temp:%6.1f°C", temp);
		ssd1306_print(3, 0, str);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
