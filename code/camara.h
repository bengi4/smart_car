/*
 * camara.h
 *
 *  Created on: 2025年1月8日
 *      Author: 10834
 */

#ifndef CODE_CAMARA_H_
#define CODE_CAMARA_H_

#include "zf_common_typedef.h"
#include "zf_common_headfile.h"

#define white_pixel 255
#define black_pixel 0

#define bin_jump_num    1//跳过的点数
#define border_max  image_w-2 //边界最大值
#define border_min  1   //边界最小值

#define image_w 94
#define image_h 60

extern void image_process(void);
extern uint8 original_image[image_h][image_w];
extern uint8 bin_image[image_h][image_w];//图像数组
extern uint8 center_line[image_h];
extern uint8 r_border[image_h];
extern uint8 l_border[image_h];
extern int16 limit_a_b(int16 x, int a, int b);

extern int wucha;

#endif /* CODE_CAMARA_H_ */
