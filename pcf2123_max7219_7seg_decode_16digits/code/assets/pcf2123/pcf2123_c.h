#ifndef PCF2123_C
#define	PCF2123_C
//------------------------------------------------------------------------------
#include "pcf2123_h.h"
//------------------------------------------------------------------------------
void pcf2123_init(uint8_t time[])
{
  spi_init();   
  
  pinMode(CS2, OUTPUT, PUSH_PULL);
  digitalWrite(CS2, LOW);     // CS2 = 0;      // Deselect initially
  
  // uncomment the next line if you want to set the initial date and time
	//pcf2123_setDateTime(time);	// Set initial date and time
}
//------------------------------------------------------------------------------
void pcf2123_setDateTime(uint8_t time[])
{  
	digitalWrite(CS2, HIGH);  // CS2 = 1;
	
	spi_write(WR+SEC_REG);		// Auto Increments after initial Write
	spi_write(calc_bcdTime(time[0]));		// Secs
	spi_write(calc_bcdTime(time[1]));		// Mins
	spi_write(calc_bcdTime(time[2]));		// Hrs
	spi_write(calc_bcdTime(time[3]));		// Month Day
	spi_write(calc_bcdTime(time[4]));		// Week Day
	spi_write(calc_bcdTime(time[5]));		// Month
	spi_write(calc_bcdTime(time[6]));		// Years
	
	digitalWrite(CS2, LOW);   // CS2 = 0;
}
//------------------------------------------------------------------------------
void pcf2123_getDateTime(time_t *tm, uint8_t time[])
{	
	digitalWrite(CS2, HIGH);  // CS2 = 1;
	
	spi_write(RD+SEC_REG);		// Auto Increments after initial Read
	time[0] = calc_decTime(spi_read() & OS_FLAG);		// Secs
	time[1] = calc_decTime(spi_read());							// Mins
	time[2] = calc_decTime(spi_read());							// Hrs
	time[3] = calc_decTime(spi_read());							// Month Day
	time[4] = calc_decTime(spi_read());							// Week Day
	time[5] = calc_decTime(spi_read());							// Month
	time[6] = calc_decTime(spi_read());							// Years two digits (e.g., 23 for 2023)
	
	digitalWrite(CS2, LOW);   // CS2 = 0;

  pcf2123_setDateTimeObj(tm, time);
}
//------------------------------------------------------------------------------
void pcf2123_setDateTimeObj(time_t *tm, uint8_t time[])
{
  tm->second = time[0]; // (Discards OS Flag from Secs _register)
  tm->minute = time[1]; 
  tm->hour = time[2];  
  tm->dayOfWeek = time[3];  			// Day of the week (1-7)
  tm->dayOfMonth = time[4]; 			// Day of the month (1-31)
  tm->month = time[5];      			// Month (1-12)
  tm->year = time[6];       			// Year two digits (e.g., 23 for 2023)
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
