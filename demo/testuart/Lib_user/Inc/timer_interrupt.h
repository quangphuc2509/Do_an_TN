#ifndef TIMER_INTERRUPT_H
#define TIMER_INTERRUPT_H

#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart1;

extern uint16_t calculate_Period2(float speed);
extern uint16_t calculate_Period3(float speed);
extern uint16_t calculate_Period4(float speed);
extern uint16_t float_to_uint32(float number);

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void Handle_TIM1(void);
void Handle_TIM2(void);
void Handle_TIM3(void);
void Handle_TIM4(void);

#endif // TIMER_INTERRUPT_H
