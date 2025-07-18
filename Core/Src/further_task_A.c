#define CAR_A
#ifdef CAR_A

#include<main.h>
#include "string.h"


void further_task1()
{
    int8_t flag = 0;
    int8_t flag_far = 0;
    int8_t i = 0;
    float initial_angle;
    float speed = 80;
    float turn_speed = 70;
    char tag = 0;//用于提醒另一辆小车采取下一步行动
    encoder_flag = 0;
    //需要用到的相关变量及其初始化

    GetTargetNum();
	HAL_Delay(3000);
    while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) ==  GPIO_PIN_SET)  {}
    //出发前读取纸片并等待装药

	__HAL_TIM_SET_COUNTER(&htim1, 0);
	HAL_TIM_Encoder_Stop(&htim1, TIM_CHANNEL_ALL);
    Trace(speed);
    reset_encoder();
	Set_PWM(speed, speed);
	HAL_Delay(150);
    Trace(speed);
	car_brake();

    initial_angle = Yaw;
    flag = encoder_flag;
    TurnRightangel(flag, turn_speed);
    Trace(50);
	car_brake();
    HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);

    //HAL_UART_Transmit(&huart3,read_data,2,30);
    //蓝牙输出：两边的数字

    HAL_UART_Receive(&huart3,tag,10,HAL_MAX_DELAY);
    //等待小车2到达暂停位置

    //while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) ==  GPIO_PIN_RESET)  {}
    HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
    //进入送药房并等待卸药

    HAL_UART_Transmit(&huart3, "ok", 2, 100);

    //reverse_encoder(60);
    reverse_straight(initial_angle + 90 * flag, 50);
    stop();
    //Reverse(40);
    HAL_UART_Transmit(&huart3,tag,1,30);
    //完成倒车后向小车2传递启动信号

    TurnRightangel(flag, turn_speed);
    Trace(100);
	Set_PWM(speed, speed);
	HAL_Delay(150);
    Trace(50);
	car_brake();
    HAL_GPIO_TogglePin(LEDG_GPIO_Port, LEDG_Pin);
    //完事回家
}

void further_task2()
{
    int8_t flag = 0;
    int8_t flag_B = 0;
    int8_t flag_far = 0;
    int8_t i = 0;
	float initial_angle = 0;
    float speed = 70;
    float turn_speed = 70;
    char tag = 0;//用于提醒另一辆小车采取下一步行动
    encoder_flag = 0;
    char data[5];
    //需要用到的相关变量及其初始化

    GetTargetNum();
    while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) ==  GPIO_PIN_SET)  {}
    //出发前读取纸片并等待装药

    Trace(100);
    Set_PWM(speed, speed);
	HAL_Delay(150);
    Trace(100);
    reset_encoder();
    Set_PWM(speed, speed);
	HAL_Delay(150);
    Trace(60);
	car_brake();

    flag_far = encoder_flag;
    data[4] = flag_far + '0';//保存A车第三个十字路口转向方向
    TurnRightangel(flag_far, turn_speed);
    for(int i = 0; i < 4; i++)
        data[i] = read_data[i]; //保存第三个十字路口的数据

    reset_encoder();//3
    __HAL_TIM_SET_COUNTER(&htim1, 500);
    Trace(speed);
	car_brake();
	initial_angle = Yaw;
    flag = encoder_flag;
    TurnRightangel(flag, turn_speed);//4
    Trace(50);
	car_brake();

    HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
    HAL_UART_Transmit(&huart3, data, 5, 30);
    HAL_UART_Receive(&huart3, tag, 1, HAL_MAX_DELAY);
    flag_B = tag - '0';
    while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) ==  GPIO_PIN_RESET) {}
    HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
    //进入送药房并等待卸药

    reverse_straight(initial_angle + flag * 90, 50);

    TurnRightangel(flag, turn_speed);
    if (flag_B != flag_far)
    {
        trace_encoder(1500,60);
        while(tag != 2){
            HAL_UART_Transmit(&huart3, tag, 1, 30);
            HAL_UART_Receive(&huart3, tag, 1, 30);
        }
        Trace(speed);
		car_brake();
    }
    else
    {
        Trace(100);
        trace_encoder(1500,60);
        HAL_UART_Transmit(&huart3, tag, 1, HAL_MAX_DELAY);
        HAL_UART_Receive(&huart3, tag, 1, HAL_MAX_DELAY);
        reverse_straight(Yaw, 50);
    } 
    TurnRightangel(-flag_far, turn_speed);
    Trace(100);
    Trace(100);
    Trace(50);
	car_brake();
    HAL_GPIO_TogglePin(LEDG_GPIO_Port, LEDG_Pin);
}

void further_task3()
{
    
}

void further_task4()
{
    
}

#endif