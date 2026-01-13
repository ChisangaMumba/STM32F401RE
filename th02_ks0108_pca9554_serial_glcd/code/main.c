//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "./assets/gpio/gpio_c.h"
#include "./assets/delay/delay_c.h"
#include "./assets/th02/th02_c.h"
#include "./assets/ks0108/ks0108_c.h"
//------------------------------------------------------------------------------
char str[30];
//------------------------------------------------------------------------------
int main(void)
{			
	HSI_init();				 // Set Clock to 16Mhz	
	ks0108_init();
	th02_init(); 
	
	ks0108_print(0, 12, font2, "*TH02 Sensor*"); 
	ks0108_print(2,  0, font1, "Device ID: 0x%x", th02_readDevice(DEV_ID_REG));
	ks0108_print(4,  0, font1, "Readings:");
	
	while(1)
	{ 
		ks0108_print(5, 0, font1, "Humd:%7.2f%c", th02_getHumd(), '%');		
		ks0108_print(6, 0, font1, "Temp:%7.2f°C", th02_getTemp()); 

		delay_ms(100);
	}
}
//------------------------------------------------------------------------------
