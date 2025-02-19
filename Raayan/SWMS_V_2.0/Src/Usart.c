/*
 * Usart.c
 *
 *  Created on: Feb 5, 2025
 *      Author: ADMIN
 */


#include "main.h"
#include "stdio.h"
#include "string.h"
#include "USART6.h"


extern UART_HandleTypeDef huart6;
extern int lm35_data;

char *cmds[]={
		"AT\r\n",
		"AT+RST\r\n",
		"AT+CWMODE=3\r\n",
		"AT+CWJAP_DEF=\"KM-2.4G\",\"9963111084\"\r\n",
		"AT+CIPMUX=0\r\n",
		"AT+CIPMODE=0\r\n",
		"end"};




void sendcmds_wifi_init(void)
{
	int i;
	for(i=0;i<6;i++)
	{
		HAL_UART_Transmit(&huart6, (uint8_t *)cmds[i], (cmds[i+1]-cmds[i]), 100);

		if(Check_Wifi_Response() != 0)
		{
			//HAL_UART_Transmit(&huart6, (uint8_t *)cmds[i], (cmds[i+1]-cmds[i]), 100);
			i--;
		}

	}

	}







