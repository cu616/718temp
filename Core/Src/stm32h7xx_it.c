/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    stm32h7xx_it.c
 * @brief   Interrupt Service Routines.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32h7xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "HMC5883.h"
#include "mpu6050.h"
#include "filter.h"
#include "jy61p.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern UART_HandleTypeDef huart2;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
  while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32H7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32h7xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles EXTI line3 interrupt.
  */
void EXTI3_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI3_IRQn 0 */
  key1state = 1;
  /* USER CODE END EXTI3_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY1_Pin);
  /* USER CODE BEGIN EXTI3_IRQn 1 */

  /* USER CODE END EXTI3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */
  key2state = 1;
  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(KEY2_Pin);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM4 global interrupt.
  */
void TIM4_IRQHandler(void)
{
  /* USER CODE BEGIN TIM4_IRQn 0 */
  //  encoder_flag2 = 1;
  //  HAL_UART_Transmit(&huart1, "get", 3, 0xFFFF);
  //  int text;
  //  while(text )
  //  {
  //
  //  }
  //  int8_t receive = uart;//possible value:1L -1R
  //  if(encoder_flag1 != 0){
  //    encoder_flag1 = receive;
  //  }
  //  else{
  //    encoder_flag2 = receive;
  //  }
  //  stop();
  //  char msg[7];
  //  HAL_UART_Transmit(&huart1, "get\r\n", 5, 20);
  //  HAL_UART_Receive(&huart1, msg, 7, 30);
  //  switch (msg[0])
  //  {
  //  case 'L':
  //    encoder_flag1 = 1;
  //    break;
  //  case 'R':
  //    encoder_flag1 = -1;
  //    break;
  //  case 'M':
  //    encoder_flag1 = 0;
  //    break;
  //  default:
  //    encoder_flag1 = 1;
  //    break;
  //  }
  /* USER CODE END TIM4_IRQn 0 */
  HAL_TIM_IRQHandler(&htim4);
  /* USER CODE BEGIN TIM4_IRQn 1 */
  //  __HAL_TIM_DISABLE_IT(&htim4,TIM_IT_UPDATE);
  /* USER CODE END TIM4_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(&huart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles TIM6 global interrupt, DAC1_CH1 and DAC1_CH2 underrun error interrupts.
  */
void TIM6_DAC_IRQHandler(void)
{
  /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
  jy61p_caculate();
  /* USER CODE END TIM6_DAC_IRQn 0 */
  HAL_TIM_IRQHandler(&htim6);
  /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

  /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */
  int16_t encoder_num[2];
  char msg[10];
  read_encoder(encoder_num);
  sprintf(msg, "%d, %d", encoder_num[0], encoder_num[1]);
  if (encoder_num[0] > 4200 && encoder_num[0] < 4500)
  {
    stop();
    OLED_ShowString(0, 30, msg, 8, 1);
    OLED_Refresh();
    GetTurnData();
    if (read_data[3] == '0')
    {
      if (read_data[0] == target + '0')
      {
        encoder_flag = 1;
      }
      else if (read_data[1] == target + '0')
      {
        encoder_flag = -1;
      }
    }
    else
    {
      if (read_data[0] == target + '0' || read_data[1] == target + '0')
      {
        encoder_flag = 1;
      }
      else if (read_data[2] == target + '0' || read_data[3] == target + '0')
      {
        encoder_flag = -1;
      }
    }
    char flag_msg[4];
    sprintf(flag_msg,"%d",encoder_flag+1);
    OLED_ShowString(64, 40, flag_msg, 8, 1);
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    __HAL_TIM_SET_COUNTER(&htim4, 0);
    HAL_TIM_Encoder_Stop_IT(&htim1, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Stop_IT(&htim4, TIM_CHANNEL_ALL);
    OLED_ShowString(64, 0, "IT finish", 8, 1);
    OLED_Refresh();
  }
  // 此部分为陀螺仪及相关调试代码
  // MPU6050_Read_Result();
  // printf("Accel: AX=%.2f, AY=%.2f, AZ=%.2f\r\n", Ax, Ay, Az);
  // printf("Gyro: GX=%.3f, GY=%.3f, GZ=%.3f \r ", Gx, Gy, Gz);
  // printf("mroll=%.3f \r mpitch=%.3f \r myaw=%.3f \r ",mroll,mpitch,myaw);
  // MPU6050_Read_Result();
  // printf("Accel: X=%.2f, Y=%.2f, Z=%.2f\r\n", Ax, Ay, Az);
  // printf("Gyro: Z=%.2f\r", Gz);
  // HMC5883_getyaw();
  // printf("Bx=%d \rBy=%d \rBz=%d \rhyaw=%f \r \n",Bx,By,Bz,hyaw);
  // printf("hyaw=%.3f \n",hyaw);
  // Kalman_getangle();
  // printf("Kroll=%f\r Kpitch=%f\r Kyaw=%f\n",Kroll ,Kpitch,Kyaw);
  // printf("myaw=%f\r  Kyaw=%f\n",myaw ,Kyaw);
  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/* USER CODE BEGIN 1 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart == &huart2) // �ж��ж�Դ
  {
    if (jytime)
    {
      jy61p_ReceiveData(g_usart2_receivedata);
      HAL_UART_Receive_IT(&huart2, &g_usart2_receivedata, 1);
    }
  }
}
/* USER CODE END 1 */
