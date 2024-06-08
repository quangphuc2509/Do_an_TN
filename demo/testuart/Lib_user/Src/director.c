#include "director.h"
#include <var.h>
#include <define.h>

/*Hàm xác định chiều của 3 động cơ, nếu xung dương thì quay cùng chiều, xung âm thì quay ngược chiều */

void director(void){

    if (xungmotor2 > 0) {
        HAL_GPIO_WritePin(STEP2_PORT, STEP2_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(DIR2_PORT, DIR2_PIN, GPIO_PIN_SET);
        flag2 = 1;
    } else if (xungmotor2 < 0) {
        xungmotor2 = -xungmotor2;
        HAL_GPIO_WritePin(STEP2_PORT, STEP2_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(DIR2_PORT, DIR2_PIN, GPIO_PIN_RESET);
        flag2 = 2;
    }

    if (xungmotor3 > 0) {
        HAL_GPIO_WritePin(STEP3_PORT, STEP3_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(DIR3_PORT, DIR3_PIN, GPIO_PIN_SET);
        flag3 = 1;
    } else if (xungmotor3 < 0) {
        xungmotor3 = -xungmotor3;
        HAL_GPIO_WritePin(STEP3_PORT, STEP3_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(DIR3_PORT, DIR3_PIN, GPIO_PIN_RESET);
        flag3 = 2;
    }

    if (xungmotor4 > 0) {
        HAL_GPIO_WritePin(STEP4_PORT, STEP4_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(DIR4_PORT, DIR4_PIN, GPIO_PIN_SET);
        flag4 = 1;
    } else if (xungmotor4 < 0) {
        xungmotor4 = -xungmotor4;
        HAL_GPIO_WritePin(STEP4_PORT, STEP4_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(DIR4_PORT, DIR4_PIN, GPIO_PIN_RESET);
        flag4 = 2;
    }

    biennho3 = (int)(targetSpeed3 / acceleration1);
    biennho2 = (int)(targetSpeed2 / acceleration1);
    biennho4 = (int)(targetSpeed4 / acceleration1);
}
