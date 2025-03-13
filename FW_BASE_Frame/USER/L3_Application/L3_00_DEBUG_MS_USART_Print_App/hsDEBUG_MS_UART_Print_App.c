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

/* Includes ------------------------------------------------------------------*/
#include "hsDEBUG_MS_UART_Print_App.h"

//HW Config
#include "port_hsDEBUG_MS_UART_Print_App.h"

//Public 
//Extern variable

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

//OS
#define hsDEBUG_UART_TX_TSK_MEM         256
#define hsDEBUG_UART_TX_TSK_PRIO        (tskIDLE_PRIORITY + 1)     // 6 5 4 3 2 |1| 0
#define hsDEBUG_UART_TX_TSK_MAX_PRIO    (configMAX_PRIORITIES - 1) // |6| 5 4 3 2 1 0

#define hsDEBUG_UART_RX_QUE_SZ          128
#define hsDEBUG_UART_TX_QUE_SZ          512

/* Private macro -------------------------------------------------------------*/
#define hsDEBUG_ERROR_HANDLE            hsGlobalErrorBlocking_2nd
#define hsDEBUG_LOW_LEVEL_ERR_HANDLE    HW_LowCode_Error

/* Private variables ---------------------------------------------------------*/
//OS
SemaphoreHandle_t g_xSemaDEBUG_UART_TX_CMPLT_Signal;
QueueHandle_t g_xQue_DEBUG_UART_RX_DAT_Handle;
QueueHandle_t g_xQue_DEBUG_UART_TX_DAT_Handle;

TaskHandle_t g_xDEBUG_UART_TX_Task_Handle;

//Normal
uint8_t g_uDEBUG_RD_RX_DAT;

Rework_PP_Drv_t *p_tDEBUG_UART_PP_DRV;
/* Private function prototypes -----------------------------------------------*/
void hsDEBUG_UART_TX_Task(void * p_vParam);

/* Private functions ---------------------------------------------------------*/

//------------------------------------------------------------------------------
//IRQ Callback Function 
/**
  * @brief  
  * @param  None
  * @retval None
  */
void hsDEBUG_UART_IRQ_TX_DMA_Callback(uint32_t dwPortNum)
{
  BaseType_t xHigherPriorityTaskWoken;
  xHigherPriorityTaskWoken = pdFALSE;
  
  xSemaphoreGiveFromISR(g_xSemaDEBUG_UART_TX_CMPLT_Signal, &xHigherPriorityTaskWoken);
  
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
void hsDEBUG_UART_IRQ_RX_Callback(uint32_t dwPortNum)
{
  BaseType_t xToken;
  BaseType_t xHigherPriorityTaskWoken;
  int32_t dwCheck = 0;
  
  xHigherPriorityTaskWoken = pdFALSE;
  
  xToken = xQueueSendFromISR(g_xQue_DEBUG_UART_RX_DAT_Handle, &g_uDEBUG_RD_RX_DAT, &xHigherPriorityTaskWoken);
  if(xToken == pdFALSE)
  {
    xQueueReset(g_xQue_DEBUG_UART_RX_DAT_Handle);
  }
  
  if(p_tDEBUG_UART_PP_DRV != NULL)
  {
    dwCheck = port_hsDEBUG_UART_RX_Run(p_tDEBUG_UART_PP_DRV->p_PP_Drv, &g_uDEBUG_RD_RX_DAT, 1);
    if(dwCheck) hsDEBUG_LOW_LEVEL_ERR_HANDLE(dwCheck);
  }
}

//------------------------------------------------------------------------------
//DEBUG UART Config
/**
  * @brief  
  * @param  None
  * @retval None
  */
int32_t hsDEBUG_MS_UART_Print_App_Config(uint8_t uMode)
{
  int32_t dwCheck = 0;
  
  p_tDEBUG_UART_PP_DRV = Read_Rework_PP_Drv(RWRK_USART1_PP);
  
  port_hsDEBUS_UART_IRQ_Linker( (uint32_t)hsDEBUG_UART_IRQ_RX_Callback, (uint32_t)hsDEBUG_UART_IRQ_TX_DMA_Callback,  PORT_NUM_USART1);
  
  if(uMode & hsDEBUG_CONF_RX)
  {
    g_xQue_DEBUG_UART_RX_DAT_Handle = xQueueCreate(hsDEBUG_UART_RX_QUE_SZ, sizeof(uint8_t));
    dwCheck = port_hsDEBUG_UART_RX_Run(p_tDEBUG_UART_PP_DRV->p_PP_Drv, &g_uDEBUG_RD_RX_DAT, 1);
    if(dwCheck) return dwCheck;
  }
  
  if(uMode & hsDEBUG_CONF_TX)
  {
    g_xQue_DEBUG_UART_TX_DAT_Handle = xQueueCreate(hsDEBUG_UART_TX_QUE_SZ, sizeof(uint8_t));
    g_xSemaDEBUG_UART_TX_CMPLT_Signal = xSemaphoreCreateBinary();
    xTaskCreate(hsDEBUG_UART_TX_Task, "DEBUG_TX", hsDEBUG_UART_TX_TSK_MEM, (void *)p_tDEBUG_UART_PP_DRV, hsDEBUG_UART_TX_TSK_PRIO, &g_xDEBUG_UART_TX_Task_Handle);
  }
  
  
  hsDebug_MSG_Config( (void *)hsDEBUG_UART_TX_String);
  
  return dwCheck;
}


//------------------------------------------------------------------------------
//TX API Handle
#define hsDEBUG_UART_TX_OUT_BUF_SZ      128  
#define hsDEBUG_UART_TX_OUT_END_TIMOUT  250

uint8_t g_DEBUG_UART_TX_OUT_Mem[hsDEBUG_UART_TX_OUT_BUF_SZ];

/**
  * @brief  
  * @param  None
  * @retval None
  */
void hsDEBUG_UART_TX_Task(void * p_vParam)
{
  BaseType_t xToken;
  UBaseType_t xCnt;
  Rework_PP_Drv_t *p_tPP_Drv;
  uint32_t dwCnt, dwWaitTime;
  int32_t dwCheck = 0;
  
  p_tPP_Drv = p_vParam;
  
  for(;;)
  {
DEBUG_UART_TX_TSK_START:
  
    dwWaitTime = portMAX_DELAY;
    
    for(dwCnt = 0; dwCnt < hsDEBUG_UART_TX_OUT_BUF_SZ; dwCnt++) g_DEBUG_UART_TX_OUT_Mem[dwCnt] = 0; //Buff Reset
    
    for(dwCnt = 0; dwCnt < hsDEBUG_UART_TX_OUT_BUF_SZ; dwCnt++)
    {
      xToken = xQueueReceive(g_xQue_DEBUG_UART_TX_DAT_Handle, &g_DEBUG_UART_TX_OUT_Mem[dwCnt], dwWaitTime);
      if(xToken == pdFALSE) break;
      
      dwWaitTime = 1;
    }
    
    if(dwCnt > 0)
    {
      xCnt = uxSemaphoreGetCount(g_xSemaDEBUG_UART_TX_CMPLT_Signal);
      if(xCnt > 0) xSemaphoreTake(g_xSemaDEBUG_UART_TX_CMPLT_Signal, 5);
      
      dwCheck = port_hsDEBUS_UART_TX_Run(p_tPP_Drv->p_PP_Drv, g_DEBUG_UART_TX_OUT_Mem, dwCnt);
      if(dwCheck)
      {
        //Error Code
        hsDEBUG_ERROR_HANDLE(dwCheck);
        goto DEBUG_UART_TX_TSK_START;
      }
      
      xToken = xSemaphoreTake(g_xSemaDEBUG_UART_TX_CMPLT_Signal, hsDEBUG_UART_TX_OUT_END_TIMOUT);
      if(xToken ==  pdFALSE)
      {
        dwCheck = OS_SIG_TIMOUT;
        hsDEBUG_ERROR_HANDLE(dwCheck);
        goto DEBUG_UART_TX_TSK_START;
      }
    }
  }
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
int32_t hsDEBUG_UART_TX_Char(char uDat)
{
  BaseType_t xToken;
  UBaseType_t xCnt;
  int32_t dwCheck = 0;
  
  xCnt = uxQueueSpacesAvailable(g_xQue_DEBUG_UART_TX_DAT_Handle);
  if(xCnt < 2)
  {
    vTaskPrioritySet(g_xDEBUG_UART_TX_Task_Handle, hsDEBUG_UART_TX_TSK_MAX_PRIO);
    vTaskDelay(10);
    vTaskPrioritySet(g_xDEBUG_UART_TX_Task_Handle, hsDEBUG_UART_TX_TSK_PRIO);
  }
  
  if(uDat == '\n')
  {
    uDat = '\r';
    xToken = xQueueSend(g_xQue_DEBUG_UART_TX_DAT_Handle, &uDat, 1);
    if(xToken == pdTRUE)
    {
      uDat = '\n';
      xToken = xQueueSend(g_xQue_DEBUG_UART_TX_DAT_Handle, &uDat, 1);
    }
  }
  else
  {
    xToken = xQueueSend(g_xQue_DEBUG_UART_TX_DAT_Handle, &uDat, 1);
  }
  
  if(xToken == pdFALSE)
  {
    dwCheck = OS_QUE_PUT_FAIL;
  }
  
  return dwCheck;
}


/**
  * @brief  
  * @param  None
  * @retval None
  */
int32_t hsDEBUG_UART_TX_String(char *p_uStringData)
{
  int32_t dwCheck = 0;
  
  while(*p_uStringData)
  {
    dwCheck = hsDEBUG_UART_TX_Char(*p_uStringData++);
    if(dwCheck)
    {
      hsDEBUG_ERROR_HANDLE(dwCheck);
      break;
    }
  }
  
  return dwCheck;
}


/**
  * @brief  
  * @param  None
  * @retval None
  */

//------------------------------------------------------------------------------
// RX API Handle
/**
  * @brief  
  * @param  None
  * @retval None
  */
int32_t hsDEBUG_UART_RX_QueGet(uint8_t *p_GetMem, uint32_t dwWaitTime)
{
  BaseType_t xToken;
  int32_t dwCheck = 0;
  
  xToken = xQueueReceive(g_xQue_DEBUG_UART_RX_DAT_Handle, p_GetMem, dwWaitTime);
  if(xToken == pdFALSE) dwCheck = OS_QUE_GET_FAIL;
  
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

