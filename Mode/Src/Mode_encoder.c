// 通过编码器记录行驶长度的相关模组

#include <main.h>
#include <Mode_encoder.h>

void trace_encoder(uint16_t encoder_max, float speed)
{
	PID TracePID;
	float TracePID_Kp = 30, TracePID_Ki = 0, TracePID_Kd = 5;
	float TracePID_Target = 0, TracePID_MinOutput = -35, TracePID_MaxOutput = 35;
	float IntergretPID_MinOutput = -10, IntergretPID_MaxOutput = 10;
	float TracePID_Input = 0;
	PID_Init(&TracePID, TracePID_Kp, TracePID_Ki, TracePID_Kd, TracePID_Target,
			 0, 0, TracePID_MinOutput, TracePID_MaxOutput);

	float transform = 0; // 两轮基于基础巡线速度的差值
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
	// HAL_TIM_Encoder_Stop(&htim1,TIM_CHANNEL_ALL);
	__HAL_TIM_SET_COUNTER(&htim4, 0);

	while (1)
	{
		if (__HAL_TIM_GET_COUNTER(&htim4) > encoder_max)
		{
			break;
		}
		transform = PID_Compute(&TracePID, get_Terror());
		Set_PWM(speed - transform, speed + transform);
		HAL_Delay(10);
	}
	return;
}
