/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RL_8_Pin GPIO_PIN_2
#define RL_8_GPIO_Port GPIOE
#define RL_9_Pin GPIO_PIN_3
#define RL_9_GPIO_Port GPIOE
#define RL_6_Pin GPIO_PIN_4
#define RL_6_GPIO_Port GPIOE
#define RL_7_Pin GPIO_PIN_5
#define RL_7_GPIO_Port GPIOE
#define RL_5_Pin GPIO_PIN_13
#define RL_5_GPIO_Port GPIOC
#define RL_2_Pin GPIO_PIN_14
#define RL_2_GPIO_Port GPIOC
#define RL_3_Pin GPIO_PIN_15
#define RL_3_GPIO_Port GPIOC
#define LIM0_Pin GPIO_PIN_2
#define LIM0_GPIO_Port GPIOB
#define LIM1_Pin GPIO_PIN_7
#define LIM1_GPIO_Port GPIOE
#define LIM2_Pin GPIO_PIN_8
#define LIM2_GPIO_Port GPIOE
#define LIM3_Pin GPIO_PIN_9
#define LIM3_GPIO_Port GPIOE
#define LIM4_Pin GPIO_PIN_10
#define LIM4_GPIO_Port GPIOE
#define LIM5_Pin GPIO_PIN_11
#define LIM5_GPIO_Port GPIOE
#define LIM6_Pin GPIO_PIN_12
#define LIM6_GPIO_Port GPIOE
#define LIM7_Pin GPIO_PIN_13
#define LIM7_GPIO_Port GPIOE
#define LIM8_Pin GPIO_PIN_14
#define LIM8_GPIO_Port GPIOE
#define LIM9_Pin GPIO_PIN_15
#define LIM9_GPIO_Port GPIOE
#define RL_4_Pin GPIO_PIN_10
#define RL_4_GPIO_Port GPIOB
#define LIM10_Pin GPIO_PIN_12
#define LIM10_GPIO_Port GPIOB
#define LIM11_Pin GPIO_PIN_13
#define LIM11_GPIO_Port GPIOB
#define LIM12_Pin GPIO_PIN_14
#define LIM12_GPIO_Port GPIOB
#define LIM13_Pin GPIO_PIN_15
#define LIM13_GPIO_Port GPIOB
#define LIM14_Pin GPIO_PIN_8
#define LIM14_GPIO_Port GPIOD
#define LIM15_Pin GPIO_PIN_9
#define LIM15_GPIO_Port GPIOD
#define LCD_RS_Pin GPIO_PIN_10
#define LCD_RS_GPIO_Port GPIOD
#define LCD_EN_Pin GPIO_PIN_11
#define LCD_EN_GPIO_Port GPIOD
#define LCD_B4_Pin GPIO_PIN_12
#define LCD_B4_GPIO_Port GPIOD
#define LCD_B5_Pin GPIO_PIN_13
#define LCD_B5_GPIO_Port GPIOD
#define LCD_B6_Pin GPIO_PIN_14
#define LCD_B6_GPIO_Port GPIOD
#define LCD_B7_Pin GPIO_PIN_15
#define LCD_B7_GPIO_Port GPIOD
#define BT_10_Pin GPIO_PIN_9
#define BT_10_GPIO_Port GPIOC
#define BUZZER_Pin GPIO_PIN_8
#define BUZZER_GPIO_Port GPIOA
#define RL_0_Pin GPIO_PIN_10
#define RL_0_GPIO_Port GPIOC
#define RL_1_Pin GPIO_PIN_11
#define RL_1_GPIO_Port GPIOC
#define BT_9_Pin GPIO_PIN_0 //Button Test
#define BT_9_GPIO_Port GPIOD
#define BT_7_Pin GPIO_PIN_1 //Button Left
#define BT_7_GPIO_Port GPIOD
#define BT_8_Pin GPIO_PIN_2 //Button Silent
#define BT_8_GPIO_Port GPIOD
#define BT_5_Pin GPIO_PIN_3 //Button Ok
#define BT_5_GPIO_Port GPIOD
#define BT_6_Pin GPIO_PIN_4 //Button Down
#define BT_6_GPIO_Port GPIOD
#define BT_3_Pin GPIO_PIN_5 //Button Right
#define BT_3_GPIO_Port GPIOD
#define BT_4_Pin GPIO_PIN_6 //Button Up
#define BT_4_GPIO_Port GPIOD
#define BT_1_Pin GPIO_PIN_7 //Unused
#define BT_1_GPIO_Port GPIOD
#define BT_2_Pin GPIO_PIN_3 //Button Mute
#define BT_2_GPIO_Port GPIOB
#define RL_16_Pin GPIO_PIN_4 
#define RL_16_GPIO_Port GPIOB
#define BT_0_Pin GPIO_PIN_5
#define BT_0_GPIO_Port GPIOB
#define RL_14_Pin GPIO_PIN_6
#define RL_14_GPIO_Port GPIOB
#define RL_15_Pin GPIO_PIN_7
#define RL_15_GPIO_Port GPIOB
#define RL_12_Pin GPIO_PIN_8
#define RL_12_GPIO_Port GPIOB
#define RL_13_Pin GPIO_PIN_9
#define RL_13_GPIO_Port GPIOB
#define RL_10_Pin GPIO_PIN_0
#define RL_10_GPIO_Port GPIOE
#define RL_11_Pin GPIO_PIN_1
#define RL_11_GPIO_Port GPIOE

//extern TIM_HandleTypeDef htim6;

//extern UART_HandleTypeDef huart1;
//extern UART_HandleTypeDef huart6;

//extern void init_pheriperal(){
//	HAL_UART_Init(&huart1);
//	HAL_UART_Init(&huart6);
//	HAL_TIM_Base_Start_IT(&htim6);
//}
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
