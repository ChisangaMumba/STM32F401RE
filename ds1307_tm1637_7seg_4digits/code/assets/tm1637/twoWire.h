#ifndef TWO_WIRE_H
#define TWO_WIRE_H
//------------------------------------------------------------------------------
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "../delay/delay_c.h"
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define CLK   PA0			// Clock pin
#define DIO   PA1			// Data I/O pin
//------------------------------------------------------------------------------
void twoWire_init(void)
{	
	pinMode(CLK, OUTPUT, PUSH_PULL);

  digitalWrite(CLK, LOW);   					// CLK = 0
  pinMode(DIO, OUTPUT, OPEN_DRAIN);		// DIO = 0
}
//------------------------------------------------------------------------------
void twoWire_start(void)
{	
	digitalWrite(CLK, HIGH);						// CLK = 1;
  pinMode(DIO, INPUT, OPEN_DRAIN);	  // DIO = 1;
  delay_us(2);
  pinMode(DIO, OUTPUT, OPEN_DRAIN);	  // DIO = 0;
}
//------------------------------------------------------------------------------
void twoWire_stop(void)
{	
	digitalWrite(CLK, LOW);	  					// CLK = 0;
  delay_us(2);
  pinMode(DIO, OUTPUT, OPEN_DRAIN);	  // DIO = 0;
  delay_us(2);
  digitalWrite(CLK, HIGH);						// CLK = 1;
  delay_us(2);
  pinMode(DIO, INPUT, OPEN_DRAIN);    // DIO = 1;
}
//------------------------------------------------------------------------------
void twoWire_ack(void)
{	
	digitalWrite(CLK, LOW);	  // CLK = 0;
  delay_us(5);
  digitalWrite(CLK, HIGH);	// CLK = 1;
  delay_us(2);
  digitalWrite(CLK, LOW);	  // CLK = 0;
}
//------------------------------------------------------------------------------
void twoWire_write(uint8_t data)
{
  for(char tx = 0 ; tx < 8 ; tx++)
  {		
	  digitalWrite(CLK, LOW);		// CLK = 0;
	  pinMode(DIO, ((data >> tx) & 0x01) ? INPUT : OUTPUT, OPEN_DRAIN);   // LSB first (Real 12c sends MSB first)   
	  digitalWrite(CLK, HIGH);	// CLK = 1;                    // Toggle CLK pin to latch data bit		
		
		delay_us(6);
  }
}
//------------------------------------------------------------------------------
#endif	/* tm1637_H */

