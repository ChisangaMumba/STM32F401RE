#ifndef ADC_C
#define ADC_C
//------------------------------------------------------------------------------
#include "adc_h.h"
//-----------------------------------------------------------------------------
void adc_init(uint8_t adcNum, uint8_t portPin)
{	
	ADC_TypeDef * ADCx;
	pinMode(portPin, ANALOG, PUSH_PULL);  	// Analogue input pin
	
	RCC->APB2ENR |= 0x01 << (8 + adcNum);   // Enable ADCx clock. ADC2 & ADC3 NOT available in STM32F401xB/C and STM32F401xD/E.
	
	ADCx = adc_getAdcType(adcNum);
	ADCx->SQR3 = adc_getChannel(adcNum, portPin);  // Regular Sequence Register 3	
	
	// ADC Control Register 2
	ADCx->CR2 = 0;  												// Reset the whole register.  
	ADCx->CR2 |=  1;												// Enable ADC 
	while((ADCx->CR2 & 1) == 0);						// Wait for ADC to turn on fully
}
//-----------------------------------------------------------------------------
// ADCx. ADC2 & ADC3 NOT available in STM32F401xB/C and STM32F401xD/E.
//-----------------------------------------------------------------------------
ADC_TypeDef * adc_getAdcType(uint8_t adcNum)
{
	ADC_TypeDef * ADCx;
	
	switch(adcNum)
	{
		case (0): ADCx = ADC1; break;
		#ifdef ADC2
		case (1): ADCx = ADC2; break;
		#endif
		#ifdef ADC3
		case (2): ADCx = ADC3; break;
		#endif
	}
	
	return ADCx;
}
//-----------------------------------------------------------------------------
uint8_t adc_getChannel(uint8_t adcNum, uint16_t portPin)
{
	uint8_t channel = 0;
	
	for(uint8_t i = 0; i < CH_ROWS; i++)
	{
		if((portPin == CHANNEL_MAP[i][0]) && (adcNum == CHANNEL_MAP[i][1]))
		{
			channel = CHANNEL_MAP[i][2]; break;
		}
	}
	
	return channel;
}
//---------------------------------------------------------------------------
uint32_t adc_rawValue(uint8_t adcNum, uint16_t portPin)
{
	uint32_t result = 0;
	uint8_t channel = 0;
	ADC_TypeDef * ADCx;
	
	ADCx = adc_getAdcType(adcNum);
	channel = adc_getChannel(adcNum, portPin);
	
	// if channel changed, reassign to new channel
	if(channel != ADCx->SQR3)
	{
		ADCx->SQR3 = channel;
	}
	
	ADCx->CR2 |= 1UL << 30;		// Start conversion
	while(!(ADCx->SR & 2));  	// Wait for conversion to complete
	result = ADCx->DR;       	// Read conversion
	
	return result;
}
//---------------------------------------------------------------------------
float adc_getVoltage(uint8_t adcNum, uint16_t portPin)
{
	float voltage = 0.0f;
	
	uint32_t rawValue = adc_rawValue(adcNum, portPin);
	voltage = (float)rawValue / 4095 * 330;
  
	return voltage;
}
//------------------------------------------------------------------------------
#endif	/* ADC_C */

