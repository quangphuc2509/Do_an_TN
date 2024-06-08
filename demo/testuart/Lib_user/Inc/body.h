#ifndef __BODY_H
#define __BODY_H

#include "stm32f1xx_hal.h"
#include <var.h>
#include <define.h>

extern UART_HandleTypeDef huart2;  // Đảm bảo UART_HandleTypeDef đã được định nghĩa ở đâu đó
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

void gan_du_lieu_uart(void);
void reset_gia_tri_dem(void);
void send_encoder_begin(void);
void send_encoder_finish(void);
void begin_motor(void);
void stop_motor(void);
void wait_uart(void);
void wait_motor_finish(void);
void motor_finish(void);
void send_uart(void);

#endif /* __BODY_H */
