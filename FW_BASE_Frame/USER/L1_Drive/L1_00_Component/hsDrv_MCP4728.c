
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
#include "hsDrv_MCP4728.h"
#include "port_hsDrv_MCP4728.h"

//define 
#define hsMCP4728_ACCESS_TIMEOUT        500
#define hsMCP4728_BUSY_WAIT_TIM         100

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
int32_t hsMCP4728_Drv_SingleWrite_Config(hsDrv_MCP4728_t *p_Drv, uint32_t dwRework_ID, uint32_t dwPort_Num, uint8_t uDevAddress)
{
  int32_t dwCheck = 0;
  
  p_Drv->p_tRework_PP_Drv = Read_Rework_PP_Drv(dwRework_ID);
  p_Drv->dwPort_Num = dwPort_Num;
  
  //Single Write Setting
  p_Drv->tMCP4728_REG.Bit3_C = hsMCP4728_C;
  p_Drv->tMCP4728_REG.Bit2_W = hsMCP4728_W;
  
  //Address
  p_Drv->tMCP4728_REG.Bit_DevAdd = hsMCP4728_BASE_ADD | (uDevAddress << 1);
  
  //UDAN
  p_Drv->tMCP4728_REG.Bit1_nUDAC = hsMCP4728_nU;
    
  return dwCheck;
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
int32_t hsMCP4728_Drv_SingleWrite(hsDrv_MCP4728_t *p_Drv, uint32_t dwChannel, uint32_t dwVref, uint32_t dwPD_MD, uint32_t dwGain, uint32_t dwDAT_12Bit)
{
  int32_t dwCheck = 0;
  uint8_t uWriteDataMem[4];
  
  void *p_vHALDrv;
  
  p_vHALDrv = p_Drv->p_tRework_PP_Drv->p_PP_Drv;
  
  
  dwCheck = Lock_Rework_PP_Drv(p_Drv->p_tRework_PP_Drv, hsMCP4728_ACCESS_TIMEOUT);
  if(dwCheck) return dwCheck;
  
  p_Drv->tMCP4728_REG.Bit2_Channel      = dwChannel;
  p_Drv->tMCP4728_REG.Bit1_Vref         = dwVref;
  p_Drv->tMCP4728_REG.Bit2_PowerDown    = dwPD_MD;
  p_Drv->tMCP4728_REG.Bit1_Gain         = dwGain;
  p_Drv->tMCP4728_REG.Bit12_DacDat      = dwDAT_12Bit;
  
  uWriteDataMem[0] = (p_Drv->tMCP4728_REG.dwREG_DAT) >> 24;
  uWriteDataMem[1] = (p_Drv->tMCP4728_REG.dwREG_DAT) >> 16;
  uWriteDataMem[2] = (p_Drv->tMCP4728_REG.dwREG_DAT) >>  8;
  uWriteDataMem[3] = (p_Drv->tMCP4728_REG.dwREG_DAT);
  
  dwCheck = port_MCP4728_I2C_Write(p_vHALDrv, uWriteDataMem);
  
  Unlock_Rework_PP_Drv(p_Drv->p_tRework_PP_Drv);
  
  return dwCheck;
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
int32_t hsMCP4728_BusyWait(hsDrv_MCP4728_t *p_Drv)
{
  int32_t dwCheck = 0;
  
  vTaskDelay(hsMCP4728_BUSY_WAIT_TIM);
  
  return dwCheck;
}

#if 0
int32_t hsMCP4728_BusyWait(hsDrv_MCP4728_t *p_Drv)
{
  int32_t dwCheck = 0;
  uint32_t dwReady_nBusyCheck = 0;
  
  dwCheck = port_MCP4728_nBusyCheck(p_Drv->dwPort_Num, &dwReady_nBusyCheck);
  if(dwCheck) return dwCheck;
  
  if(dwReady_nBusyCheck) return dwCheck;
  
  vTaskDelay(hsMCP4728_BUSY_WAIT_TIM);
  
  dwCheck = port_MCP4728_nBusyCheck(p_Drv->dwPort_Num, &dwReady_nBusyCheck);
  if(dwCheck) return dwCheck;
  
  if(dwReady_nBusyCheck) return dwCheck;
  
  dwCheck = DEV_HNDL_FAIL;
  
  return dwCheck;
}
#endif

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
