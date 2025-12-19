#ifndef SI7021_C
#define	SI7021_C
//------------------------------------------------------------------------------
#include "mcp9800_h.h"
//------------------------------------------------------------------------------
void mcp9800_init(int16_t highTemp, int16_t lowTemp, uint8_t res, mcp9800_config_t * configObj)
{
	delay_ms(10);
	
	// Set thermostat
  mcp9800_write(TSET_REG,  highTemp << 8);    // Set the temperature set register to default
  mcp9800_write(THYST_REG, lowTemp  << 8);    // Set the hysteresis register to default
  
	// Polarity High (Active High) Thermostate output
	mcp9800_setConfig(res);
	
	mcp9800_setConfigObj(configObj);
	mcp9800_convDelay(configObj->res);
}
//------------------------------------------------------------------------------
void mcp9800_setConfig(uint8_t settings)
{
	i2c_start(); 
    
  i2c_write(ADDR + Wr); 
  i2c_write(CONFIG_REG); 
  i2c_write(settings);       
                           
  i2c_stop();
}
//------------------------------------------------------------------------------
void mcp9800_setConfigObj(mcp9800_config_t *configObj)
{
	uint8_t rawConfig = mcp9800_getConfig();
	int16_t rawtemp = 0;
	
	rawtemp = mcp9800_read(TSET_REG);
	configObj->tempHigh = toFloat(rawtemp);		// High thermostat value
	
	rawtemp = mcp9800_read(THYST_REG);
  configObj->tempLow = toFloat(rawtemp);		// Low thermostat value
	
	configObj->res = (rawConfig & 0x60) >> 5;	// Resolution number
}
//------------------------------------------------------------------------------
uint8_t mcp9800_getConfig(void)
{
	uint8_t config = 0;
	
  i2c_start();
    
  i2c_write(ADDR + Wr);
	i2c_write(CONFIG_REG);
	i2c_restart();	
  i2c_write(ADDR + Rd);	        
  config = i2c_read(NACK);    // Signal End of reception with NACK
	
  i2c_stop(); 
	
	return config;
}
//------------------------------------------------------------------------------
void mcp9800_write(uint8_t reg, uint16_t settings)
{
  i2c_start(); 
    
  i2c_write(ADDR + Wr); 
  i2c_write(reg); 
  i2c_write(settings >> 8);          // MSByte first
  i2c_write(settings & 0x00ff);      // LSByte second
                           
  i2c_stop();
}
//------------------------------------------------------------------------------
int16_t mcp9800_read(uint8_t reg)
{
	uint8_t data[2];
   
  i2c_start(); 	           
  
  i2c_write(ADDR + Wr);	    
  i2c_write(reg);	    
  i2c_restart();	
  i2c_write(ADDR + Rd);	    
  data[1] = i2c_read(ACK);     // MSB
  data[0] = i2c_read(NACK);    // LSB. Signal End of reception with NACK

  i2c_stop();	
  
  return ((data[1] << 8) + data[0]);   // NB: Result is 16bits Long
}
//------------------------------------------------------------------------------
float mcp9800_getTemp(void)
{ 
  int16_t rawtemp = mcp9800_read(TEMP_REG);

  return toFloat(rawtemp);
}
//------------------------------------------------------------------------------
void mcp9800_convDelay(uint8_t resNum)
{
	// Wait for conversion to complete based on resolution
  switch(resNum)
  {
    case (0x00): delay_ms(75);  break;   // 0.5°C
    case (0x01): delay_ms(150); break;   // 0.25°C
    case (0x02): delay_ms(300); break;   // 0.125°C
    case (0x03): delay_ms(600); break;   // 0.0625°C
    default:     delay_ms(75);  break;   // 0.5°C
  }
  // Delay based on resolution to allow temperature conversion to complete
  // 0.5°C: 75ms, 0.25°C: 150ms, 0.125°C: 300ms, 0.0625°C: 600ms
  // This ensures accurate temperature readings after writing to the device
}
//------------------------------------------------------------------------------
float toFloat(int16_t rawData)
{
  float tempr   = rawData >> 8;         // Get the integer part
  int16_t count = rawData & FRAC_FLAG;          
  
  if(count) 
  {
		tempr += ((count >> 4) * 0.0625);   // Get the fractional part
  }
  
	return tempr; 
}
//------------------------------------------------------------------------------
#endif
