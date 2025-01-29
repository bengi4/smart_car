/*
 * control.c
 *
 *  Created on: 2025年1月8日
 *      Author: 10834
 */
#include "zf_common_headfile.h"
int error=0;
float dif_speed,dif_speed_k;
int speed_used=2000;

void get_error()
{

    for(int i=105;i<=115;i++)
    {
        error +=(int)((center_line[i]-94)/10);
    }
    ips200_show_int(200, 220, error, 3);

}

void get_diff()
{
    dif_speed=dif_speed_k*error;
    if(error==0)
    {
        speedl=speed_used;
        speedr=speed_used;
    }
    else if(error<0)
    {

        limit_a_b(error,-speed_used,0);
        speedl=(int)(speed_used-dif_speed);
        speedr=(int)(speed_used);
    }
    else
    {
        limit_a_b(error,0,3000);
        speedl=(int)(speed_used);
        speedr=(int)(speed_used-dif_speed);
    }
}
void pwm_out()
{
//    left_pwm_out=0;
//    right_pwm_out=0;//���ע��ȡ�� ��Ϊ����

    if(speedl>=0)
    {
        gpio_set_level(P21_5, 1);
        pwm_set_duty(PWM_CH4, speedl);
    }
    else
    {
        gpio_set_level(P21_5, 0);
        pwm_set_duty(PWM_CH4, speedl);
    }
    if(speedr>=0)
    {
        gpio_set_level(P21_3, 1);
        pwm_set_duty(PWM_CH1, speedr);//r
    }
    else
    {
        gpio_set_level(P21_3, 0);
        pwm_set_duty(PWM_CH1, speedr);//r
    }
}
void control()
{
//      get_error();
//    get_diff();
//    pwm_out();


}
