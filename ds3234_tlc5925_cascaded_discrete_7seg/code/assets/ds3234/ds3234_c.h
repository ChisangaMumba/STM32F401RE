#ifndef DS3234_C
#define	DS3234_C
//------------------------------------------------------------------------------
#include "ds3234_h.h"
//------------------------------------------------------------------------------
void ds3234_init(uint8_t time[])
{
  spi_init();   
  
  pinMode(CS2, OUTPUT, PUSH_PULL);
  digitalWrite(CS2, HIGH);      // CS2 = 1;      //Deselect initially
  
  ds3234_write(control_reg, 0x20);
  ds3234_write(status_reg, 0x48);

  // uncomment the next line if you want to set the initial date and time
	//ds3234_setDateTime(time);	// Set initial date and time
}
//------------------------------------------------------------------------------
uint8_t ds3234_read(uint8_t address)
{ 
	uint8_t data_t = 0;
  digitalWrite(CS2, LOW);       // CS2 = 0;

  spi_write(address + read_cmd);
  data_t = spi_read(); 
  
  digitalWrite(CS2, HIGH);      // CS2 = 1;

  return data_t;
}
//------------------------------------------------------------------------------
void ds3234_write(uint8_t address, uint8_t data_t)
{
  digitalWrite(CS2, LOW);       // CS2 = 0;

  spi_write(address + write_cmd);
  spi_write(data_t);
  
  digitalWrite(CS2, HIGH);      // CS2 = 1;
}
//------------------------------------------------------------------------------
void ds3234_setDateTime(uint8_t time[])
{  
	for(uint8_t reg = 0; reg < 7 ;reg++)
  {
    uint8_t data = calc_bcdTime(time[reg]);
    ds3234_write(reg, data);              // Sec, Min, Hour, WDay, MDay, Month, Year
  }
}
//------------------------------------------------------------------------------
void ds3234_getDateTime(time_t *tm, uint8_t time[])
{	
  for(uint8_t reg = 0; reg < 7; reg++)
  {
    uint8_t data = ds3234_read(reg);
    time[reg] = calc_decTime(data);        // Sec, Min, Hour, WDay, MDay, Month, Year
  }

  ds3234_setDateTimeObj(tm, time);
}
//------------------------------------------------------------------------------
void ds3234_setDateTimeObj(time_t *tm, uint8_t time[])
{
  tm->second = time[0]; 
  tm->minute = time[1]; 
  tm->hour = time[2];  
  tm->dayOfWeek = time[3];  // Day of the week (1-7)
  tm->dayOfMonth = time[4]; // Day of the month (1-31)
  tm->month = time[5];      // Month (1-12)
  tm->year = time[6];       // Year two digits (e.g., 23 for 2023)
}
//------------------------------------------------------------------------------
uint16_t ds3234_getRawTemp(void)
{
	uint16_t data_t[2];
	
	data_t[0] = ds3234_read(tempLSB_REG);
	data_t[1] = ds3234_read(tempMSB_REG);
	
	return (data_t[1] << 8) | data_t[0];
}
//------------------------------------------------------------------------------
float ds3234_getTemp(void)
{	
	uint16_t rawTemp = ds3234_getRawTemp();
	return toFloat(rawTemp);
}
//------------------------------------------------------------------------------
float toFloat(int16_t rawData)
{
	float tempr  =  rawData >> 8; // Get the integer part    
	int16_t count =  rawData & FRAC_FLAG;          
																			 
	if(count) 
	{
		tempr += ((count >> 6) * 0.25); // Get the integer part. 2^(-2) = 0.25 (result is in multiples of 0.25 LSBit for 10-bit_ res ADC)
	}

	return tempr;
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
