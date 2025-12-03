#ifndef ADC_H
#define ADC_H
//------------------------------------------------------------------------------
#include "stm32f4xx.h"
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
void adc_init(uint8_t adcNum, uint8_t portPin);
ADC_TypeDef * adc_getAdcType(uint8_t adcNum);
uint8_t adc_getChannel(uint8_t adcNum, uint16_t portPin);
uint32_t adc_rawValue(uint8_t adcNum, uint16_t portPin);
float adc_getVoltage(uint8_t adcNum, uint16_t portPin);
//------------------------------------------------------------------------------
enum ADCs { adc1 = 0, adc2, adc3 };
//------------------------------------------------------------------------------
const uint8_t CH_ROWS = 48;
const uint8_t CH_COLS = 3;
static const uint8_t CHANNEL_MAP[48][3] = 
{
//{ PIN, ADCx, Channel }	
	{ PF3, adc3,  9 },
	{ PF4, adc3, 14 },
	{ PF5, adc3, 15 },
	{ PF6, adc3,  4 },
	{ PF7, adc3,  5 },
	{ PF8, adc3,  6 },
	{ PF9, adc3,  7 },
	{ PF10,adc3,  8 },
	{ PC0, adc1, 10 },
	{ PC0, adc2, 10 },
	{ PC0, adc3, 10 },
	{ PC1, adc1, 11 },
	{ PC1, adc2, 11 },
	{ PC1, adc3, 11 },
	{ PC2, adc1, 12 },
	{ PC2, adc2, 12 },
	{ PC2, adc3, 12 },
	{ PC3, adc1, 13 },
	{ PC3, adc2, 13 },
	{ PC3, adc3, 13 },
	{ PA0, adc1,  0 },
	{ PA0, adc2,  0 },
	{ PA0, adc3,  0 },
	{ PA1, adc1,  1 },
	{ PA1, adc2,  1 },
	{ PA1, adc3,  1 },
	{ PA2, adc1,  2 },
	{ PA2, adc2,  2 },
	{ PA2, adc3,  2 },
	{ PA3, adc1,  3 },
	{ PA3, adc2,  3 },
	{ PA3, adc3,  3 },
	{ PA4, adc1,  4 },
	{ PA4, adc2,  4 },
	{ PA5, adc1,  5 },
	{ PA5, adc2,  5 },
	{ PA6, adc1,  6 },
	{ PA6, adc2,  6 },
	{ PA7, adc1,  7 },
	{ PA7, adc2,  7 },
	{ PC4, adc1, 14 },
	{ PC4, adc2, 14 },
	{ PC5, adc1, 15 },
	{ PC5, adc2, 15 },
	{ PB0, adc1,  8 },
	{ PB0, adc2,  8 },
	{ PB1, adc1,  9 },
	{ PB1, adc2,  9 },
};
//------------------------------------------------------------------------------
/*
		Channel				ADC1		ADC2		ADC3
ADC Channel 0			PA0			PA0			PA0
ADC Channel 1			PA1			PA1			PA1
ADC Channel 2			PA2			PA2			PA2
ADC Channel 3			PA3			PA3			PA3
ADC Channel 4			PA4			PA4			PF6
ADC Channel 5			PA5			PA5			PF7
ADC Channel 6			PA6			PA6			PF8
ADC Channel 7			PA7			PA7			PF9
ADC Channel 8			PB0			PB0			PF10
ADC Channel 9			PB1			PB1			PF3
ADC Channel 10		PC0			PC0			PC0
ADC Channel 11		PC1			PC1			PC1
ADC Channel 12		PC2			PC2			PC2
ADC Channel 13		PC3			PC3			PC3
ADC Channel 14		PC4			PC4			PF4
ADC Channel 15		PC5			PC5			PF5
*/
//------------------------------------------------------------------------------
#endif		/* ADC_H */
