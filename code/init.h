/*
 * init.h
 *
 *  Created on: 2025��1��11��
 *      Author: 10834
 */

#ifndef CODE_INIT_H_
#define CODE_INIT_H_

extern void init();
extern int16 L_encoder_data_quaddec;
extern int16 R_encoder_data_quaddec;
extern pid_type_def pid_left,pid_right;   //����PID�ṹ��
extern float pid_left_arr[3];   //����PID����
extern float pid_right_arr[3];  //����PID����
extern int speedl;
extern int speedr;



#endif /* CODE_INIT_H_ */
