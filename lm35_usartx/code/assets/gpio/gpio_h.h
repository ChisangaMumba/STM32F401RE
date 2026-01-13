#ifndef GPIO_H
#define GPIO_H
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdint.h>
#include <stm32f4xx.h>
//------------------------------------------------------------------------------
//												MODE Register (MODER) config
//------------------------------------------------------------------------------
#define INPUT         0
#define OUTPUT        1
#define ALTFUN	      2
#define ANALOG 	      3
//------------------------------------------------------------------------------
//												Outpute SPEED Register (OSPEEDR) config
//------------------------------------------------------------------------------
#define LOWS_PEED     0
#define MEDIUM_SPEED  1
#define FAST_SPEED    2
#define HIGH_SPEED    3
//------------------------------------------------------------------------------
//												Pull-Up Pull-Down Register (PUPDR) config
//------------------------------------------------------------------------------
#define NO_PU_PD     	0
#define PULL_UP       1
#define PULL_DOWN			2
//------------------------------------------------------------------------------
//												Outpute TYPE Register (OTYPER) config
//------------------------------------------------------------------------------
#define PUSH_PULL     0		
#define OPEN_DRAIN    1		
//------------------------------------------------------------------------------
#define LOW           0
#define HIGH          1
//------------------------------------------------------------------------------
enum PORTA{PA0 = 0,   PA1,PA2,PA3,PA4,PA5,PA6,PA7,PA8,PA9,PA10,PA11,PA12,PA13,PA14,PA15}; 
enum PORTB{PB0 = 16,  PB1,PB2,PB3,PB4,PB5,PB6,PB7,PB8,PB9,PB10,PB11,PB12,PB13,PB14,PB15}; 
enum PORTC{PC0 = 32,  PC1,PC2,PC3,PC4,PC5,PC6,PC7,PC8,PC9,PC10,PC11,PC12,PC13,PC14,PC15}; 
enum PORTD{PD0 = 48,  PD1,PD2,PD3,PD4,PD5,PD6,PD7,PD8,PD9,PD10,PD11,PD12,PD13,PD14,PD15}; 
enum PORTE{PE0 = 64,  PE1,PE2,PE3,PE4,PE5,PE6,PE7,PE8,PE9,PE10,PE11,PE12,PE13,PE14,PE15}; 
enum PORTF{PF0 = 80,  PF1,PF2,PF3,PF4,PF5,PF6,PF7,PF8,PF9,PF10,PF11,PF12,PF13,PF14,PF15}; 
enum PORTG{PG0 = 96,  PG1,PG2,PG3,PG4,PG5,PG6,PG7,PG8,PG9,PG10,PG11,PG12,PG13,PG14,PG15}; 
enum PORTH{PH0 = 112, PH1,PH2,PH3,PH4,PH5,PH6,PH7,PH8,PH9,PH10,PH11,PH12,PH13,PH14,PH15}; 
enum PORTI{PI0 = 128, PI1,PI2,PI3,PI4,PI5,PI6,PI7,PI8,PI9,PI10,PI11,PI12,PI13,PI14,PI15}; 
enum PORTJ{PJ0 = 144, PJ1,PJ2,PJ3,PJ4,PJ5,PJ6,PJ7,PJ8,PJ9,PJ10,PJ11,PJ12,PJ13,PJ14,PJ15}; 
//------------------------------------------------------------------------------
void HSI_init(void);
GPIO_TypeDef * getGPIO(uint8_t gpioPortNum);
void pinMode(uint16_t portPin, uint8_t mode, uint8_t oType);
void digitalWrite(uint16_t portPin, uint8_t state);
//------------------------------------------------------------------------------
#endif 
