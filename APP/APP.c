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
	/* Initializing Variable To store The Command*/
	uint8_t local_TempStr[MAX_SIZE];

		/*Asking for the Command*/
		UART_SendString("Enter The Command: ");
		/*Getting the Command and  confirm it*/
		UART_ReceiveString(local_TempStr);
		UART_SendString(local_TempStr);
		UART_SendString("\r\n");

		/* Check if the command match the condtions*/
		if(strcmp(local_TempStr,"START")==IDINTICAL)
		{
			LED_ON(GREEN);
			LED_OFF(YELLOW);
			LED_OFF(RED);
			UART_SendString("Green LED is on \r\n");
		}
		else if(strcmp(local_TempStr,"WAIT")==IDINTICAL)
		{
			LED_OFF(GREEN);
			LED_ON(YELLOW);
			LED_OFF(RED);
			UART_SendString("Yellow LED is on\r\n");
		}
		else if(strcmp(local_TempStr,"STOP")==IDINTICAL)
		{
			LED_OFF(GREEN);
			LED_OFF(YELLOW);
			LED_ON(RED);
			UART_SendString("Red LED is on \r\n");
		}
		else if(strcmp(local_TempStr,"AT")==IDINTICAL)
		{
			UART_SendString("OK \r\n");
		}
		else
		{
			UART_SendString(local_TempStr);
			UART_SendString("\r\n");
		}

}
