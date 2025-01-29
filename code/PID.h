#ifndef __PID_H_
#define __PID_H_


enum PID_MODE		//pid控制模式类型
{
  PID_POSITION = 0,	//位置式pid
  PID_DELTA			//增量式pid
};
 
typedef struct
{
  uint8 mode;
  float Kp;	//PID 三参数
  float Ki;
  float Kd;
  float max_out;  //最大输出
  float max_iout; //最大积分输出
  float set;
  float fdb;
  float out;
  float Pout;
  float Iout;
  float Dout;
  float Dbuf[3];  //微分项 0最新 1上一次 2上上次
  float error[3]; //误差项 0最新 1上一次 2上上次
} pid_type_def;

//PID数值初始化（指向一个pid结构体的指针，pid控制器的模式，包含pid三个系数的数组，pid最大输出值，i部分最大输出值）
extern void PID_init(pid_type_def *pid, uint8 mode, float PID[3], float max_out, float max_iout);
//pid计算（指向一个pid结构体的指针，目标值，实际值）
extern float PID_calc(pid_type_def *pid, float ref, float set);
//pid数据清空（指向一个pid结构体的指针）
extern void PID_clear(pid_type_def *pid);


#endif