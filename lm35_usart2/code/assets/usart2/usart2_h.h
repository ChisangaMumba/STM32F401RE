#ifndef USART2_H
#define USART2_H
//------------------------------------------------------------------------------
#include <stdbool.h>
#include "../gpio/gpio_c.h"
#define SYSCLK_HZ    16000000U
char is_TReceived = false;
//------------------------------------------------------------------------------
void usart2_init(uint32_t baudrate);
uint8_t usart2_write(uint8_t ch);
uint8_t usart2_read(void);
//------------------------------------------------------------------------------
#endif /* USART_H */
