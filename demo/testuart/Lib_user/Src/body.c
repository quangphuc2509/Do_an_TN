#include "body.h"

void gan_du_lieu_uart(void){
	ngatuart=0;
	xungmotor2=pre_xungmotor2;
	xungmotor3=pre_xungmotor3;
	xungmotor4=pre_xungmotor4;
	targetSpeed2=pre_targetSpeed2;
	targetSpeed3= pre_targetSpeed3;
	targetSpeed4=pre_targetSpeed4;
}

void reset_gia_tri_dem(void){
	dem2=0;
	dem3=0;
	dem4=0;
	state=0;
	sta1=0;
}

void send_encoder_begin(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,0);
}
void send_encoder_finish(void){
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,1);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,0);
}

void begin_motor(void){
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);
}

void stop_motor(void){
	ngatuart=0;
	isTimerInterrupt2 = 1;
	isTimerInterrupt3 = 1;
	isTimerInterrupt4 = 1;
	HAL_TIM_Base_Stop_IT(&htim2);
	HAL_TIM_Base_Stop_IT(&htim3);
	HAL_TIM_Base_Stop_IT(&htim4);
	HAL_GPIO_WritePin(EN2_PORT, EN2_PIN, 1);
	HAL_GPIO_WritePin(EN3_PORT, EN3_PIN, 1);
	HAL_GPIO_WritePin(EN4_PORT, EN4_PIN, 1);
}

void wait_uart(void){
	while(!(ngatuart)){};
}

void wait_motor_finish(void){
	while (!((isTimerInterrupt2==1)&&(isTimerInterrupt3==1)&&(isTimerInterrupt4==1))) {}
}

void motor_finish(void){
	if (((isTimerInterrupt2==1)&&(isTimerInterrupt3==1)&&(isTimerInterrupt4==1)))
	{
		send_encoder_finish();
		HAL_TIM_Base_Stop_IT(&htim1);
		isTimerInterrupt2 = 0;
		isTimerInterrupt3 = 0;
		isTimerInterrupt4 = 0;
		state=1;
		sta1=sta1+1;
		sta2= sta2+1;
		send_uart();
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
}

void send_uart(void){
	char buffer12[200];
	sprintf(buffer12, "an%dn%.3fn%dn%.3fn%dn%.3fn%dn%dnz\n", current_position2, currentSpeed2, current_position3, currentSpeed3, current_position4, currentSpeed4, sta2, state);
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer12, strlen(buffer12), HAL_MAX_DELAY);
}
