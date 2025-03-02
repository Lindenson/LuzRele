/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Up_Pin GPIO_PIN_13
#define Up_GPIO_Port GPIOC
#define Up_EXTI_IRQn EXTI15_10_IRQn
#define Relay_Pin GPIO_PIN_1
#define Relay_GPIO_Port GPIOA
#define Down_Pin GPIO_PIN_3
#define Down_GPIO_Port GPIOA
#define Down_EXTI_IRQn EXTI3_IRQn
#define OK_Pin GPIO_PIN_4
#define OK_GPIO_Port GPIOA
#define OK_EXTI_IRQn EXTI4_IRQn
#define Cancel_Pin GPIO_PIN_5
#define Cancel_GPIO_Port GPIOA
#define Cancel_EXTI_IRQn EXTI9_5_IRQn
#define MOVE_SENSOR_Pin GPIO_PIN_0
#define MOVE_SENSOR_GPIO_Port GPIOB
#define MOVE_SENSOR_EXTI_IRQn EXTI0_IRQn

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
