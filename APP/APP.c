/*
 * APP.c
 *
 *  Created on: Jan 29, 2022
 *      Author: Abdelrahman Mohamed
 */
#include "../LIB/BIT_MATH.h"
#include "../LIB/STD_TYPES.h"
#include <string.h>
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
			/* Initializing Variables*/
			uint8_t Str[100];
			uint8_t Start_string[]="START";
			uint8_t Wait_string[]="WAIT";
			uint8_t Stop_string[]="STOP";
			uint8_t AT_string[]="AT";

				/*Asking for the Command*/
				UART_SendString("Enter The Command: ");
				/*Getting the Command and  confirm it*/
		    	UART_ReceiveString(Str);
		    	UART_SendString(Str);
		    	UART_SendString("\r\n");

		    	/* Check if the command match the condtions*/
		    	if(strcmp(Str,Start_string)==0)
		    	{
		    		LED_ON(LED0);
		    		LED_OFF(LED1);
		    		LED_OFF(LED2);
		    		UART_SendString("Green LED is on \r\n");
		    	}
		    	else if(strcmp(Str,Wait_string)==0)
		    	{
		    		LED_OFF(LED0);
		    		LED_ON(LED1);
					LED_OFF(LED2);
					UART_SendString("Yellow LED is on\r\n");
		    	}
		    	else if(strcmp(Str,Stop_string)==0)
		    	{
		    		LED_OFF(LED0);
		    		LED_OFF(LED1);
					LED_ON(LED2);
					UART_SendString("Red LED is on \r\n");
		    	}
		    	else if(strcmp(Str,AT_string)==0)
		    	{
		    		LED_OFF(LED0);
					LED_OFF(LED1);
					LED_ON(LED2);
					UART_SendString("OK \r\n");
		    	}
		    	else
		    	{
		    		UART_SendString(Str);
		    		UART_SendString("\r\n");
		    	}

}
