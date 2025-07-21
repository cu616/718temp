// 转向模组

#include <main.h>
#include <Mode_turn.h>

void turn(float turn, float speed, float ratio)
{ // 只旋转外侧轮
    char msg[20], msg1[20];
    float speed1, speed2;
    float angle_end = turn + Yaw;

    if (turn > 0)
    { // 向左转动，则左轮为内轮
        speed1 = speed * ratio;
        speed2 = speed;
    }
    if (turn > 0)
    { // 向右转动，则右轮为内轮
        speed1 = speed * ratio;
        speed2 = speed;
    }
    while (1)
    {
        sprintf(msg1, "%.2f", Yaw);
        OLED_ShowString(0, 30, msg1, 8, 1);
        OLED_Refresh();
        // read_angle();//更新Yaw
        if (Yaw > angle_end - 0.5 && Yaw < angle_end + 0.5)
        { // 允许误差值
            stop();
            break;
        } // 达到目标角度附近便停止
        else
        {
            Set_PWM(speed1, speed2);
        }
        HAL_Delay(5);
    }
    Set_PWM(-speed1, -speed2);
    HAL_Delay(100);
    OLED_Clear();
    stop();
}

void turnto(float aim_angle, float speed, float ratio)
{
    float turn_angle = aim_angle - Yaw;
    turn(turn_angle, speed, ratio);
}

void autoturn(int8_t flag, float turn_speed) // 从当前位置旋转至寻到下一个轨迹(无制动)
{                          // speed>0时向左旋转，speed<时向右旋转
    if (flag == 0)
		return;
	float speed = flag * turn_speed;
	float start_angle = Yaw;

	while (get_T(4) || get_T(5))
	{
		Set_PWM(-speed, speed);
		HAL_Delay(10);
	} // 先脱离当前轨道

	while (!(get_T(4) || get_T(5)) || (Yaw-start_angle)*flag < 70 )
	{
		Set_PWM(-speed, speed);
		HAL_Delay(10);
	} // 中间两路寻到轨迹后判断中间靠边两路
}

void autoturn_serial(int8_t flag, float turn_speed) // 从当前位置旋转至寻到下一个轨迹(有制动)
{                          // speed>0时向左旋转，speed<时向右旋转
    if (flag == 0)
		return;
	float speed = flag * turn_speed;
	float start_angle = Yaw;
	uint8_t value[8];
	get_path_serial(value);

	while (value[4-1] || value[5-1])
	{
		get_path_serial(value);
		Set_PWM(-speed, speed);
		HAL_Delay(10);
	} // 先脱离当前轨道

	while ( !(value[4-1] || value[5-1] || value[3-1] || value[6-1]) &&  (Yaw-start_angle)*flag < 90  )
	{
		get_path_serial(value);
		Set_PWM(-speed, speed);
		HAL_Delay(10);
	} // 中间两路寻到轨迹后判断中间靠边两路

    Set_PWM(speed*2, -speed*2);
	HAL_Delay(100);
    //进行制动

    Set_PWM(50,50);
    HAL_Delay(100);
    //脱离轨迹
}