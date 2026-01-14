#ifndef I2C_H
#define I2C_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define SCL  PA0 
#define SDA  PA1
//------------------------------------------------------------------------------
#define ACK  0
#define NACK 1
//------------------------------------------------------------------------------ 
void i2c_init(void); 
void i2c_start(void); 
void i2c_restart(void);
void i2c_stop(void); 
void i2c_ack(uint8_t ackn); 
uint8_t i2c_write(uint8_t data);
uint8_t i2c_read(uint8_t ackState);
//------------------------------------------------------------------------------
#endif

