
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
#include "User_Main.h"

//HW
#include "hsCLI_App.h"
#include "hsDEBUG_MS_UART_Print_App.h"

//-----------------------------------------------------------------------------
//define 

//OS Config
#define hsUSER_MAIN_TSK_MEM                           128 // 512 Byte
#define hsUSER_MAIN_TSK_PRIO                          (tskIDLE_PRIORITY + 0) // 6 5 4 3 2 1 |0|

//Other

//Typedef
/* Extern --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
TaskHandle_t            g_xUserMain_Task_Handle;
void                    *gp_UserMain_Param;

/* Private function prototypes -----------------------------------------------*/
void hsUserMain_Task(void *pvParam);

/* Interrupt  ----------------------------------------------------------------*/

/*Function -------------------------------------------------------------------*/

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void hsMain_User_Config(void)
{
  int32_t dwCheck = 0;
  
  dwCheck = hsHW_Config();
  if(dwCheck) HW_LowCode_Error(dwCheck);
  
  dwCheck = hsDEBUG_MS_UART_Print_App_Config(hsDEBUG_CONF_BOTH);
  if(dwCheck) HW_LowCode_Error(dwCheck);
  
  dwCheck = hsCLI_App_Config();
  if(dwCheck) HW_LowCode_Error(dwCheck);
  
  xTaskCreate(hsUserMain_Task, "MAIN", hsUSER_MAIN_TSK_MEM, gp_UserMain_Param,
              hsUSER_MAIN_TSK_PRIO, &g_xUserMain_Task_Handle);
  
  
}

//-----------------------------------------------------------------------------
/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None pdTRUE 
  */

void hsUserMain_Task(void *pvParam)
{
  int32_t dwCheck;
  
  vTaskDelay(500);
  
  for(;;)
  {
    HW_STA_LED_ONOFF(MCU_STA_LED_CH_1, OFF);
    vTaskDelay(500);
    HW_STA_LED_ONOFF(MCU_STA_LED_CH_1, ON);
    vTaskDelay(500);
    
    hsGlobalErrorReadAllHandle((uint32_t *)&dwCheck);
    
    while(dwCheck)
    {
      vTaskDelay(500);
    }
  }
}
//-----------------------------------------------------------------------------

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

//----------------------------------------------------------------------------
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
