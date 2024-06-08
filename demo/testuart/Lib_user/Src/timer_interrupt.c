#include "timer_interrupt.h"
#include "define.h"
#include "var.h"
#include "body.h"
#include <string.h> // Add this line to include the declaration of strlen

/*Hàm ngắt Timer*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM1) {
        Handle_TIM1();
    } else if (htim->Instance == TIM2) {
        Handle_TIM2();
    } else if (htim->Instance == TIM3) {
        Handle_TIM3();
    } else if (htim->Instance == TIM4) {
        Handle_TIM4();
    } else {

    }
}

void Handle_TIM1(void) {
	// Logic cho Timer 1
	sta1 = sta1 + 1;
	sta2 = sta1*2;
	send_uart();
}

void Handle_TIM2(void) {
	 // Logic cho Timer 2
	 if (flag2 == 1) {current_position2 = current_position2 + 1;}
	 else if (flag2 == 2) {
	    if (current_position2 == 0) {current_position2 = current_position2 + 1;}
	    current_position2 = current_position2 - 1;
	  }
	 dem2 = dem2 + 1;
	 HAL_GPIO_WritePin(STEP2_PORT, STEP2_PIN, 1);
	 HAL_GPIO_WritePin(STEP2_PORT, STEP2_PIN, 0);
	 currentSpeed2 = currentSpeed2 + acceleration2;
	 if (currentSpeed2 >= targetSpeed2) {currentSpeed2 = targetSpeed2;}
	 period2 = calculate_Period2(currentSpeed2);
	 TIM2->ARR = period2;
	 if (xungmotor2 > (biennho2 * 2)) {
	    if (dem2 >= ((int)(xungmotor2 - (biennho2 - 100)))) {acceleration2 = -acceleration1;}
	 } else if (xungmotor2 > 0) {
	    if (dem2 <= (biennho2 * 2)) {
	    	if (dem2 >= ((int)((xungmotor2 / 2) + 100))) {acceleration2 = -acceleration1;}
	     }
	 }
	 if (dem2 >= (xungmotor2)) {
	     isTimerInterrupt2 = 1;
	     HAL_TIM_Base_Stop_IT(&htim2);
	 }
}

void Handle_TIM3(void) {
	 // Logic cho Timer 3
	if (flag3 == 1) {current_position3 += 1;}
	else if (flag3 == 2) {
	  if (current_position3 == 0) {current_position3 = current_position3 + 1;}
	     current_position3 =current_position3-1;
	  }
	 dem3 = dem3 + 1;
	 HAL_GPIO_WritePin(STEP3_PORT, STEP3_PIN, 1);
	 HAL_GPIO_WritePin(STEP3_PORT, STEP3_PIN, 0);
	 currentSpeed3 = currentSpeed3 + acceleration3;
	 if (currentSpeed3 >= targetSpeed3) {currentSpeed3 = targetSpeed3;}
	 period3 = calculate_Period3(currentSpeed3);
	 TIM3->ARR = period3;
	 if (xungmotor3 > (biennho3 * 2)) {
	   if (dem3 >= ((int)(xungmotor3 - (biennho3 - 100)))) {acceleration3 = -acceleration1;}
	   } else if (xungmotor3 > 0) {
	      if (dem3 <= (biennho3 * 2)) {
	        if (dem3 >= ((int)((xungmotor3 / 2) + 100))) {acceleration3 = -acceleration1;}
	     }
	  }
	  if (dem3 >= (xungmotor3)) {
	     isTimerInterrupt3 = 1;
	     HAL_TIM_Base_Stop_IT(&htim3);
	  }
}

void Handle_TIM4(void) {
	 // Logic cho Timer 4
	 if (flag4 == 1) {current_position4 = current_position4 + 1;}
	 else if (flag4 == 2) {
	     if (current_position4 == 0) {current_position4 = current_position4 + 1;}
	     current_position4 = current_position4 - 1;
	 }
	 dem4 = dem4 + 1;
	 HAL_GPIO_WritePin(STEP4_PORT, STEP4_PIN, 1);
	 HAL_GPIO_WritePin(STEP4_PORT, STEP4_PIN, 0);
	 currentSpeed4 = currentSpeed4 + acceleration4;
	 if (currentSpeed4 >= targetSpeed4) {currentSpeed4 = targetSpeed4;}
	    period4 = calculate_Period4(currentSpeed4);
	    TIM4->ARR = period4;
	 if (xungmotor4 > (biennho4 * 2)) {
	    if (dem4 >= ((int)(xungmotor4 - (biennho4 - 100)))) {acceleration4 = -acceleration1;}
	 } else if (xungmotor4 > 0) {
	    if (dem4 <= (biennho4 * 2)) {
	      if (dem4 >= ((int)((xungmotor4 / 2) + 100))) {acceleration4 = -acceleration1;}
	    }
	 }
	 if (dem4 >= (xungmotor4)) {
	    isTimerInterrupt4 = 1;
	    HAL_TIM_Base_Stop_IT(&htim4);
	 }
}
