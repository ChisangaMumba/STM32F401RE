//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bmp280/bmp280_c.h"
#include "./assets/max6951/max6951_c.h"
//------------------------------------------------------------------------------
char str[20];
bmp280_calib_coefs calib;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				// Set Clock to 16Mhz	
	max6951_init(1);	// Number of chips connected in parallel
	bmp280_init(&calib, osrs_t_x1, osrs_p_x1, normal_mode); // Initialize BMP280 with 1x oversampling for both temperature and pressure in normal mode

	while(1)
	{		 
		sprintf(str, "%7.1f°C",  bmp280_getTemp(calib)); 
		max6951_displayText(str);
		
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------

