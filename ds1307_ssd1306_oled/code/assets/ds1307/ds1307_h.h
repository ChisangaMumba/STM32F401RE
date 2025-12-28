#ifndef DS1307_H
#define	DS1307_H
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c.h"
#define CS2 	PA4
//------------------------------------------------------------------------------
typedef struct 
{
  uint16_t  second;     //second (0-59)
  uint16_t  minute;     //minute (0-59)
  uint16_t  hour;       //hour (0-23)
  uint16_t  dayOfWeek;  //day of the week (1-7, 1=Sunday)
  uint16_t  dayOfMonth; //month (1-31)
  uint16_t  month;      //month (1-12)
  uint16_t  year;       //year (e.g., 2023)
} time_t;
//------------------------------------------------------------------------------
#define DS1307_ADDR 	0xD0
#define SECS_REG			0x00
#define WR 						0
#define RD 						1
//------------------------------------------------------------------------------
void 		ds1307_init(uint8_t time[]);
uint8_t ds1307_readReg(uint8_t addr);
void 		ds1307_writeReg(uint8_t regAddr, uint8_t data);
void 		ds1307_setDateTime(uint8_t time[]);
void 		ds1307_getDateTime(time_t *tm, uint8_t time[]);
void 		ds1307_setDateTimeObj(time_t *tm, uint8_t time[]);
uint8_t calc_decTime(uint8_t time);
uint8_t calc_bcdTime(uint8_t time);
//------------------------------------------------------------------------------
#endif
