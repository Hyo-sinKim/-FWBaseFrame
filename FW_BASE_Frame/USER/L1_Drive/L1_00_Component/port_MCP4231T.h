/**
  ******************************************************************************
  * @file     
  * @author  
  * @version 
  * @date    
  * @brief   
  ******************************************************************************
  * @attention
  *
  *
  *
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HS_PORT_MCP4231T_H
#define __HS_PORT_MCP4231T_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"



/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int32_t portMCP4231_SPI_Config(void *p_HAL);

int32_t portMCP4231_nCS(uint32_t dwDev_Num, uint32_t dwStat_nCS);

int32_t portMCP4231_SPI_WriteRead(void *p_HAL, uint8_t *p_uSend, uint8_t *p_uReceive, uint16_t dwSize);

#endif /* __HS_PORT_MCP4231T_H */

/* Includes ------------------------------------------------------------------*/
