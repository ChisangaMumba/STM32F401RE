#ifndef MCP330X_C
#define	MCP330X_C
//------------------------------------------------------------------------------
#include "mcp330x_h.h"
//------------------------------------------------------------------------------
void mcp330x_init(void)
{
	spi_init();
	
	pinMode(CS2, OUTPUT, PUSH_PULL);
	
	digitalWrite(CS2, HIGH);	// CS2 = 1; // deselect initially
}
//-----------------------------Returns 0..4096----------------------------------
uint16_t mcp330x_read(uint8_t mode, uint8_t chn)
{
	uint8_t data[2];
	uint16_t cmd = ((mode << 8) | (channel[chn] << 7));
	
	digitalWrite(CS2, LOW);		// CS2 = 0;                     

	spi_write(cmd >> 4);
	data[1] = spi_read();			// MSB
  data[0] = spi_read();			// LSB

  digitalWrite(CS2, HIGH);	// CS2 = 1;
  
	return ((data[1] << 4) | (data[0] >> 4));
}
//------------------------------------------------------------------------------
float mcp330x_getVoltage(uint8_t mode, uint8_t chn)
{
	uint16_t rawData = mcp330x_read(mode, chn);
	
	return calcVoltage(rawData);
}
//------------------------------------------------------------------------------
float calcVoltage(uint16_t adcValue)
{
	float Vin = (float)(adcValue * 5)/4096; // Vin = (Code * Vref)/4096.
	
	return Vin;
}
//------------------------------------------------------------------------------
#endif
