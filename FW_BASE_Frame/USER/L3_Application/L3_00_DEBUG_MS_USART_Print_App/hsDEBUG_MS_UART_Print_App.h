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
#ifndef __hsDEBUG_UART_HNDL_H
#define __hsDEBUG_UART_HNDL_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/
#define hsDEBUG_CONF_RX         0x01
#define hsDEBUG_CONF_TX         0x02
#define hsDEBUG_CONF_BOTH       0x03


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
int32_t hsDEBUG_MS_UART_Print_App_Config(uint8_t uMode);

int32_t hsDEBUG_UART_TX_Char(char uDat);
int32_t hsDEBUG_UART_TX_String(char *p_uStringData);

int32_t hsDEBUG_UART_RX_QueGet(uint8_t *p_GetMem, uint32_t dwWaitTime);

#endif /* __hsDEBUG_UART_HNDL_H */

/* Includes ------------------------------------------------------------------*/
