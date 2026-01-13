#ifndef ADS101x_C
#define	ADS101x_C
//------------------------------------------------------------------------------
#include "ads101x_h.h"
//------------------------------------------------------------------------------
void ads101x_init(void)
{	
	i2c_init(); 
	delay_ms(100);
}
//------------------------------------------------------------------------------
uint16_t ads101x_read(uint8_t reg)
{
	uint8_t data[2] = { 0, 0 };

	i2c_start(); 

	i2c_write(ADS101x_ADDR | 0);  // 0 = Write  
	i2c_write(reg);
	i2c_restart();
	i2c_write(ADS101x_ADDR | 1);  // 1 = Read 	
	data[1] = i2c_read(ACK);			// MSB
	data[0] = i2c_read(NACK);			// LSB

	i2c_stop();

	return ((data[1] << 8) | data[0]);
}
//------------------------------------------------------------------------------
void ads101x_write(uint8_t reg, uint16_t data)
{	
	i2c_start(); 

	i2c_write(ADS101x_ADDR | 0);	// 0 = Write  
	i2c_write(reg);						
	i2c_write(data >> 8);					// MSB
	i2c_write(data);							// LSB
	
	i2c_stop();
}
//------------------------------------------------------------------------------
void ads101x_config(uint16_t data)
{
	ads101x_write(REG_CONFIG, data);
	
	delay_ms(10);
}
//------------------------------------------------------------------------------
float ads101x_getVoltage(uint8_t mode, uint8_t chn)
{
	float v_in;
	
	uint16_t chnSelect = (mode == 0) ? sing_channel[chn] : diff_channel[chn];
	ads101x_config(chnSelect | FS_6144mV | MODE_CONT_CONV | DATA_RATE_860SPS);
	delay_ms(1);
	v_in = (ads101x_read(REG_CONV) * 6.144f) / 32767;  // 32767 = 0x7FFF, max positive digital word for 16 bit system
	
	return v_in;
}
//------------------------------------------------------------------------------
#endif
