
/**
  ******************************************************************************
  * @file           : 
  * @brief          : 
  ******************************************************************************
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "Common_HAL.h"

//Define ---------------------------------------------------------------------

    
/* Extern --------------------------------------------------------------------*/
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

/* Private variables ---------------------------------------------------------*/
uint32_t g_dwMainTickCnt;
uint32_t g_dwInitError_Pos;

void (*gFp_Uart_Rx_Callback[PORT_NUM_USART_MAX])(uint32_t dwCOM_Port);
void (*gFp_Uart_Tx_Callback[PORT_NUM_USART_MAX])(uint32_t dwCOM_Port);

/* Private function prototypes -----------------------------------------------*/

//Macro Function


/* Interrupt  ----------------------------------------------------------------*/
/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  
  switch( (uint32_t)(huart->Instance))
  {
  case (uint32_t)USART1:
    
    if( gFp_Uart_Rx_Callback[PORT_NUM_USART1] != NULL)
    {
      (gFp_Uart_Rx_Callback[PORT_NUM_USART1])(PORT_NUM_USART1);
    }
    
    break;

  case (uint32_t)USART2:
    
    if( gFp_Uart_Rx_Callback[PORT_NUM_USART2] != NULL)
    {
      (gFp_Uart_Rx_Callback[PORT_NUM_USART2])(PORT_NUM_USART2);
    }
    
    break;

  case (uint32_t)USART3:
    
    if( gFp_Uart_Rx_Callback[PORT_NUM_USART3] != NULL)
    {
      (gFp_Uart_Rx_Callback[PORT_NUM_USART3])(PORT_NUM_USART3);
    }
    
    break;
    
  default:
    
    HW_LowCode_Error(SET);
    
    break;
  }
  
}


/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  
  switch( (uint32_t)(huart->Instance))
  {
  case (uint32_t)USART1:
    
    if(gFp_Uart_Tx_Callback[PORT_NUM_USART1] != NULL)
    {
      (gFp_Uart_Tx_Callback[PORT_NUM_USART1])(PORT_NUM_USART1);
    }
    
    break;

  case (uint32_t)USART2:
    
    if(gFp_Uart_Tx_Callback[PORT_NUM_USART2] != NULL)
    {
      (gFp_Uart_Tx_Callback[PORT_NUM_USART2])(PORT_NUM_USART2);
    }
    
    break;

  case (uint32_t)USART3:
    
    if(gFp_Uart_Tx_Callback[PORT_NUM_USART3] != NULL)
    {
      (gFp_Uart_Tx_Callback[PORT_NUM_USART3])(PORT_NUM_USART3);
    }
    
    break;
    
  default:
    
    HW_LowCode_Error(SET);
    
    break;
  }  
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None

  */



/*Function -------------------------------------------------------------------*/


//------------------------------------------------------------------------------
//HAL Delay 
/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void HAL_IncTick(void)
{
  g_dwMainTickCnt += uwTickFreq;
}

/**
  * @brief  This 
  * @param  file:  0(USART1) ~ 4 (USART5)
  * @param  line: 
  * @retval None
  */
void HAL_Delay(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)(uwTickFreq);
  }

  while ((HAL_GetTick() - tickstart) < wait)
  {
  }
  
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
uint32_t HAL_GetTick(void)
{
  return g_dwMainTickCnt;
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None Status LED Sink   
*/
int32_t hsHW_Config(void)
{
  int32_t dwCheck = 0;
  
  //Rework Peripheral Config
  
  //USART
  dwCheck = Rework_PP_Drv_Config(&huart1, RWRK_USART1_PP);
  if(dwCheck) return dwCheck;
  dwCheck = Rework_PP_Drv_Config(&huart2, RWRK_USART2_PP);
  if(dwCheck) return dwCheck;
  dwCheck = Rework_PP_Drv_Config(&huart3, RWRK_USART3_PP);
  if(dwCheck) return dwCheck;
  
  //I2C
  dwCheck = Rework_PP_Drv_Config(&hi2c1, RWRK_I2C1_PP);
  if(dwCheck) return dwCheck;
  dwCheck = Rework_PP_Drv_Config(&hi2c2, RWRK_I2C2_PP);
  if(dwCheck) return dwCheck;
  
  //SPI
  dwCheck = Rework_PP_Drv_Config(&hspi1, RWRK_SPI1_PP);
  if(dwCheck) return dwCheck;
  
  // Other Device Config
  hsGlobalErrorUseConfig( (uint32_t)HW_ERR_LED_ONOFF);

  HW_STA_LED_ONOFF(MCU_STA_LED_CH_1, OFF);
  HW_STA_LED_ONOFF(MCU_STA_LED_CH_2, OFF);
  HW_STA_LED_ONOFF(MCU_STA_LED_CH_2, OFF);
  HW_ERR_LED_ONOFF(OFF);
  
  return dwCheck;
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */



/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */



/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */



//==============================================================================
// UTILL

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
uint32_t BSP_hsSysTickTimer(uint32_t *p_TickTimer, uint32_t dwWaitTickTime)
{
  uint32_t dwGetNowTick;
  
  dwGetNowTick = HAL_GetTick();
  
  if(*p_TickTimer == 0)
  {
    *p_TickTimer = dwGetNowTick;
  }
  else
  {
    if( (dwGetNowTick - *p_TickTimer) >= dwWaitTickTime) 
    {
      *p_TickTimer = 0; 
      
      return RESET;
    }
  }
  
  return SET;
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */

//-----------------------------------------------------------------------------
/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void HW_ERR_LED_ONOFF(uint32_t dwON_nOFF)
{
  if(dwON_nOFF) STA_ERR_LED_GPIO_Port->BSRR = STA_ERR_LED_Pin;
  else STA_ERR_LED_GPIO_Port->BRR = STA_ERR_LED_Pin;
}


/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void HW_STA_LED_ONOFF(uint32_t dwLED_Channel, uint32_t dwON_nOFF)
{
  switch(dwLED_Channel)
  {
  case MCU_STA_LED_CH_1:
    if(dwON_nOFF) STA_LED1_GPIO_Port->BSRR = STA_LED1_Pin;
    else STA_LED1_GPIO_Port->BRR = STA_LED1_Pin;
    break;
  case MCU_STA_LED_CH_2:
    if(dwON_nOFF) STA_LED2_GPIO_Port->BSRR = STA_LED2_Pin;
    else STA_LED2_GPIO_Port->BRR = STA_LED2_Pin;
    break;
  case MCU_STA_LED_CH_3:
    if(dwON_nOFF) STA_LED3_GPIO_Port->BSRR = STA_LED3_Pin;
    else STA_LED3_GPIO_Port->BRR = STA_LED3_Pin;    
    break;
  default:
    break;
  }
}


/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void HW_LowCode_Error(uint32_t dwErrData)
{
  
  HW_STA_LED_ONOFF(MCU_STA_LED_CH_1, OFF);
  HW_STA_LED_ONOFF(MCU_STA_LED_CH_2, OFF);
  HW_STA_LED_ONOFF(MCU_STA_LED_CH_2, OFF);
  
  while(dwErrData)
  {
    HW_ERR_LED_ONOFF(ON);
    HAL_Delay(500);
    HW_ERR_LED_ONOFF(OFF);
    HAL_Delay(500);
  }
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
