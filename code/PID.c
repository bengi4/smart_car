#include "zf_common_headfile.h"

//限幅（输入值，最大值）
#define LimitMax(input, max){if(input > max){input = max;}else if (input < -max){ input = -max;}}
        
//PID数值初始化（指向一个pid结构体的指针，pid控制器的模式，包含pid三个系数的数组，pid最大输出值，i部分最大输出值）
void PID_init(pid_type_def *pid, uint8 mode, float PID[3], float max_out, float max_iout)
{
	//检查是否为空指针，排查错误
	if (pid == NULL || PID == NULL){return;}
	//给相应的结构体赋初值
	pid->mode = mode;
	pid->Kp = PID[0];
	pid->Ki = PID[1];
	pid->Kd = PID[2];
	pid->max_out = max_out;
	pid->max_iout = max_iout;
	pid->Dbuf [0] = pid->Dbuf [1] = pid->Dbuf [2] = 0.0f;	//储存d部分数据缓冲区初始化
	pid->error[0] = pid->error[1] = pid->error[2] = 0.0f;	//储存误差数据缓冲区初始化
	pid->Pout = pid->Iout = pid->Dout = pid->out = 0.0f;	//pid输出值初始化
}
 
//pid计算（指向一个pid结构体的指针，实际值，目标值）
float PID_calc(pid_type_def *pid, float set, float ref)
{
	if (pid == NULL){return 0.0f;}	//检查是否为空指针，排查错误
  
	pid->error[2] = pid->error[1];	//更新误差数据
	pid->error[1] = pid->error[0];
	pid->set = set;
	pid->fdb = ref;
	pid->error[0] = ref - set;		//存储误差数据（目标值-实际值）
	
	if (pid->mode == PID_POSITION)	//如果pid模式是位置式
	{
		pid->Pout =  pid->Kp * pid->error[0];	//p部分输出值
		pid->Iout += pid->Ki * pid->error[0];	//i部分输出值累加
		pid->Dbuf[2] = pid->Dbuf[1];			//d部分数据存储
		pid->Dbuf[1] = pid->Dbuf[0];
		pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
		
		if(pid->Dbuf[0]<=2&&pid->Dbuf[0]>=-2){pid->Dbuf[0]=0;}		//对d进行限幅，另外加的
		
		pid->Dout = pid->Kd * pid->Dbuf[0];		//d部分输出值
		LimitMax(pid->Iout, pid->max_iout);		//i部分限幅
		pid->out = pid->Pout + pid->Iout + pid->Dout;	//pid总输出值
		LimitMax(pid->out, pid->max_out);		//总输出值限幅
	}
	else if (pid->mode == PID_DELTA)	//如果pid模式是增量式
	{
		pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);	//p部分输出值
		pid->Iout = pid->Ki * pid->error[0];					//i部分输出值
		pid->Dbuf[2] = pid->Dbuf[1];							//d部分数据存储
		pid->Dbuf[1] = pid->Dbuf[0];
		pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
		pid->Dout = pid->Kd * pid->Dbuf[0];						//d部分输出值
		pid->out += pid->Pout + pid->Iout + pid->Dout;			//pid总输出值
		LimitMax(pid->out, pid->max_out);						//总输出值限幅
	}
	return pid->out;
}
 
//pid数据清空（指向一个pid结构体的指针）
void PID_clear(pid_type_def *pid)
{
	if (pid == NULL){return;}	//错误排查
	pid->error[0] = pid->error[1] = pid->error[2] = 0.0f;
	pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
	pid->out = pid->Pout = pid->Iout = pid->Dout = 0.0f;
	pid->fdb = pid->set = 0.0f;
}
