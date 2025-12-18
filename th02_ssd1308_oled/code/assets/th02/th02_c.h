#ifndef TH02_C
#define	TH02_C
//------------------------------------------------------------------------------
#include "th02_h.h"
//------------------------------------------------------------------------------
void th02_init(void)
{
	i2c_init(); 
}
//------------------------------------------------------------------------------
void th02_command(uint8_t command)
{
  i2c_start();                      
  
  i2c_write((TH02_ADDR << 1) | 0);  // 0 = Write             
	i2c_write(CONFIG_REG);
	i2c_write(command);
	
	i2c_stop();
	
	// Wait for the sensor to complete measurement (adjust delay as necessary).
	delay_ms(50);				//  35ms max in Normal mode, 18ms max in Fast mode
}
//------------------------------------------------------------------------------
uint8_t th02_readDevice(uint8_t command)
{
	uint8_t data = 0;
	
  i2c_start(); 
	
  i2c_write((TH02_ADDR << 1) | 0);  // 0 = Write  
  i2c_write(command);
	i2c_restart();
  i2c_write((TH02_ADDR << 1) | 1);  // 1 = Read 	
  data = i2c_read(NACK);						
	
  i2c_stop();
	
	return data;
}
//------------------------------------------------------------------------------
uint16_t th02_readConv(uint8_t command)
{
  uint8_t data[2] = {0, 0}; 
  
	th02_command(command);
	
  i2c_start(); 
	
  i2c_write((TH02_ADDR << 1) | 0);  // 0 = Write  
  i2c_write(0x01);
	i2c_restart();
  i2c_write((TH02_ADDR << 1) | 1);  // 1 = Read 	
	data[1] = i2c_read(ACK);					// MSB
  data[0] = i2c_read(NACK);					// LSB
	
  i2c_stop();
  
	return (data[1] << 8) + data[0];
}
//------------------------------------------------------------------------------
float th02_getHumd(void)
{
	uint16_t rawHumd = th02_readConv(HUMD_CMD) >> 4;

	return ((float)rawHumd / 16.0f) - 24.0f;
}
//------------------------------------------------------------------------------
float th02_getTemp(void)
{
	uint16_t rawTemp = th02_readConv(TEMP_CMD) >> 2;
	
	return ((float)rawTemp / 32.0f) - 50.0f;
}
//------------------------------------------------------------------------------
#endif
