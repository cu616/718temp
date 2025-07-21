#include "jy61p.h"

static uint8_t RxBuffer[11];/*接收数据数组*/
static volatile uint8_t RxState = 0;/*接收状态标志位*/
static uint8_t RxIndex = 0;/*接受数组索引*/
float Roll,Pitch,Yaw=0;/*角度信息，如果只需要整数可以改为整数类型*/
float Yaw_tran,Yaw_cur;//暂态和现态
int Yaw_flag=0;
int jytime=1;

/**
 * @brief       数据包处理函数
 * @param       串口接收的数据RxData
 * @retval      无
 */
void jy61p_ReceiveData(uint8_t RxData)
{
	//printf("in jy!\n");
	uint8_t i,sum=0;
	if (RxState == 0)	//等待包头
	{
		if (RxData == 0x55)	//收到包头
		{
			RxBuffer[RxIndex] = RxData;
			RxState = 1;
			RxIndex = 1;	//进入下一状态
			//printf("state0\n");
		}else{
			RxState = 0;
			RxIndex = 0;
			}
	}
	else if (RxState == 1)
	{
		if (RxData == 0x53)	/*判断数据内容，修改这里可以改变要读的数据内容，0x53为角度输出*/
		{
			RxBuffer[RxIndex] = RxData;
			RxState = 2;
			RxIndex = 2;	//进入下一状态
			//printf("state1\n");
		}else {
			RxState = 0;
			RxIndex = 0;
		}
	}
	else if (RxState == 2)	//接收数据
	{
		//printf("state2,index=%u\n",RxIndex);
		RxBuffer[RxIndex++] = RxData;
		if(RxIndex == 11)	//接收完成
		{
			for(i=0;i<10;i++)
			{
				sum = sum + RxBuffer[i];	//计算校验和
			}
			if(sum == RxBuffer[10])		//校验成功
			{
				if(Yaw_flag==0){
				/*计算数据，根据数据内容选择对应的计算公式*/
				//Roll = ((int16_t) ((int16_t) RxBuffer[3] << 8 | (int16_t) RxBuffer[2])) / 32768.0f * 180.0f;
				//Pitch = ((int16_t) ((int16_t) RxBuffer[5] << 8 | (int16_t) RxBuffer[4])) / 32768.0f * 180.0f;
					Yaw_cur = ((int16_t) ((int16_t) RxBuffer[7] << 8 | (int16_t) RxBuffer[6])) / 32768.0f * 180.0f;
					Yaw_flag=1;
				//printf("Yaw1=%3.2f\n",Yaw);
				}else if(Yaw_flag==1){
						Yaw_tran=	Yaw_cur;
						Yaw_cur = ((int16_t) ((int16_t) RxBuffer[7] << 8 | (int16_t) RxBuffer[6])) / 32768.0f * 180.0f;
						float dyaw;
						if(Yaw_cur-Yaw_tran>180){
							dyaw=Yaw_cur-Yaw_tran-360;
						}else if(Yaw_cur-Yaw_tran<-180){
							dyaw=Yaw_cur-Yaw_tran+360;
						}else dyaw=Yaw_cur-Yaw_tran;
						Yaw=Yaw+dyaw;
					}else Yaw_flag=0;
					jytime=0;
				//printf("Yaw=%3.2f\n",Yaw);
			}
			RxState = 0;
			RxIndex = 0;	//读取完成，回到最初状态，等待包头
			//printf("Yaw2=%3.2f\n",Yaw);
		//	for (int j = 0; j < 11; j++)printf("%2X ",RxBuffer[j]);
		//	printf("\n");
		}
	}else{
			RxState = 0;
			RxIndex = 0;
	}
}
void jy61p_DataCombine(uint8_t* jyregroup,int len){
	int i=0;
	for(i=0;i<len;i++)jy61p_ReceiveData(jyregroup[i]);
}
void jy61p_caculate(){
	jytime=1;
	//	printf("in\n");
		HAL_UART_Receive_IT(&huart2,&g_usart2_receivedata,1);
	
	//	printf("out\n");
}
