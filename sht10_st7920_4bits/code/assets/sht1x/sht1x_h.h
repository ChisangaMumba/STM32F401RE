#ifndef SHT1x_H
#define	SHT1x_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
// Define the SHT1x I/O pins (adjust as needed)
#define 	SHT_CLK  						PA7  		// SHT10 clock
#define 	SHT_DATA 						PA8			// SHT10 data (bidirectional)
//------------------------------------------------------------------------------
#define 	TEMP_CMD  					0x03
#define 	HUMD_CMD  					0x05
#define 	WR_STATUS_REG_CMD  	0x06
#define 	RD_STATUS_REG_CMD  	0x07
#define 	SOFT_RESET_CMD  		0x1E
#define 	TIMEOUT_LIMIT 			10000
//------------------------------------------------------------------------------
#define 	SHT_ACK  						0
#define 	SHT_NACK 						1
//------------------------------------------------------------------------------
typedef struct 
{
  float temperature;
	float humidity;        
} sht1x_t;
//------------------------------------------------------------------------------
void 			SBus_start(void);
uint8_t 	SBus_ack(uint8_t ack);
uint8_t 	SBus_write(uint8_t data_);
uint8_t 	SBus_read(uint8_t ack);
uint8_t 	SBus_waitForResult(void);
uint16_t 	sht1x_read(uint8_t command);
float 		sht1x_getTemp(void);
float 		sht1x_getHumd(float tempr);
//------------------------------------------------------------------------------
#endif
