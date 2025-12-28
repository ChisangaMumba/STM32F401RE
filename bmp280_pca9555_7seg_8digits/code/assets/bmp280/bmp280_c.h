#ifndef BMP280_C
#define	BMP280_C
//------------------------------------------------------------------------------
#include "bmp280_h.h"
//------------------------------------------------------------------------------
//  Calibration coefficients are read from the BMP280 sensor's NVRAM
//  These coefficients are used in the temperature and pressure calculations.
//  See page 23 of BMP280 datasheet (Calibration data)
//------------------------------------------------------------------------------
void bmp280_init(bmp280_calib_coefs *calib, uint8_t osrs_t, uint8_t osrs_p, uint8_t mode)
{
  i2c_init(); 

  // Read calibration coefficients from the sensor
  bmp280_getCalib(calib);

  // Set the control register with oversampling and mode settings
  uint8_t control = (osrs_t << 5) | (osrs_p << 2) | mode;
  bmp280_write(control_reg, control);
}
//------------------------------------------------------------------------------
void bmp280_write(uint8_t reg, uint8_t data)
{
  i2c_start();                      
  
  i2c_write(BMP280_I2C_ADDR);								//Datasheet says WRITE (0x9B), but that does NOT work              
  i2c_write(reg);                                      
  i2c_write(data);                
  
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t bmp280_read8(uint8_t regAddr)
{
	uint8_t result = 0;
	
  i2c_start();                      
  
  i2c_write(BMP280_I2C_ADDR);								
  i2c_write(regAddr);           
  i2c_restart();                           
  i2c_write(BMP280_I2C_ADDR | 1);								                
	result = i2c_read(NACK);
  
  i2c_stop();
  
  return result;
}
//------------------------------------------------------------------------------
uint16_t bmp280_read16(uint8_t regAddr)
{
	uint8_t data[2];
	
  i2c_start();                      
  
  i2c_write(BMP280_I2C_ADDR);								
  i2c_write(regAddr);           
  i2c_restart();                           
  i2c_write(BMP280_I2C_ADDR | 1);	
	
	data[1] = i2c_read(ACK);	    //LSB
	data[0] = i2c_read(NACK);     //MSB

  i2c_stop();
  
  return ((data[0] << 8) | data[1]);
}
//------------------------------------------------------------------------------
uint32_t bmp280_readUncomp(uint8_t msb)
{ 
 	uint32_t data[3];
	
  i2c_start();                      
  
  i2c_write(BMP280_I2C_ADDR);								
  i2c_write(msb);       // temperature or pressure MSB register        
  i2c_restart();                           
  i2c_write(BMP280_I2C_ADDR | 1);	
	
	data[2] = i2c_read(ACK);	    //MSB
	data[1] = i2c_read(ACK);	    //LSB
	data[0] = i2c_read(NACK);     //XLSB

  i2c_stop();
  
  return ((data[2] << 16) | (data[1] << 8) | data[0]) >> 4;
}
//------------------------------------------------------------------------------
//  see page 45-46 of BMP280 datasheet or page 22 (Algorithm for temperature measurement)             
//------------------------------------------------------------------------------
float bmp280_getTemp(bmp280_calib_coefs calib)
{
  int32_t var1, var2, tmp;
  int32_t adc_T = bmp280_readUncomp(tMSB);
 
  var1 = (((int32_t)adc_T >> 3) - ((int32_t)calib.dig_T1 << 1)) * (int32_t)calib.dig_T2 >> 11;
  var2 = (((((adc_T>>4) - ((int32_t)calib.dig_T1)) * ((adc_T>>4) - ((int32_t)calib.dig_T1))) >> 12) *  ((int32_t)calib.dig_T3)) >> 14;
  t_fine = var1 + var2;
  tmp = (t_fine * 5 + 128) >> 8; 
  
  return tmp * 0.01; // Convert to Celsius with one decimal place
}
//------------------------------------------------------------------------------
//  see page 46 of BMP280 datasheet or page 22 (Algorithm for pressure measurement)             
//------------------------------------------------------------------------------
float bmp280_getPres(bmp280_calib_coefs calib)
{
  int32_t var1, var2; 
  uint32_t p; 
  int32_t adc_P = bmp280_readUncomp(pMSB);

  var1 = (((int32_t)t_fine)>>1) - (int32_t)64000; 
  var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((int32_t)calib.dig_P6); 
  var2 = var2 + ((var1*((int32_t)calib.dig_P5))<<1); 
  var2 = (var2>>2)+(((int32_t)calib.dig_P4)<<16); 
  var1 = (((calib.dig_P3 * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((int32_t)calib.dig_P2) * var1)>>1))>>18; 
  var1 =((((32768+var1))*((int32_t)calib.dig_P1))>>15); 
  if (var1 == 0) 
  { 
    return 0; // avoid exception caused by division by zero 
  } 
  p = (((uint32_t)(((int32_t)1048576)-adc_P)-(var2>>12)))*3125; 
  if (p < 0x80000000)  
  { 
    p = (p << 1) / ((uint32_t)var1); 
  }  
  else  
  { 
    p = (p / (uint32_t)var1) * 2; 
  } 
  var1 = (((int32_t)calib.dig_P9) * ((int32_t)(((p>>3) * (p>>3))>>13)))>>12; 
  var2 = (((int32_t)(p>>2)) * ((int32_t)calib.dig_P8))>>13; 
  p = (uint32_t)((int32_t)p + ((var1 + var2 + calib.dig_P7) >> 4)); 

  return p * 0.01; // Convert to hPa
}
//------------------------------------------------------------------------------
void bmp280_getCalib(bmp280_calib_coefs *calib)
{
  uint8_t dummy = bmp280_read16(status_reg);  // Read dummy data to clear the register

  calib->dig_T1 = bmp280_read16(dig_T1_REG);
  calib->dig_T2 = bmp280_read16(dig_T2_REG); 
  calib->dig_T3 = bmp280_read16(dig_T3_REG);
  calib->dig_P1 = bmp280_read16(dig_P1_REG);
  calib->dig_P2 = bmp280_read16(dig_P2_REG);
  calib->dig_P3 = bmp280_read16(dig_P3_REG);
  calib->dig_P4 = bmp280_read16(dig_P4_REG);
  calib->dig_P5 = bmp280_read16(dig_P5_REG);
  calib->dig_P6 = bmp280_read16(dig_P6_REG);
  calib->dig_P7 = bmp280_read16(dig_P7_REG);
  calib->dig_P8 = bmp280_read16(dig_P8_REG);
  calib->dig_P9 = bmp280_read16(dig_P9_REG);
}
//------------------------------------------------------------------------------
#endif
