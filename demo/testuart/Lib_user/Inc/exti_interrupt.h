#ifndef __EXTI_INTERRUPT_H
#define __EXTI_INTERRUPT_H

#include "stm32f1xx_hal.h"
#include <var.h>
#include <define.h>

extern UART_HandleTypeDef huart2;  // Đảm bảo UART_HandleTypeDef đã được định nghĩa ở đâu đó
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
static void Handle_GPIO_PIN_1(void);
static void Handle_GPIO_PIN_5(void);
static void Handle_GPIO_PIN_6(void);
static void Handle_GPIO_PIN_7(void);

#endif // __EXTI_INTERRUPT_H
