/*
 * element.h
 *
 *  Created on: 2025��1��9��
 *      Author: 10834
 */

#ifndef CODE_ELEMENT_H_
#define CODE_ELEMENT_H_

#include "zf_common_headfile.h"
float Slope_Calculate(uint8 begin, uint8 end, uint8 *border);
void calculate_s_i(uint8 start, uint8 end, uint8 *border, float *slope_rate, float *intercept);
void cross_fill(uint8(*image)[image_w], uint8 *l_border, uint8 *r_border, uint16 total_num_l, uint16 total_num_r,
                                         uint16 *dir_l, uint16 *dir_r, uint16(*points_l)[2], uint16(*points_r)[2]);


#endif /* CODE_ELEMENT_H_ */
