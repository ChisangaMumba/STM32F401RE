//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bme280/bme280_c.h"
#include "./assets/max7219/max7219_c.h"
//------------------------------------------------------------------------------
char str[12];
bme280_calib_coefs calib;
//------------------------------------------------------------------------------
int main(void)
{	  
	HSI_init();				 	// Set Clock to 16Mhz	
	max7219_init(1);		// Number of chips connected in daisy chain
	bme280_init(&calib, osrs_t_x1, osrs_p_x1, osrs_h_x1, normal_mode); // Initialize BME280 with 1x oversampling for temperature, pressure, & humidity in normal mode

	while(1)
	{		
		sprintf(str, "%7.2f°C", bme280_getTemp(calib)); 
		max7219_displayText(str);
		
		delay_ms(200);
	}
}
//------------------------------------------------------------------------------
