//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bme280/bme280_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
char str[90];
float temp, humd, pres;
bme280_calib_coefs calib; // Calibration coefficients structure
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 		// Set Clock to 16Mhz	
	lcd_init();
	bme280_init(&calib, osrs_t_x1, osrs_p_x1, osrs_h_x1, normal_mode); // Initialize BME280 with 1x oversampling for temperature, pressure, & humidity in normal mode
		
	lcd_string(0, 7, "BME280");
	
	while(1)
	{ 	
		temp = bme280_getTemp(calib);
		humd = bme280_getHum(calib);
		pres = bme280_getPres(calib);
		
		sprintf(str, "Pres:%8.2fhPa", pres);
		lcd_string(1, 0, str);
		
		sprintf(str, "Temp:%7.1f°C", temp);
		lcd_string(2, 0, str);
		
		sprintf(str, "Humd:%7.1f%c", humd, '%');
		lcd_string(3, 0, str);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
