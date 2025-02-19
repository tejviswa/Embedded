
/*
Program     :
File name   :
Author      : Tejo prapulla
Date        :

Board       : Raayanmini
Controller  : STM32F401RBT6
Version     :4.0

Pins Used   :
*/

#include "main.h"



char s1[3]="OK";
char s2[20]="ready";
char s3[20]="CONNECT";

int main()
{
	
	//INITIALIZATION
//	PORT_init(A);
	//PORT_init(B);
	PORT_init(C);
	SYSTICK_init();
	KM_LCD_Init();
	
	// CONFIGURATION
	//MODER_config(B,01,13);          //PB13,PB14 as ouput mode for LEDS's
	//MODER_config(B,01,14);
	//GPIOB_ODR |=(0X01<<13);
	//GPIOB_ODR |=(0X01<<14);
//	
//	PUPDR_config(C,01,8);          //PC8,PC9 configuring PULL UP resistors
//	PUPDR_config(C,01,9);
//	
	
	MODER_config(C,10,6);           //Enabling PC6,PC7 as alternate function mode as they are connected to USART 6
	MODER_config(C,10,7);
	
	GPIOC_AFRL |= (0x88000000);           //selecting USART6 from Alternate function for PORT C
	RCC_APB2ENR |=(0X01<<5);             //Enabling clock for USART6
	
	
	USART6_BRR |=(0X8B);           //Baud rate  for WiFi
	
	
	USART6_CR1 |=(0X01<<13);        //USART ON
	USART6_CR1 |=(0X01<<2);         //RE ON
	USART6_CR1 |=(0X01<<3);					//TE ON
	
	//USART6_CR1 |=(0X01<<7);					//TXEIE ON
	//USART6_CR1 |=(0X01<<5);					//RXEIE ON
	
	//NVIC_ISER2 |= (0X01<<7);         //NVIC ON 
	
	
	
	
		KM_delayms_IT2(500);
	
		//============================================	
		// AT 
//========================================
		USART6_outchar_str("AT\r\n");
			if(!(WiFi_STR_response("OK")))
		{ 
			KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("NO WiFi");
			while(1);
		}
		else
		{
			KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("DEVICE OK");
		}
		
		KM_delayms_IT2(2000);
		USART6_outchar_str("AT+CWSAP?\r\n");
		KM_delayms_IT2(2000);
		//============================================	
		// AT+RST
//========================================
		USART6_outchar_str("AT+RST\r\n");
		KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("CHECKING RST");
		KM_delayms_IT2(2000);
		
	
		//============================================	
		// AT+CWMODE
//========================================	
		USART6_outchar_str("AT+CWMODE=3\r\n");
			
		if(!(WiFi_OK_response()))
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("CW MODE NOT OK");
		}
		else
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("AT+CWMODE=3");
		}
		KM_delayms_IT2(2000);
		
	/*		
		USART6_outchar_str("AT+CWJAP=\"KM-2.4G\",\"9963111084\"\r\n");
		if(!(WiFi_OK_response()))
		{
			KM_LCD_Write_Str("WIFI NOT CONNECTED");
		}
		else
		{
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("WIFI CONNECTED");
		}
		
		KM_delayms_IT2(3000);
		
		*/
	
		//============================================	
		// AT+CIPMUX
//========================================		
		USART6_outchar_str("AT+CIPMUX=0\r\n");
		if(!(WiFi_OK_response()))
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("CIPMUX NO RESPONSE");
		}
		else
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("AT+CIPMUX=0");
		}
		KM_delayms_IT2(2000);
		
		
	/*	
		USART6_outchar_str("AT+CIFSR\r\n");
		if(!(WiFi_OK_response()))
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str(" CIFSR NO RESPONSE");
		}
		else
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("AT+CIFSR");
		}
			KM_delayms_IT2(3000);
		*/
	
		
		
		
//		USART6_outchar_str("AT+CWLAP\r\n");
//		KM_delayms_IT2_IT2(3000);
	
		//============================================	
		// AT+CIPMODE
//========================================		
		USART6_outchar_str("AT+CIPMODE=0\r\n");
		
		if(!(WiFi_OK_response()))
		{
			KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("CIPMODE NO RESPONSE");
		}
		else
		{
			KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("AT+CIPMODE=0");
		}
			KM_delayms_IT2(2000);
	
	
		
//		
	//DEVICE OPERATION

	while(1)
	{
		//============================================	
		// CIP STATUS
//========================================
		clearbuff();
		USART6_outchar_str("AT+CIPSTATUS\r\n");
			//KM_delayms_IT2(200);
		if(!(WiFi_OK_response()))
		{
			KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("CIPSTATUS NO RESPONSE");
		}
		else
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("AT+CIPSTATUS");
		}
		KM_delayms_IT2(2000);
		clearbuff();

		//============================================	
		//CIP START
//========================================
		USART6_outchar_str("AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n");
		
		if(!(WiFi_STR_response("CONNECT")))
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("CIPSTART NO RESPONSE");
		}
		else
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("SERVER CONNECTED");
		}
		KM_delayms_IT2(2000);
		clearbuff();
		
	//============================================	
		//CIP SEND
//========================================
		
		USART6_outchar_str("AT+CIPSEND=50\r\n");
			
		if(!(WiFi_OK_response()))
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("CIPSEND NO RESPONSE");
		}
		else
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("AT+CIPSEDND OK");
		}
		KM_delayms_IT2(2000);
		clearbuff();
		
		USART6_outchar_str("GET /page.php?temp=26&hum=45&dev=04\r\n\r\n");
		
		KM_delayms_IT2(2000);
		clearbuff();
	}
}
		
//		USART6_outchar_str("AT+CIPSTATUS");
//		if(!(WiFi_OK_response()))
//		{
//			KM_LCD_Write_Str("CIPSTATUS NO RESPONSE");
//		}
//		else
//		{
//			KM_LCD_Write_Cmd(0xC0);
//			KM_LCD_Write_Str("AT+CIPSTATUS");
//		}
		
	//	KM_delayms_IT2(3000);
		
//		KM_delayms_IT2(3000);
//		USART6_outchar_str("AT+CIPCLOSE\r\n");
//		
//	}


