#ifndef I2C_C
#define I2C_C
//------------------------------------------------------------------------------
#include "../i2c/soft_i2c_h.h"
//------------------------------------------------------------------------------ 
void i2c_init(void)
{
  // Note i2c SDA is open drain, this means we need to use INPUT for an SDA high logic. I.e. we can't just write digitalWrite(pin, HIGH) for the SDA.
  pinMode(SCL, OUTPUT, PUSH_PULL, NO_PU_PD);

  pinMode(SDA, INPUT, OPEN_DRAIN, PULL_UP); 		// SDA = 1	PULL_UP
  digitalWrite(SCL, HIGH);   										// SCL = 1
}
//------------------------------------------------------------------------------ 
void i2c_start(void)
{
  pinMode(SDA, OUTPUT, OPEN_DRAIN, PULL_UP);		// SDA = 0
  digitalWrite(SCL, LOW);   										// SCL = 0
}
//------------------------------------------------------------------------------ 
void i2c_restart(void)
{
  pinMode(SDA, INPUT, OPEN_DRAIN, PULL_UP);		// SDA = 1
  digitalWrite(SCL, HIGH);   									// SCL = 1
  pinMode(SDA, OUTPUT, OPEN_DRAIN, PULL_UP);  // SDA = 0
  digitalWrite(SCL, LOW);    									// SCL = 0
}
//------------------------------------------------------------------------------ 
void i2c_stop(void)
{
  digitalWrite(SCL, LOW);    									// SCL = 0
  pinMode(SDA, OUTPUT, OPEN_DRAIN, PULL_UP);  // SDA = 0
  digitalWrite(SCL, HIGH);   									// SCL = 1
  pinMode(SDA, INPUT, OPEN_DRAIN, PULL_UP);   // SDA = 1
}
//------------------------------------------------------------------------------ 
void i2c_ack(uint8_t ackn)
{
  pinMode(SDA, (ackn == 1) ? INPUT : OUTPUT, OPEN_DRAIN, PULL_UP);		// SDA = ackn; 
  digitalWrite(SCL, HIGH);                      											// SCL = 1
  digitalWrite(SCL, LOW);                       											// SCL = 0
  pinMode(SDA, INPUT, OPEN_DRAIN, PULL_UP);                         	// SDA = 1
}
//------------------------------------------------------------------------------ 
uint8_t i2c_write(uint8_t data)
{	
  for(uint8_t tx = 0; tx < 8; tx++)
  {
    pinMode(SDA, ((data << tx) & 0x80) ? INPUT : OUTPUT, OPEN_DRAIN, PULL_UP) ; //MSB first SDAT 1 or 0
    digitalWrite(SCL, HIGH);   // SCL = 1
    digitalWrite(SCL, LOW);    // SCL = 0 // Toggle SCK pin So that slave can latch data bit                   
  }
	
  i2c_ack(ACK);
	
  return SDA;
}
//------------------------------------------------------------------------------ 
uint8_t i2c_read(uint8_t ackState)
{
	uint8_t data = 0;

	for(uint8_t rx = 0; rx < 8; rx++) 
	{
		digitalWrite(SCL, HIGH);   					// SCL = 1
    data += digitalRead(SDA) << (7-rx); // MSB first
		digitalWrite(SCL, LOW);    					// SCL = 0
	}
	
	i2c_ack(ackState);
	
	return data;
}
//------------------------------------------------------------------------------
#endif

