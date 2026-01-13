#ifndef GPIO_C
#define GPIO_C
//------------------------------------------------------------------------------
#include "../delay/delay_c.h"
#include "gpio_h.h"
//------------------------------------------------------------------------------
void system_config(void)
{
	HSI_init();
	//delay_init();
}
//------------------------------------------------------------------------------
void HSI_init(void)  //Set Clock to 16Mhz
{
	// Set the HSION bit and wait for HSIRDY
	RCC->CR |= 1UL << 0;
	while(!(RCC->CR & 2UL)){};

  // System clock switch to HSI		
  RCC->CFGR &= ~(3UL << 0);   // HSI oscillator selected as system clock
	RCC->CFGR &= ~(7UL << 27);  // MCO2 Prescaler. NO DIVISION selected 
	RCC->CFGR &= ~(3UL << 30);  // System clock (SYSCLK) selected
}
//------------------------------------------------------------------------------
GPIO_TypeDef * getGPIO(uint8_t gpioPortNum)
{
	GPIO_TypeDef * targetPort;
	
	switch(gpioPortNum)
	{
		case (0): targetPort = GPIOA; break;
		case (1): targetPort = GPIOB; break;
		case (2): targetPort = GPIOC; break;
		#ifdef GPIOD
		case (3): targetPort = GPIOD; break;
		#endif
		#ifdef GPIOE
		case (4): targetPort = GPIOE; break;
		#endif
		#ifdef GPIOF
		case (5): targetPort = GPIOF; break;
		#endif
		#ifdef GPIOG
		case (6): targetPort = GPIOG; break;
		#endif
		#ifdef GPIOH
		case (7): targetPort = GPIOH; break;
		#endif
		#ifdef GPIOI
		case (8): targetPort = GPIOI; break;
		#endif
		#ifdef GPIOJ
		case (9): targetPort = GPIOJ; break;
		#endif
		#ifdef GPIOK
		case (10): targetPort = GPIOK; break;
		#endif
	}
	
	return targetPort;
}
//------------------------------------------------------------------------------
void pinMode(uint16_t portPin, uint8_t mode, uint8_t oType, uint8_t pupd)
{
	uint8_t port = portPin / 16;
	uint8_t pin = portPin % 16;
	GPIO_TypeDef * GPIO = getGPIO(port);
	
	// RCC AHB1 peripheral clock enable register
	RCC->AHB1ENR |= (0x01UL << port);

	// Mode Register (MODER): input, output, Alt function, analogue
	GPIO->MODER &= ~(0x03UL<<(pin*2));	// Resetting the value of the bits
	GPIO->MODER |= (mode<<pin*2); 		// Setting up bit value to the mode
	
	if(mode == ALTFUN)
	{
		//uint8_t reg = pin/8;
		
		//GPIO->AFR[reg] &= ~(0x0FU << (pin*4));	// Resetting the value of the bits
    //GPIO->AFR[reg] |=  (pin   << (pin*4));	// AF1 = TIM2
		
		GPIO->AFR[0] &= ~(0x0FU << (0*4));	// Resetting the value of the bits
    GPIO->AFR[0] |=  (1U   << (0*4));	// AF1 = TIM2
	}
	
	// Output Type Register (OTYPER): push-pull or open drain
	if(oType == 1)
	{
		GPIO->OTYPER |= 0x01UL<<pin; 				// Set bit pos: open drain
	}
	else 
			if(oType == 0)
			{
				GPIO->OTYPER &= ~(0x01UL<<pin);	// reset bit pos: push-pull (reset state)
			}
	
	// Pull-Up Pull-Down Register (OSPEEDR):  No pull-up (reset state), pull-down;  Pull-up;  Pull-down
	GPIO->PUPDR &= ~(0x03UL<<(pin*2)); 			// Resetting the value of the bits
	//GPIO->PUPDR |= (PULL_UP<<pin*2); 		// Setting up bit value
	GPIO->PUPDR |= (pupd<<pin*2); 		// Setting up bit value
			
	// Output Speed Register (OSPEEDR): Low, medium, fast, high
	GPIO->OSPEEDR &= ~(0x03UL<<(pin*2)); 		// Resetting the value of the bits
	GPIO->OSPEEDR |= (FAST_SPEED<<pin*2); // Setting up bit value
}
//------------------------------------------------------------------------------
void digitalWrite(uint16_t portPin, uint8_t state)
{
	uint8_t port = portPin / 16;
	uint8_t pin = portPin % 16;
	GPIO_TypeDef * GPIO = getGPIO(port);		
	
	// Bit Set/Reset register (BSRR)
	uint32_t bitPos = 0x01UL << pin;
	GPIO->BSRR = (state) ? bitPos : (bitPos) << 16;
}
//------------------------------------------------------------------------------
uint8_t digitalRead(uint16_t portPin)
{
	uint8_t port = portPin / 16;
	uint8_t pin = portPin % 16;
	GPIO_TypeDef * GPIO = getGPIO(port);		
	
	// Input data register (IDR)
	uint16_t bitPos = 0x01UL << pin;
	uint8_t state = (GPIO->IDR & bitPos) ? HIGH : LOW;
	
	return state;
}
//------------------------------------------------------------------------------
#endif
