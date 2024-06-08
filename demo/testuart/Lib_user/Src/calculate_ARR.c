#include "calculate_ARR.h"

/* Các hàm tính toán giá trị ARR dựa trên tần số có sẵn  */

uint16_t calculate_Period2(float frequency) {
	if (frequency <= 0.0f) {
	   return 0;
	}
    float period=((72000000.0 / (frequency * (720-1)*1000.0)) - 1);
    uint16_t period_u = float_to_uint16(period);
    return period_u;
}
uint16_t calculate_Period3(float frequency) {
	if (frequency <= 0.0f) {
		return 0;
	}
	float period=((72000000.0 / (frequency * (720-1)*1000.0)) - 1);
	uint16_t period_u = float_to_uint16(period);
	return period_u;
}
uint16_t calculate_Period4(float frequency) {
	if (frequency <= 0.0f) {
		return 0;
	}
	float period=((72000000.0 / (frequency * (720-1)*1000.0)) - 1);
	uint16_t period_u = float_to_uint16(period);
	return period_u;
}
uint16_t float_to_uint16(float number){
	 if (number < 0.0f) {
	        return 0;
	    } else if (number > 65535.0f) {
	        return 65535;
	    } else {
	        return (uint16_t)number;
	    }
}
