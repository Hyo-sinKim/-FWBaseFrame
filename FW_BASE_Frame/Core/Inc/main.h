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
#include "stm32l4xx_hal.h"

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
#define DAC_SEL0_Pin GPIO_PIN_13
#define DAC_SEL0_GPIO_Port GPIOC
#define DAC_SEL1_Pin GPIO_PIN_14
#define DAC_SEL1_GPIO_Port GPIOC
#define RS485_DIR_Pin GPIO_PIN_4
#define RS485_DIR_GPIO_Port GPIOA
#define SPI_nCS_Pin GPIO_PIN_0
#define SPI_nCS_GPIO_Port GPIOB
#define PB12_OUT_Pin GPIO_PIN_12
#define PB12_OUT_GPIO_Port GPIOB
#define PB13_OUT_Pin GPIO_PIN_13
#define PB13_OUT_GPIO_Port GPIOB
#define PB14_OUT_Pin GPIO_PIN_14
#define PB14_OUT_GPIO_Port GPIOB
#define STA_LED1_Pin GPIO_PIN_15
#define STA_LED1_GPIO_Port GPIOB
#define PC8_IN_Pin GPIO_PIN_8
#define PC8_IN_GPIO_Port GPIOC
#define PC9_IN_Pin GPIO_PIN_9
#define PC9_IN_GPIO_Port GPIOC
#define STA_LED2_Pin GPIO_PIN_8
#define STA_LED2_GPIO_Port GPIOA
#define STA_LED3_Pin GPIO_PIN_12
#define STA_LED3_GPIO_Port GPIOA
#define STRIP_LED_CTRL_Pin GPIO_PIN_15
#define STRIP_LED_CTRL_GPIO_Port GPIOA
#define LS_PW1_CTRL_Pin GPIO_PIN_10
#define LS_PW1_CTRL_GPIO_Port GPIOC
#define LS_PW2_CTRL_Pin GPIO_PIN_11
#define LS_PW2_CTRL_GPIO_Port GPIOC
#define A4988_nRST_Pin GPIO_PIN_4
#define A4988_nRST_GPIO_Port GPIOB
#define A4988_DIR_Pin GPIO_PIN_5
#define A4988_DIR_GPIO_Port GPIOB
#define STA_ERR_LED_Pin GPIO_PIN_9
#define STA_ERR_LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
