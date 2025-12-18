//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bmp280/bmp280_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
char str[20];
bmp280_calib_coefs calib;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	lcd_init();
	bmp280_init(&calib, osrs_t_x1, osrs_p_x1, normal_mode); // Initialize BMP280 with 1x oversampling for both temperature and pressure in normal mode

	while(1)
	{ 		
		sprintf(str, "Pres:%7.2fhPa", bmp280_getPres(calib));
		lcd_string(0, 0, str);
		
		sprintf(str, "Temp:%5.1f°C", bmp280_getTemp(calib));
		lcd_string(1, 0, str);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
