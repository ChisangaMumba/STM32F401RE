#ifndef PCF2123_H
#define	PCF2123_H
//------------------------------------------------------------------------------
#include "../spi/soft_spi.h"
#define CS2 	PA4
//------------------------------------------------------------------------------
typedef struct 
{
  uint16_t  second;     // second (0-59)
  uint16_t  minute;     // minute (0-59)
  uint16_t  hour;       // hour (0-23)
  uint16_t  dayOfWeek;  // day of the week (1-7, 1=Sunday)
  uint16_t  dayOfMonth; // month (1-31)
  uint16_t  month;      // month (1-12)
  uint16_t  year;       // year (e.g., 2023)
} time_t;
//------------------------------------------------------------------------------
#define SA        0x01   //subaddress; other codes will cause the device to ignore data transfer
#define RD        0x90   //RD + Subaddress + Sec
#define WR        0x10
//------------------------------------------------------------------------------
#define OS_FLAG   0x7F
#define SEC_REG   0x02
#define MIN_REG   0x03
#define HOUR_REG  0x04
#define DAY_REG   0x05
#define MDAY_REG  0x06
#define WDAY_REG  0x07
#define MONTH_REG 0x08
#define YEAR_REG  0x09
//------------------------------------------------------------------------------
void pcf2123_init(uint8_t time[]);
void pcf2123_setDateTime(uint8_t time[]);
void pcf2123_getDateTime(time_t *tm, uint8_t time[]);
void pcf2123_setDateTimeObj(time_t *tm, uint8_t time[]);
uint8_t calc_decTime(uint8_t time);
uint8_t calc_bcdTime(uint8_t time);
//------------------------------------------------------------------------------
#endif
