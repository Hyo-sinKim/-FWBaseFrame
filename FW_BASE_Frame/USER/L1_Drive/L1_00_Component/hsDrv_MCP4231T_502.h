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
#ifndef __HS_DRV_MCP4231T_H__
#define __HS_DRV_MCP4231T_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

//PUBLIC define

//Data Type
typedef union
{
  struct
  {
    __IO uint16_t       DATA_1  :8; //Low
    __IO uint16_t       DATA_2  :2;
    __IO uint16_t       CTRL    :2;
    __IO uint16_t       ADDRESS :4; //HIgh
  };
  __IO uint16_t REG_16BIT;
}__MCP4231_REG_Type;

typedef struct
{
  Rework_PP_Drv_t *p_tRework_PP_Drv;
  uint32_t dwDEV_Num;
  
  __MCP4231_REG_Type tMCP4231_REG[2];
}hsMCP4231_Drv_t;


//Function ----------------------------------------------------
int32_t hsMCP4231T_Drv_Config(hsMCP4231_Drv_t *p_tDrv, uint32_t dwRework_ID, uint32_t dwDev_Num);

int32_t hsMCP4231T_Wrie_Volum(hsMCP4231_Drv_t *p_tDrv, uint32_t dwChannel, uint32_t dwVolum);
int32_t hsMCP4231T_Read_Volum(hsMCP4231_Drv_t *p_tDrv, uint32_t dwChannel, uint32_t *p_dwVolum);

#endif /* __HS_DRV_MCP4231T_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
