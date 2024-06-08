#ifndef __VAR_DEFINE_H
#define __VAR_DEFINE_H

#include "stm32f1xx_hal.h"




// Định nghĩa các biến toàn cục
extern uint32_t sta1;
extern uint32_t sta2;
extern uint32_t positionmax;
extern int8_t state;
extern int8_t ngatuart;
extern uint8_t rxData;
extern uint8_t bufferIndex;
extern uint32_t current_position2;
extern uint32_t current_position3;
extern uint32_t current_position4;
extern uint32_t dem2;
extern uint32_t dem3;
extern uint32_t dem4;
extern uint16_t period2;
extern uint16_t period3;
extern uint16_t period4;
extern uint8_t isTimerInterrupt2;
extern uint8_t isTimerInterrupt3;
extern uint8_t isTimerInterrupt4;
extern uint8_t flag2;
extern uint8_t flag3;
extern uint8_t flag4;
extern char uartBuffer[100];
extern float numbers[7];
extern float targetSpeed2;
extern float targetSpeed3;
extern float targetSpeed4;
extern float pre_targetSpeed2;
extern float pre_targetSpeed3;
extern float pre_targetSpeed4;
extern float currentSpeed2;
extern float currentSpeed3;
extern float currentSpeed4;
extern float acceleration4;
extern float acceleration2;
extern float acceleration3;
extern float acceleration1;
extern uint32_t biennho2;
extern uint32_t biennho3;
extern uint32_t biennho4;
extern int xungmotor2;
extern int xungmotor3;
extern int xungmotor4;
extern int pre_xungmotor2;
extern int pre_xungmotor3;
extern int pre_xungmotor4;

#endif /* __VAR_DEFINE_H */
