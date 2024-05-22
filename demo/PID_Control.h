/*
 * PID_Control.h
 *
 *  Created on: Apr 27, 2024
 *      Author: quang
 */
#include "stdint.h"
#include "stdio.h"
#ifndef INC_PID_CONTROL_H_
#define INC_PID_CONTROL_H_



struct PID_Motor{
	float HIGH, LOW;
	float Kp, Ki, Kd;
	float Up, Up_1;
	double Ui, Ui_1;
	float Ud, Ud_1;
	double Ui_Antiwindup;
	uint16_t Out_PWM;
	double Temp_PWM;
	float Out_fPWM;
} PID_MR, PID_ML;

struct PID_Motor* pt_PID_MR = &PID_MR;


void pid_func(struct PID_Motor* pt_PID_M, float h );

float Average_5_times(float Var, float Temp[20]);


#endif /* INC_PID_CONTROL_H_ */
