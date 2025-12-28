//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/bmp280/bmp280_c.h"
#include "./assets/sevenSeg/sevenSeg_c.h"
//------------------------------------------------------------------------------
bmp280_calib_coefs calib;
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();	// Set Clock to 16Mhz	
	sevenSeg_init();
	bmp280_init(&calib, osrs_t_x1, osrs_p_x1, normal_mode); // Initialize BMP280 with 1x oversampling for both temperature and pressure in normal mode
		
	while(1)
	{ 	
		sevenSeg_print("%8.2f°C", bmp280_getTemp(calib));
	}
}
//------------------------------------------------------------------------------
