
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
#include "hsCLI_App.h"

#include "FreeRTOS_CLI.h"    
    
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "stdbool.h"
#include "stdlib.h"


#include "hsDEBUG_MS_UART_Print_App.h"

//define 
#define MAX_INPUT_LENGTH                50

//OS Config
#define hsCLI_CONSOL_TSK_MEM         128
#define hsCLI_CONSOL_TSK_PRIO        (tskIDLE_PRIORITY + 0)     // 6 5 4 3 2 1 0

 //Typedef

/* Extern --------------------------------------------------------------------*/


extern const CLI_Command_Definition_t xCommandList[];
/* Private variables ---------------------------------------------------------*/
//OS
TaskHandle_t g_xCLI_CONSOL_Task_Handle;

//Normal
int8_t cRxedChar;
char cOutputBuffer[configCOMMAND_INT_MAX_OUTPUT_SIZE], pcInputString[MAX_INPUT_LENGTH];

const char * cli_prompt = "\nHS> ";

/* CLI escape sequences*/
uint8_t backspace[] = "\b \b";
uint8_t backspace_tt[] = " \b";

/* Private function prototypes -----------------------------------------------*/
void vCLI_ConsoleTask(void *p_vParam);

void cliWrite(const char *str);
void handleNewline(const char *const pcInputString, char *cOutputBuffer, uint8_t *cInputIndex);
void handleBackspace(uint8_t *cInputIndex, char *pcInputString);
void handleCharacterInput(uint8_t *cInputIndex, char *pcInputString);

void vRegisterCLICommands(void);
/* Interrupt  ----------------------------------------------------------------*/

/*Function -------------------------------------------------------------------*/

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
int32_t hsCLI_App_Config(void)
{
  int32_t dwCheck = 0;
  
  xTaskCreate(vCLI_ConsoleTask, "CLI_APP", hsCLI_CONSOL_TSK_MEM, (void *)1, hsCLI_CONSOL_TSK_PRIO, &g_xCLI_CONSOL_Task_Handle);
    
  return dwCheck;
}

//-----------------------------------------------------------------------------
/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void vCLI_ConsoleTask(void *p_vParam)
{
  uint8_t cInputIndex = 0; 
  uint32_t receivedValue;
  char uTemp_Str[2] = {0};
  
  UNUSED(p_vParam);
  
  vRegisterCLICommands();
  
  hsDebug_MSG("*** OCT_DEV_v1.0 Command Line Interface ***\n");
  //hsDEBUG_UART_RX_QueGet((uint8_t *)&receivedValue, portMAX_DELAY);
  //cRxedChar = receivedValue & 0xFF;
  
  cliWrite(cli_prompt);
  
  for(;;)
  {
    hsDEBUG_UART_RX_QueGet((uint8_t *)&receivedValue, portMAX_DELAY);
    
    cRxedChar = receivedValue & 0xFF;
    
    uTemp_Str[0] = cRxedChar;
    
    cliWrite(uTemp_Str); //echo recevied char
    //cliWrite(&cRxedChar);
    
    if( (cRxedChar == '\r') || (cRxedChar == '\n') ) handleNewline(pcInputString, cOutputBuffer, &cInputIndex); //// user pressed enter, process the command
    else handleCharacterInput(&cInputIndex, pcInputString); //user pressed a character add it to the input string
    
  }
  
}
//----------------------------------------------------------------------------
/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void cliWrite(const char *str)
{
  hsDebug_MSG("%s", str);
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void handleNewline(const char *const pcInputString, char *cOutputBuffer, uint8_t *cInputIndex)
{
  uint32_t dwCnt;
  BaseType_t xMoreDataToFollow;
  
  cliWrite("\n");
  
  do
  {
    xMoreDataToFollow = FreeRTOS_CLIProcessCommand(pcInputString, cOutputBuffer, configCOMMAND_INT_MAX_OUTPUT_SIZE);
    
   cliWrite(cOutputBuffer);
   
  }while(xMoreDataToFollow != pdFALSE);
  
  cliWrite(cli_prompt);
  
  *cInputIndex = 0;
  
  for(dwCnt = 0; dwCnt < MAX_INPUT_LENGTH; dwCnt++) ((uint8_t *)pcInputString)[dwCnt] = 0x00;
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void handleBackspace(uint8_t *cInputIndex, char *pcInputString)
{
  uint8_t right[] = "\x1b\x5b\x43";
  
  if(*cInputIndex > 0)
  {
    (*cInputIndex)--;
    pcInputString[*cInputIndex] = '\0';
    cliWrite((char *)backspace_tt);
  }
  else
  {
    cliWrite((char *)right);
  }
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void handleCharacterInput(uint8_t *cInputIndex, char *pcInputString)
{
  if(cRxedChar ==  '\r') return;
  else if( (cRxedChar == (uint8_t)0x08)||(cRxedChar==(uint8_t)0x7F) )
  {
    handleBackspace(cInputIndex, pcInputString);
  }
  else
  {
    if( *cInputIndex < MAX_INPUT_LENGTH)
    {
      pcInputString[*cInputIndex] = cRxedChar;
      (*cInputIndex)++;
    }
  }
}

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
void vRegisterCLICommands(void)
{
  int32_t dwCnt;
  
  for(dwCnt = 0; xCommandList[dwCnt].pcCommand != NULL ; dwCnt++) FreeRTOS_CLIRegisterCommand(&xCommandList[dwCnt]);
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
