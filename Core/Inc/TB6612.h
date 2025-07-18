#ifndef __TB6612_H__
#define __TB6612_H__
#include "main.h"
#define PWM_Prescaler 0
#define PWM_Period 10000

void Set_PWM(float PWMB_in, float PWMA_in);//BΪ���֣�AΪ����
void TB6612_Init();//�����������ص�ģ����г�ʼ����������ʹ�õ��ǰ����
void reset_encoder();
void start_encoder_IT(uint32_t period);//���ñ�������ֵ
void read_encoder(int16_t encoder[]);//��ȡ���������ڵ�ֵ

void stop();//ͣ��
void car_brake();

int16_t Read_Encoder(uint8_t TIMX);//�����ṩ�Ķ�ȡ�������ò���
//uint16_t Get_adc();
//uint16_t Get_adc_Average(uint8_t times);
#endif