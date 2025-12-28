//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bme280/bme280_c.h"
#include "./assets/ks0108/ks0108_c.h"
//------------------------------------------------------------------------------
char str[30];
bme280_calib_coefs calib;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	ks0108_init();
	bme280_init(&calib, osrs_t_x1, osrs_p_x1, osrs_h_x1, normal_mode); // Initialize BME280 with 1x oversampling for temperature, pressure, & humidity in normal mode
	
	ks0108_print(0, 12, font2, "Bme280 Sensor"); 
	
	while(1)
	{
		ks0108_print(2, 0, font1, "Pres:%8.2fhPa", bme280_getPres(calib)); 
		ks0108_print(4, 0, font1, "Temp:%7.1f°C", bme280_getTemp(calib)); 
		ks0108_print(6, 0, font1, "Humd:%7.1f%c", bme280_getHum(calib), '%');

		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
