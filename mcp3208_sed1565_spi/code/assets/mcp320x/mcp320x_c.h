#ifndef MCP320X_C
#define	MCP320X_C
//------------------------------------------------------------------------------
#include "mcp320x_h.h"
//------------------------------------------------------------------------------
void mcp320x_init(void)
{
	spi_init();
	
	pinMode(CS2, OUTPUT, PUSH_PULL);
	
	digitalWrite(CS2, HIGH);		// CS2 = 1; // deselect initially
}
//-----------------------------Returns 0..1024----------------------------------
uint16_t mcp320x_read(uint8_t mode, uint8_t chn)
{
	uint8_t data[2];
	uint16_t cmd = ((mode << 8) | (channel[chn] << 6));
	
	digitalWrite(CS2, LOW);		// CS2 = 0;                     

	spi_write(cmd >> 4);
	data[1] = spi_read();			// MSB
  data[0] = spi_read();			// LSB

  digitalWrite(CS2, HIGH);	// CS2 = 1;
  
	return ((data[1] << 4) | (data[0] >> 4));
}
//------------------------------------------------------------------------------
float mcp320x_getVoltage(uint8_t mode, uint8_t chn)
{
	uint16_t rawData = mcp320x_read(mode, chn);
	
	return calcVoltage(rawData);
}
//------------------------------------------------------------------------------
float calcVoltage(uint16_t adcValue)
{
	float Vin = (float)(adcValue * 5)/4096; //Vin = (Code * Vref)/4096. See MCP3204 datasheet page 17
	
	return Vin;
}
//------------------------------------------------------------------------------
#endif
