/*
 * init.c
 *
 *  Created on: 2025��1��11��
 *      Author: 10834
 */

#include "zf_common_headfile.h"
void all_init()
{

    mt9v03x_init();
    ips200_init(IPS200_TYPE_PARALLEL8);

    pwm_init(PWM_CH1, 17000, 0);                                                // ��ʼ�� PWM ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%r
  //  pwm_init(PWM_CH2, 17000, 0);                                                // ��ʼ�� PWM ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%
  //  pwm_init(PWM_CH3, 17000, 0);                                                // ��ʼ�� PWM ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%
    pwm_init(PWM_CH4, 17000, 0);                                                // ��ʼ�� PWM ͨ�� Ƶ�� 17KHz ��ʼռ�ձ� 0%l
    gpio_init(PWM1_dir, GPO, 1, GPO_PUSH_PULL);//��ʼ����������r
    gpio_init(PWM2_dir, GPO, 1, GPO_PUSH_PULL);//��ʼ����������l
    PID_init(&pid_left,     PID_DELTA,      pid_left_arr,   10000.0f,   10000.0f);
    PID_init(&pid_right,     PID_DELTA,      pid_left_arr,   10000.0f,   10000.0f);
    encoder_dir_init(L_ENCODER_DIR, L_ENCODER_DIR_PULSE, L_ENCODER_DIR_DIR);   // ��ʼ��������ģ�������� �������������ģʽ
    encoder_dir_init(R_ENCODER_DIR, R_ENCODER_DIR_PULSE, R_ENCODER_DIR_DIR);
    wireless_uart_init();

    seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_DEBUG_UART);

    pit_ms_init(CCU60_CH0, 5);
    pit_ms_init(CCU60_CH1, 10);
}
