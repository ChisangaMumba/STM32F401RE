#ifndef LM75_C
#define	LM75_C
//------------------------------------------------------------------------------
#include "lm75_h.h"
//------------------------------------------------------------------------------
//void lm75_init(int16_t tempH, int16_t tempL)
void lm75_init(int16_t tempH, int16_t tempL, lm75_t *sensor)
{ 
	i2c_init(); 
	sensor->isThermSet = 0;
	
	//For Thermostat functions ONLY... can be left out if so wished and device will still read Tempr
	lm75_write(TOS_REG,  tempH << 8);			//Over Temperature Threshold Activate 
	lm75_write(THYST_REG,tempL << 8);			//Over Temperature Threshold deactivate

	lm75_setSensor(sensor);
}
//------------------------------------------------------------------------------
int16_t lm75_read(uint8_t regAddress)
{
  uint8_t data[2];
  
  i2c_start();                      
  
  i2c_write(LM75_ADDRESS + 0);        // 0 = Write             
  i2c_write(regAddress);        
  i2c_restart();                           
  i2c_write(LM75_ADDRESS + 1);        // 1 = Read   
  data[1] = i2c_read(ACK);						// MSB
  data[0] = i2c_read(NACK);					// LSB
	
  i2c_stop();
  
	return (data[1] << 8) + data[0];
}
//------------------------------------------------------------------------------
void lm75_setConfig(uint8_t data)
{  
  i2c_start();                      
  
  i2c_write(LM75_ADDRESS);                       
  i2c_write(CONFIG_REG);              
  i2c_write(data);       
  
  i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t lm75_readConfig()
{  
	uint8_t config;
	
  i2c_start();                      
  
  i2c_write(LM75_ADDRESS + 0);        // 0 = Write               
  i2c_write(CONFIG_REG);        
  i2c_restart();                           
  i2c_write(LM75_ADDRESS + 1);        // 1 = Read   
  config = i2c_read(NACK);
	
  i2c_stop();
  
  return config;
}
//------------------------------------------------------------------------------
void lm75_write(uint8_t regAddress, int16_t data)
{  
  i2c_start();                      
  
  i2c_write(LM75_ADDRESS);                    
  i2c_write(regAddress);      //Registers: Config,THYST,OVER TEMP SINK (OS) /*See Datasheet*/                       
  i2c_write(data >> 8);       //MSByte       
  i2c_write(data);            //LSByte
  
  i2c_stop();
}
//------------------------------------------------------------------------------
void lm75_setSensor(lm75_t *sensor)
{
	if(sensor->isThermSet == 0)
	{
		sensor->tempHigh = lm75_getTemp(TOS_REG);		// TH
		sensor->tempLow = lm75_getTemp(THYST_REG);	// TL
		sensor->isThermSet = 1;
	}
	
	sensor->temp = lm75_getTemp(TEMP_REG);
}
//------------------------------------------------------------------------------
float lm75_getTemp(uint8_t regAddress)
{
	int16_t tempr = lm75_read(regAddress);
	
	return toFloat(tempr);
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr)
{
  float result = tempr >> 8;      //Discard LSByte (Only holds fraction flag bit - see datasheet)  
	
	if(tempr & FRACTION_FLAG) 
		result += 0.5f; 
	
	return result;
}
//------------------------------------------------------------------------------
#endif
