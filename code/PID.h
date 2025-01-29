#ifndef __PID_H_
#define __PID_H_


enum PID_MODE		//pid����ģʽ����
{
  PID_POSITION = 0,	//λ��ʽpid
  PID_DELTA			//����ʽpid
};
 
typedef struct
{
  uint8 mode;
  float Kp;	//PID ������
  float Ki;
  float Kd;
  float max_out;  //������
  float max_iout; //���������
  float set;
  float fdb;
  float out;
  float Pout;
  float Iout;
  float Dout;
  float Dbuf[3];  //΢���� 0���� 1��һ�� 2���ϴ�
  float error[3]; //����� 0���� 1��һ�� 2���ϴ�
} pid_type_def;

//PID��ֵ��ʼ����ָ��һ��pid�ṹ���ָ�룬pid��������ģʽ������pid����ϵ�������飬pid������ֵ��i����������ֵ��
extern void PID_init(pid_type_def *pid, uint8 mode, float PID[3], float max_out, float max_iout);
//pid���㣨ָ��һ��pid�ṹ���ָ�룬Ŀ��ֵ��ʵ��ֵ��
extern float PID_calc(pid_type_def *pid, float ref, float set);
//pid������գ�ָ��һ��pid�ṹ���ָ�룩
extern void PID_clear(pid_type_def *pid);


#endif