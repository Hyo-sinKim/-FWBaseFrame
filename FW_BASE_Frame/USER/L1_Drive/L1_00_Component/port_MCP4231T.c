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
#include "port_MCP4231T.h"

//HW Config

//CONST Define

//Public 

//Extern variable
extern SPI_HandleTypeDef hspi1;

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
int32_t portMCP4231_SPI_Config(void *p_HAL)
{
  int32_t dwCheck = 0;
  SPI_HandleTypeDef *p_HAL_SPI = p_HAL;
  
  //------------------------------------------
  //  SPI1 Config
  //------------------------------------------
    
  p_HAL_SPI->Instance = SPI1;
  p_HAL_SPI->Init.Mode = SPI_MODE_MASTER;
  p_HAL_SPI->Init.Direction = SPI_DIRECTION_2LINES;
  p_HAL_SPI->Init.DataSize = SPI_DATASIZE_8BIT;
  p_HAL_SPI->Init.CLKPolarity = SPI_POLARITY_LOW;
  p_HAL_SPI->Init.CLKPhase = SPI_PHASE_1EDGE;
  p_HAL_SPI->Init.NSS = SPI_NSS_SOFT;
  p_HAL_SPI->Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  p_HAL_SPI->Init.FirstBit = SPI_FIRSTBIT_MSB;
  p_HAL_SPI->Init.TIMode = SPI_TIMODE_DISABLE;
  p_HAL_SPI->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  p_HAL_SPI->Init.CRCPolynomial = 7;
  p_HAL_SPI->Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  p_HAL_SPI->Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  
  dwCheck = HAL_SPI_Init(p_HAL_SPI);
  
  return dwCheck;
}


/**
  * @brief  
  * @param  None
  * @retval None
  */
int32_t portMCP4231_nCS(uint32_t dwDev_Num, uint32_t dwStat_nCS)
{
  int32_t dwCheck = 0;
  
  switch(dwDev_Num)
  {
  case 0:
  
    if(dwStat_nCS) //Status SET --> no chip select
    {
      SPI_nCS_GPIO_Port->BSRR = (uint32_t)SPI_nCS_Pin;
    }
    else // Status RESET  --> Chip select
    {
      SPI_nCS_GPIO_Port->BRR = (uint32_t)SPI_nCS_Pin;
    }
    
    break;
  default:
    
    dwCheck = DAT_ERR_PARAM_DATA;
      
    break;
  }
  
  return dwCheck;
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
int32_t portMCP4231_SPI_WriteRead(void *p_HAL, uint8_t *p_uSend, uint8_t *p_uReceive, uint16_t dwSize)
{
  int32_t dwCheck = 0;
  
  dwCheck = HAL_SPI_TransmitReceive(p_HAL, p_uSend, p_uReceive, dwSize, 500);
  
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

