//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bme280/bme280_c.h"
#include "./assets/lcd_serial/lcd_serial_c.h"
//------------------------------------------------------------------------------
char str[70];
bme280_calib_coefs calib;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	lcd_init();
	
	bme280_init(&calib, osrs_t_x1, osrs_p_x1, osrs_h_x1, normal_mode); // Initialize BME280 with 1x oversampling for temperature, pressure, & humidity in normal mode
	lcd_string(0, 2, "Bme280 Sensor");
	
	while(1)
	{ 		
		sprintf(str, "Pres:%8.2fhPa", bme280_getPres(calib));			// Pressure
		lcd_string(1, 0, str);
		
		sprintf(str, "Temp:%7.1f°C", bme280_getTemp(calib));			// Temperature
		lcd_string(2, 0, str);
		
		sprintf(str, "Humd:%7.1f%c", bme280_getHum(calib), '%');	// Humidity
		lcd_string(3, 0, str);
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
