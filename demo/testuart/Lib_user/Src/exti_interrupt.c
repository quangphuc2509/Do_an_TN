#include "exti_interrupt.h"
#include "body.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_1) {
        Handle_GPIO_PIN_1();
    } else if (GPIO_Pin == GPIO_PIN_5) {
        Handle_GPIO_PIN_5();
    } else if (GPIO_Pin == GPIO_PIN_6) {
        Handle_GPIO_PIN_6();
    } else if (GPIO_Pin == GPIO_PIN_7) {
        Handle_GPIO_PIN_7();
    }
}

static void Handle_GPIO_PIN_5(void) {
	char buffer1234[200];
	sprintf(buffer1234, "ngatA5\n");
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer1234, strlen(buffer1234), HAL_MAX_DELAY);
	HAL_UART_AbortReceive(&huart2);
	stop_motor();
	for (int x=10000000; x>0;x--);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
	HAL_NVIC_ClearPendingIRQ(EXTI9_5_IRQn);

}

static void Handle_GPIO_PIN_1(void) {
	char bufferb4[200];
	sprintf(bufferb4, "ngatB1\n");
	HAL_UART_Transmit(&huart2, (uint8_t *)bufferb4, strlen(bufferb4), HAL_MAX_DELAY);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, 0);
	HAL_UART_Receive_IT(&huart2, uartBuffer, 1);
	reset_EN();
	for (int x=5000000; x>0;x--);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);
	HAL_NVIC_ClearPendingIRQ(EXTI1_IRQn);
}

static void Handle_GPIO_PIN_6(void) {
	char buffera5[200];
	sprintf(buffera5, "ngatA6\n");
	HAL_UART_Transmit(&huart2, (uint8_t *)buffera5, strlen(buffera5), HAL_MAX_DELAY);
	HAL_UART_AbortReceive(&huart2);
	stop_motor();
	for (int x=10000000; x>0;x--);
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6);
	HAL_NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
}

static void Handle_GPIO_PIN_7(void) {
	char buffera8[200];
	sprintf(buffera8, "ngatA7\n");
	HAL_UART_Transmit(&huart2, (uint8_t *)buffera8, strlen(buffera8), HAL_MAX_DELAY);
    HAL_UART_AbortReceive(&huart2);
    stop_motor();
    for (int x=10000000; x>0;x--);
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7);
    HAL_NVIC_ClearPendingIRQ(EXTI9_5_IRQn);
}
