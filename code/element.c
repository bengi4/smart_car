/*
 * element.c
 *
 *  Created on: 2025��1��9��
 *      Author: 10834
 */
#include "zf_common_headfile.h"

/**
* @brief ��С���˷�
* @param uint8 begin                �������
* @param uint8 end                  �����յ�
* @param uint8 *border              ������Ҫ����б�ʵı߽��׵�ַ
*  @see CTest       Slope_Calculate(start, end, border);//б��
* @return ����˵��
*     -<em>false</em> fail
*     -<em>true</em> succeed
*/
float Slope_Calculate(uint8 begin, uint8 end, uint8 *border)
{
    float xsum = 0, ysum = 0, xysum = 0, x2sum = 0;
    int16 i = 0;
    float result = 0;
    static float resultlast;

    for (i = begin; i < end; i++)
    {
        xsum += i;
        ysum += border[i];
        xysum += i * (border[i]);
        x2sum += i * i;

    }
    if ((end - begin)*x2sum - xsum * xsum) //�жϳ����Ƿ�Ϊ��
    {
        result = ((end - begin)*xysum - xsum * ysum) / ((end - begin)*x2sum - xsum * xsum);
        resultlast = result;
    }
    else
    {
        result = resultlast;
    }
    return result;
}

/**
* @brief ����б�ʽؾ�
* @param uint8 start                �������
* @param uint8 end                  �����յ�
* @param uint8 *border              ������Ҫ����б�ʵı߽�
* @param float *slope_rate          ����б�ʵ�ַ
* @param float *intercept           ����ؾ��ַ
*  @see CTest       calculate_s_i(start, end, r_border, &slope_l_rate, &intercept_l);
* @return ����˵��
*     -<em>false</em> fail
*     -<em>true</em> succeed
*/
void calculate_s_i(uint8 start, uint8 end, uint8 *border, float *slope_rate, float *intercept)
{
    uint16 i, num = 0;
    uint16 xsum = 0, ysum = 0;
    float y_average, x_average;

    num = 0;
    xsum = 0;
    ysum = 0;
    y_average = 0;
    x_average = 0;
    for (i = start; i < end; i++)
    {
        xsum += i;
        ysum += border[i];
        num++;
    }

    //�������ƽ����
    if (num)
    {
        x_average = (float)(xsum / num);
        y_average = (float)(ysum / num);

    }

    /*����б��*/
    *slope_rate = Slope_Calculate(start, end, border);//б��
    *intercept = y_average - (*slope_rate)*x_average;//�ؾ�
}

/**
* @brief ʮ�ֲ��ߺ���
* @param uint8(*image)[image_w]     �����ֵͼ��
* @param uint8 *l_border            ������߽��׵�ַ
* @param uint8 *r_border            �����ұ߽��׵�ַ
* @param uint16 total_num_l         �������ѭ���ܴ���
* @param uint16 total_num_r         �����ұ�ѭ���ܴ���
* @param uint16 *dir_l              ����������������׵�ַ
* @param uint16 *dir_r              �����ұ����������׵�ַ
* @param uint16(*points_l)[2]       ������������׵�ַ
* @param uint16(*points_r)[2]       �����ұ������׵�ַ
*  @see CTest       cross_fill(image,l_border, r_border, data_statics_l, data_statics_r, dir_l, dir_r, points_l, points_r);
* @return ����˵��
*     -<em>false</em> fail
*     -<em>true</em> succeed
 */
void cross_fill(uint8(*image)[image_w], uint8 *l_border, uint8 *r_border, uint16 total_num_l, uint16 total_num_r,
                                         uint16 *dir_l, uint16 *dir_r, uint16(*points_l)[2], uint16(*points_r)[2])
{
    uint8 i;
    uint8 break_num_l = 0;
    uint8 break_num_r = 0;
    uint8 start, end;
    float slope_l_rate = 0, intercept_l = 0;
    //��ʮ��
    for (i = 1; i < total_num_l; i++)
    {
        if (dir_l[i - 1] == 4 && dir_l[i] == 4 && dir_l[i + 3] == 6 && dir_l[i + 5] == 6 && dir_l[i + 7] == 6)
        {
            break_num_l = points_l[i][1];//����y����
            printf("brea_knum-L:%d\n", break_num_l);
            printf("I:%d\n", i);
            printf("ʮ�ֱ�־λ��1\n");
            break;
        }
    }
    for (i = 1; i < total_num_r; i++)
    {
        if (dir_r[i - 1] == 4 && dir_r[i] == 4 && dir_r[i + 3] == 6 && dir_r[i + 5] == 6 && dir_r[i + 7] == 6)
        {
            break_num_r = points_r[i][1];//����y����
            printf("brea_knum-R:%d\n", break_num_r);
            printf("I:%d\n", i);
            printf("ʮ�ֱ�־λ��1\n");
            break;
        }
    }
    if (break_num_l&&break_num_r&&image[image_h- 1][4] && image[image_h- 1][image_w - 4])//�����������򶼷�������
    {
        //����б��
        start = break_num_l - 15;
        start = limit_a_b(start, 0, image_h);
        end = break_num_l - 5;
        calculate_s_i(start, end, l_border, &slope_l_rate, &intercept_l);
        //printf("slope_l_rate:%d\nintercept_l:%d\n", slope_l_rate, intercept_l);
        for (i = break_num_l - 5; i < image_h- 1; i++)
        {
            l_border[i] = slope_l_rate * (i)+intercept_l;//y = kx+b
            l_border[i] = limit_a_b(l_border[i], border_min, border_max);//�޷�
        }

        //����б��
        start = break_num_r - 15;//���
        start = limit_a_b(start, 0, image_h);//�޷�
        end = break_num_r - 5;//�յ�
        calculate_s_i(start, end, r_border, &slope_l_rate, &intercept_l);
        //printf("slope_l_rate:%d\nintercept_l:%d\n", slope_l_rate, intercept_l);
        for (i = break_num_r - 5; i < image_h- 1; i++)
        {
            r_border[i] = slope_l_rate * (i)+intercept_l;
            r_border[i] = limit_a_b(r_border[i], border_min, border_max);
        }


    }

}

