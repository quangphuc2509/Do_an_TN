#ifndef __UART_INTERRUPT_H
#define __UART_INTERRUPT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart2;  // Đảm bảo UART_HandleTypeDef đã được định nghĩa ở đâu đó

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#ifdef __cplusplus
}
#endif

#endif /* __UART_INTERRUPT_H */
