
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
#include "hsDrv_MCP4231T_502.h"
#include "port_MCP4231T.h"

//define 
#define hsMCP4231_ACCESS_TIMEOUT        500
#define hsMCP4231_BUSY_WAIT_TIM         100


//Address
#define hsMCP4231_ADD_VW0               0
#define hsMCP4231_ADD_VW1               1
//#define hsMCP4231_ADD_RE1               2
//#define hsMCP4231_ADD_RE2               3
#define hsMCP4231_ADD_TCON              4
#define hsMCP4231_ADD_STA               5


//CMD
#define hsMCP4231_CMD_WR                0
#define hsMCP4231_CMD_INCR              1
#define hsMCP4231_CMD_DECR              2
#define hsMCP4231_CMD_RD                3

//R Volume
#define hsMCP4231_R_VOL                 5000 // 502 = 5K                  
#define hsMCP4231_GRADE                 128 


//Data Type

/* Extern --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

//Macro Function

/*Function -------------------------------------------------------------------*/
/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
int32_t hsMCP4231T_Drv_Config(hsMCP4231_Drv_t *p_tDrv, uint32_t dwRework_ID, uint32_t dwDev_Num)
{
  int32_t dwCheck = 0;
  
  p_tDrv->p_tRework_PP_Drv = Read_Rework_PP_Drv(dwRework_ID);
  p_tDrv->dwDEV_Num = dwDev_Num;
  
  dwCheck = portMCP4231_SPI_Config(p_tDrv->p_tRework_PP_Drv->p_PP_Drv);
  
  return dwCheck;
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */

//------------------------------------------------------------------------------
/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
#define hsMCP4231_R_VOL                 5000 // 502 = 5K                  
#define hsMCP4231_GRADE                 128 
portMCP4231_SPI_WriteRead(void *p_HAL, uint8_t *p_uSend, uint8_t *p_uReceive, uint16_t dwSize)

  */
int32_t hsMCP4231T_Wrie_Volum(hsMCP4231_Drv_t *p_tDrv, uint32_t dwChannel, uint32_t dwVolum)
{
  int32_t dwCheck = 0;
  uint8_t uSend[2] = {0}, uRecive[2] = {0};
  uint32_t dwCAL;
  void *p_HAL;
  
  if( (dwChannel > 1) || (dwVolum >= hsMCP4231_R_VOL) ) return DAT_ERR_PARAM_DATA;
  
  dwCheck = Lock_Rework_PP_Drv(p_tDrv->p_tRework_PP_Drv, hsMCP4231_ACCESS_TIMEOUT);
  if(dwCheck) return dwCheck;
  
  p_HAL = p_tDrv->p_tRework_PP_Drv->p_PP_Drv;
  
  p_tDrv->tMCP4231_REG[dwChannel].ADDRESS = dwChannel;
  p_tDrv->tMCP4231_REG[dwChannel].CTRL    = hsMCP4231_CMD_WR;
  
  dwCAL = ((hsMCP4231_R_VOL - dwVolum) * hsMCP4231_GRADE)/hsMCP4231_R_VOL;
  if(dwCAL < 128 ) dwCAL =  dwCAL + 1;
  p_tDrv->tMCP4231_REG[dwChannel].DATA_1 = dwCAL;
  p_tDrv->tMCP4231_REG[dwChannel].DATA_2 = 0;
  
  uSend[0] = (p_tDrv->tMCP4231_REG[dwChannel].REG_16BIT) >> 8;
  uSend[1] = p_tDrv->tMCP4231_REG[dwChannel].REG_16BIT;
  
  dwCheck = portMCP4231_SPI_WriteRead(p_HAL, uSend, uRecive, 2); // 2 byte
  
  Unlock_Rework_PP_Drv(p_tDrv->p_tRework_PP_Drv);
  
  return dwCheck;
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
int32_t hsMCP4231T_Read_Volum(hsMCP4231_Drv_t *p_tDrv, uint32_t dwChannel, uint32_t *p_dwVolum)
{
  int32_t dwCheck = 0;
  uint8_t uSend[2] = {0}, uRecive[2] = {0};
  uint32_t dwCAL;
  void *p_HAL;

  if(dwChannel > 1) return DAT_ERR_PARAM_DATA;
  
  dwCheck = Lock_Rework_PP_Drv(p_tDrv->p_tRework_PP_Drv, hsMCP4231_ACCESS_TIMEOUT);
  if(dwCheck) return dwCheck;
  
  p_HAL = p_tDrv->p_tRework_PP_Drv->p_PP_Drv;
  
  p_tDrv->tMCP4231_REG[dwChannel].ADDRESS = dwChannel;
  p_tDrv->tMCP4231_REG[dwChannel].CTRL    = hsMCP4231_CMD_RD;
  
  p_tDrv->tMCP4231_REG[dwChannel].DATA_1 = 0;
  p_tDrv->tMCP4231_REG[dwChannel].DATA_2 = 0;
  
  uSend[0] = (p_tDrv->tMCP4231_REG[dwChannel].REG_16BIT) >> 8;
  uSend[1] = p_tDrv->tMCP4231_REG[dwChannel].REG_16BIT;
  
  dwCheck = portMCP4231_SPI_WriteRead(p_HAL, uSend, uRecive, 2); // 2 byte
  
  if(dwCheck == 0)
  {
    p_tDrv->tMCP4231_REG[dwChannel].REG_16BIT = (uRecive[0] << 8) | (uRecive[1]);
    
    dwCAL = hsMCP4231_R_VOL - ( (p_tDrv->tMCP4231_REG[dwChannel].DATA_1 * hsMCP4231_R_VOL)/hsMCP4231_GRADE);
    
    *p_dwVolum = dwCAL;
  }
  
  Unlock_Rework_PP_Drv(p_tDrv->p_tRework_PP_Drv);
  
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


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
