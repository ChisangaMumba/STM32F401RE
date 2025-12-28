#ifndef DS1307_C
#define	DS1307_C
//------------------------------------------------------------------------------
#include "ds1307_h.h"
//------------------------------------------------------------------------------
void ds1307_init(uint8_t time[])
{
  i2c_init();   

  // uncomment the next line if you want to set the initial date and time
	//ds1307_setDateTime(time);	// Set initial date and time
}
//------------------------------------------------------------------------------
uint8_t ds1307_readReg(uint8_t address)
{ 
	uint8_t data = 0;
	
  i2c_start();
   
  i2c_write(DS1307_ADDR | WR); 
  i2c_write(address);    
  i2c_restart();
  i2c_write(DS1307_ADDR | RD);                                
  data = i2c_read(NACK);        
   
  i2c_stop();

  return data;
}
//------------------------------------------------------------------------------
void ds1307_writeReg(uint8_t regAddr, uint8_t data)
{ 
	i2c_start();
  
  i2c_write(DS1307_ADDR | WR);
  i2c_write(regAddr);	         // Time registers 0x00 - 0x06, Control Reg 0x07, SRAM 0x8 - 0x3F	
  i2c_write(data);              
  
	i2c_stop();
}
//------------------------------------------------------------------------------
void ds1307_setDateTime(uint8_t time[])
{ 
	i2c_start();
  
  i2c_write(DS1307_ADDR | WR);
  i2c_write(SECS_REG);	// start from seconds register, then auto increments reg addr	
	for(uint8_t reg = 0; reg < 7 ;reg++)
  {
    uint8_t data = calc_bcdTime(time[reg]);
    i2c_write(data);              // Sec, Min, Hour, WDay, MDay, Month, Year
  }
	
	i2c_stop();
}
//------------------------------------------------------------------------------
void ds1307_getDateTime(time_t *tm, uint8_t time[])
{		
	i2c_start();
   
  i2c_write(DS1307_ADDR | WR);	// Write to device to iniate reads starting from the seconds register
  i2c_write(SECS_REG);					// Start from seconds register, then auto increments reg addr	    
  i2c_restart();
  i2c_write(DS1307_ADDR | RD);	// Initiate Read

	time[0] = calc_decTime(i2c_read(ACK));		// Sec
	time[1] = calc_decTime(i2c_read(ACK));		// Min
	time[2] = calc_decTime(i2c_read(ACK));		// WDay
	time[3] = calc_decTime(i2c_read(ACK));		// MDay
	time[4] = calc_decTime(i2c_read(ACK));		// Month
	time[5] = calc_decTime(i2c_read(ACK));		// Year
	time[6] = calc_decTime(i2c_read(NACK));		// Get year & Signal the end of reception
  
	i2c_stop();
	
  ds1307_setDateTimeObj(tm, time);
}
//------------------------------------------------------------------------------
void ds1307_setDateTimeObj(time_t *tm, uint8_t time[])
{
  tm->second = time[0]; 
  tm->minute = time[1]; 
  tm->hour = time[2];  
  tm->dayOfWeek = time[3];  // Day of the week (1-7)
  tm->dayOfMonth = time[4]; // Day of the month (1-31)
  tm->month = time[5];      // Month (1-12)
  tm->year = time[6];       // Year two digits (e.g., 23 for 2023)
}
//-----------------------Change BCD time to Decimal-----------------------------
uint8_t calc_decTime(uint8_t time)
{   
  return ((time >> 4) * 10) + (time & 0x0F);  
}
//-----------------------Change Decimal time to BCD-----------------------------
uint8_t calc_bcdTime(uint8_t time)
{
  return ((time / 10) << 4) + (time % 10);
}
//------------------------------------------------------------------------------
#endif
