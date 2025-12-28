#ifndef SAA1064_C
#define SAA1064_C
//------------------------------------------------------------------------------
#include "saa1064_h.h"
//------------------------------------------------------------------------------
void saa1064_init(void)
{           	
  i2c_init();     
  
  i2c_start();
	
  i2c_write(SAA1064_ADDRESS);              
	i2c_write(CONTROL_REG); 
	i2c_write(DEVICE_CONFIG); 
	
  i2c_stop();
	
	saa1064_write(0);	// Clear outputs
}
//------------------------------------------------------------------------------
void saa1064_write(uint16_t data)
{
	i2c_start();    
	
	i2c_write(SAA1064_ADDRESS); 
	i2c_write(DISPLAY_REG);			// Display data start address. Auto increments on every write.  
  i2c_write(data);						// Lower Byte
	i2c_write(data >> 8);				// Higher Byte
	
	i2c_stop();
}
//------------------------------------------------------------------------------
#endif
