#ifndef __TB6612_H__
#define __TB6612_H__

#include "main.h"
#define PWM_Prescaler 0
#define PWM_Period 10000

void Set_PWM(float PWMB_in, float PWMA_in);//设置两轮速度
void TB6612_Init();//// 初始化TB6612相关模组
void reset_encoder();

void read_encoder(int16_t encoder[]);////阅读两编码器的值
int16_t Read_Encoder(uint8_t TIMX);//阅读TIMX对应的编码器

/* uint16_t Get_adc();
uint16_t Get_adc_Average(uint8_t times); */

#endif