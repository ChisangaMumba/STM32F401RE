#ifndef THREE_WIRE_H
#define	THREE_WIRE_H
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define DQ    PB0
#define CLK   PB1
#define RST   PB2
//------------------------------------------------------------------------------
void threeWire_init(void);
void threeWire_start(void);
void threeWire_stop(void);
int16_t threeWire_read(void);
void threeWire_write(int16_t data_, uint8_t sz);
//------------------------------------------------------------------------------
void threeWire_init(void)
{
	pinMode(DQ, OUTPUT, PUSH_PULL);                                               
	pinMode(CLK, OUTPUT, PUSH_PULL);             
	pinMode(RST, OUTPUT, PUSH_PULL);       
}
//------------------------------------------------------------------------------
void threeWire_start(void)
{
	digitalWrite(RST, LOW);     	// RST = 0;
	digitalWrite(CLK, HIGH);    	// CLK = 1;
	digitalWrite(RST, HIGH);     	// RST = 1;
}
//------------------------------------------------------------------------------
void threeWire_stop(void)
{
	digitalWrite(RST, LOW);      	// RST = 0;
}
//------------------------------------------------------------------------------
void threeWire_write(int16_t data, uint8_t sz)
{
	pinMode(DQ, OUTPUT, PUSH_PULL);
	
	for(int tx = 0; tx < sz; tx++)
	{
		digitalWrite(CLK, LOW);     	// CLK = 0;
		digitalWrite(DQ, ((data >> tx) & 0x01) ? HIGH : LOW);   //LSB first (Real 12c sends MSB first)
		digitalWrite(CLK, HIGH);     	// CLK = 1;
	}
	
	pinMode(DQ, INPUT, PUSH_PULL);
}
//------------------------------------------------------------------------------
int16_t threeWire_read(void)
{	
	int16_t data = 0;

  pinMode(DQ, INPUT, PUSH_PULL);                 

	for(uint8_t rx = 0; rx < 9; rx++)
	{
    digitalWrite(CLK, LOW);         // CLK = 0;
		data += (digitalRead(DQ) << rx);
		digitalWrite(CLK, HIGH);        // CLK = 1;
	}
	
	pinMode(DQ, OUTPUT, PUSH_PULL);                

	return data;
}
//------------------------------------------------------------------------------
#endif
