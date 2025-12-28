//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bme280/bme280_c.h"
#include "./assets/sed1565/sed1565_c.h"
//------------------------------------------------------------------------------
char str[70];
bme280_calib_coefs calib;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	sed1565_init();
	bme280_init(&calib, osrs_t_x1, osrs_p_x1, osrs_h_x1, normal_mode); // Initialize BME280 with 1x oversampling for temperature, pressure, & humidity in normal mode
	
	sed1565_print(1, 20, "Bme280 Sensor");
	
	while(1)
	{
		sed1565_print(3, 0, "Pres:%8.2fhPa", bme280_getPres(calib));
		sed1565_print(5, 0, "Temp:%7.1f°C", bme280_getTemp(calib));
		sed1565_print(7, 0, "Humd:%7.1f%c", bme280_getHum(calib), '%');
		
		delay_ms(100);
	}
}
//------------------------------------------------------------------------------


