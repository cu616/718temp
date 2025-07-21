// 直行模组

#include <main.h>
#include <Mode_straight.h>

void go_straight(float angle, float speed)
{
	// read_angle();
	char msg[20], msg1[20];
	sprintf(msg, "%.2f", angle);
	OLED_ShowString(0, 20, msg, 8, 1);
	OLED_Refresh();
	PID *pid_straight = malloc(sizeof(PID));
	pid_straight->Kp = 1.8;
	pid_straight->Ki = 0;
	pid_straight->Kd = 2.5;
	pid_straight->target = angle; // 直行角度
	pid_straight->minIntegral = -5;
	pid_straight->maxIntegral = 5;
	pid_straight->minOutput = -10;
	pid_straight->maxOutput = 10;
	pid_straight->error = 0.0;		// 不需要修改
	pid_straight->last_error = 0.0; // 不需要修改
	pid_straight->integral = 0.0;	// 不需要修改
	float transform = 0;
	// read_angle();
	while (1) // get_T_ALL() == 0x00)
	{		  // 寻到轨迹是停止直行
		// read_angle();//更新Yaw
		sprintf(msg1, "%.2f", Yaw);
		OLED_ShowString(0, 30, msg1, 8, 1);
		OLED_Refresh();
		transform = PID_Compute(pid_straight, Yaw);
		if (transform > 0)
		{
			Set_PWM(speed - transform, speed); // Yaw偏小时transform>0,左轮减速可增大Yaw
		}
		else if (transform < 0)
		{
			Set_PWM(speed, speed + transform); // Yaw偏大时transform<0,右轮减速可减小Yaw
		}
		else
		{
			Set_PWM(speed, speed);
		}
		// OLED_ShowNum(10,40,transform,6,8,1);
		// OLED_Refresh();
		// Delay_Ms(10);
	}
}