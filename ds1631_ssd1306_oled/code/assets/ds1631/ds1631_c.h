#ifndef DS1631_C
#define	DS1631_C
//------------------------------------------------------------------------------
#include "ds1631_h.h"
//------------------------------------------------------------------------------
void ds1631_init(int16_t tempH, int16_t tempL, uint8_t resolution, ds1631_t * configObj)
{
  i2c_init(); 
	
	// Set thermostat
	ds1631_write2ByteReg(TH_REG, tempH << 8);	// Thermostat High
	ds1631_write2ByteReg(TL_REG, tempL << 8);	// Thermostat Low
	
	// Polarity High (Active High) Thermostate output	
  ds1631_config(resolution | POL_HIGH);

	ds1631_convertCmd(START_CONV);
	ds1631_setConfig(configObj);
	ds1631_convDelay(configObj->resolution); 
}
//----------------------------Setup Device--------------------------------------
void ds1631_config(uint8_t command)
{
  i2c_start(); 
    
  i2c_write(DS1631_ADDR + Wr); 
  i2c_write(CONFIG_REG); 
  i2c_write(command); 
                           
  i2c_stop();
	
	delay_ms(15);
}
//---------------------Start or stop temp converstion---------------------------
void ds1631_convertCmd(uint8_t command)
{
  i2c_start();
    
  i2c_write(DS1631_ADDR + Wr);
  i2c_write(command);
	
  i2c_stop(); 
	
	delay_ms(15);
}
//------------------------------------------------------------------------------
uint8_t ds1631_read1ByteReg(uint8_t deviceReg)
{
  uint8_t data = 0;
   
  i2c_start(); 	           
   	
  i2c_write(DS1631_ADDR + Wr);	    
  i2c_write(deviceReg);	    
  i2c_restart();	           
  i2c_write(DS1631_ADDR + Rd);	        
  data = i2c_read(NACK);	// Signal End of reception with NACK
	
  i2c_stop();	
   
  return data;
}
//------------------------------------------------------------------------------
void ds1631_write2ByteReg(uint8_t deviceReg, uint16_t settings)
{   
  i2c_start(); 	           
   	
  i2c_write(DS1631_ADDR + Wr);	    
  i2c_write(deviceReg);	    
  i2c_write(settings >> 8);	// Higher byte
	i2c_write(settings);			// Lower byte
                                                   
  i2c_stop();
	
	delay_ms(15);
}
//------------------------------------------------------------------------------
int16_t ds1631_read2ByteReg(uint8_t deviceReg)
{
  uint8_t data[2] = {0, 0};
   
  i2c_start(); 	           
   	
  i2c_write(DS1631_ADDR + Wr);	    	    
  i2c_write(deviceReg);	    
  i2c_restart();	           
  i2c_write(DS1631_ADDR + Rd);	    
  data[1] = i2c_read(ACK);     
  data[0] = i2c_read(NACK);		// Signal End of reception with NACK
	
  i2c_stop();	
   
  return ((data[1] << 8) + data[0]);	// NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
void ds1631_setConfig(ds1631_t * configObj)
{
	uint8_t rawConfig = ds1631_read1ByteReg(CONFIG_REG);

	configObj->tempHigh = ds1631_getTemp(TH_REG);
	configObj->tempHFlag = (rawConfig & 0x40) >> 6;
	configObj->tempLow = ds1631_getTemp(TL_REG);
	configObj->tempLFlag = (rawConfig & 0x20) >> 5;
	configObj->resolution = (rawConfig & 0x0C) >> 2;
}
//------------------------------------------------------------------------------
void ds1631_convDelay(uint8_t resNum)
{
	switch(resNum) 
	{
		case(0): delay_ms(94);  break;   // 9-bit  res 93.75ms conversion time
		case(1): delay_ms(188); break;   // 10-bit res 187.5ms conversion time
		case(2): delay_ms(375); break;   // 11-bit res 375ms conversion time
		case(3): delay_ms(750); break;   // 12-bit res (Power-up default) 750ms conversion time
	}
}
//------------------------------------------------------------------------------
float ds1631_getTemp(uint8_t regName)
{
	int16_t tempr = ds1631_read2ByteReg(regName);
	
	return toFloat(tempr);
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr)
{
  float result 	 = tempr >> 8;	// Get the integer part 
	uint16_t count = tempr & FRAC_FLAG;
	
	if(count)
	{
		result += ((count >> 4) * 0.0625); // Get the fractional part. 2^(-4) = 0.0625 (result is in multiples of 0.0625 LSBit for 12-bit res ADC)
	}
  
	return result;
}
//------------------------------------------------------------------------------
#endif
