#include <var.h>

// Định nghĩa các biến toàn cục

uint32_t sta1=-1;
uint32_t sta2=0;
uint32_t positionmax;
int8_t state=0;
int8_t ngatuart=0;
uint8_t rxData = 0;
uint8_t bufferIndex = 0;
uint32_t current_position2=0;
uint32_t current_position3=0;
uint32_t current_position4=0;
uint32_t dem2=0;
uint32_t dem3=0;
uint32_t dem4=0;
uint16_t period2=720;
uint16_t period3=720;
uint16_t period4=720;
uint8_t isTimerInterrupt2 = 0;
uint8_t isTimerInterrupt3 = 0;
uint8_t isTimerInterrupt4 = 0;
uint8_t flag2=0;
uint8_t flag3=0;
uint8_t flag4=0;

char uartBuffer[100];
float numbers[7];
float targetSpeed2 = 69;
float targetSpeed3 = 138;
float targetSpeed4 = 138;
float pre_targetSpeed2 = 69;
float pre_targetSpeed3 = 138;
float pre_targetSpeed4 = 138;
float currentSpeed2 = 0.0;
float currentSpeed3 = 0.0;
float currentSpeed4 = 0.0;
float acceleration4 = 0.000681333316;
float acceleration2 = 0.000681333316;
float acceleration3 = 0.000681333316;
float acceleration1 = 0.000681333316;
uint32_t biennho2;
uint32_t biennho3;
uint32_t biennho4;
int xungmotor2;
int xungmotor3;
int xungmotor4;
int pre_xungmotor2;
int pre_xungmotor3;
int pre_xungmotor4;

