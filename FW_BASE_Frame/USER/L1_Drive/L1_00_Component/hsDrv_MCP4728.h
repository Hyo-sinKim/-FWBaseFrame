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
#ifndef __HS_DRV_MCP4728_H__
#define __HS_DRV_MCP4728_H__

/* Includes ------------------------------------------------------------------*/
#include "main.h"

//PUBLIC define
#define hsMCP4728_BASE_ADD              0xC0    // 1100 A2A1A0 R/nW
#define hsMCP4728_C                     2
#define hsMCP4728_W                     3
#define hsMCP4728_nU                    0

enum hsMCP4728_CH
{
  hsMCP4728_CH1 = 0,
  hsMCP4728_CH2,
  hsMCP4728_CH3,
  hsMCP4728_CH4
};

enum hsMCP4728_PD
{
  hsMCP4728_N = 0,
  hsMCP4728_1K,
  hsMCP4728_100K,
  hsMCP4728_500K,
};

enum hsMCP4728_VREF
{
  hsMCP4728_VDD = 0,
  hsMCP4728_2048,
};

enum hsMCP4728_GAIN
{
  hsMCP4728_G1 = 0,
  hsMCP4728_G2,
};


//Data Type
typedef union
{
  struct
  {
    uint32_t Bit12_DacDat:          12; //Low 
    uint32_t Bit1_Gain:              1;
    uint32_t Bit2_PowerDown:         2;
    uint32_t Bit1_Vref:              1;
    uint32_t Bit1_nUDAC:             1;
    uint32_t Bit2_Channel:           2;
    uint32_t Bit2_W:                 2;
    uint32_t Bit3_C:                 3;
    uint32_t Bit_DevAdd:             8; //High
  };
  
  uint32_t dwREG_DAT;
  
}__MCP4728_REG_Type;

typedef struct
{
  Rework_PP_Drv_t *p_tRework_PP_Drv;
  uint32_t dwPort_Num;
  
  __MCP4728_REG_Type tMCP4728_REG;
  
}hsDrv_MCP4728_t;


//Function ----------------------------------------------------

int32_t hsMCP4728_Drv_SingleWrite_Config(hsDrv_MCP4728_t *p_Drv, uint32_t dwRework_ID, uint32_t dwPort_Num, uint8_t uDevAddress);
int32_t hsMCP4728_Drv_SingleWrite(hsDrv_MCP4728_t *p_Drv, uint32_t dwChannel, uint32_t dwVref, uint32_t dwPD_MD, uint32_t dwGain, uint32_t dwDAT_12Bit);
int32_t hsMCP4728_BusyWait(hsDrv_MCP4728_t *p_Drv);


#endif /* __HS_DRV_MCP4728_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
