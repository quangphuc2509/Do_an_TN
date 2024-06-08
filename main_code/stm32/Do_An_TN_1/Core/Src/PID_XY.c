/*
 * PID_XY.c
 *
 *  Created on: May 14, 2024
 *      Author: Admin
 */

#include "PID_XY.h"
#include "stm32f4xx_hal.h"
#include "math.h"
/*
vconst = Vc; %m/s

v1 = u1*L/2 + vconst;
v2 = -u1*L/2 + vconst;

v = (v1+v2)/2;

wr = v1/R;
wl = v2/R;
*/


// Lập quỹ đạo đường thẳng
void Test_duong_thang(struct Possision_Input* Pos, float a, float b, float x_robot, float y_robot)
{
	/*
	a = 1/3;
	b = 0;
	Delta_S = 0.001
	xf = (y_robot-b)/(a)
	yf = a*xf + b

	Theta_tiep_tuyen = atan2((a*(xf+Delta_S)+b-yf),(Delta_S))
	*/
	float Delta_S = 0.01; // Khoảng cách giữa hai điểm x và x+1

	Pos->x = (Pos->y - b)/(a);  // Cập nhật vị trí x quy hoạch
	Pos->y = a * Pos->x + b;   // Cập nhật vị trí y quy hoạch
	Pos->theta_tiep_tuyen = atan2f((a*(Pos->x + Delta_S) + b - Pos->y), Delta_S);  // Góc tiếp tuyến với quỹ đạo mà xe hướng đến

}

// Xử lí sai số
void Processing_Error(struct PID_XY* Theta_Ctrl, struct PID_XY* Pos_Ctrl, struct Possision_Input* Pos, float x_robot, float theta_robot)
{
	Theta_Ctrl->ek = Pos->theta_tiep_tuyen - theta_robot ; // Sai số góc theta của robot
	Pos_Ctrl->ek = -1*(Pos->x - x_robot); // Sai số của PID 2 là hiệu của x quy hoạch và x robot

}

void PID_XY(struct PID_XY* u1)
{
	u1->Up = u1->ek * u1->Kp;  // Khâu P
	u1->Ui = u1->Ui_1 + u1->Ki * u1->ek * Time_Interrupt_global;  // Khâu I
	u1->Ud = u1->Kd * (u1->ek - u1->ek_1)/(Time_Interrupt_global); // Khâu D
	u1->Output_Temp = u1->Up + u1->Ui + u1->Ud;  // Output PID

	// Limit Output
	if(u1->Output_Temp >= u1->High_Limit)
	{
		u1->Output = u1->High_Limit;
	}
	else if(u1->Output_Temp <= u1->Low_Limit)
	{
		u1->Output = u1->Low_Limit;
	}
	else
	{
		u1->Output = u1->Output_Temp;
	}

	// Gán lại sai số
	u1->Ui_1 = u1->Ui;
	u1->Ud_1 = u1->Ui;
	u1->ek_1 = u1->ek;
}


