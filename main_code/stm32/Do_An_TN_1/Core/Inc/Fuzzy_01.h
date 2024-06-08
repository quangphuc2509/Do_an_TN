/*
 * Fuzzy_KA_01.h
 *
 *  Created on: May 6, 2024
 *      Author: Admin
 */

#ifndef INC_FUZZY_01_H_
#define INC_FUZZY_01_H_

// Hàm vẽ membership function dạng tam giác
float triaf(float x, int n, int m, float A[n][3]);

// Hàm kiểm tra xem với 1 x bất kì thuộc tập hợp nào của input
// Với n là số lượng membership function của inpur đó
void Processing(float x, int8_t n, float Input[n][3], int8_t ID1[n], float Value_ID[n]);

// Hàm so sánh giá trị và tạo luật điều khiển
// Với ID1, ID2 là mảng chứa thông tin xem với giá trị x đó thì nó thuộc khoảng của membership function nào
// Value_ID là giá trị phụ thuộc của membership function đó là muy(u)
// Với e là vị trí của output và Output_P là mảng chứa output
// Luật được tạo ra là quan hệ input i1, i2 và output o1
void Rule(int8_t ID1[], int8_t ID2[], float Output[], float Value_ID_1[], float Value_ID_2[], int8_t e, float Output_P[e][2], int8_t i1, int8_t i2, int8_t o1);

// Hàm tính ra output của Fuzzy
void Final_Value_FC(float Target, float Final_Value[], int8_t num_Rule, float Output_PWM[][2]);

/**************************************Example******************************************/

    // // Bien dem
    // int i, j, k;
    // // Tạo x1 x2 bất kì
    // float x1, x2;

    // //**********************Instruction**********************//
    // // Tạo Input theo lần lược từ thấp đến lớn với mỗi mảng có 3 giá trị Input[x][3]
    // float IN_01[5][3] = {{-1000000, -1, -0.1}, {-0.2, -0.1, 0}, {-0.001, 0, 0.001}, {0, 0.1, 0.2}, {0.1, 1, 1000000}};
    // float IN_02[5][3] = {{-1000000, -1, -0.3}, {-0.3, -0.1, 0}, {-0.01, 0, 0.01}, {0, 0.1, 0.3}, {0.3, 1, 1000000}};
    // // Tạo Output
    // float Output[5] = {-1, -0.5, 0, 0.5, 1};
    // // Tạo mảng cho ID và giá trị của ID so sánh
    // int8_t ID1[5], ID2[5];
    // float Value_1[5], Value_2[5];
    // // Tạo mảng lưu Output
    // float Output_PWM[25][2];
    // float Final_Value[2];
    // float Target;
    // /***********************************************************/

    // // Tiền xử lí dữ liệu khi có biến x1 và x2 để biết nó thuộc membership nào
    // // Sau khi tính ra thì biết được sự liên thuộc qua ID và mỗi ID sẽ có một giá trị liên thuộc của nó là Value_ID
    // Processing(x1, 5, IN_01, ID1, Value_1);
    // Processing(x2, 5, IN_02, ID2, Value_2);
    // // Sau khi tiền xử lí thì nó so sánh xem nó thuộc bộ luật nào
    // // Nó sẽ tính ra output vào Output_PWM với Output_PWM[0] là giá trị phần trên tử vs Output_PWM[1] là giá trị phần dưới mẫu
    // printf("\n\n");
    // Rule(ID1, ID2, Output, Value_1, Value_2, 0 , Output_PWM, 0, 0, 0);  // Rule 1 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 1 , Output_PWM, 0, 1, 0);  // Rule 2 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 2 , Output_PWM, 0, 2, 1);  // Rule 3 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 3 , Output_PWM, 0, 3, 1);  // Rule 4 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 4 , Output_PWM, 0, 4, 2);  // Rule 5 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 5 , Output_PWM, 1, 0, 0);  // Rule 6 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 6 , Output_PWM, 1, 1, 1);  // Rule 7 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 7 , Output_PWM, 1, 2, 2);  // Rule 8 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 8 , Output_PWM, 1, 3, 2);  // Rule 9 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 9 , Output_PWM, 1, 4, 3);  // Rule 10 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 10, Output_PWM, 2, 0, 1);  // Rule 11 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 11, Output_PWM, 2, 1, 2);  // Rule 12 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 12, Output_PWM, 2, 2, 2);  // Rule 13 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 13, Output_PWM, 2, 3, 2);  // Rule 14 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 14, Output_PWM, 2, 4, 3);  // Rule 15 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 15, Output_PWM, 3, 0, 1);  // Rule 16 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 16, Output_PWM, 3, 1, 2);  // Rule 17 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 17, Output_PWM, 3, 2, 2);  // Rule 18 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 18, Output_PWM, 3, 3, 3);  // Rule 19 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 19, Output_PWM, 3, 4, 4);  // Rule 20 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 20, Output_PWM, 4, 0, 2);  // Rule 21 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 21, Output_PWM, 4, 1, 3);  // Rule 22 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 22, Output_PWM, 4, 2, 3);  // Rule 23 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 23, Output_PWM, 4, 3, 4);  // Rule 24 (0 0 1)
    // Rule(ID1, ID2, Output, Value_1, Value_2, 24, Output_PWM, 4, 4, 4);  // Rule 25 (0 0 1)

    // Final_Value_FC(Target, Final_Value, 25, Output_PWM);






#endif /* INC_FUZZY_01_H_ */
