/*
 * PID_XY.h
 *
 *  Created on: May 14, 2024
 *      Author: Admin
 */

#ifndef INC_PID_XY_H_
#define INC_PID_XY_H_


// Khai báo struct của PID x,y
struct PID_XY
{
	float Kp, Ki, Kd;   // Thông số 3 khâu PID
	float Ui, Ui_1, Ud, Ud_1, Up;  // Các Up,Ui,Ud
	float Output_Temp, Output; // Giá trị output và biến tạm output
	float ek, ek_1;  // Giá trị sai số
	float High_Limit, Low_Limit;  // Ngưỡng trên và dưới của Output PID
	float Kb; // Khâu Antiwindup
};

struct Possision_Input
{
	float x,y;
	float theta_tiep_tuyen;
};

extern float Time_Interrupt_global;

void Test_duong_thang(struct Possision_Input* Pos, float a, float b, float x_robot, float y_robot);
// Xử lí sai số
void Processing_Error(struct PID_XY* Theta_Ctrl, struct PID_XY* Pos_Ctrl, struct Possision_Input* Pos, float x_robot, float theta_robot);
void PID_XY(struct PID_XY* u1);

#endif /* INC_PID_XY_H_ */
