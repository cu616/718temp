#include "mytask.h"
uint8_t target;
char read_data[4];
extern volatile int8_t encoder_flag;

void MainTask(void)
{
	int map[4];						// 用于存储行驶记录, 便于实现回程
	int turn_flag, cross_count = 0; // 分别为转弯flag和经过十字路口数目
	encoder_flag = 0;

	GetTargetNum();

	for (int i = 0; i < 4; i++)
	{
		reset_encoder(); // 重置编码器

		Trace(40); // 循迹

		Set_PWM(40, 40);
		HAL_Delay(300); // 向前继续一小段

		//		turn_flag = encoder_flag;//正常测试用
		turn_flag = 1; // debug用
		map[i] = turn_flag;

		TurnRightangel(turn_flag,40); // 转弯

		cross_count++;

		if (i < 2 && map[i] != 0)
		{
			break;
		}
	}

	// 进入送药最后部分循迹
	Trace(40); // 倒车

	Reverse(40); // 回程

	for (int i = 0; i < cross_count; i++)
	{
		if ((cross_count - 1 - i) == (3 - 1))
			TurnRightangel(-map[cross_count - 1 - i], 40); // 转弯
		else
			TurnRightangel(map[cross_count - 1 - i], 40);

		Trace(40); // 循迹

		Set_PWM(40, 40);
		HAL_Delay(300); // 向前继续一小段
	}
}

void Main_Task(void)
{
	int8_t flag = 0;
	int8_t flag_far = 0;
	int8_t i = 1;
	float initial_angle = 0;
	float speed = 80;
	float turn_speed = 70;
	encoder_flag = 0;

	__HAL_TIM_SET_COUNTER(&htim1, 0);
	__HAL_TIM_SET_COUNTER(&htim4, 0);
	HAL_TIM_Encoder_Stop_IT(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Stop_IT(&htim4, TIM_CHANNEL_ALL);

	GetTargetNum();
	HAL_Delay(3000);

	Set_PWM(speed, speed);
	HAL_Delay(150);
	Trace(speed);
	// 第一次循迹

	if (encoder_flag != 0)
	{
		initial_angle = Yaw;
		flag = encoder_flag;
		car_brake();
		TurnRightangel(flag, turn_speed);
	}
	else{
		for (i = 2; i <= 3; i++)
		{
			reset_encoder();
			Set_PWM(speed, speed);
			HAL_Delay(150);
			Trace(speed);
			if (flag = encoder_flag)
			{
				initial_angle = Yaw;
				car_brake();
				TurnRightangel(flag, turn_speed);
				break;
			}
			OLED_Clear();
		}
	}

	if (i == 3)
	{
		reset_encoder();
		__HAL_TIM_SET_COUNTER(&htim1, 300);
		__HAL_TIM_SET_COUNTER(&htim4, 300);
		Trace(60);
		flag_far = flag;
		flag = encoder_flag;
		initial_angle = Yaw;
		car_brake();
		TurnRightangel(flag, turn_speed);
	}

	Trace(40);
	// 等待卸药
	reverse_straight(initial_angle + 90 * flag, turn_speed);
	// reverse(40);
	// reverse_straight(Kyaw,40);//陀螺仪version

	TurnRightangel(flag, turn_speed);
	if (i == 3)
	{
		Trace(speed);
		car_brake();
		TurnRightangel(-flag_far, turn_speed);
	}
	while (i)
	{
		Set_PWM(speed, speed);
		HAL_Delay(150);
		Trace(speed);
		i--;
	}
}

int reverse(float speed)
{
	PID TracePID;
	TracePID.Kp = 20, TracePID.Ki = 0, TracePID.Kd = 0;
	TracePID.target = 0, TracePID.minOutput = -speed/2, TracePID.maxOutput = speed/2;
	TracePID.minIntegral = -10, TracePID.maxIntegral = 10;
	TracePID.error = 0;
	float transform = 0;
	Set_PWM(-speed, -speed);
	HAL_Delay(300);
	while (1)
	{
		if (get_T(3) == 0 && get_T(4) == 0 && get_T(5) == 0 && get_T(6) == 0)
		{
			Set_PWM(-speed, -speed);
		}
		else
		{
			// if ((get_T(1) == 1 || get_T(8) == 1) && (get_T(4) == 1 || get_T(5) == 1))
			//{
			//	Set_PWM(-speed, -speed);
			//	HAL_Delay(10);
			//	if ((get_T(1) == 1 || get_T(8) == 1) && (get_T(4) == 1 || get_T(5) == 1)){
			//		//break;
			//	}
			// }
			// if (get_T_ALL() == 0x00)
			//{
			//	//return 0;
			// }
			transform = PID_Compute(&TracePID, get_Terror());
			Set_PWM(-speed + transform, -speed - transform);
		}
		HAL_Delay(5);
	}
	Set_PWM(40, 40);
	HAL_Delay(500); // 先直行一段，到合适位置再转向
	stop();
	return 1; // 遇到十字路口返回1
}

void autoturn(float speed) // 从当前位置旋转至寻到下一个轨迹
{						   // speed>0时向左旋转，speed<时向右旋转
	while (get_T_ALL() != 0x00)
	{ // 先脱离当前轨道
		Set_PWM(-speed, speed);
		HAL_Delay(5);
	}
	while (get_T(4) == 0 && get_T(5) == 0)
	{ // 中间两路寻到轨迹时停止旋转
		Set_PWM(-speed, speed);
		HAL_Delay(5);
	}
	//		Set_PWM(turn_angle, -turn_angle);//反向补偿
	//		HAL_Delay(Delayturn);
	OLED_Clear();
	stop();
}

int trace()
{
	PID TracePID;
	float TracePID_Kp = 20, TracePID_Ki = 0, TracePID_Kd = 0;
	float TracePID_Target = 0, TracePID_MinOutput = -60/2, TracePID_MaxOutput = 60/2;
	float IntergretPID_MinOutput = -10, IntergretPID_MaxOutput = 10;
	float TracePID_Input = 0;
	PID_Init(&TracePID, TracePID_Kp, TracePID_Ki, TracePID_Kd, TracePID_Target,
			 0, 0, TracePID_MinOutput, TracePID_MaxOutput);
	float transform = 0;
	while (1)
	{
		if (get_T_ALL() == 0xFF)
		{
			// HAL_Delay(5);
			// if (get_T_ALL() == 0xFF)
			//{
			break;
			//}
		}
		if (get_T_ALL() == 0x00)
		{
			HAL_Delay(10);
			if (get_T_ALL() == 0x00)
			{
				stop();
				return 0; // 巡不到轨迹返回0
			}
		}
		transform = PID_Compute(&TracePID, get_Terror());
		Set_PWM(60 - transform, 60 + transform);
		HAL_Delay(5);
	}
	stop();
	return 1; // 遇到十字路口返回1
}