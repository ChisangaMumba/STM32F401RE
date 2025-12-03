#ifndef TCN75_C
#define	TCN75_C
//------------------------------------------------------------------------------
#include "tcn75_h.h"
//------------------------------------------------------------------------------
void tcn75_init(int16_t tempH, int16_t tempL, uint8_t res, tcn75_t *sensor)
{ 
	i2c_init(); 
	sensor->isThermSet = 0;
	
	//For Thermostat functions ONLY... can be left out if so wished and device will still read Tempr
	tcn75_set(TOS_REG,  tempH << 8);			// Over Temperature Threshold Activate 
	tcn75_set(THYST_REG,tempL << 8);			// Over Temperature Threshold deactivate
	
	tcn75_setConfig(res);
	tcn75_setSensor(sensor);
}
//------------------------------------------------------------------------------
int16_t tcn75_read(uint8_t regAddress)
{
	uint8_t data_[2];
	
	i2c_start();                      
	
	i2c_write(TCN75_ADDRESS + 0);        	// 0 = Write             
	i2c_write(regAddress);        
	i2c_restart();                           
	i2c_write(TCN75_ADDRESS + 1);        	// 1 = Read   
	data_[1] = i2c_read(ACK);							// MSB
	data_[0] = i2c_read(NACK);						// LSB
	
	i2c_stop();
	
	return (data_[1] << 8) + data_[0];
}
//------------------------------------------------------------------------------
void tcn75_setConfig(uint8_t data)
{ 
	uint8_t config = tcn75_readConfig();
	
	i2c_start();                      
	
	i2c_write(TCN75_ADDRESS);                       
	i2c_write(CONFIG_REG);              
	i2c_write(data | config);       
	
	i2c_stop();
}
//------------------------------------------------------------------------------
uint8_t tcn75_readConfig(void)
{  
	uint8_t config;
	
	i2c_start();                      
	
	i2c_write(TCN75_ADDRESS + 0);   // 0 = Write               
	i2c_write(CONFIG_REG);        
	i2c_restart();                           
	i2c_write(TCN75_ADDRESS + 1);		// 1 = Read   
	config = i2c_read(NACK);				// Signal End of reception with NACK
	
	i2c_stop();
	
	return config;
}
//------------------------------------------------------------------------------
void tcn75_set(uint8_t regAddress, int16_t data)
{  	
	i2c_start();                      
	
	i2c_write(TCN75_ADDRESS);                    
	i2c_write(regAddress);      	// Registers: Config,THYST,OVER TEMP SINK (OS) /*See Datasheet*/                       
	i2c_write(data >> 8);        // MSByte       
	i2c_write(data);            	// LSByte
	
	i2c_stop();
}
//------------------------------------------------------------------------------
void tcn75_setSensor(tcn75_t *sensor)
{
	if(sensor->isThermSet == 0)
	{
		sensor->tempHigh = tcn75_getTemp(TOS_REG);				// TH
		sensor->tempLow = tcn75_getTemp(THYST_REG);				// TL
		sensor->resol = (tcn75_readConfig() & 0x60) >> 5;	// get resolution;
		sensor->isThermSet = 1;
	}
	
	convDelay(sensor->resol);
	sensor->temp = tcn75_getTemp(TEMP_REG);
}
//------------------------------------------------------------------------------
float tcn75_getTemp(uint8_t regAddress)
{
	int16_t tempr = tcn75_read(regAddress);
	
	return toFloat(tempr);
}
//------------------------------------------------------------------------------
float toFloat(int16_t tempr)
{
	float  result = tempr >> 8;	// Discard LSByte (Only holds fraction flag bit - see datasheet)  
	uint8_t count = tempr & FRAC_FLAG;          

	if(count) 
	{
		result += ((count >> 4) * 0.0625); // 2^(-4) = 0.0625 (result is in multiples of 0.0625 LSBit for 12-bit_ res ADC)
	}

	return result;
}
//------------------------------------------------------------------------------
void convDelay(uint8_t resNum)
{
  switch(resNum)
  {
    case (0x00): delay_ms(30);  break;  	// 0.5°C
    case (0x01): delay_ms(60); break;   	// 0.25°C
    case (0x02): delay_ms(120); break;   	// 0.125°C
    case (0x03): delay_ms(240); break;   	// 0.0625°C
    default:     delay_ms(30);  break;   	// 0.5°C
  }
  // Delay based on resolution to allow temperature conversion to complete
  // 0.5°C: 30ms, 0.25°C: 60ms, 0.125°C: 120ms, 0.0625°C: 240ms
  // This ensures accurate temperature readings after writing to the device
}
//------------------------------------------------------------------------------
#endif
