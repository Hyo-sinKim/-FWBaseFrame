/**
  ******************************************************************************
  * @file    main.c 
  * @author  KMAC Electronic Controll Team
  * @version V1.0.0
  * @date    2014 10 14
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  *
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "port_hsDrv_MCP4728.h"

//HW Config

//CONST Define
#define MCP4728_DAT_SIZE        3

#define MCP4728_WAIT_TIM        1000

//Public 

//Extern variable


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
/**
  * @brief  
  * @param  None
  * @retval None
  */
int32_t port_MCP4728_I2C_Write(void *p_HALDrv, uint8_t *p_uWriteDataMem)
{
  int32_t dwCheck = 0;
  
  dwCheck = HAL_I2C_Master_Transmit(p_HALDrv, p_uWriteDataMem[0], &(p_uWriteDataMem[1]), MCP4728_DAT_SIZE, MCP4728_WAIT_TIM);
  
  return dwCheck;
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
int32_t port_MCP4728_nBusyCheck(uint32_t dwPort_Num, uint32_t *p_dw_n_BusyCheck)
{
  int32_t dwCheck = 0;
#if 0  

  GPIO_PinState tStatusPin;
  
  switch(dwPort_Num)
  {
  case PORT_NUM_I2C1:
    tStatusPin = HAL_GPIO_ReadPin(DAC_BUSY_IN_GPIO_Port, DAC_BUSY_IN_Pin);
    
    *p_dw_n_BusyCheck = (uint32_t)tStatusPin;
    break;
  default:
    dwCheck = DAT_ERR_PARAM_CMD;
    break;
  }
#endif
  
  *p_dw_n_BusyCheck = SET;
  
  
  return dwCheck;
}

/**
  * @brief  
  * @param  None
  * @retval None
  */


/**
  * @brief  
  * @param  None
  * @retval None
  */

