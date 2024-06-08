#include "uart_interrupt.h"
#include <var.h>
#include <define.h>

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

// Định nghĩa hàm callback ngắt UART

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART2) {
        static int numbersIndex = 0;
        static char numberBuffer[20];
        if (uartBuffer[0] == 'a') {
            bufferIndex = 0;
        }
        uartBuffer[bufferIndex] = uartBuffer[0];
        bufferIndex++;
        if (uartBuffer[bufferIndex - 1] == 'z') {
            int i = 0;
            int j = 0;
            while (i < bufferIndex) {
                if (uartBuffer[i] == 'n') {
                    numberBuffer[j] = '\0';
                    sscanf(numberBuffer, "%f", &numbers[numbersIndex]);
                    numbersIndex++;
                    j = 0;
                } else {
                    numberBuffer[j] = uartBuffer[i];
                    j++;
                }
                i++;
            }
            bufferIndex = 0;
            numbersIndex = 0;
            pre_xungmotor2 = numbers[1];
            pre_targetSpeed2 = numbers[2];
            pre_xungmotor3 = numbers[3];
            pre_targetSpeed3 = numbers[4];
            pre_xungmotor4 = numbers[5];
            pre_targetSpeed4 = numbers[6];
            ngatuart = 1;
        }
        if (bufferIndex >= UART_BUFFER_SIZE) {
            bufferIndex = 0; // Reset buffer index
        }
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
        HAL_UART_Receive_IT(&huart2, uartBuffer, 1);
    }
}
