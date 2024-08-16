#include "drv_can.h"
#include "pid.h"
#include "roboinit.h"
#include "kalman.h"
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include"task.h"
#include"debug.h"

int cnt_mood=5;
extern Kalman kalman_pos_follow;


Pid vec_pid;
Pid pos_pid;

/*
float expect_speed=200;
float expect_speed_division;
float expect_speed_rise;
float expect_speed_dec;
int cnt=1;
*/

void roboinit()
{

     PidInit(&vec_pid,20,5,0,15000,25000,3000,Normal_state);//60.5
     setPidTarget(&pos_pid,CAN_GetMotorAngel(1)/8191.0f*360.0f);

     PidInit(&pos_pid,0.7,0.0,1,1000,400,3000,Normal_state);


    //KalmanInit(&kalman_pos_follow,1,9);//卡尔曼滤波器调参数

}


//以下为之前裸机编程没有使用freertos时，使用定时器中断写的程序
/*
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{


     if(htim==&htim2)
     {




         encodor.direction=__HAL_TIM_IS_TIM_COUNTING_DOWN(encodor.paramater.tim_hander);

         encodor.counter.counter=(int16_t)__HAL_TIM_GET_COUNTER(encodor.paramater.tim_hander);

         encodor.counter.conuter_total+=encodor.counter.counter;

         encodor.counter.counter_increase=(int64_t)((int16_t)encodor.counter.counter-0);

         __HAL_TIM_SetCounter(encodor.paramater.tim_hander,0);//清空计数器的值，解决溢出问题

         encodor.position.rotations=(double)encodor.counter.conuter_total/((double)encodor.paramater.multi_frequency*(double)encodor.paramater.reduction_speed*(double)encodor.paramater.resolution_ratio);


         encodor.speed.w=(double)encodor.counter.counter_increase/(((double)encodor.paramater.multi_frequency*(double)encodor.paramater.reduction_speed*(double)encodor.paramater.resolution_ratio))*1000*60/10.0;

         printf("%d,%.2f,%.2f\n",encodor.direction,encodor.position.rotations,encodor.speed.w);

         EncodorGetCounter(&encodor);
         EncodorGetPosition(&encodor);
         EncodorGetSpeed(&encodor,10);

         //模式1，实现速度pid
        if(cnt_mood%5==1)
        {
            setPidTarget(&vec_pid,200);

            vec_pid.variables.output.output_total=PidGet(&vec_pid,encodor.speed.w,5.0,200.0);

            Motor_Dirctiion_Speed(vec_pid.variables.output.output_total);


         }


         //实现位置pid
         if(cnt_mood%5==2)
         {
             setPidTarget(&pos_pid,360);

         pos_pid.variables.output.output_total=PidGet(&pos_pid,encodor.position.angle,5.0,200.0);

             Motor_Dirctiion_Speed(pos_pid.variables.output.output_total);


         }


          //实现串级pid（包含稳定启动和缓慢停下）
         if(cnt_mood%5==3)
         {

         setPidTarget(&pos_pid,360);

         expect_speed_division=expect_speed/10;


         //实现稳定停启动，逐次（每隔10s）增加内环pid的目标速度
         if(cnt<=10)
         {
             expect_speed_rise=expect_speed_division*cnt;
             cnt++;
             expect_speed=expect_speed_rise;

         }


         //实现稳定停下来，逐次（每隔10s）减小内环pid的目标速度
         if(pos_pid.variables.output.output_total<expect_speed&&cnt>0)
         {
             expect_speed_dec=expect_speed_division*cnt;
             cnt--;
             expect_speed=expect_speed_dec;

         }


         pos_pid.variables.output.output_total=limit_float(pos_pid.variables.output.output_total,expect_speed);

         setPidTarget(&vec_pid,pos_pid.variables.output.output_total);

         vec_pid.variables.output.output_total=PidGet(&vec_pid,encodor.position.angle,2.0,100);

         Motor_Dirctiion_Speed(vec_pid.variables.output.output_total);


             printf("%.2f,%.2f\n",encodor.position.angle,encodor.speed.w);

         }




     }



}

*/