
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
#include <stdbool.h>
#include <stdlib.h>


#include "hsDEBUG_MS_UART_Print_App.h"
#include "Common_HAL.h"

//define
#define CLI_OUT_BUF_SZ                  configCOMMAND_INT_MAX_OUTPUT_SIZE

//OS Config

 //Typedef

/* Extern --------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
//OS

//Normal

/* Private function prototypes -----------------------------------------------*/
/* Interrupt  ----------------------------------------------------------------*/

/*Function -------------------------------------------------------------------*/

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
BaseType_t cmd_clearScreen(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
  uint32_t dwCnt;
  
  (void)pcCommandString;
  (void)xWriteBufferLen;
  
  for(dwCnt = 0; dwCnt < xWriteBufferLen; dwCnt++)((uint8_t *)pcWriteBuffer)[dwCnt] = 0x00;
  
  hsDebug_MSG("\033[2J\033[1;1H");
  
  return pdFALSE; //no more string output is needed
}

BaseType_t cmd_BD_Info(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{  
  (void)pcCommandString;
  (void)xWriteBufferLen;
  
  snprintf(pcWriteBuffer, CLI_OUT_BUF_SZ, "BD Information ....Run\n");
  hsDebug_MSG("BD NAME: OCT_DEV_v1.0\n");
  hsDebug_MSG("MCU    : STM32L471RET6\n");
  hsDebug_MSG("IDE    : IAR EWARM v8.32\n");
  hsDebug_MSG("HAL VER: STM32Cube FW_L4 V1.18.1\n");
    
  return pdFALSE; //no more string output is needed
}


#if 0
/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
BaseType_t DP_Volum_Control(char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString)
{
  char *pcParameter1, *pcParameter2;
  BaseType_t  xParameter1StringLength, xParameter2StringLength;
  int32_t dwChannel, dwVolume;
  int32_t dwCheck = 0;
  hsCTRL_CMD_DAT_t tSendCmd;

  pcParameter1 = (char *)FreeRTOS_CLIGetParameter(pcCommandString, 1, &xParameter1StringLength);
  pcParameter2 = (char *)FreeRTOS_CLIGetParameter(pcCommandString, 2, &xParameter2StringLength);
  
  dwChannel = strtoul(pcParameter1, NULL, 10);
  dwVolume = strtoul(pcParameter2, NULL, 10);  
  
  if( dwChannel < 2 )
  {
    if(dwVolume < 5000) // Max Resistor 5K
    {
      //dwChannel = dwChannel - 1;
      
      tSendCmd.wATT = CMD_CTRL_ATT_RUN;
      tSendCmd.wACMD = cmdOCT_DEV_DP_SET;
      tSendCmd.dwData[0] = (uint32_t)dwChannel;
      tSendCmd.dwData[1] = (uint32_t)dwVolume;
      tSendCmd.dwData[2] = 0;
      tSendCmd.dwData[3] = 0;
      
      dwCheck = OCT_DEV_CTRL_CMD_Put_Que(&tSendCmd, 1000);
      if(dwCheck)
      {
        snprintf(pcWriteBuffer, CLI_OUT_BUF_SZ, "Error! Command Run ..Fail! [%d]\n", dwCheck);
      }
      else
      {
        snprintf(pcWriteBuffer, CLI_OUT_BUF_SZ, "DP Channel[%d], Volume[%d] ohm Setting ..OK!\n", dwChannel, dwVolume);
      }
      
    }
    else
    {
      snprintf(pcWriteBuffer, CLI_OUT_BUF_SZ, "Error! Current Max Range Out.(Volume < 5000 ohm) [%d].\n", dwVolume);
    }
    
  }
  else
  {
    snprintf(pcWriteBuffer, CLI_OUT_BUF_SZ, "Error! Channel Range Out(0-1) [%d].\n", dwChannel);
  }
  
  return pdFALSE;
}
#endif



//------------------------------------------------------------------------------
/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */
const CLI_Command_Definition_t xCommandList[] = {
  
    {
        .pcCommand = "cls", /* The command string to type. */
        .pcHelpString = "cls:\n Clears screen\n\n",
        .pxCommandInterpreter = cmd_clearScreen, /* The function to run. */
        .cExpectedNumberOfParameters = 0 /* No parameters are expected. */
    },

    {
        .pcCommand = "bdinfor", /* The command string to type. */
        .pcHelpString = "bdinfor: Board Intormation\n",
        .pxCommandInterpreter = cmd_BD_Info, /* The function to run. */
        .cExpectedNumberOfParameters = 0 /* No parameters are expected. */
    },

#if 0    
    {
        .pcCommand = "dpset", /* The command string to type. */
        .pcHelpString = "dpset [channel 0-1] [volume < 5000]\n",
        .pxCommandInterpreter = DP_Volum_Control, /* The function to run. */
        .cExpectedNumberOfParameters = 2 /* No parameters are expected. */
    },
    
#endif    
    {
        .pcCommand = NULL /* simply used as delimeter for end of array*/
    } 

};

/**
  * @brief  This 
  * @param  file: 
  * @param  line: 
  * @retval None
  */


#if 0
const CLI_Command_Definition_t xCommandList[] = {
  
    {
        .pcCommand = "cls", /* The command string to type. */
        .pcHelpString = "cls:\n Clears screen\n\n",
        .pxCommandInterpreter = cmd_clearScreen, /* The function to run. */
        .cExpectedNumberOfParameters = 0 /* No parameters are expected. */
    },
    {
        .pcCommand = "home", /* The command string to type. */
        .pcHelpString = "home [x] or [y]\n",
        .pxCommandInterpreter = cmd_home, /* The function to run. */
        .cExpectedNumberOfParameters = 1 /* No parameters are expected. */
    },
    {
        .pcCommand = "move", /* The command string to type. */
        .pcHelpString = "move [x] or [y]  [Position]\n",
        .pxCommandInterpreter = cmd_move, /* The function to run. */
        .cExpectedNumberOfParameters = 2 /* 2 parameters are expected. */
    },
    {
        .pcCommand = "setpoint", /* The command string to type. */
        .pcHelpString = "setpoint [x] or [y]  [Position1] [Position2]\n",
        .pxCommandInterpreter = cmd_setpoint, /* The function to run. */
        .cExpectedNumberOfParameters = 3 /* 2 parameters are expected. */
    },
    {
        .pcCommand = "pointmove", /* The command string to type. */
        .pcHelpString = "pointmove [x] or [y]  [Replaycnt]\n",
        .pxCommandInterpreter = cmd_pointmove, /* The function to run. */
        .cExpectedNumberOfParameters = 2 /* 2 parameters are expected. */
    },
    {
        .pcCommand = "status", /* The command string to type. */
        .pcHelpString = "status [x] or [y]\n",
        .pxCommandInterpreter = cmd_status, /* The function to run. */
        .cExpectedNumberOfParameters = 1 /* 2 parameters are expected. */
    },
    {
        .pcCommand = "stop", /* The command string to type. */
        .pcHelpString = "stop [x] or [y]\n",
        .pxCommandInterpreter = cmd_stop, /* The function to run. */
        .cExpectedNumberOfParameters = 1 /* 2 parameters are expected. */
    },
    {
        .pcCommand = NULL /* simply used as delimeter for end of array*/
    } 
  
};
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
