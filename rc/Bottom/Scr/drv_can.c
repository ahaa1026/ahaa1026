//#include <cstring>
#include "drv_can.h"
#include "debug.h"
CAN_TxHeaderTypeDef TxMeg;
extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
MotorMsg Motor1,Motor2,Motor3,Motor4;




//滤波器初始化函数
void CAN_Filter_Init(CAN_HandleTypeDef* hcan)
{
	CAN_FilterTypeDef sFilterConfig;

	HAL_StatusTypeDef HAL_Status;

	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK; //工作在标识符屏蔽位模式
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;//滤波器位宽为单个32位

	sFilterConfig.FilterIdHigh = 0X0000;
	sFilterConfig.FilterIdLow = 0X0000;
	//过滤屏蔽码
	sFilterConfig.FilterMaskIdHigh = 0X0000;
	sFilterConfig.FilterMaskIdLow = 0X0000;

	sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	if (hcan->Instance == CAN1)
	{
		sFilterConfig.FilterBank = 0;//滤波器组
	}
	else if (hcan->Instance == CAN2)
	{
		sFilterConfig.FilterBank = 14;
	}
	//sFilterConfig.SlaveStartFilterBank = 0x14;
	sFilterConfig.FilterActivation = ENABLE;//使能

	HAL_Status = HAL_CAN_ConfigFilter(hcan, &sFilterConfig);
	if (HAL_Status != HAL_OK)
	{
		//usart_printf(" NO \r\n");
	}
}

//CAN收发数据的初始化函数
void CAN_All_Init(void)
{
	CAN_Filter_Init(&hcan1);//can通信的过滤器初始化
	HAL_CAN_Start(&hcan1);//打开can，使能
	__HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);//使能中断
	// HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);


    //配置cbuemx的时候顺便把can2配置了，但是这次做的这几个拓展里没有用到can2
	CAN_Filter_Init(&hcan2);
	HAL_CAN_Start(&hcan2);
	__HAL_CAN_ENABLE_IT(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
	//HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);

	//检测关键传参
	assert_param(hcan != NULL);
}


///CAN自动选择邮箱，然后使用HAL_CAN_AddTxMessage(hcan, pHeader, aData, pTxMailbox)CAN发送函数发送
int CAN_TxMessage(CAN_HandleTypeDef* hcan, CAN_TxHeaderTypeDef* pHeader, uint8_t aData[])
{
	//先自动选择空闲邮箱
	// 防止多个CAN设备挤在一个邮箱里面，导致can卡死
	uint8_t mailbox = 0;//这里修改默认邮箱
	uint32_t pTxMailbox[mailbox];

	//如果 CAN 控制器的发送状态寄存器（TSR）的第27位（从0开始计数）被置位（即等于1），那么将变量 mailbox 设为 0。
	if (hcan->Instance->TSR & (1 << 26)) mailbox = 0;       //邮箱0为空

	else if (hcan->Instance->TSR & (1 << 27)) mailbox = 1;  //邮箱1为空
	else if (hcan->Instance->TSR & (1 << 28)) mailbox = 2;  //邮箱2为空
	//以下这句可能需要注释
	else return 0xFF;                                   //无空邮箱,无法发送

	hcan->Instance->sTxMailBox[mailbox].TIR = 0;        //清除之前的设置
	HAL_CAN_AddTxMessage(hcan, pHeader, aData, pTxMailbox);//CAN发送函数
	return mailbox;
}

float angle_last;
int rotate_times=0;
float Angle_Consecutive(float angle_now)
{
	float angle_this;//结合angle_last=angle_this;
	angle_this = angle_now;
	if ((angle_this - angle_last) > 300)//角度连续化的同时进行的角度积累，需要仔细想一想就很清楚的意思
		rotate_times--;
	if ((angle_this - angle_last) < -300)
		rotate_times++;
	angle_now = angle_this + rotate_times * 360.0f;
	//usart_printf("%d\r\n", rotate_times);
	angle_last=angle_this;//结合angle_this = angle_now;进行编码器读取的原始值的保存

	return angle_now;
}

//想了一个优化思路，可以采用结构体，把两个函数和一起对主从电机can读回来的角度进行连续化.
// 这次只有主从电机两个需要角度连续化，两个函数其实也不算多先这么用挺好哈哈哈
float angle_last1;
int rotate_times1=0;
float Angle_Consecutive1(float angle_now1)
{
	float angle_this1;
	angle_this1 = angle_now1;
	if ((angle_this1 - angle_last) > 300)
		rotate_times--;
	if ((angle_this1 - angle_last) < -300)
		rotate_times++;
	angle_now1 = angle_this1 + rotate_times * 360.0f;
	//usart_printf("%d\r\n", rotate_times);
	angle_last=angle_this1;

	return angle_now1;
}


void CAN_SendCurrent(int16_t current1,int16_t current2,int16_t current3,int16_t current4)
{
	CAN_TxHeaderTypeDef tx_msg;
	uint32_t send_mail_box = 0;
	uint8_t send_data[8];

	//这块我写了简单的注释表明具体含义，详细的可以再看看can通信协议的格式
	tx_msg.StdId = CAN_SEND_ID;//标识CAN ID，同时可以用于仲裁，显性电平的设备继续发，隐性电平的设备闭嘴
	tx_msg.IDE = CAN_ID_STD;//扩展帧格式标记，标准数据帧中是显性电平0，扩展帧中是隐性电平1
	tx_msg.RTR = CAN_RTR_DATA;//远程发送请求，数据帧中是显性电平0，遥控帧中是隐性电平1
	tx_msg.DLC = 0x08;//数据长度的字节数，can协议中数据长度为0~8字节，但我们要知道其实收方如果接收到9以上也不算出错

	//电机1
	send_data[0] = (current1 >> 8);//send_data[0]存高八位的数据一个字节,右移八位，send_data[0]存储
	send_data[1] = current1;////send_data[1]存低八位的数据一个字节

	//电机2
	send_data[2] = (current2 >> 8);//send_data[2]存高八位的数据一个字节
	send_data[3] = current2;////send_data[3]存低八位的数据一个字节

	//依次类推
	send_data[4] = (current3 >> 8);
	send_data[5] = current3;

	send_data[6] = (current4 >> 8);
	send_data[7] = current4;

	//调用自定义的CAN_TxMessage发送函数
	CAN_TxMessage(&hcan1, &tx_msg, send_data);
}



//接收回调函数，虚函数，_weak，我在这里重新定义
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
	uint8_t recvData[8];

	HAL_StatusTypeDef HAL_Status;
	CAN_RxHeaderTypeDef RxMeg;
	HAL_Status = HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxMeg, recvData);
	if (hcan->Instance == CAN1)
	{
		// usart_printf("%d\n",RxMeg.StdId);

		if (HAL_Status == HAL_OK)                                                    //在这里接收数据
		{

			if (RxMeg.StdId == CAN_REC_ID1)//接收到的是电机1的数据
			{
				//usart_printf("%d\n",Motor1.MotorAngle);

				Motor1.Connected = 1;
				Motor1.MotorAngle = (int16_t)(recvData[0] << 8 | recvData[1]);     // 0~8191
				Motor1.MotorSpeed = (int16_t)(recvData[2] << 8 | recvData[3]);     // prm
				Motor1.MotorTorque = (int16_t)(recvData[4] << 8 | recvData[5]);        //转矩(电流)
				Motor1.MotorTempture = (int16_t)(recvData[6]);                         //温度
				Motor1.Null = (int16_t)(recvData[7]);
				Motor1.UpDateAngle += 1;
				return;
			}

			if (RxMeg.StdId == CAN_REC_ID2)
			{
				Motor2.Connected = 1;
				Motor2.MotorAngle = (int16_t)(recvData[0] << 8 | recvData[1]);     // 0~8191
				Motor2.MotorSpeed = (int16_t)(recvData[2] << 8 | recvData[3]);     // prm
				Motor2.MotorTorque = (int16_t)(recvData[4] << 8 | recvData[5]);        //转矩(电流)
				Motor2.MotorTempture = (int16_t)(recvData[6]);                         //温度
				Motor2.Null = (int16_t)(recvData[7]);
				Motor2.UpDateAngle += 1;
				return;
			}

			if (RxMeg.StdId == CAN_REC_ID3)
			{
				Motor3.Connected = 1;
				Motor3.MotorAngle = (int16_t)(recvData[0] << 8 | recvData[1]);     // 0~8191
				Motor3.MotorSpeed = (int16_t)(recvData[2] << 8 | recvData[3]);     // prm
				Motor3.MotorTorque = (int16_t)(recvData[4] << 8 | recvData[5]);        //转矩(电流)
				Motor3.MotorTempture = (int16_t)(recvData[6]);                         //温度
				Motor3.Null = (int16_t)(recvData[7]);
				Motor3.UpDateAngle += 1;
				return;
			}

			if (RxMeg.StdId == CAN_REC_ID4)
			{
				Motor4.Connected = 1;
				Motor4.MotorAngle = (int16_t)(recvData[0] << 8 | recvData[1]);     // 0~8191
				Motor4.MotorSpeed = (int16_t)(recvData[2] << 8 | recvData[3]);     // prm
				Motor4.MotorTorque = (int16_t)(recvData[4] << 8 | recvData[5]);        //转矩(电流)
				Motor4.MotorTempture = (int16_t)(recvData[6]);                         //温度
				Motor4.Null = (int16_t)(recvData[7]);
				Motor4.UpDateAngle += 1;
				return;
			}
		}
	}
}



//获取can传回来的四个电机的速度
int16_t CAN_GetMotorVelocity(int8_t Which_x)
{
	switch (Which_x)
	{
	case 1:
	{
		return Motor1.MotorSpeed;//电机1
	}
	case 2:
	{
		return Motor2.MotorSpeed;//电机2
	}
	case 3:
	{
		return Motor3.MotorSpeed;//电机3
	}
	case 4:
	{
		return Motor4.MotorSpeed;//电机4
	}

	}
	return 0;
}


//获取can传回来的四个电机的角度
uint16_t CAN_GetMotorAngel(int8_t Which_x)
{
	switch (Which_x)
	{
	case 1:
	{
		return Motor1.MotorAngle;//电机1
	}
	case 2:
	{
		return Motor2.MotorAngle;//电机2
	}
	case 3:
	{
		return Motor3.MotorAngle;//电机3
	}
	case 4:
	{
		return Motor4.MotorAngle;//电机4
	}
	}
	return 0;
}
