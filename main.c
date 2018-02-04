/* ###################################################################
**     Filename    : main.c
**     Project     : clockTest
**     Processor   : MKL25Z128VLK4
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2018-01-27, 15:19, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "C_CLK.h"
#include "BitIoLdd1.h"
#include "C_DATA.h"
#include "BitIoLdd2.h"
#include "C_RST.h"
#include "BitIoLdd3.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "WAIT1.h"
#include "MCUC1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "DS1302.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

char command[50];

void flush_cmd(){
	int i=0;
	for(;i<50;i++)
		command[i] = '\0';
}

int process_cmd(){
	if(command[1]!='T')
		return -1;
	if(command[2]=='\0'){
		Term1_SendStr("OK\n\r");
		return 0;
	}
	if(command[2]!='+')
		return -1;
	if(command[3]=='T'){ //settime command hhmmss
		hour = (command[4]-'0')*10 + (command[5]-'0');
		minutes = (command[6]-'0')*10 + (command[7]-'0');
		seconds = (command[8]-'0')*10 + (command[9]-'0');
		Term1_SendStr("Received: ");
		Term1_SendNum(hour);
		Term1_SendChar(':');
		Term1_SendNum(minutes);
		Term1_SendChar(':');
		Term1_SendNum(seconds/10);
		Term1_SendNum(seconds%10);
		Term1_CRLF();
		writeTime();
		return 0;
	}
	else if(command[3]=='D'){ //setdate command ddmmyyyy
		date = (command[4]-'0')*10 + (command[5]-'0');
		month = (command[6]-'0')*10 + (command[7]-'0');
		year = (command[8]-'0')*10 + (command[9]-'0');
		Term1_SendStr("Received: ");
		Term1_SendNum(date);
		Term1_SendChar('/');
		Term1_SendNum(month/10);
		Term1_SendNum(month%10);
		Term1_SendChar('/');
		Term1_SendNum(year);
		Term1_CRLF();
		writeDate();
		return 0;
	}
	else if(command[3]=='R'){ //read all data and print
		DS1302_readAll();
		Term1_SendStr("Device data:\n\r");
		Term1_SendNum(hour);
		Term1_SendChar(':');
		Term1_SendNum(minutes);
		Term1_SendChar(':');
		Term1_SendNum(seconds/10);
		Term1_SendNum(seconds%10);
		Term1_CRLF();
		Term1_SendNum(date);
		Term1_SendChar('/');
		Term1_SendNum(month/10);
		Term1_SendNum(month%10);
		Term1_SendChar('/');
		Term1_SendNum(year);
		Term1_CRLF();
		return 0;
	}
	
	return -1;
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/

  /* Write your code here */
  /* For example: for(;;) { } */
  
  
  Term1_SendStr("Startup v0.1\n\r");
  while(1){
	  Term1_ReadChar(command);
	  WAIT1_Waitms(50);
	  if(command[0] == 'A'){ //Check for AT command
		  Term1_ReadLine(command+1);
		  if(process_cmd()==-1)
			  Term1_SendStr("Invalid format\n\r");
	  }else if(command[0]!='\0'){
		  Term1_ReadLine(command+1);
		  Term1_SendStr("Invalid format\n\r");
	  }
	  flush_cmd();
		  
  }

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
