#ifndef EXTINT_C
#define	EXTINT_C
//------------------------------------------------------------------------------
#include <stdbool.h>
#include "../gpio/gpio_c.h"
//------------------------------------------------------------------------------
uint8_t pressCount = 0;
uint8_t isPaused = false;
//------------------------------------------------------------------------------
#define RISING_EDGE 	0
#define FALLING_EDGE 	1
//------------------------------------------------------------------------------
void extInt_init(uint8_t portPin, uint8_t trigger_mode)
{ 
	uint8_t port = portPin / 16;
	uint8_t pin = portPin % 16;
	GPIO_TypeDef * GPIO = getGPIO(port);
	
	// Enable System Config clock
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	// RCC AHB1 peripheral clock enable register
	RCC->AHB1ENR |= (0x01UL << port);
	
	// Mode Register (MODER): input, output, Alt function, analogue
	GPIO->MODER &= ~(0x03UL << (pin*2));	// Resetting the value of the bits
	GPIO->MODER |= INPUT << (pin*2); 		// Setting up bit value to the mode
	
	// External Interrupt Configuration Register (EXTICRx)
	uint8_t confReg = pin / 4;		// EXTICR0, EXTICR1, EXTICR2, EXTICR3
	uint8_t confPos = pin % 4;		// 0,1,2,3 e.g: |exti12 (0)| exti13 (1)| exti14 (2)| exti15 (3)|
	
	SYSCFG->EXTICR[confReg] &= ~(0x0F << (confPos * 4));// each register is 4 bits wide hence 4 shifts first ~(0x00F0);
	SYSCFG->EXTICR[confReg] |= port << (confPos * 4); 
	
	// Interuppt Mask Register (IMR)
	uint32_t pinPos = 0x01UL << pin;
	EXTI->IMR |= pinPos; // exti0, exti2, exti3...
	
	if(trigger_mode == 0)
	{
		// Rising Trigger Selection Register (RTSR)
		EXTI->RTSR |= pinPos; // Rising edge triggered.
	}	
	else
			{
				// Falling Trigger Selection Register (FTSR)
				EXTI->FTSR |= pinPos; // Falling edge triggered.
			}
		
	uint8_t irqNum;
  IRQn_Type EXTIx_IRQn;
	
	if(pin <= 4)
	{
		switch(pin)
		{
			case(0): irqNum = 6; 	EXTIx_IRQn = EXTI0_IRQn; break;
			case(1): irqNum = 7; 	EXTIx_IRQn = EXTI1_IRQn; break;
			case(2): irqNum = 8; 	EXTIx_IRQn = EXTI2_IRQn; break;
			case(3): irqNum = 9; 	EXTIx_IRQn = EXTI3_IRQn; break;
			case(4): irqNum = 10;	EXTIx_IRQn = EXTI4_IRQn; break;
		}
	}
	else
			if(pin >= 5 && pin <= 9)
			{
				irqNum = 23;
				EXTIx_IRQn = EXTI9_5_IRQn; // EXTI_9_IRQn to EXTI_5_IRQn
			}
			else
					if(pin >= 10 && pin <= 15)
					{
						irqNum = 40;
						EXTIx_IRQn = EXTI15_10_IRQn; // EXTI_15_IRQn to EXTI_10_IRQn
					}
	
	uint8_t extReg = irqNum / 32;		
	uint8_t extPos = irqNum % 32;
					
	NVIC->ISER[extReg] = 0x01UL << (extPos);
	NVIC_EnableIRQ(EXTIx_IRQn);
}
//------------------------------------------------------------------------------
void EXTI0_IRQHandler(void)
{
	// External Interrupt (push button)
  if(EXTI->PR & EXTI_PR_PR0)
	{		
		isPaused = (pressCount % 2 == 0) ? true : false;
	
		printf("%s\r\n", (isPaused == true) ? "paused" : "resumed");
		ADC1->CR2 |= (isPaused == true) ? 0 : 1;
		pressCount = (pressCount < 9) ? pressCount + 1 : 0;
	}	
	
	EXTI->PR = EXTI_PR_PR0;
}
//------------------------------------------------------------------------------
#endif
