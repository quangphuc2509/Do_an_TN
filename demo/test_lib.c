#include <stdio.h>
#include <stdint.h>
#include "PID_Control.h"

float Average_5_times(float Var, float Temp[20]);
float kq;
float mang[20] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
float var;
float temp[20];

int main(void){
    for (int i = 0; i < 20; i++)
    {
        var = mang[i];
        kq = Average_5_times(var, temp);
    }

    printf("Gia tri trung binh la: %f", kq);
    
}