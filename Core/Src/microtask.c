#include<main.h>

void stop_delay(){//调试用，让小车在每个动作之间稍作等待
	stop();
	HAL_Delay(800);
}

void microtask_12(){//flag为1时为左转flag为-1时为右转
	int8_t flag = 1;
	//Set_PWM(40,40);
	//HAL_Delay(delaytime); // 先直行一段至合适位置识别数字
	//阻塞函数写在这里,读取到的值存入flag
//	start_encoder_IT(period_IT);
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	reset_encoder();
//	Set_PWM(60, 60);
//	HAL_Delay(500);
	trace();
	flag = encoder_flag;
	float angle = 90 * flag;
	float speed = 50 * flag;
	float initial_angle = Kyaw;
	Set_PWM(40,40);
	HAL_Delay(250); // 先直行一段，到合适位置再转向
	autoturn(speed);
	trace();
	while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) == GPIO_PIN_RESET)
		;
	//走到卸药区域
	reverse_straight(initial_angle + angle, 50);
	//reverse(40);
	Set_PWM(40,40);
	HAL_Delay(500); // 先直行一段，到合适位置再转向
	//turnto(180 * flag);
	autoturn(speed);
	trace();
}

void microtask_1212(uint8_t flag){//flag为1时为左转flag为-1时为右转
	float angle = 90 * flag;
	float speed = 40 * flag;
	float initial_angle = Kyaw;
	Set_PWM(40,40);
	HAL_Delay(300); // 先直行一段，到合适位置再转向
	autoturn(speed);
	stop();
	HAL_Delay(500);
	//turn_and_stop(30);
	trace();
	stop();
	HAL_Delay(500);
	//走到卸药区域
	turn_both(180);
	//autoturn(40);
	//reverse(40);
	stop();
	trace();
	stop();
	HAL_Delay(500);
	Set_PWM(40,40);
	HAL_Delay(300); // 先直行一段，到合适位置再转向
	//turnto(180 * flag);
	autoturn(-speed);
}

void microtask_3(){
	int8_t flag = 0;//flag为1时为左转flag为-1时为右转

	//阻塞函数写在这里,读取到的值存入flag
	reset_encoder();
	trace();
	flag = encoder_flag;
	//stop_delay();//停下等待，方便观察执行到哪一步
	float angle = 90 * flag;
	float speed = 40 * flag;
	Set_PWM(40,40);
	HAL_Delay(200); // 先直行一段，到合适位置再转向
	autoturn(speed);

	reset_encoder();

	//指示转弯后小弯的方向
	microtask_12();
	trace();
	//stop_delay();//停下等待，方便观察执行到哪一步
	Set_PWM(40,40);
	HAL_Delay(250); // 先直行一段，到合适位置再转向
	autoturn(-speed);
	//stop_delay();//停下等待，方便观察执行到哪一步
	trace();
}