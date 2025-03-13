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
#include "port_hsDEBUG_MS_UART_Print_App.h"

//HW Config

//Public 
//Extern variable
extern void (*gFp_Uart_Rx_Callback[])(uint32_t);
extern void (*gFp_Uart_Tx_Callback[])(uint32_t);


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define hsDEBUG_USART_RX_DMA_USE     0
#define hsDEBUG_USART_TX_DMA_USE     1

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  
  * @param  None
  * @retval None
  */
int32_t port_hsDEBUG_UART_IF_Config(uint32_t dwEN_nDIS)
{
  int32_t dwCheck = 0;
  
  if(dwEN_nDIS) //Enable 
  {
    
  }
  else         //Disable
  {
    
  } 
  return dwCheck;
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
void port_hsDEBUS_UART_IRQ_Linker(uint32_t dwFP_Rx, uint32_t dwFP_Tx, uint32_t dwPort_Num)
{
  gFp_Uart_Rx_Callback[dwPort_Num] = (void(*)(uint32_t))dwFP_Rx;
  gFp_Uart_Tx_Callback[dwPort_Num] = (void(*)(uint32_t))dwFP_Tx;
}

/**
  * @brief  
  * @param  None
  * @retval None
  */
int32_t port_hsDEBUG_UART_RX_Run(void *p_PP_DRV, uint8_t *p_uGetDataMem, uint32_t dwGetDataSize)
{
  int32_t dwCheck = 0;
  
#if  hsDEBUG_USART_RX_DMA_USE
  dwCheck = HAL_UART_Receive_DMA(p_PP_DRV, p_uGetDataMem, dwGetDataSize);
#else
  dwCheck = HAL_UART_Receive_IT(p_PP_DRV, p_uGetDataMem, dwGetDataSize);
#endif  
  return dwCheck;
}
/**
  * @brief  
  * @param  None
  * @retval None
  */
int32_t port_hsDEBUS_UART_TX_Run(void *p_PP_DRV, uint8_t *p_uPutDataMem, uint32_t dwPutDataSize)
{
  int32_t dwCheck = 0;
  
#if hsDEBUG_USART_TX_DMA_USE
  dwCheck = HAL_UART_Transmit_DMA(p_PP_DRV, p_uPutDataMem, dwPutDataSize);
#else
  dwCheck = HAL_UART_Transmit_IT(p_PP_DRV, p_uPutDataMem, dwPutDataSize);
#endif
  
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

