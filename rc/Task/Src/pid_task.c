#include "debug.h"
#include "pid.h"

#include "drv_can.h"
#include "PID_MATLAB.h"
#include "usart.h"
//本文件是实现串级pid的以指定速度达到目标位置，实现了稳定启动和平稳停下

extern Pid pos_pid;
extern Pid vec_pid;

float angle;
int16_t speed;
extern int start_flag;


void pid_task0(void)
{
   //start_flag=1;

    /*
     PidInit(&vec_pid,20,5,0,15000,25000,3000,Normal_state);//60.5
     setPidTarget(&pos_pid,CAN_GetMotorAngel(1)/8191.0f*360.0f);

     PidInit(&pos_pid,0.7,0.0,1,1000,400,3000,Normal_state);
*/

    angle=CAN_GetMotorAngel(1)*360/8191;
    angle=Angle_Consecutive(angle);//角度连续化

    speed=CAN_GetMotorVelocity(1);
   // setPidTargetwithRamp(&pos_pid,1000);//设置外环pid目标，后期可用串口接收

    Pid_Update_Gamp(&pos_pid,angle);
    pos_pid.variables.output.output_total=PidGet(&pos_pid,angle,0.1f,300.0);

   //setPidTarget(&vec_pid,pos_pid.variables.output.output_total);
   setPidTargetwithRamp(&vec_pid,pos_pid.variables.output.output_total);

    Pid_Update_Gamp(&vec_pid,speed);//实现斜坡函数，单独封装
    vec_pid.variables.output.output_total=PidGet(&vec_pid,speed,0.1f,200);//实现内环速度pid

    CAN_SendCurrent(vec_pid.variables.output.output_total,0,0,0);


     usart_printf("%d,%d,%d,%d\n",(int)angle,speed,(int)pos_pid.variables.target,(int)vec_pid.variables.target);

}

float angle2;

void pid_task1(void)
{

    /*任务最终参数
    PidInit(&vec_pid,70,1,0,15000,25000,3000,Normal_state);
    PidInit(&pos_pid,2.8,0.0,1,50,300,3000,Normal_state);//普通位置跟随的参数
    */



    start_flag=1;

    angle=(float)(CAN_GetMotorAngel(1)*360/8191);
    angle=Angle_Consecutive(angle);//角度连续化
    speed=CAN_GetMotorVelocity(1);


    angle2=(float)(CAN_GetMotorAngel(2)*360/8191);
    angle2=Angle_Consecutive1(angle2);//角度连续化

        setPidTarget(&pos_pid,angle2);//设置外环pid目标，后期可用串口接收
        Pid_Update_Gamp(&pos_pid,angle);
        pos_pid.variables.output.output_total=PidGet(&pos_pid,angle,0.1f,300.0);

        setPidTarget(&vec_pid,pos_pid.variables.output.output_total);
       // setPidTargetwithRamp(&vec_pid,pos_pid.variables.output.output_total);

    //setPidTarget(&vec_pid,200);
    Pid_Update_Gamp(&vec_pid,speed);//实现斜坡函数，单独封装
    vec_pid.variables.output.output_total=PidGet(&vec_pid,speed,0.1f,200);//实现内环速度pid

    //CAN_SendCurrent(vec_pid.variables.output.output_total,0,0,0);
    CAN_SendCurrent(vec_pid.variables.output.output_total,0,0,0);


    // usart_printf("%d\n",speed);

  usart_printf("%d,%d\n",(int)angle,(int)angle2);

    //usart_printf("%d\n",1);
}



#define param PID_MATLAB_U
#define current PID_MATLAB_Y.Current
void pid_task2(void)
{

    angle=(float)((CAN_GetMotorAngel(1)*360.0f/8191.0f));
    angle=Angle_Consecutive(angle);//角度连续化
    speed=CAN_GetMotorVelocity(1);
    angle2=(float)((CAN_GetMotorAngel(2)*360.0f/8191.0f));
    angle2=Angle_Consecutive1(angle2);//角度连续化
    param.P_P2=0.12;

    param.P_P=2.8;
    param.P_I=0;
    param.P_D=0.01;
    param.P_N=180;

    param.V_P=31.5;
    param.V_I=22;
    param.V_D=0;
    param.V_N=0;

    param.P_TARGET=angle2;
    param.P_FEED=angle;
    param.P_FEED1=speed;
    PID_MATLAB_step();
    CAN_SendCurrent((int)current,0,0,0);
    usart_printf("%.2f,%.2f\n",(float)angle,(float)angle2);


}

