/*
 * main.c
 *
 *  Created on: Jan 25, 2022
 *      Author: Abdelrahman Mohamed
 */

#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/UART/UART_Interface.h"
#include "../HAL/LED/LED_Interface.h"

#include "APP.h"

void APP_Init()
{
	/* Initializing UART and LEDS*/
			UART_Init();
			LED_Init(GREEN);
			LED_Init(YELLOW);
			LED_Init(RED);
}

void APP_Run()
{
		/* Initializing Variables */
		uint8_t Input_String[MAX_SIZE];				//To Store The input
		uint8_t Start_String[]="START";				// START Check condition
		uint8_t Wait_String[]="WAIT";				// WAIT Check condition
		uint8_t Stop_String[]="STOP";               // STOP Check condition
		uint8_t AT_string[]="AT";                   // AT Check condition

		/*	Initializing variables for checking the not passed condition */
		uint8_t Start_NotPass =NO_CONFLICT;
		uint8_t Wait_NotPass =NO_CONFLICT;
		uint8_t Stop_NotPass =NO_CONFLICT;
		uint8_t AT_NotPass =NO_CONFLICT;

		/*	Asking for Input from Terminal UART*/
		UART_SendString("Enter The String: \r\n");
		UART_ReceiveString(&Input_String);

		/*	Checking the Input by Char */
	  for(uint8_t i =0;Input_String[i]!='\0';i++)
	  {
		  if(Input_String[i]!=Start_String[i] && Start_NotPass ==NO_CONFLICT)
		  {
			  Start_NotPass ++;
		  }
		  if(Input_String[i]!=Wait_String[i] && Wait_NotPass ==NO_CONFLICT)

		  {
			  Wait_NotPass ++;
		  }
		   if(Input_String[i]!=Stop_String[i] && Stop_NotPass ==NO_CONFLICT)

		   {
			   Stop_NotPass++;
		   }
		   if(Input_String[i]!=AT_string[i] && AT_NotPass ==NO_CONFLICT)

		  {
			  AT_NotPass ++;
		  }

	  }

	  /*Action States*/
	  /* Check if there is  conflict  with any condition */
	  /* Take action based on conflict data*/
	  if(Start_NotPass ==NO_CONFLICT)
		  {
				LED_ON(GREEN);
				LED_OFF(YELLOW);
				LED_OFF(RED);
				UART_SendString("Green LED is on \r\n");
		  }
	  else if(Wait_NotPass ==NO_CONFLICT)
	  {
				LED_OFF(GREEN);
				LED_ON(YELLOW);
				LED_OFF(RED);
				UART_SendString("Yellow LED is on\r\n");
	  }
	  else if(Stop_NotPass ==NO_CONFLICT)
	  {
			LED_OFF(GREEN);
			LED_OFF(YELLOW);
			LED_ON(RED);
			UART_SendString("Red LED is on \r\n");

	  }
	  else if(AT_NotPass ==NO_CONFLICT)
	  {
		  UART_SendString("OK\r\n");
	  }
	  else
	  {
		  UART_SendString(Input_String);
		  UART_SendString("\r\n");
	  }


}
