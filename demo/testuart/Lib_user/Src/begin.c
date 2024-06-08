#include "begin.h"

void reset_EN(void){
	HAL_GPIO_WritePin(EN2_PORT, EN2_PIN, 0);
	HAL_GPIO_WritePin(EN3_PORT, EN3_PIN, 0);
	HAL_GPIO_WritePin(EN4_PORT, EN4_PIN, 0);
}

void reset_dir(void){
	HAL_GPIO_WritePin(DIR2_PORT, DIR2_PIN, 0);
	HAL_GPIO_WritePin(DIR3_PORT, DIR3_PIN, 0);
	HAL_GPIO_WritePin(DIR4_PORT, DIR4_PIN, 0);
}

void reset_step(void){
	HAL_GPIO_WritePin(STEP2_PORT, STEP2_PIN, 0);
	HAL_GPIO_WritePin(STEP3_PORT, STEP3_PIN, 0);
	HAL_GPIO_WritePin(STEP4_PORT, STEP4_PIN, 0);
}

void reset_thong_so(void){
	currentSpeed2 = 0.0;
	currentSpeed3 = 0.0;
	currentSpeed4 = 0.0;
	acceleration2 = 0.000681333316;
	acceleration3 = 0.000681333316;
	acceleration4 = 0.000681333316;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,0);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,0);
}
void khoi_tao(void){
	HAL_UART_Receive_IT(&huart2, uartBuffer, 1);
	reset_EN();
	reset_dir();
}
