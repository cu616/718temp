#include<main.h>
#include "TB6612.h"
volatile int8_t encoder_flag;
//volatile int8_t encoder_flag2;


void Set_PWM(float PWMB_in, float PWMA_in)//BΪ���֣�AΪ���֣����������������Ϊ���֡�����ռ�ձ�
{
  int PWMA = PWMA_in * PWM_Period / 100;
  int PWMB = PWMB_in * PWM_Period / 100;
  /* ���A������ƣ�PC0/PC13�� */
  if(PWMA > 0) {
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);   // AIN2�ߵ�ƽ
    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET); // AIN1�͵�ƽ
  } 
	else {
    HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);   // AIN1�ߵ�ƽ
    HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET); // AIN2�͵�ƽ
    PWMA = -PWMA; // ȡ����ֵ
  }

  /* ���B������ƣ�PB10/PE14�� */
  if(PWMB > 0) {
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);   // BIN2�ߵ�ƽ
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET); // BIN1�͵�ƽ
  } 
	else {
    HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);   // BIN1�ߵ�ƽ
    HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET); // BIN2�͵�ƽ
    PWMB = -PWMB; // ȡ����ֵ
  }

  /* ����PWMռ�ձȣ�TIM2ͨ��1��TIM3ͨ��3��(PA0,PB0) */
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, PWMA); // ����TIM2_CH1ռ�ձ�
  __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, PWMB); // ����TIM3_CH3ռ�ձ�
}

void stop(){   //�ƶ�ֹͣ
	HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET); 
  HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
}

void car_brake(){
  Set_PWM(-100,-100);
	HAL_Delay(100);
  stop();
}

void TB6612_Init(void){    //���ģ����س�ʼ����������ʹ�õ��֮ǰ����
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
  __HAL_TIM_ENABLE_IT(&htim7, TIM_IT_UPDATE);
    __HAL_TIM_SET_PRESCALER(&htim2, PWM_Prescaler);
    __HAL_TIM_SET_AUTORELOAD(&htim2, PWM_Period);
    __HAL_TIM_SET_PRESCALER(&htim3, PWM_Prescaler);
    __HAL_TIM_SET_AUTORELOAD(&htim3, PWM_Period);
    __HAL_TIM_SET_COUNTER(&htim7,0);
}//PWM_Prescaler��PWM_Period��TB6612.h�ļ����޸ģ�Ϊ����PWM���ļ�������Ԥ��Ƶ�����Զ���װ��ֵ

void reset_encoder(){
  //encoder_flag = 0;
  //encoder_flag2 = 0;
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  __HAL_TIM_SET_COUNTER(&htim4, 0);
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
}

void start_encoder_IT(uint32_t period){
  __HAL_TIM_SET_COUNTER(&htim1, 0);
  __HAL_TIM_SET_COUNTER(&htim4, 0);
  //__HAL_TIM_SET_AUTORELOAD(&htim4, period);
  //__HAL_TIM_ENABLE_IT(&htim4,TIM_IT_UPDATE);
}

void read_encoder(int16_t encoder[]){
  encoder[0] = (int16_t)__HAL_TIM_GET_COUNTER(&htim1);
  encoder[1] = (int16_t)__HAL_TIM_GET_COUNTER(&htim4);
}


//
//
//����ĺ����ò���
//
//



int16_t Read_Encoder(uint8_t TIMX)
{
    int16_t Encoder_TIM = 0;
    TIM_HandleTypeDef *htim = NULL;

    switch (TIMX)
    {
    case 1:
        htim = &htim1;  // ���� htim2 ��ȫ�ֱ�����TIM2 �ľ����
        break;
    case 4:
        htim = &htim4;  // ���� htim4 ��ȫ�ֱ�����TIM4 �ľ����
        break;
    default:
        return 0;  // ��Ч�� TIMX
    }

    // ��ȡ��ǰ����ֵ���Զ�ת��Ϊ int16_t ����ȷ����������
    Encoder_TIM = (int16_t)__HAL_TIM_GET_COUNTER(htim);
    
    // ���ü�����Ϊ 0
    //__HAL_TIM_SET_COUNTER(htim, 0);

    return Encoder_TIM;
}

//// ��ȡ����ADCת��ֵ����
//uint16_t Get_adc()  // channel: ADCͨ���� (ADC_CHANNEL_x)
//{


//    // ����ADCת��
//    HAL_ADC_Start(&hadc1);  // ����ADC1ת��
//    
//    // �ȴ�ת����ɣ���ʱʱ��10ms��
//    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY); // ��ѯת����ɱ�־

//    return HAL_ADC_GetValue(&hadc1);  // ��ȡ12λADCת��ֵ

//}

//// ��ȡ���ADC����ƽ��ֵ����
//uint16_t Get_adc_Average(uint8_t times)  // channel: ͨ����, times: ��������
//{                                       
//    uint32_t temp_val = 0;  // ��ʱ�ۼӱ��� - �洢��β������ܺ�
//    
//    // ѭ���ɼ�ָ��������ADCֵ
//    for(uint8_t t = 0; t < times; t++)
//    {
//        // ��ȡ����ADCֵ���ۼ�
//        temp_val += Get_adc();  // ���õ���ADCת������
//        
//        // ÿ�β�������ʱ5ms���ȶ�ʱ�䣩
//        HAL_Delay(5);  // ʹ��HAL����ʱ�����ȴ�5����
//    }
//    
//    // ����ƽ��ֵ������
//    return (uint16_t)(temp_val / times);  // �ܺͳ��Բ��������õ�ƽ��ֵ    
//}