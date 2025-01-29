#include "zf_common_headfile.h"

//�޷�������ֵ�����ֵ��
#define LimitMax(input, max){if(input > max){input = max;}else if (input < -max){ input = -max;}}
        
//PID��ֵ��ʼ����ָ��һ��pid�ṹ���ָ�룬pid��������ģʽ������pid����ϵ�������飬pid������ֵ��i����������ֵ��
void PID_init(pid_type_def *pid, uint8 mode, float PID[3], float max_out, float max_iout)
{
	//����Ƿ�Ϊ��ָ�룬�Ų����
	if (pid == NULL || PID == NULL){return;}
	//����Ӧ�Ľṹ�帳��ֵ
	pid->mode = mode;
	pid->Kp = PID[0];
	pid->Ki = PID[1];
	pid->Kd = PID[2];
	pid->max_out = max_out;
	pid->max_iout = max_iout;
	pid->Dbuf [0] = pid->Dbuf [1] = pid->Dbuf [2] = 0.0f;	//����d�������ݻ�������ʼ��
	pid->error[0] = pid->error[1] = pid->error[2] = 0.0f;	//����������ݻ�������ʼ��
	pid->Pout = pid->Iout = pid->Dout = pid->out = 0.0f;	//pid���ֵ��ʼ��
}
 
//pid���㣨ָ��һ��pid�ṹ���ָ�룬ʵ��ֵ��Ŀ��ֵ��
float PID_calc(pid_type_def *pid, float set, float ref)
{
	if (pid == NULL){return 0.0f;}	//����Ƿ�Ϊ��ָ�룬�Ų����
  
	pid->error[2] = pid->error[1];	//�����������
	pid->error[1] = pid->error[0];
	pid->set = set;
	pid->fdb = ref;
	pid->error[0] = ref - set;		//�洢������ݣ�Ŀ��ֵ-ʵ��ֵ��
	
	if (pid->mode == PID_POSITION)	//���pidģʽ��λ��ʽ
	{
		pid->Pout =  pid->Kp * pid->error[0];	//p�������ֵ
		pid->Iout += pid->Ki * pid->error[0];	//i�������ֵ�ۼ�
		pid->Dbuf[2] = pid->Dbuf[1];			//d�������ݴ洢
		pid->Dbuf[1] = pid->Dbuf[0];
		pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
		
		if(pid->Dbuf[0]<=2&&pid->Dbuf[0]>=-2){pid->Dbuf[0]=0;}		//��d�����޷�������ӵ�
		
		pid->Dout = pid->Kd * pid->Dbuf[0];		//d�������ֵ
		LimitMax(pid->Iout, pid->max_iout);		//i�����޷�
		pid->out = pid->Pout + pid->Iout + pid->Dout;	//pid�����ֵ
		LimitMax(pid->out, pid->max_out);		//�����ֵ�޷�
	}
	else if (pid->mode == PID_DELTA)	//���pidģʽ������ʽ
	{
		pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);	//p�������ֵ
		pid->Iout = pid->Ki * pid->error[0];					//i�������ֵ
		pid->Dbuf[2] = pid->Dbuf[1];							//d�������ݴ洢
		pid->Dbuf[1] = pid->Dbuf[0];
		pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
		pid->Dout = pid->Kd * pid->Dbuf[0];						//d�������ֵ
		pid->out += pid->Pout + pid->Iout + pid->Dout;			//pid�����ֵ
		LimitMax(pid->out, pid->max_out);						//�����ֵ�޷�
	}
	return pid->out;
}
 
//pid������գ�ָ��һ��pid�ṹ���ָ�룩
void PID_clear(pid_type_def *pid)
{
	if (pid == NULL){return;}	//�����Ų�
	pid->error[0] = pid->error[1] = pid->error[2] = 0.0f;
	pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
	pid->out = pid->Pout = pid->Iout = pid->Dout = 0.0f;
	pid->fdb = pid->set = 0.0f;
}
