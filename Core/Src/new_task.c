#include "task.h"
#include "Trace.h"
#include "main.h"
#include "pid.h"

#define BASIC_SPEED 60
#define	STRAIGHT_ANGEL -180
#define MAGIC_ANGEL 38
#define LINEFOLLOWING_SPEED 40
#define COMPENSATE_SPEED 50


void task1(){
//	reset_encoder();
//	char msg[7] = {0};
//	HAL_UART_Transmit(&huart1, "get\r\n", 5, 20);
//	while (msg[0] == 0)
//	{
//		HAL_UART_Receive(&huart1, msg, 7, 30);
//	}
//	OLED_ShowString(0, 30, msg, 8, 1);
//	OLED_Refresh();
//	HAL_Delay(3000);
//	for (int i = 0; i < 5; i++)
//		HAL_UART_Receive(&huart1, msg, 7, 30);//确定target
//	while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) ==  GPIO_PIN_SET)
//		;
//	microtask_12();
	Main_Task();
	stop();
}

void task2(){
	further_task1();
	//__HAL_TIM_DISABLE_IT(&htim7, TIM_IT_UPDATE);
	////Trace(100);
	//Trace(80);
	//car_brake();
	//float initial_angle = Yaw;
	//TurnRightangel(1, 70);
//
	//Trace(60);
	//car_brake();
	////reverse_encoder(60);
	//reverse_straight(initial_angle + 90, 50);
//
	//TurnRightangel(1, 70);
	////Trace(100);
	//Trace(60);
	//car_brake();
	//stop();
}

void task3(){	
	__HAL_TIM_DISABLE_IT(&htim7, TIM_IT_UPDATE);
	//Trace(100);
	Trace(80);
	car_brake();
	float initial_angle = Yaw;
	TurnRightangel(-1, 70);

	Trace(60);
	car_brake();
	//reverse_encoder(60);
	reverse_straight(initial_angle - 90, 70);

	TurnRightangel(1, 70);
	//Trace(100);
	Trace(60);
	car_brake();
	stop();
}

void task4(){
	MainTask();
}
