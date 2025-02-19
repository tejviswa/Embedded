
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

#include "../inc/main.h"

//FOR SWITCH CASE
#define SUCCESS 1
#define FAIL    0
int n,res;
	



int temp,s;
int pot;
int channel=10;
char wifi[100];
char np[50]="No AP";
char wc[50]="WIFI CONNECTED";
char ssid[10]="KM";
char s1[50],s2[50];
char c[8] = {0x1C,0x14,0x1C,0x00,0x00,0x00,0x00,0x00};

void ADC_print(void)
{
		
		itoa(s1,temp);                      //converting temp value to string
		KM_LCD_Write_Cmd(0x8C);
		KM_LCD_Write_Str(s1);
		
		
		// condition for pots
		if(pot<=999)
		{
			KM_LCD_Write_Cmd(0xC9);
			KM_LCD_Write_Data(' ');
			if(pot<=99)
			{
				KM_LCD_Write_Cmd(0xC8);
				KM_LCD_Write_Data(' ');
			}
		}
		
		itoa(s2,pot);                          //converting Pot value to string
		KM_LCD_Write_Cmd(0xC6);
		KM_LCD_Write_Str(s2);
		
}




int main()
{
	
//==========================
//        ADC PART
//=========================
	
	//Initialization
	PORT_init(C);                            //Clock to port C
	APB2ENR_init(8,1);                       //Clock to ADC1
	SYSTICK_init();
	KM_LCD_Init();
	
	//Configuration
	GPIOC_MODER |=(0x00000003);                //PC0 as Analog mode
	GPIOC_MODER |=(0x0000000C);               //PC1 as Analog mode
	ADC_SQR1 |=(0x01<<20);                    //Length field
	ADC_SQR3 |=(0x0A);                       //PC0 as ADC_10 channel
	ADC_SQR3 |=(0x160);                      //PC1 as ADC_11 channel
	//EOCS_config(1);
	ADC_CR1 |=(0X01<<8);			        //SCAN mode ON
	ADC_CR1 |=(0X01<<5);              //EOCIE ON
	ADC_CR2 |=(0X01<<10);              //EOCS ON
	
	//ADC_CR2 |= (0X01<<1);
	NVIC_ISER0 |=(0X01<<18);           //ADC interrupt line
	
	ADC_CR2 |=0x01;                 // ADC  ON
	
//======================================
//             WIFI PART
//=======================================
		
	MODER_config(C,10,6);           //Enabling PC6,PC7 as alternate function mode as they are connected to USART 6
	MODER_config(C,10,7);
	
	GPIOC_AFRL |= (0x88000000);           //selecting USART6 from Alternate function for PORT C
	RCC_APB2ENR |=(0X01<<5);             //Enabling clock for USART6
	
	
	USART6_BRR |=(0X8B);           //Baud rate  for WiFi
	
	
	USART6_CR1 |=(0X01<<13);        //USART6 ON
	USART6_CR1 |=(0X01<<2);         //RE ON
	USART6_CR1 |=(0X01<<3);					//TE ON
	
	
	

	
	while(1)
	{
		KM_delayms_IT2(2000);
		clearbuff();
		switch(n)
		{
			case 0:USART6_outchar_str("AT\r\n");
						res=WiFi_STR_response("OK");
			
						if(res==SUCCESS)
							{
								n=1;                             //go for next command
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Str("DEVICE OK");
							}
							else
							{
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Cmd(0xC0);
								KM_LCD_Write_Str("DEVICE NOT FOUND");
							}
								
							break;
			
			case 1:USART6_outchar_str("AT+RST\r\n");
							res=RST_response();
							if(res==SUCCESS)
							{
								n=2;                              //go for next command
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Str("RST OK ");
							}
							else
							{
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Cmd(0xC0);
								KM_LCD_Write_Str("RST NOT OK");
							}
							break;
			
			case 2:USART6_outchar_str("AT+CWMODE=3\r\n");
							res = WiFi_OK_response();
							if(res==SUCCESS)
							{
								n=3;
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Str("AT+CWMODE=3 OK");
							}
							else
							{
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Cmd(0xC0);
								KM_LCD_Write_Str("AT+CWMODE=3 OK");
							}
							break;
															
			case 3:USART6_outchar_str("AT+CWJAP?\r\n");
							//KM_delayms_IT2(500);
							res=WiFi_CWJAP_response();
							if(res==SUCCESS)
							{
								n=5;
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Str("AP FOUND");
							}
							else
							{
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Cmd(0xC0);
								KM_LCD_Write_Str("NO AP");
								n=4;
							}
							break;
			
			case 4:USART6_outchar_str("AT+CWJAP=\"SIVA\",\"7036484328\"\r\n");
							res = WiFi_STR_response(wc);
							if(res==SUCCESS)
							{
								n=5;
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Str("WIFI CONNECTED");
							}
							else
							{
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Str("WIFI not CONNECTED");
								
							}
			break;
							
			case 5:USART6_outchar_str("AT+CIPMUX=0\r\n");
							res=(WiFi_OK_response());
							if(res==SUCCESS)
							{
								n=6;
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Str("AT+CIPMUX=0  OK");
								
							}
							else
							{
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Str("CIPMUX NO RESPONSE");
								
							}
					
			break;
							
			case 6:USART6_outchar_str("AT+CIPMODE=0\r\n");
							res=(WiFi_OK_response());
							if(res==SUCCESS)
							{
								n=7;
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Str("AT+CIPMODE=0");
								
							}
							else
							{
								KM_LCD_Write_Cmd(0x01);
								KM_LCD_Write_Cmd(0xC0);
								KM_LCD_Write_Str("AT+CIPMODE not OK");
							}
							
			break;
							
			case 7:KM_LCD_Write_Cmd(0x01);
							KM_LCD_Write_Cmd(0x80);
							KM_LCD_Write_Str("Temperature:");
							KM_LCD_Write_Cmd(0xC0);
							KM_LCD_Write_Str("Pot :");
							
							//custom charcater
							KM_LCD_Write_Cmd(0x40);
							custom(c);
							KM_LCD_Write_Cmd(0x8E);
							KM_LCD_Write_Data(0);
							//charcater C
							KM_LCD_Write_Cmd(0x8F);
							KM_LCD_Write_Data(0x43);
							n=8;
				break;
							
			case 8:while(1)
							{
											
								//====================================
								//           ADC PART
								//====================================
								
								ADC_CR2 |=0x01<<30;             //SWSTART ON
								KM_delayms_IT2(100);
								ADC_print();
								
								//===============================
								//        WIFI PART
								//=============================
								
								USART6_outchar_str("AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n");
								KM_delayms_IT2(1000);
								
								sprintf(wifi,"GET /page.php?temp=%d&hum=%d&dev=4\r\n\r\n",temp,pot);
								
								USART6_outchar_str("AT+CIPSEND=45\r\n");
								KM_delayms_IT2(200);
								
								USART6_outchar_str(wifi);
								KM_delayms_IT2(2000);
								
								USART6_outchar_str("AT+CIPSTATUS\r\n");
								KM_delayms_IT2(1000);
								
								if(!(WiFi_OK_response()))
								{
									KM_LCD_Write_Cmd(0xCB);
								//	KM_delayms_IT2(2000);
									KM_LCD_Write_Str("SENT");
								}
								else
								{
									KM_LCD_Write_Cmd(0xCB);
									KM_LCD_Write_Str("FAILED");
								}
								KM_delayms_IT2(500);
								
								KM_LCD_Write_Cmd(0xCB);
								KM_LCD_Write_Str("      ");
													
							}
						}
					
								
					}
				}
							
									
		
			
	


//=====================================
//           ADC IRQ HANDLER
//=====================================

void ADC_IRQHandler(void)
{
	if(channel==10)
	{
		temp = (ADC_DR*330)/4096;
		
		channel=11;
	}
	else if(channel==11)
	{
		pot = ADC_DR & 0x0FFF;
		channel=10;
	}
	
}




