#include <main.h>
#include <basic_task.h>

void task1()
{
    int8_t flag = 0;
	int8_t flag_far = 0;
	int8_t i = 1;
	float initial_angle = 0;
	float speed = 60;
	float turn_speed = 60;
	encoder_flag = 0;

	__HAL_TIM_SET_COUNTER(&htim1, 0);
	__HAL_TIM_SET_COUNTER(&htim4, 0);
	HAL_TIM_Encoder_Stop_IT(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Stop_IT(&htim4, TIM_CHANNEL_ALL);

	GetTargetNum();
	HAL_Delay(3000);

	Set_PWM(speed, speed);
	HAL_Delay(350);
	trace_to_cross_serial(speed);
	// 第一次循迹

	if (encoder_flag != 0)
	{
		initial_angle = Yaw;
		flag = encoder_flag;
		//car_brake();
		autoturn_serial(flag, turn_speed);
	}
	else{
		for (i = 2; i <= 3; i++)
		{
			reset_encoder();
			//if(i == 3)
			//	__HAL_TIM_SET_COUNTER(&htim1, 7500);
			Set_PWM(speed, speed);
			HAL_Delay(150);
			trace_to_cross_serial(speed);
			if (flag = encoder_flag)
			{
				initial_angle = Yaw;
				//car_brake();
				autoturn_serial(flag, turn_speed);
				break;
			}
			OLED_Clear();
		}
	}

	if (i == 3)
	{
		reset_encoder();
		__HAL_TIM_SET_COUNTER(&htim1, 1000);
		__HAL_TIM_SET_COUNTER(&htim4, 1000);
		trace_to_cross_serial(speed);
		flag_far = flag;
		flag = encoder_flag;
		initial_angle = Yaw;
		//car_brake();
		autoturn_serial(flag, turn_speed);
	}

    trace_to_cross_serial(speed);
	car_brake();
	// 等待卸药
	reverse_straight(initial_angle + 90 * flag, 50);
	// reverse(40);
	// reverse_straight(Kyaw,40);//陀螺仪version

	autoturn_serial(flag, turn_speed);
	if (i == 3)
	{
		trace_to_cross_serial(speed);
		//car_brake();
		autoturn_serial(-flag_far, turn_speed);
	}
	while (i)
	{
		Set_PWM(speed, speed);
		HAL_Delay(150);
		trace_to_cross_serial(speed);
		i--;
	}
	car_brake();
	//回到药房
}

void task2()
{
    HAL_TIM_Encoder_Stop_IT(&htim1, TIM_CHANNEL_ALL);
    trace_to_cross_serial(60);
    //HAL_Delay(500);
    float initial_angle = Yaw;
    //trace_to_cross_serial_encoder(500,60);	
    autoturn_serial(1,60);
    trace_to_cross_serial(50);
    reverse_straight(initial_angle+90, 50);
    //trace_to_cross_serial_encoder(1000,60);
    autoturn_serial(1,60);
    trace_to_cross_serial(50);
    stop();
}

void task3()
{
}

void task4()
{
}