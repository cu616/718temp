/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "i2c.h"
#include "TB6612.h"
#include "pid.h"
#include "filter.h"
#include "mpu6050.h"
#include "Trace.h"
#include "task.h"
#include "oled.h"
#include "UI.h"
#include "mytask.h"
#include "jy61p.h"
#include "gw_grayscale_sensor.h"
#include "GWKJ.h"


#include <stdio.h>
#include "math.h"
#include "stdlib.h"	
#include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern volatile bool key1state;
extern volatile bool key2state;
extern volatile int8_t encoder_flag;
extern uint8_t target;
extern char read_data[4];
//extern volatile int8_t encoder_flag2;
extern volatile int led_beep_flag;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define KEY1_Pin GPIO_PIN_3
#define KEY1_GPIO_Port GPIOE
#define KEY1_EXTI_IRQn EXTI3_IRQn
#define LEDY_Pin GPIO_PIN_0
#define LEDY_GPIO_Port GPIOA
#define LEDG_Pin GPIO_PIN_1
#define LEDG_GPIO_Port GPIOA
#define RING_Pin GPIO_PIN_4
#define RING_GPIO_Port GPIOA
#define LEDR_Pin GPIO_PIN_5
#define LEDR_GPIO_Port GPIOA
#define OLED_D0_Pin GPIO_PIN_4
#define OLED_D0_GPIO_Port GPIOC
#define KEY2_Pin GPIO_PIN_5
#define KEY2_GPIO_Port GPIOC
#define KEY2_EXTI_IRQn EXTI9_5_IRQn
#define OLED_D1_Pin GPIO_PIN_0
#define OLED_D1_GPIO_Port GPIOB
#define OLED_RES_Pin GPIO_PIN_1
#define OLED_RES_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_2
#define OLED_DC_GPIO_Port GPIOB
#define OLED_CS_Pin GPIO_PIN_7
#define OLED_CS_GPIO_Port GPIOE
#define BL1_Pin GPIO_PIN_8
#define BL1_GPIO_Port GPIOE
#define BL2_Pin GPIO_PIN_9
#define BL2_GPIO_Port GPIOE
#define BL3_Pin GPIO_PIN_10
#define BL3_GPIO_Port GPIOE
#define BL4_Pin GPIO_PIN_11
#define BL4_GPIO_Port GPIOE
#define BL5_Pin GPIO_PIN_12
#define BL5_GPIO_Port GPIOE
#define BL6_Pin GPIO_PIN_13
#define BL6_GPIO_Port GPIOE
#define BL7_Pin GPIO_PIN_14
#define BL7_GPIO_Port GPIOE
#define BL8_Pin GPIO_PIN_15
#define BL8_GPIO_Port GPIOE
#define AOUT1_Pin GPIO_PIN_12
#define AOUT1_GPIO_Port GPIOD
#define AOUT2_Pin GPIO_PIN_13
#define AOUT2_GPIO_Port GPIOD
#define AIN1_Pin GPIO_PIN_14
#define AIN1_GPIO_Port GPIOD
#define AIN2_Pin GPIO_PIN_15
#define AIN2_GPIO_Port GPIOD
#define PWMA_Pin GPIO_PIN_8
#define PWMA_GPIO_Port GPIOC
#define BOUT1_Pin GPIO_PIN_8
#define BOUT1_GPIO_Port GPIOA
#define BOUT2_Pin GPIO_PIN_9
#define BOUT2_GPIO_Port GPIOA
#define PWMB_Pin GPIO_PIN_15
#define PWMB_GPIO_Port GPIOA
#define BIN1_Pin GPIO_PIN_10
#define BIN1_GPIO_Port GPIOC
#define BIN2_Pin GPIO_PIN_11
#define BIN2_GPIO_Port GPIOC
#define DETECT_Pin GPIO_PIN_1
#define DETECT_GPIO_Port GPIOD
#define SDA_Pin GPIO_PIN_6
#define SDA_GPIO_Port GPIOB
#define SCL_Pin GPIO_PIN_7
#define SCL_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
