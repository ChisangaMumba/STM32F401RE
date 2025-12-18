#ifndef MCP300X_C
#define	MCP300X_C
//------------------------------------------------------------------------------
#include "mcp300x_h.h"
//------------------------------------------------------------------------------
void mcp300x_init(void)
{
	spi_init();
	
	pinMode(CS2, OUTPUT, PUSH_PULL);
	
	digitalWrite(CS2, HIGH);		// CS2 = 1; // deselect initially
}
//-----------------------------Returns 0..1024----------------------------------
uint16_t mcp300x_read(uint8_t mode, uint8_t chn)
{
	uint8_t data[2];
	uint8_t cmd = (START | mode | channel[chn]);
	
	digitalWrite(CS2, LOW);					// CS2 = 0;                     

	spi_write(cmd);
	data[1] = spi_read() & 0x1F;		// MSB
  data[0] = spi_read();					// LSB

  digitalWrite(CS2, HIGH);				// CS2 = 1;
  
	return ((data[1] << 4) | (data[0] >> 4));
}
//------------------------------------------------------------------------------
float mcp300x_getVoltage(uint8_t mode, uint8_t chn)
{
	uint16_t rawData = mcp300x_read(mode, chn);
	
	return calcVoltage(rawData);
}
//------------------------------------------------------------------------------
float calcVoltage(uint16_t adcValue)
{
	float Vin = (float)(adcValue * 5)/1024; //Vin = (Code * Vref)/1024. See MCP3004 datasheet page 17
	
	return Vin;
}
//------------------------------------------------------------------------------
#endif
