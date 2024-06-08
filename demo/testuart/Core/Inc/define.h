#ifndef __DEFINE_H
#define __DEFINE_H

#include "stm32f1xx_hal.h"

// Definitions for GPIO ports and pins
#define EN2_PORT GPIOA
#define EN2_PIN GPIO_PIN_8
#define DIR2_PORT GPIOA
#define DIR2_PIN GPIO_PIN_9
#define STEP2_PORT GPIOA
#define STEP2_PIN GPIO_PIN_10

#define EN3_PORT GPIOA
#define EN3_PIN GPIO_PIN_11
#define DIR3_PORT GPIOA
#define DIR3_PIN GPIO_PIN_12
#define STEP3_PORT GPIOB
#define STEP3_PIN GPIO_PIN_15

#define EN4_PORT GPIOB
#define EN4_PIN GPIO_PIN_7
#define DIR4_PORT GPIOB
#define DIR4_PIN GPIO_PIN_6
#define STEP4_PORT GPIOB
#define STEP4_PIN GPIO_PIN_5

#define UART_BUFFER_SIZE 100

#endif // __DEFINE_H
