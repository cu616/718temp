// 基础运动模组

#include <main.h>
#include <Mode_motion.h>

void stop()
{ // 停车
	HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
}

void car_brake(uint32_t time)
{
	Set_PWM(-100, -100);
	HAL_Delay(time);
	stop();
}