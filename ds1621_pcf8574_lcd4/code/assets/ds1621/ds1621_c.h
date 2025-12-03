#ifndef DS1621_C
#define	DS1621_C
//------------------------------------------------------------------------------
#include "ds1621_h.h"
//------------------------------------------------------------------------------
void ds1621_init(int16_t tempH, int16_t tempL)
{
  i2c_init(); 

	// Polarity High (Active High) Thermostate output	
  ds1621_config(POL_HIGH);
	
	// Set thermostat
	ds1621_write2ByteReg(TH_REG, tempH << 8);	// Thermostat High
	ds1621_write2ByteReg(TL_REG, tempL << 8);	// Thermostat Low
	
	ds1621_convertCmd(START_CONV);
}
//----------------------------Setup Device--------------------------------------
void ds1621_config(uint8_t command)
{
  i2c_start(); 
    
  i2c_write(DS1621_ADDR + Wr); 
  i2c_write(CONFIG_REG); 
  i2c_write(CONT_CONV); // Continuous conversion, Active high polarity
                           
  i2c_stop();
	
	delay_ms(15);
}
//---------------------Start or stop temp converstion---------------------------
void ds1621_convertCmd(uint8_t command)
{
  i2c_start();
    
  i2c_write(DS1621_ADDR + Wr);
  i2c_write(command);
	
  i2c_stop(); 
	
	delay_ms(15);
}
//------------------------------------------------------------------------------
uint8_t ds1621_read1ByteReg(uint8_t deviceReg)
{
  uint8_t data = 0;
   
  i2c_start(); 	           
   	
  i2c_write(DS1621_ADDR + Wr);	    
  i2c_write(deviceReg);	    
  i2c_restart();	           
  i2c_write(DS1621_ADDR + Rd);	        
  data = i2c_read(NACK);	// Signal End of reception with NACK
	
  i2c_stop();	
   
  return data;
}
//------------------------------------------------------------------------------
void ds1621_write2ByteReg(uint8_t deviceReg, uint16_t settings)
{   
  i2c_start(); 	           
   	
  i2c_write(DS1621_ADDR + Wr);	    
  i2c_write(deviceReg);	    
  i2c_write(settings >> 8);	// Higher byte
	i2c_write(settings);			// Lower byte
                                                   
  i2c_stop();
	
	delay_ms(15);
}
//------------------------------------------------------------------------------
int16_t ds1621_read2ByteReg(uint8_t deviceReg)
{
  uint8_t data[2] = {0, 0};
   
  i2c_start(); 	           
   	
  i2c_write(DS1621_ADDR + Wr);	    	    
  i2c_write(deviceReg);	    
  i2c_restart();	           
  i2c_write(DS1621_ADDR + Rd);	    
  data[1] = i2c_read(ACK);     
  data[0] = i2c_read(NACK);		// Signal End of reception with NACK
	
  i2c_stop();	
   
  return ((data[1] << 8) + data[0]);	// NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
float ds1621_getTemp(uint8_t regName)
{
	int16_t tempr = ds1621_read2ByteReg(regName);
	
	return toFloat(tempr);
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr)
{
  float result = tempr >> 8;	// Get the integer part 
	
	if(tempr & FRAC_FLAG)
	{
		result += 0.5;						// Get the fractional part
	}
  
	return result;
}
//------------------------------------------------------------------------------
#endif
