#ifndef DS3232_H
#define	DS3232_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
#define CS2 	PA4
//------------------------------------------------------------------------------
typedef struct 
{
  int  second;     //second (0-59)
  int  minute;     //minute (0-59)
  int  hour;       //hour (0-23)
  int  dayOfWeek;  //day of the week (1-7, 1=Sunday)
  int  dayOfMonth; //month (1-31)
  int  month;      //month (1-12)
  int  year;       //year (e.g., 2023)
} time_t;
//------------------------------------------------------------------------------
#define WR 0
#define RD 1
//------------------------------------------------------------------------------
#define tempMSB_REG            0x11
#define tempLSB_REG            0x12
#define FRAC_FLAG		 	         0x00C0
//------------------------------------------------------------------------------
void ds3232_init(uint8_t time[]);
uint8_t ds3232_read(uint8_t addr);
void ds3232_setDateTime(uint8_t time[]);
void ds3232_getDateTime(time_t *tm, uint8_t time[]);
void ds3232_setDateTimeObj(time_t *tm, uint8_t time[]);
uint16_t ds3232_getRawTemp(void);
float ds3232_getTemp(void);
float toFloat(int16_t rawData);
uint8_t calc_decTime(uint8_t time);
uint8_t calc_bcdTime(uint8_t time);
//------------------------------------------------------------------------------
#endif
