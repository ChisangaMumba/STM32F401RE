#ifndef BME280_C
#define	BME280_C
//------------------------------------------------------------------------------
#include "bme280_h.h"
//------------------------------------------------------------------------------
//  Calibration coefficients are read from the BMe280 sensor's NVRAM
//  These coefficients are used in the temperature and pressure calculations.
//  See page 23 of BME280 datasheet (Calibration data)
//------------------------------------------------------------------------------
void bme280_init(bme280_calib_coefs *calib, uint8_t osrs_t, uint8_t osrs_p, uint8_t osrs_h, uint8_t mode)
{
  spi_init(); 

	pinMode(CS3, OUTPUT, PUSH_PULL);

  // Read calibration coefficients from the sensor
  bme280_getCalib(calib);

  // Set the control register with oversampling and mode settings
  uint8_t control = (osrs_t << 5) | (osrs_p << 2) | mode;
  bme280_write(control_reg, control);

  bme280_write(ctrl_hum_reg, osrs_h); // Set humidity oversampling if applicable
}
//------------------------------------------------------------------------------
void bme280_write(uint8_t reg, uint8_t data)
{
  digitalWrite(CS3, LOW);     // CS2 = 0;                     
  		             
  spi_write(reg & 0x7F);      // Write operation, clear the MSB for write                             
  spi_write(data);                
  
  digitalWrite(CS3, HIGH);    // CS2 = 1;
}
//------------------------------------------------------------------------------
uint8_t bme280_read8(uint8_t regAddr)
{
	uint8_t data = 0;
	
  digitalWrite(CS3, LOW);     // CS2 = 0;                      
  								
  spi_write(regAddr);           							                
	data = spi_read();
  
  digitalWrite(CS3, HIGH);    // CS2 = 1;
  
  return data;
}
//------------------------------------------------------------------------------
uint16_t bme280_read16(uint8_t regAddr)
{
	uint8_t data[2];
	
  digitalWrite(CS3, LOW);   // CS2 = 0;                       
  
  spi_write(regAddr);       // temperature or pressure MSB register	
	data[1] = spi_read();	    // LSB
	data[0] = spi_read();     // MSB

  digitalWrite(CS3, HIGH);  // CS2 = 1;
  
  return ((data[0] << 8) | data[1]);
}
//------------------------------------------------------------------------------
uint32_t bme280_readUncomp(uint8_t msb)
{ 
 	uint32_t data[3];
	
  digitalWrite(CS3, LOW);   // CS2 = 0;                       
  							
  spi_write(msb);           // temperature or pressure MSB register        	
	data[2] = spi_read();	    // MSB
	data[1] = spi_read();	    // LSB
	data[0] = spi_read();     // XLSB

  digitalWrite(CS3, HIGH);  // CS2 = 1;
  
  return ((data[2] << 16) | (data[1] << 8) | data[0]) >> 4;
}
//------------------------------------------------------------------------------
//  see page 45-46 of BMe280 datasheet or page 22 (Algorithm for temperature measurement)             
//------------------------------------------------------------------------------
float bme280_getTemp(bme280_calib_coefs calib)
{
  int32_t var1, var2, tmp;
  int32_t adc_T = bme280_readUncomp(tMSB);
 
  var1 = (((int32_t)adc_T >> 3) - ((int32_t)calib.dig_T1 << 1)) * (int32_t)calib.dig_T2 >> 11;
  var2 = (((((adc_T>>4) - ((int32_t)calib.dig_T1)) * ((adc_T>>4) - ((int32_t)calib.dig_T1))) >> 12) *  ((int32_t)calib.dig_T3)) >> 14;
  t_fine = var1 + var2;
  tmp = (t_fine * 5 + 128) >> 8; 
  
  return tmp * 0.01; // Convert to Celsius with one decimal place
}
//------------------------------------------------------------------------------
//  see page 46 of BMe280 datasheet or page 22 (Algorithm for pressure measurement)             
//------------------------------------------------------------------------------
float bme280_getPres(bme280_calib_coefs calib)
{
  int32_t var1, var2; 
  uint32_t p; 
  int32_t adc_P = bme280_readUncomp(pMSB);

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
float bme280_getHum(bme280_calib_coefs calib)
{
  int32_t v_x1_u32r;
  uint32_t humdity;
  int32_t adc_H = bme280_readUncomp(hMSB) >> 4; // Read humidity as 16-bit value

  v_x1_u32r = (t_fine - ((int32_t)76800));

  v_x1_u32r = (((((adc_H << 14) - (((int32_t)calib.dig_H4) << 20) - (((int32_t)calib.dig_H5) * v_x1_u32r)) +
      ((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)calib.dig_H6)) >> 10) * (((v_x1_u32r *
      ((int32_t)calib.dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
      ((int32_t)calib.dig_H2) + 8192) >> 14));
      
  v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)calib.dig_H1)) >> 4));
  v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
  v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
   
  humdity = (uint32_t)(v_x1_u32r >> 12); // Convert to percentage with no decimal places

  return humdity / 1024.0f; // Convert to percentage with two decimal places
}
//------------------------------------------------------------------------------
void bme280_getCalib(bme280_calib_coefs *calib)
{
  uint8_t dummy = bme280_read16(status_reg);  // Read dummy data to clear the register

  // Read temperature calibration coefficients
  // These are always present in both BME280 and BMP280
  calib->dig_T1 = bme280_read16(dig_T1_REG);
  calib->dig_T2 = bme280_read16(dig_T2_REG); 
  calib->dig_T3 = bme280_read16(dig_T3_REG);
  calib->dig_P1 = bme280_read16(dig_P1_REG);
  calib->dig_P2 = bme280_read16(dig_P2_REG);
  calib->dig_P3 = bme280_read16(dig_P3_REG);
  calib->dig_P4 = bme280_read16(dig_P4_REG);
  calib->dig_P5 = bme280_read16(dig_P5_REG);
  calib->dig_P6 = bme280_read16(dig_P6_REG);
  calib->dig_P7 = bme280_read16(dig_P7_REG);
  calib->dig_P8 = bme280_read16(dig_P8_REG);
  calib->dig_P9 = bme280_read16(dig_P9_REG);

  // Read humidity calibration coefficients
  // These are only present in BME280, not in BMP280
  calib->dig_H1 = bme280_read8(dig_H1_REG);
  calib->dig_H2 = bme280_read16(dig_H2_REG);
  calib->dig_H3 = bme280_read8(dig_H3_REG);
  calib->dig_H4 = (bme280_read8(dig_H4_REG) << 4) | (bme280_read8(dig_H4_REG + 1) & 0x0F); 
  calib->dig_H5 = (bme280_read8(dig_H5_REG + 1) << 4) | (bme280_read8(dig_H5_REG) >> 4); 
  calib->dig_H6 = bme280_read8(dig_H6_REG);  
}
//------------------------------------------------------------------------------
#endif
