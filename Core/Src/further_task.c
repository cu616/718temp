#include<main.h>

void further_task1()
{
	while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) ==  GPIO_PIN_SET)	{}
	float initial_angle;
	Trace(40);
	Trace(40);
	initial_angle = Yaw;
	Set_PWM(40,40);
	HAL_Delay(1000);
	Reverse(40);

	int8_t flag = 0;
	int8_t flag_far = 0;
	int8_t i = 0;
	encoder_flag = 0;

	GetTargetNum();
	HAL_Delay(3000);
	TurnRightangel(flag);

	Trace(40);
	while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) ==  GPIO_PIN_RESET)	{}
	Reverse(40);

	TurnRightangel(flag);
	Trace(40);
	Trace(40);
}

void further_task2()
{
    
}

void further_task3()
{
    
}

void further_task4()
{
    
}