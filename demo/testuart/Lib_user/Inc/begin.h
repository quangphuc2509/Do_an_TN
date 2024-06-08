#ifndef __BEGIN_H
#define __BEGIN_H

#include "stm32f1xx_hal.h"
#include <var.h>
#include <define.h>

extern UART_HandleTypeDef huart2;  // Đảm bảo UART_HandleTypeDef đã được định nghĩa ở đâu đó
void reset_EN(void);
void reset_step(void);
void reset_dir(void);
void khoi_tao(void);
void reset_thong_so(void);


#endif /* __BEGIN_H */
