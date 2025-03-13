/**
  ******************************************************************************
  * @file           : 
  * @brief          : 
  *                   
  ******************************************************************************
  ** 
  * 
  *
  *
  * 
  *
  *
  * 
  *
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HW_H__
#define __HW_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"


//Public Define
#define LED_MCU_RUN     0
#define LED_MCU_ERR     1


//Public Type
enum REWORK_PP_ID
{
  RWRK_USART1_PP = 0,
  RWRK_USART2_PP,
  RWRK_USART3_PP,
  
  RWRK_SPI1_PP,
  
  RWRK_I2C1_PP,
  RWRK_I2C2_PP,
  
  RWRK_PP_MAX
};

enum PORT_NUM_USART
{
  PORT_NUM_USART1 = 0,
  PORT_NUM_USART2,
  PORT_NUM_USART3,
  
  PORT_NUM_USART_MAX
};

enum PORT_NUM_SPI
{
  PORT_NUM_SPI1 = 0,
  
  PORT_NUM_SPI_MAX
};


enum PORT_NUM_I2C
{
  PORT_NUM_I2C1 = 0,
  PORT_NUM_I2C2,
  
  PORT_NUM_I2C_MAX
};

enum MCU_STA_LED_CH
{
  MCU_STA_LED_CH_1 = 0,
  MCU_STA_LED_CH_2,
  MCU_STA_LED_CH_3,
  
  MCU_STA_LED_CH_MAX
};


//Function Type
int32_t hsHW_Config(void);

uint32_t BSP_hsSysTickTimer(uint32_t *p_TickTimer, uint32_t dwWaitTickTime);

void HW_ERR_LED_ONOFF(uint32_t dwON_nOFF);

void HW_LowCode_Error(uint32_t dwErrData);

void HW_STA_LED_ONOFF(uint32_t dwLED_Channel, uint32_t dwON_nOFF);

#endif /* __HW_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
