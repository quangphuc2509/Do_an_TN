/*
 * Fuzzy_KA_01.c
 *
 *  Created on: May 6, 2024
 *      Author: Admin
 */

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Fuzzy_01.h"

float triaf(float x, int n, int m, float A[n][3])
{
    float Ket_qua;
    float Temp_1;
    // Ve phuong trinh duong thang trong 2 mien a->b vs b->c
    if(x >= A[m][0] && x < A[m][1])
    {
        Temp_1 = 1.0 - (1.0/(A[m][1]-A[m][0]))*A[m][1];  // he so b trong y = ax+b
        Ket_qua = ((1.0/(A[m][1] - A[m][0]))*x) + Temp_1;
    }
    else if (x >= A[m][1] && x <= A[m][2])
    {
        Temp_1 = 1 - (-1/(A[m][2]-A[m][1]))*A[m][1];
        Ket_qua = ((-1/(A[m][2]-A[m][1]))*x) + Temp_1;
    }
    else
    {
        //printf("Khong thuoc tap hop");
        Ket_qua = 0;
    }
    return Ket_qua;
}

// Hàm kiểm tra xem với 1 x bất kì thuộc tập hợp nào của input
// Với n là số lượng membership function của inpur đó
void Processing(float x, int8_t n, float Input[n][3], int8_t ID1[n], float Value_ID[n])
{
    int i = 0;
    float Temp = 0;
        //Kiem tra x co thuoc tap hop Input nao
        for(i=0;i<n; i++)
        {
            if(x > Input[i][0] && x < Input[i][2])  // So sánh xem x có thuộc khoảng Min Input[0] và nhỏ hơn Max Input[2]
            {
                // Nếu thuộc khoảng nào thì ID của khoảng đó sẽ lên 1
                ID1[i] = 1;
                //printf("%f ID la %d \n",x, i + 1);
                // Tính ra giá trị phụ thuộc muy (u) của hàm đó
                Temp = triaf(x, n, i, Input);  // Tính giá trị ra biến tạm và gán vào Value của ID đó
                Value_ID[i] = Temp;
            }
            else if (x <= Input[i][0] || x >= Input[i][2])
            {
                // Nếu không thuoccj thì ID tại đó bằng 0
                ID1[i] = 0;
                Value_ID[i] = 0;
            }
        }
}

// Hàm so sánh giá trị và tạo luật điều khiển
// Với ID1, ID2 là mảng chứa thông tin xem với giá trị x đó thì nó thuộc khoảng của membership function nào
// Value_ID là giá trị phụ thuộc của membership function đó là muy(u)
// Với e là vị trí của output và Output_P là mảng chứa output
// Luật được tạo ra là quan hệ input i1, i2 và output o1
void Rule(int8_t ID1[], int8_t ID2[], float Output[], float Value_ID_1[], float Value_ID_2[], int8_t e, float Output_P[e][2], int8_t i1, int8_t i2, int8_t o1)
{
    if(ID1[i1] == 1 && ID2[i2] == 1)
    {
        if(Value_ID_1[i1]<Value_ID_2[i2])
        {
            if(Value_ID_1[i1] != 0)
            {
                Output_P[e][0] = Value_ID_1[i1] * Output[o1];
                Output_P[e][1] = Value_ID_1[i1];
            }
            else if(Value_ID_1[i1] == 0)
            {
                Output_P[e][0] = Value_ID_2[i2] * Output[o1];
                Output_P[e][1] = Value_ID_2[i2];
            }
        }
        else if(Value_ID_1[i1]>Value_ID_2[i2])
        {
            if(Value_ID_2[i2] != 0)
            {
                Output_P[e][0] = Value_ID_2[i2] * Output[o1];
                Output_P[e][1] = Value_ID_2[i2];
            }
            else if(Value_ID_2[i2] == 0)
            {
                Output_P[e][0] = Value_ID_1[i1] * Output[o1];
                Output_P[e][1] = Value_ID_1[i1];
            }
        }
        else if (Value_ID_1[i1] == Value_ID_2[i2])
        {
            if(Value_ID_1[i1] != 0)
            {
                Output_P[e][0] = Value_ID_1[i1] * Output[o1];
                Output_P[e][1] = Value_ID_1[i1];
            }
            else
            {
                Output_P[e][0] = 0;
                Output_P[e][1] = 0;
            }
        }
    }
    else
    {
        Output_P[e][0] = 0;
        Output_P[e][1] = 0;
    }
}

void Final_Value_FC(float Target, float Final_Value[], int8_t num_Rule, float Output_PWM[][2])
{
    int i = 0;
    // Sau khi tạo luật xong thì cộng dồn giá trị vào Final_Value
    for(i=0;i<num_Rule;i++)
    {
        Final_Value[0] = Final_Value[0] + Output_PWM[i][0];
        Final_Value[1] = Final_Value[1] + Output_PWM[i][1];
    }
    // Kết quả cuối cùng là chia tử với mẫu
    Target = Final_Value[0] / Final_Value[1];
}


