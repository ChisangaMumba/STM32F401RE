//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bme280/bme280_c.h"
#include "./assets/st7920/st7920_c.h"
//------------------------------------------------------------------------------
char str[70];
bme280_calib_coefs calib;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	st7920_init();
	bme280_init(&calib, osrs_t_x1, osrs_p_x1, osrs_h_x1, normal_mode); // Initialize BME280 with 1x oversampling for temperature, pressure, & humidity in normal mode
	
	st7920_print(0, 1, "Bme280 Sensor");
	
	while(1)
	{
		st7920_print(1, 0, "Pres:%8.2fhPa", bme280_getPres(calib));
		st7920_print(2, 0, "Temp:%7.1f°C", bme280_getTemp(calib));
		st7920_print(3, 0, "Humd:%7.1f%c", bme280_getHum(calib), '%');
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------


