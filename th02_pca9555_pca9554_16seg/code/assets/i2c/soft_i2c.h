#ifndef I2C_H
#define I2C_H
//------------------------------------------------------------------------------
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define SCLK  PA0 
#define SDAT  PA1
//------------------------------------------------------------------------------
#define ACK  0
#define NACK 1
//------------------------------------------------------------------------------ 
void i2c_init(void)
{
  // Note i2c SDA is open drain, this means we need to use INPUT for an SDA high logic. I.e. we can't just write digitalWrite(pin, HIGH) for the SDA.
  pinMode(SCLK, OUTPUT, PUSH_PULL, NO_PU_PD);

  pinMode(SDAT, INPUT, OPEN_DRAIN, PULL_UP); // SDAT = 1
  digitalWrite(SCLK, HIGH);   			// SCLK = 1
}
//------------------------------------------------------------------------------ 
void i2c_start(void)
{
  pinMode(SDAT, OUTPUT, OPEN_DRAIN, PULL_UP);  // SDAT = 0
  digitalWrite(SCLK, LOW);   					// SCLK = 0
}
//------------------------------------------------------------------------------ 
void i2c_restart(void)
{
  pinMode(SDAT, INPUT, OPEN_DRAIN, PULL_UP);   // SDAT = 1
  digitalWrite(SCLK, HIGH);   				// SCLK = 1
  pinMode(SDAT, OUTPUT, OPEN_DRAIN, PULL_UP);  // SDAT = 0
  digitalWrite(SCLK, LOW);    				// SCLK = 0
}
//------------------------------------------------------------------------------ 
void i2c_stop(void)
{
  digitalWrite(SCLK, LOW);    				// SCLK = 0
  pinMode(SDAT, OUTPUT, OPEN_DRAIN, PULL_UP);  // SDAT = 0
  digitalWrite(SCLK, HIGH);   				// SCLK = 1
  pinMode(SDAT, INPUT, OPEN_DRAIN, PULL_UP);   // SDAT = 1
}
//------------------------------------------------------------------------------ 
void i2c_ack(uint8_t ackn)
{
  pinMode(SDAT, (ackn == 1) ? INPUT : OUTPUT, OPEN_DRAIN, PULL_UP);  // SDAT = ackn; 
  digitalWrite(SCLK, HIGH);                      						// SCLK = 1
  digitalWrite(SCLK, LOW);                       						// SCLK = 0
  pinMode(SDAT, INPUT, OPEN_DRAIN, PULL_UP);                         // SDAT = 1
}
//------------------------------------------------------------------------------ 
uint8_t i2c_write(uint8_t data)
{	
  for(uint8_t tx = 0; tx < 8; tx++)
  {
    pinMode(SDAT, ((data << tx) & 0x80) ? INPUT : OUTPUT, OPEN_DRAIN, PULL_UP) ; //MSB first SDAT 1 or 0
    digitalWrite(SCLK, HIGH);   // SCLK = 1
    digitalWrite(SCLK, LOW);    // SCLK = 0 //Toggle SCK pin So that slave can latch data bit                   
  }
	
  i2c_ack(ACK);
	
  return SDAT;
}
//------------------------------------------------------------------------------ 
uint8_t i2c_read(uint8_t ackState)
{
	uint8_t data = 0;

	for(uint8_t rx = 0; rx < 8; rx++) 
	{
		digitalWrite(SCLK, HIGH);   // SCLK = 1
    data += digitalRead(SDAT) << (7-rx);  //MSB first
		digitalWrite(SCLK, LOW);    // SCLK = 0
	}
	
	i2c_ack(ackState);
	
	return data;
}
//------------------------------------------------------------------------------
#endif

