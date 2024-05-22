#include "PID_Control.h"

float Average_5_times(float Var, float Temp[20]){
    float sum = 0, Out_Average_Var; // Initialize sum to 0
    for (int i = 0; i < 19; i++)
    {
        Temp[i] = Temp[i + 1];  // gán giá trị hiện tại vào giá trị trước
        sum += Temp[i];        // Cộng dần các giá trị vừa lưu
    }
    // Gán giá trị mới nhất
    Temp[19] = Var;
    sum += Temp[19] ;
    // Tính trung bình
    Out_Average_Var = sum / 20;
    return Out_Average_Var;
}