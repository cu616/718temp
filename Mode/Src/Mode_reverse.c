// 倒车模组

#include <main.h>
#include <Mode_reverse.h>

int reverse_trace(float speed)
{
	PID TracePID;
	TracePID.Kp = 20, TracePID.Ki = 0, TracePID.Kd = 0;
	TracePID.target = 0, TracePID.minOutput = -30, TracePID.maxOutput = 30;
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

void reverse_straight(float angle, float speed)
{
	char msg[20], msg1[20];
	sprintf(msg, "%.2f", angle);
	OLED_ShowString(0, 20, msg, 8, 1);
	OLED_Refresh();
	Set_PWM(-speed, -speed);
	HAL_Delay(500);
	// read_angle();
	PID *pid_straight = malloc(sizeof(PID));
	pid_straight->Kp = 9, pid_straight->Ki = 0, pid_straight->Kd = 25;
	pid_straight->target = angle;
	pid_straight->minIntegral = -10, pid_straight->maxIntegral = 10;
	pid_straight->minOutput = -25, pid_straight->maxOutput = 25;
	pid_straight->error = 0.0;
	pid_straight->last_error = 0.0;
	pid_straight->integral = 0.0;
	float transform = 0;
	uint8_t value[8];
	uint32_t i = 0;

	while (1)
	{
		get_path_serial(value);
		if(i<50){
			if ((value[1 - 1] == 1 && value[2 - 1] == 1 && value[3 - 1] == 1 && value[4 - 1] == 1) ||
				(value[5 - 1] == 1 && value[6 - 1] == 1 && value[7 - 1] == 1 && value[8 - 1] == 1))
			{
				get_path_serial(value);
				HAL_Delay(10);
				if ((value[1 - 1] == 1 && value[2 - 1] == 1 && value[3 - 1] == 1 && value[4 - 1] == 1) ||
					(value[5 - 1] == 1 && value[6 - 1] == 1 && value[7 - 1] == 1 && value[8 - 1] == 1))
				{
					break;
				}
			}
			if (get_T_ALL_serial(value) == 0x00)
			{
				break;
			}
		}
		else i++;
		sprintf(msg1, "%.2f", Yaw);
		OLED_ShowString(0, 30, msg1, 8, 1);
		OLED_Refresh();
		transform = PID_Compute(pid_straight, Yaw);
		if (transform > 0)
		{
			Set_PWM(-speed, -speed + transform); // Yaw偏小时transform>0,右轮减速可增大Yaw
		}
		else if (transform < 0)
		{
			Set_PWM(-speed - transform, -speed); // Yaw偏大时transform>0,左轮减速可减小Yaw
		}
		else
		{
			Set_PWM(-speed, -speed);
		}
		HAL_Delay(10);
	}
	Set_PWM(50, 50);
	while (!((value[1 - 1] == 1 && value[2 - 1] == 1 && value[3 - 1] == 1 && value[4 - 1] == 1) ||
			 (value[5 - 1] == 1 && value[6 - 1] == 1 && value[7 - 1] == 1 && value[8 - 1] == 1)))
		;
	HAL_Delay(350);
}

void reverse_encoder(float speed)
{
	char msg[20], msg1[20];
	__HAL_TIM_DISABLE_IT(&htim7, TIM_IT_UPDATE);
	int16_t encoder[2] = {0};
	// 做好相关准备

	Set_PWM(-speed, -speed);
	HAL_Delay(500);
	// 先离开黑线

	PID *pid_straight = malloc(sizeof(PID));
	pid_straight->Kp = 7, pid_straight->Ki = 0, pid_straight->Kd = 2.5;
	pid_straight->target = 0;
	pid_straight->minIntegral = -10, pid_straight->maxIntegral = 10;
	pid_straight->minOutput = -15, pid_straight->maxOutput = 15;
	pid_straight->error = 0.0;
	pid_straight->last_error = 0.0;
	pid_straight->integral = 0.0;
	float transform = 0;
	// read_angle();
	while (1)
	{
		if ((get_T(1) == 1 && get_T(2) == 1 && get_T(3) == 1 && get_T(4) == 1) ||
			(get_T(5) == 1 && get_T(6) == 1 && get_T(7) == 1 && get_T(8) == 1))
		{
			HAL_Delay(5);
			if ((get_T(1) == 1 && get_T(2) == 1 && get_T(3) == 1 && get_T(4) == 1) ||
				(get_T(5) == 1 && get_T(6) == 1 && get_T(7) == 1 && get_T(8) == 1))
			{
				break;
			}
		}
		if (get_T_ALL() == 0x00)
		{
			break;
		}
		// 到十字路口口或空地时停止

		reset_encoder();
		transform = PID_Compute(pid_straight, encoder[1] - encoder[0]);
		if (transform > 0)
		{
			Set_PWM(-speed + transform, -speed); // Yaw偏小时transform>0,右轮减速可增大Yaw
		}
		else if (transform < 0)
		{
			Set_PWM(-speed, -speed - transform); // Yaw偏大时transform>0,左轮减速可减小Yaw
		}
		else
		{
			Set_PWM(-speed, -speed);
		}
		HAL_Delay(10);
		read_encoder(encoder);
	}
	// stop();

	Set_PWM(62, 60);
	HAL_Delay(350);
	// 直行至十字路口
}