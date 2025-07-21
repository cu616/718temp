// 循迹模组

#include <main.h>
#include <Mode_trace.h>

int trace(float speed)
{
	PID TracePID;
	float TracePID_Kp = 30, TracePID_Ki = 0, TracePID_Kd = 5;
	float TracePID_Target = 0, TracePID_MinOutput = -35, TracePID_MaxOutput = 35;
	float IntergretPID_MinOutput = -10, IntergretPID_MaxOutput = 10;
	float TracePID_Input = 0;
	PID_Init(&TracePID, TracePID_Kp, TracePID_Ki, TracePID_Kd, TracePID_Target,
			 0, 0, TracePID_MinOutput, TracePID_MaxOutput);
	float transform = 0;
	while (1) // 可在此添加跳出条件
	{
		transform = PID_Compute(&TracePID, get_Terror());
		Set_PWM(speed - transform, speed + transform);
		HAL_Delay(5);
	}
	stop();
	return 1; // 遇到十字路口返回1
}

int trace_serial(float speed)
{
	PID TracePID;
	float TracePID_Kp = 30, TracePID_Ki = 0, TracePID_Kd = 5;
	float TracePID_Target = 0, TracePID_MinOutput = -35, TracePID_MaxOutput = 35;
	float IntergretPID_MinOutput = -10, IntergretPID_MaxOutput = 10;
	float TracePID_Input = 0;
	PID_Init(&TracePID, TracePID_Kp, TracePID_Ki, TracePID_Kd, TracePID_Target,
			 0, 0, TracePID_MinOutput, TracePID_MaxOutput);
	float transform = 0;

	uint8_t value[8] = {0};
	while (1) // 可在此添加跳出条件
	{
		get_path_serial(value);
		transform = PID_Compute(&TracePID, get_Terror_serial(value));
		Set_PWM(speed - transform, speed + transform);
		HAL_Delay(10);
	}
	stop();
	return 1; // 遇到十字路口返回1
}

void trace_to_cross(float speed)
{
	PID TracePID;
	float TracePID_Kp = 30, TracePID_Ki = 0, TracePID_Kd = 5;
	float TracePID_Target = 0, TracePID_MinOutput = -35, TracePID_MaxOutput = 35;
	float IntergretPID_MinOutput = -10, IntergretPID_MaxOutput = 10;
	float TracePID_Input = 0;
	PID_Init(&TracePID, TracePID_Kp, TracePID_Ki, TracePID_Kd, TracePID_Target,
			 0, 0, TracePID_MinOutput, TracePID_MaxOutput);

	float transform = 0; // 两轮基于基础巡线速度的差值

	while (1)
	{
		if (((get_T(1) && get_T(2)) || (get_T(7) && get_T(8))) && (get_T(4) || get_T(5)))
		{
			HAL_Delay(5);
			if (((get_T(1) && get_T(2)) || (get_T(7) && get_T(8))) && (get_T(4) || get_T(5)))
			{
				break;
			}
		}
		if (get_T_ALL() == 0x00)
		{
			HAL_Delay(5);
			if (get_T_ALL() == 0x00)
			{
				return; // 巡不到轨迹返回
			}
		}
		transform = PID_Compute(&TracePID, get_Terror());
		Set_PWM(speed - transform, speed + transform);
		HAL_Delay(5);
	}
	return;
}

void trace_to_cross_serial(float speed)
{
	PID TracePID;
	float TracePID_Kp = 20, TracePID_Ki = 0, TracePID_Kd = 35;
	float TracePID_Target = 0, TracePID_MinOutput = -35, TracePID_MaxOutput = 35;
	float IntergretPID_MinOutput = -10, IntergretPID_MaxOutput = 10;
	float TracePID_Input = 0;
	PID_Init(&TracePID, TracePID_Kp, TracePID_Ki, TracePID_Kd, TracePID_Target,
			 0, 0, TracePID_MinOutput, TracePID_MaxOutput);

	float transform = 0; // 两轮基于基础巡线速度的差值
	uint8_t value[8];

	while (1)
	{
		get_path_serial(value);
		if (((value[1 - 1] && value[2 - 1]) || (value[8 - 1] && value[7 - 1])) && (value[4 - 1] || value[5 - 1])) // get_T(1)&&get_T(8))
		{
			HAL_Delay(10);
			get_path_serial(value);
			if (((value[1 - 1] && value[2 - 1]) || (value[8 - 1] && value[7 - 1])) && (value[4 - 1] || value[5 - 1]))
			{ // 遇到十字路口返回
				break;
			}
		}
		if (get_T_ALL_serial(value) == 0x00)
		{
			HAL_Delay(10);
			if (get_T_ALL_serial(value) == 0x00)
			{
				return; // 巡不到轨迹返回
			}
		}
		transform = PID_Compute(&TracePID, get_Terror_serial(value));
		Set_PWM(speed - transform, speed + transform);
		HAL_Delay(10);
	}
	return;
}