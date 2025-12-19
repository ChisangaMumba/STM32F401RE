#ifndef BMP180_C
#define	BMP180_C
//------------------------------------------------------------------------------
#include "bmp180_h.h"
//------------------------------------------------------------------------------
int16_t ac1 = 0;
int16_t ac2 = 0;
int16_t ac3 = 0;
uint16_t ac4 = 0;
uint16_t ac5 = 0;
uint16_t ac6 = 0;
int16_t _b1 = 0;
int16_t _b2 = 0;
int16_t mb = 0;
int16_t mc = 0;
int16_t md = 0;
//------------------------------------------------------------------------------
//  _b5 is used in the temperature and pressure calculations
int32_t _b5 = 0;
//------------------------------------------------------------------------------
//  Calibration coefficients are read from the BMP180 sensor
//  See page 13 of BMP180 datasheet 15 (Calibration data)
//------------------------------------------------------------------------------
void bmp180_init(void)
{
  i2c_init();
  
	ac1 = bmp180_read16(AC1_reg);
	ac2 = bmp180_read16(AC2_reg);
	ac3 = bmp180_read16(AC3_reg);
	ac4 = bmp180_read16(AC4_reg);
	ac5 = bmp180_read16(AC5_reg);
	ac6 = bmp180_read16(AC6_reg);
	_b1 = bmp180_read16(B1_reg);
	_b2 = bmp180_read16(B2_reg);
	mb = bmp180_read16(MB_reg);
	mc = bmp180_read16(MC_reg);
	md = bmp180_read16(MD_reg);
}
//------------------------------------------------------------------------------
void bmp180_write(uint8_t reg, uint8_t data_)
{
  i2c_start();                      
  
  i2c_write(BMP180_I2C_ADDR);								//Datasheet says WRITE (0x9B), but that does NOT work              
  i2c_write(reg);                                      
  i2c_write(data_);                
  
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t bmp180_read8(uint8_t regAddr)
{
	uint8_t result = 0;
	
  i2c_start();                      
  
  i2c_write(BMP180_I2C_ADDR);								
  i2c_write(regAddr);           
  i2c_restart();                           
  i2c_write(BMP180_I2C_ADDR | 1);								                
	result = i2c_read(NACK);
  
  i2c_stop();
  
  return result;
}
//------------------------------------------------------------------------------
uint16_t bmp180_read16(uint8_t regAddr)
{
	uint16_t data_[2];
	
  i2c_start();                      
  
  i2c_write(BMP180_I2C_ADDR);								
  i2c_write(regAddr);           
  i2c_restart();                           
  i2c_write(BMP180_I2C_ADDR | 1);	
	data_[0] = i2c_read(ACK);	
	data_[1] = i2c_read(NACK);

  i2c_stop();
  
  return ((data_[0] << 8) | data_[1]);
}
//------------------------------------------------------------------------------
uint16_t bmp180_readUncompTemp(void)
{
	uint16_t data_[2];

	bmp180_write(control_reg, temp_conv_cmd);
	delay_ms(5);
	data_[1] = bmp180_read8(MSB);   
	data_[0] = bmp180_read8(LSB);   
  
	return (data_[1] << 8) + data_[0];
}
//------------------------------------------------------------------------------
//  see page 14 of BMP180 datasheet 15 (Algorithm for pressure and temperature measurement)             
//------------------------------------------------------------------------------
float bmp180_getTemp(void)
{
  float tmp = 0;

  int32_t UT = bmp180_readUncompTemp();
  int32_t x1 = 0;
  int32_t x2 = 0;

  x1 = ((((int32_t)UT - (int32_t)ac6) * (int32_t)ac5) >> 15);
  x2 = (((int32_t)mc << 11) / (x1 + md));
  _b5 = (x1 + x2);
  tmp = ((_b5 + 8) >> 4);
  
  return tmp * 0.1f; // Convert to °C
}
//------------------------------------------------------------------------------
uint32_t  bmp180_readUncompPress(uint8_t oss) // default value for oversampling setting
{
  uint32_t data[3] = { 0, 0, 0 };

  bmp180_write(control_reg, (0x34 + (oss << 6)));

  switch(oss)
  {
    case (1):  delay_ms(8);  break;
    case (2):  delay_ms(14); break;
    case (3):  delay_ms(26); break;
    default:   delay_ms(5); break;
  }

  data[2] = bmp180_read8(MSB);
  data[1] = bmp180_read8(LSB);
  data[0] = bmp180_read8(XLSB);

  return ((data[2] << 16) | (data[1] << 8) | data[0]) >> (8 - oss);
}
//------------------------------------------------------------------------------
//  see page 14 of BMP180 datasheet 15 (Algorithm for pressure and temperature measurement)             
//------------------------------------------------------------------------------
float bmp180_getPress(uint8_t oss) // default value for oversampling setting
{
  int32_t UP = bmp180_readUncompPress(oss);

  int32_t p = 0;
  int32_t x1 = 0;
  int32_t x2 = 0;
  int32_t x3 = 0;
  int32_t _b3 = 0;
  int32_t _b6 = 0;
  uint32_t _b4 = 0;
  uint32_t _b7 = 0;

  _b6 = (_b5 - 4000);

  x1 = ((_b2 * (_b6 * _b6) >> 12) >> 11);
  x2 = ((ac2 * _b6) >> 11);
  x3 = (x1 + x2);
  _b3 = (((((((int32_t)ac1) << 2) + x3) << oss) + 2) >> 2);
  x1 = ((ac3 * _b6) >> 13);
  x2 = ((_b1 * ((_b6 * _b6) >> 12)) >> 16);
  x3 = (((x1 + x2) + 2) >> 2);
  _b4 = ((ac4 * (uint32_t)(x3 + 32768)) >> 15);
  _b7 = ((uint32_t)(UP - _b3) * (50000 >> oss));

  if(_b7 < 0x80000000)
  {
      p = ((_b7 << 1) / _b4);
  }
  else
  {
      p = ((_b7 / _b4) << 1);
  }

  x1 = ((p >> 8) * (p >> 8));
  x1 = ((x1 * 3038) >> 16);
  x2 = ((-7357 * p) >> 16);
  p += ((x1 + x2 + 3791) >> 4);

  return p * 0.01f; // Convert to hPa
}
//------------------------------------------------------------------------------
#endif

