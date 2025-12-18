#ifndef SPI_H
#define	SPI_H
//------------------------------------------------------------------------------
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
#define SCLK  PA3 
#define SDOUT PA4
#define SDIN  PA5
//------------------------------------------------------------------------------
void spi_init(void)
{
  pinMode(SCLK, OUTPUT, PUSH_PULL, NO_PU_PD);
  pinMode(SDOUT, OUTPUT, PUSH_PULL, NO_PU_PD);
  pinMode(SDIN, INPUT, PUSH_PULL, NO_PU_PD);
}
//--------------------------TX: transmit _data-----------------------------------
void spi_write(uint8_t send)
{	
	for(uint8_t tx = 0; tx < 8; tx++)
	{
		digitalWrite(SCLK, LOW);        //SCLK = 0;
    digitalWrite(SDOUT, ((send << tx) & 0x80) ? HIGH : LOW);  //MSB first
		digitalWrite(SCLK, HIGH);       //SCLK = 1;
	}
}
//--------------------------RX: recieve _data------------------------------------
uint8_t spi_read(void)
{
  uint8_t data = 0;
  
  for(uint8_t Rx = 0 ; Rx < 8 ; Rx++)
  {
    digitalWrite(SCLK, LOW);        //SCLK = 0;
    data += digitalRead(SDIN) << (7-Rx);     //MSB first.
		digitalWrite(SCLK, HIGH);       //SCLK = 1;
  }

  return data;
}
//------------------------------------------------------------------------------
#endif
