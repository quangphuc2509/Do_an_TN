#include "convert_position.h"
#include <math.h>

/*Hàm chuyển từ giáo trị xung sang giá trị chiều dài */

float convert_target_position(int xung) {
    const float SCALE_FACTOR = 12.22 * M_PI / 6400.0;
    return xung * SCALE_FACTOR;
}

/*Hàm chuyển từ giáo trị xung sang giá trị xung */
int convert_position_xung(float vitri) {
    const float SCALE_FACTOR = 12.22 * M_PI / 6400.0;
    return (int)(vitri / SCALE_FACTOR);
}
