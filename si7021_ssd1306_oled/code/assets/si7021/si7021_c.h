#ifndef SI7021_C
#define	SI7021_C
//------------------------------------------------------------------------------
#include "si7021_h.h"
//------------------------------------------------------------------------------
void si7021_init(uint8_t res)
{	
	i2c_init(); 
	
	si7021_command(RESET_CMD);
	delay_ms(30);
	si7021_writeConfig(res);
}
//------------------------------------------------------------------------------
uint8_t si7021_readConfig(void)
{
	uint8_t data = 0;

	i2c_start(); 

	i2c_write((SI7021_ADDR << 1) | 0);  // 0 = Write  
	i2c_write(READ_CONFIG_CMD);
	i2c_restart();
	i2c_write((SI7021_ADDR << 1) | 1);  // 1 = Read 	
	data = i2c_read(NACK);						

	i2c_stop();

	return data;
}
//------------------------------------------------------------------------------
void si7021_writeConfig(uint8_t data)
{	
	uint8_t config = si7021_readConfig();

	i2c_start(); 

	i2c_write((SI7021_ADDR << 1) | 0);  // 0 = Write  
	i2c_write(WRITE_CONFIG_CMD);						
	i2c_write(data | config);

	i2c_stop();
}
//------------------------------------------------------------------------------
void si7021_command(uint8_t command)
{
	i2c_start();                      

	i2c_write((SI7021_ADDR << 1) | 0);  // 0 = Write             
	i2c_write(command);

	i2c_stop(); 
}
//------------------------------------------------------------------------------
uint16_t si7021_readConv(uint8_t command)
{
	uint8_t data[3] = {0, 0, 0}; 

	si7021_command(command);
	delay_ms(30);				
		
	i2c_start();

	i2c_write((SI7021_ADDR << 1) | 1);  // 1 = Read 	
	data[0] = i2c_read(ACK);						// MSB
	data[1] = i2c_read(ACK);						// LSB
	data[2] = i2c_read(NACK);						// CRC

	i2c_stop();

	return (si7021_isDataValid(data)) ? (data[0] << 8) + data[1] : 0xFFFF;
}
//------------------------------------------------------------------------------
float si7021_calcHumd(uint16_t rawHumd)
{
	return ( ((float)rawHumd *125) / 65536 ) - 6;
}
//------------------------------------------------------------------------------
float si7021_calcTemp(uint16_t rawTemp)
{
	return ( ((float)rawTemp * 175.72f)/ 65536) - 46.85f;
}
//------------------------------------------------------------------------------
uint8_t si7021_calcCRC(uint8_t data[], uint8_t size)
{
	uint8_t i, crc = 0;

	while(size--)
	{
		crc ^= *data++;

		for(i = 0; i < 8; i++) 
		{
			crc = (crc & 0x80) ? (crc << 1) ^ 0x31 : (crc << 1);  //0x131 (see datasheet) x^8 + x^5 + x^4 + 1 => 0b 0001 0011 0001
		}
	}
	
	return crc; 
}
//------------------------------------------------------------------------------
uint8_t si7021_isDataValid(uint8_t data[])
{
	uint8_t isValid = 0;
	
	if(si7021_calcCRC(data, 2) == data[2])        // data[2] == CRC value
	{
		isValid = 1;
	}
	
	return isValid;
}
//------------------------------------------------------------------------------
#endif
