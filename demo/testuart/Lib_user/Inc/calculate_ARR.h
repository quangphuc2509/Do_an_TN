#ifndef __CALCULATE_ARR_H
#define __CALCULATE_ARR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

uint16_t calculate_Period2(float frequency);
uint16_t calculate_Period3(float frequency);
uint16_t calculate_Period4(float frequency);
uint16_t float_to_uint16(float number);

#ifdef __cplusplus
}
#endif

#endif /* __CALCULATE_ARR_H */
