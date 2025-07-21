// K230模组

#include <main.h>
#include <Mode_K230.h>


uint8_t target;
char read_data[4];
extern volatile int8_t encoder_flag;

int GetTargetNum(void)
{
	char msg[7] = {0}; // 发送信息

	HAL_UART_Transmit(&huart1, "name\r\n", 6, 30); // 给上位机信号
	HAL_UART_Receive(&huart1, msg, 1, HAL_MAX_DELAY); // 接受采样数据     

	OLED_ShowString(0, 30, msg, 8, 1); // 打印接收到信息
	OLED_Refresh();

	target = msg[0] - '0';

	for (int i = 0; i < 5; i++)
		HAL_UART_Receive(&huart1, msg, 7, 30); // 此处清除UART接受区

	if (target == 1)
	{
		encoder_flag = 1;
	}
	else if (target == 2)
	{
		encoder_flag = -1;
	}
	else{
		encoder_flag = 0;
	}

	return target;
}

int GetTurnFlag(void)
{
	char msg[7];   // 发送信息
	int turn_flag; // 转向flag

	OLED_ShowString(64, 30, "debug", 8, 1); // 可以去掉
	OLED_Refresh();

	HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, GPIO_PIN_SET);
	HAL_UART_Transmit(&huart1, "get\r\n", 5, 20);

	for (int i = 0; msg[0] == 0 && i <= 10; i++)
	{
		HAL_UART_Receive(&huart1, msg, 7, 30);
	}
	//	HAL_UART_Receive(&huart1, msg, 7, HAL_MAX_DELAY);

	OLED_ShowString(64, 40, msg, 8, 1); // 显示接收到的方向信息, 非debug可去
	OLED_Refresh();

	switch (msg[0])
	{
	case 'L':
		turn_flag = 1;
		break;
	case 'R':
		turn_flag = -1;
		break;
	case 'M':
		turn_flag = 0;
		break;
	default:
		turn_flag = 1;
		break;
	}

	for (int i = 0; i < 5; i++)
	HAL_UART_Receive(&huart1, msg, 7, 30); // 此处清除UART接受区
	OLED_ShowString(64, 20, "finish", 8, 1);   // 此处debug用
	OLED_Refresh();
	return turn_flag;
}

char *GetTurnData()
{
	OLED_ShowString(64, 30, "debug", 8, 1); // 可以去掉
	OLED_Refresh();

	// HAL_GPIO_WritePin(LEDR_GPIO_Port, LEDR_Pin, GPIO_PIN_SET);
	
	for(uint8_t i =0; i<10; i++){
		HAL_UART_Transmit(&huart1, "get\r\n", 5, 20); // 提示摄像头开始采样
		HAL_UART_Receive(&huart1, read_data, 4, 50); // 接受采样数据
	}

	OLED_ShowString(0, 40, read_data, 8, 1); // 显示接收到的方向信息, 非debug可去
	OLED_Refresh();

	return read_data;
}