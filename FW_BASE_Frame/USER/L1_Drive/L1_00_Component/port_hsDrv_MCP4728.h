/**
  ******************************************************************************
  * @file    main.h 
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
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HS_PORT_MCP4728_H
#define __HS_PORT_MCP4728_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"



/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

int32_t port_MCP4728_I2C_Write(void *p_HALDrv, uint8_t *p_uWriteDataMem);

int32_t port_MCP4728_nBusyCheck(uint32_t dwPort_Num, uint32_t *p_dw_n_BusyCheck);


#endif /* __HS_PORT_MCP4728_H */

/* Includes ------------------------------------------------------------------*/
