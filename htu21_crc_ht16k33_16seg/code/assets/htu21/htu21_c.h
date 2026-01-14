#ifndef HTU21_C
#define	HTU21_C
//------------------------------------------------------------------------------
#include "htu21_h.h"
//------------------------------------------------------------------------------
void htu21_init(uint8_t res)
{	
	i2c_init(); 
	
	htu21_command(RESET_CMD);
	delay_ms(30);
	htu21_writeConfig(res);
}
//------------------------------------------------------------------------------
uint8_t htu21_readConfig(void)
{
	uint8_t data = 0;

	i2c_start(); 

	i2c_write((HTU21_ADDR << 1) | 0);  // 0 = Write  
	i2c_write(READ_CONFIG_CMD);
	i2c_restart();
	i2c_write((HTU21_ADDR << 1) | 1);  // 1 = Read 	
	data = i2c_read(NACK);						

	i2c_stop();

	return data;
}
//------------------------------------------------------------------------------
void htu21_writeConfig(uint8_t data)
{	
	uint8_t config = htu21_readConfig();

	i2c_start(); 

	i2c_write((HTU21_ADDR << 1) | 0);  // 0 = Write  
	i2c_write(WRITE_CONFIG_CMD);						
	i2c_write(data | config);

	i2c_stop();
}
//------------------------------------------------------------------------------
void htu21_command(uint8_t command)
{
	i2c_start();                      

	i2c_write((HTU21_ADDR << 1) | 0);  // 0 = Write             
	i2c_write(command);

	i2c_stop(); 
}
//------------------------------------------------------------------------------
uint16_t htu21_readConv(uint8_t command)
{
	uint8_t data[3] = { 0, 0, 0 }; 

	htu21_command(command);
	delay_ms(50);				
		
	i2c_start();

	i2c_write((HTU21_ADDR << 1) | 1); // 1 = Read 	
	data[0] = i2c_read(ACK);					// MSB
	data[1] = i2c_read(ACK);					// LSB
	data[2] = i2c_read(NACK);					// CRC
	
	i2c_stop();

	return (htu21_isDataValid(data, 2)) ?  (data[0] << 8) + data[1] : 0xFFFF;
}
//------------------------------------------------------------------------------
float htu21_calcHumd(uint16_t rawHumd)
{
	return ( ((float)rawHumd * 125) / 65536 ) - 6;
}
//------------------------------------------------------------------------------
float htu21_calcTemp(uint16_t rawTemp)
{
	return ( ((float)rawTemp * 175.72f) / 65536 ) - 46.85f;
}
//------------------------------------------------------------------------------
uint8_t htu21_calcCRC(uint8_t data[], uint8_t size_)
{
	uint8_t i, crc = 0;

	while(size_--)
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
uint8_t htu21_isDataValid(uint8_t data[], uint8_t size_)
{
	return (htu21_calcCRC(data, size_) == data[2]) ? 1 : 0;
}
//------------------------------------------------------------------------------
#endif
