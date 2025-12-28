#ifndef DS3234_H
#define	DS3234_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
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
#define read_cmd               0x00
#define write_cmd              0x80
//------------------------------------------------------------------------------
#define control_reg            0x0E
#define status_reg             0x0F
//------------------------------------------------------------------------------
#define tempMSB_REG            0x11
#define tempLSB_REG            0x12
#define FRAC_FLAG		 	         0x00C0
//------------------------------------------------------------------------------
void ds3234_init(uint8_t time[]);
uint8_t ds3234_read(uint8_t addr);
void ds3234_write(uint8_t addr, uint8_t data_t);
void ds3234_setDateTime(uint8_t time[]);
void ds3234_getDateTime(time_t *tm, uint8_t time[]);
void ds3234_setDateTimeObj(time_t *tm, uint8_t time[]);
uint16_t ds3234_getRawTemp(void);
float ds3234_getTemp(void);
float toFloat(int16_t rawData);
uint8_t calc_decTime(uint8_t time);
uint8_t calc_bcdTime(uint8_t time);
//------------------------------------------------------------------------------
#endif
