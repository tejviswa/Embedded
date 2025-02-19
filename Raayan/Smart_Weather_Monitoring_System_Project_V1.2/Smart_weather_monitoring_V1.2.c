
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


int tick=4;

#include "main.h"
#include "../inc/I2c.h"

int lm35_flag;

#define SUCCESS 1
#define FAIL    0
int n,res;
char wifi[100];

#define SEC 0x50
#define MIN 0x50
#define HOUR 0x44      //12 HOUR MODE
#define DAY 0x6
#define DATE 0x30
#define MONTH 0x11
#define YEAR 0x24


//FOR TASK 5 CONFIGURATION
int config_flag;
char sec=0,min=0,hour=0,day=0,date=0,month=0,year=0;
char buff[10];
char str[10];




int temp,s;

char wc[50]="WIFI CONNECTED";
char ssid[10]="KM";
char s1[50],s2[50];
char c[8] = {0x1C,0x14,0x1C,0x00,0x00,0x00,0x00,0x00};




unsigned char rec[10];
unsigned char send[10];



void connect_wifi(void)
{
		clearbuff();
		USART6_outchar_str("AT+CWJAP=\"KM-2.4G\",\"9963111084\"\r\n");
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
		
		
	
}




int DECIMAL_TO_BCD(unsigned int x)
{
	int res,res1,res2;
	res1=x%10;
	res2=x/10;
	res=res1|(res2<<4);
	
	return res;
}

int BCD_TO_DECIMAL(unsigned int x)
{
	int res,res1,res2;
	res1=(x>>4)*10;
	res2=x&0x0F;
	res=res1|res2;
	return res;
}





	int d;
	
	void Task1_ReadRTC_WriteLCD_1Sec(void)
	{
	
		//KM_I2C_IsDeviceReady(0x68,1000);
		
		KM_I2C_Mem_Read(0x68,0x00,1,rec,7);
		
		KM_LCD_Write_Cmd(0x81);
		KM_LCD_Write_Data(((rec[2]>>4)&0x01)+ 48);
		KM_LCD_Write_Data(((rec[2])&0x0F) +48);
		
		KM_LCD_Write_Cmd(0x83);
		KM_LCD_Write_Str(":");
		
		
		KM_LCD_Write_Cmd(0x84);
		KM_LCD_Write_Data((rec[1]>>4)+ 48);
		KM_LCD_Write_Data(((rec[1])&0x0F) +48);
		
		KM_LCD_Write_Cmd(0x86);
		KM_LCD_Write_Str(":");
		
		KM_LCD_Write_Cmd(0x87);
		KM_LCD_Write_Data((rec[0]>>4)+ 48);
		KM_LCD_Write_Data(((rec[0])&0x0F) +48);
		
		KM_LCD_Write_Cmd(0xC1);
		KM_LCD_Write_Data((rec[4]>>4)+ 48);
		KM_LCD_Write_Data(((rec[4])&0x0F) +48);
		
		KM_LCD_Write_Cmd(0xC3);
		KM_LCD_Write_Str("/");
		
		KM_LCD_Write_Cmd(0xC4);
		KM_LCD_Write_Data((rec[5]>>4)+ 48);
		KM_LCD_Write_Data(((rec[5])&0x0F) +48);
		
		KM_LCD_Write_Cmd(0xC6);
		KM_LCD_Write_Str("/");
		
		KM_LCD_Write_Cmd(0xC7);
		KM_LCD_Write_Data((rec[6]>>4)+ 48);
		KM_LCD_Write_Data(((rec[6])&0x0F) +48);
		
	}
	
	void Task2_ReadLM35_WriteLCD_5Sec(void)
	{
		
		ADC_CR2 |=0x01<<30;             //SWSTART ON
		
		itoa(s1,temp);                      //converting temp value to string
		KM_LCD_Write_Cmd(0x8C);
		KM_LCD_Write_Str(s1);
		
	}
	
	void Task3_Wi_Fi_Tx(void)
	{
		USART6_outchar_str("AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n");
		KM_delayms_IT2(100);
		
		sprintf(wifi,"GET /page.php?temp=%d&hum=45&dev=4\r\n\r\n",temp);
		
		USART6_outchar_str("AT+CIPSEND=42\r\n");
		KM_delayms_IT2(200);
		
		USART6_outchar_str(wifi);
		KM_delayms_IT2(500);
		
//		USART6_outchar_str("AT+CIPSTATUS\r\n");
//		KM_delayms_IT2(200);
//		if(!(WiFi_OK_response()))
//		{
// 			KM_LCD_Write_Cmd(0xCB);
//		
//			KM_LCD_Write_Str("SENT");
//		}
//		else
//		{
//			KM_LCD_Write_Cmd(0xCB);
//			KM_LCD_Write_Str("FAILED");
//		}
		//KM_delayms_IT2(500);
//		
//		KM_LCD_Write_Cmd(0xCB);
//		KM_LCD_Write_Str("      ");
//		
		
		
	}
	
	
	void Task4_Check_InternetStatus(void)
	{
		clearbuff();
			
		USART6_outchar_str("AT+CIPSTATUS\r\n");
	
		res=(WiFi_OK_response());
		
		if(!(res==SUCCESS))
		{
			//connect_wifi();
			KM_LCD_Write_Cmd(0xCB);
			KM_LCD_Write_Str("FAIL");
		}
		else
		{
			KM_LCD_Write_Cmd(0xCB);
			KM_LCD_Write_Str("IPOK");
		}
		KM_delayms_IT2(100);
		
//		KM_LCD_Write_Cmd(0xCB);
//		KM_LCD_Write_Str("      ");
	}
	
	
	
	
	
	
 void Task5_SWMS_Config(void)
{
			int t=0;
			config_flag=0;
			KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0x81);
			KM_LCD_Write_Str("SS:MM:HH");
			
			KM_LCD_Write_Cmd(0xC1);
			KM_LCD_Write_Str("00");
			
	//CONFIGURATION BEGINS HERE
			while(t<8)
			{
			switch(t)
			{
				case 0:while(1)
						{
						if(!(GPIOC_IDR &(0X01<<8)))                        //FOR SEC
							{
								KM_delayms_IT2(250);
								sec=sec+1;
								if(sec>=0 && sec<60)
								{
								KM_LCD_Write_Cmd(0xC1);
								sprintf(str,"%02d",sec);
								KM_LCD_Write_Str(str);
								}
								else
								{
									sec=0;
									KM_LCD_Write_Cmd(0xC1);
									sprintf(str,"%02d",sec);
									KM_LCD_Write_Str(str);
								}
								
							}
							if(!(GPIOC_IDR &(0X01<<9)))
							{
								KM_delayms_IT2(250);
								sec = sec-1;
								if(sec>=0 && sec<60)
								{
								KM_LCD_Write_Cmd(0xC1);
								sprintf(str,"%02d",sec);
								KM_LCD_Write_Str(str);
								}
								else
								{
									sec=59;
									KM_LCD_Write_Cmd(0xC1);
									sprintf(str,"%02d",sec);
									KM_LCD_Write_Str(str);
								}
							}
							if(!(GPIOC_IDR &(0X01<<10)))
							{
								t=1;
								KM_delayms_IT2(250);
								break;
							}
						
						}
					break;
						
						
				case 1:KM_LCD_Write_Cmd(0xC3);                               //FOR MIN
							KM_LCD_Write_Str(":00");
					while(1)
						{
							if(!(GPIOC_IDR &(0X01<<8)))
							{
								KM_delayms_IT2(250);
								min=min+1;
								if(min>=0 && min<60)
								{
								KM_LCD_Write_Cmd(0xC4);
								sprintf(str,"%02d",min);
								KM_LCD_Write_Str(str);
								}
								else
								{
									min=0;
									KM_LCD_Write_Cmd(0xC4);
									sprintf(str,"%02d",min);
									KM_LCD_Write_Str(str);
								}
								
							}
							if(!(GPIOC_IDR &(0X01<<9)))
							{
								KM_delayms_IT2(250);
								min = min-1;
								if(min>=0 && min<60)
								{
								KM_LCD_Write_Cmd(0xC4);
								sprintf(str,"%02d",min);
								KM_LCD_Write_Str(str);
								}
								else
								{
									min=59;
									KM_LCD_Write_Cmd(0xC4);
									sprintf(str,"%02d",min);
									KM_LCD_Write_Str(str);
								}
							}
							if(!(GPIOC_IDR &(0X01<<10)))
							{
								t=2;
								KM_delayms_IT2(250);
								break;
							}
						
						}
					break;
						
						
				case 2:
							KM_LCD_Write_Cmd(0xC6);
							KM_LCD_Write_Str(":00");
					while(1)                                                  //FOR HOURS
						{
						if(!(GPIOC_IDR &(0X01<<8)))
							{
								KM_delayms_IT2(250);
								hour=hour+1;
								if(hour>=0 && hour<25)
								{
								KM_LCD_Write_Cmd(0xC7);
								sprintf(str,"%02d",hour);
								KM_LCD_Write_Str(str);
								}
								else
								{
									hour=0;
									KM_LCD_Write_Cmd(0xC7);
									sprintf(str,"%02d",hour);
									KM_LCD_Write_Str(str);
								}
								
							}
							if(!(GPIOC_IDR &(0X01<<9)))
							{
								KM_delayms_IT2(250);
								hour = hour-1;
								if(hour>=0 && hour<60)
								{
								KM_LCD_Write_Cmd(0xC7);
								sprintf(str,"%02d",hour);
								KM_LCD_Write_Str(str);
								}
								else
								{
									hour=23;
									KM_LCD_Write_Cmd(0xC7);
									sprintf(str,"%02d",hour);
									KM_LCD_Write_Str(str);
								}
							}
							if(!(GPIOC_IDR &(0X01<<10)))
							{
								t=3;
								KM_delayms_IT2(250);
								break;
							}
						
						}
					break;
						
				case 3:                                                    //FOR DAY
							KM_LCD_Write_Cmd(0x01);
							KM_LCD_Write_Cmd(0x81);
							KM_LCD_Write_Str("DAY:DD:MM:YY");
							KM_LCD_Write_Cmd(0xC2);
							KM_LCD_Write_Str("00");
					while(1)
						{
						if(!(GPIOC_IDR &(0X01<<8)))
							{
								KM_delayms_IT2(250);
								day=day+1;
								if(day>=0 && day<8)
								{
								KM_LCD_Write_Cmd(0xC2);
								sprintf(str,"%02d",day);
								KM_LCD_Write_Str(str);
								}
								else
								{
									day=0;
									KM_LCD_Write_Cmd(0xC2);
									sprintf(str,"%02d",day);
									KM_LCD_Write_Str(str);
								}
								
							}
							if(!(GPIOC_IDR &(0X01<<9)))
							{
								KM_delayms_IT2(250);
								day = day-1;
								if(day>=0 && day<8)
								{
								KM_LCD_Write_Cmd(0xC2);
								sprintf(str,"%02d",day);
								KM_LCD_Write_Str(str);
								}
								else
								{
									day=7;
									KM_LCD_Write_Cmd(0xC2);
									sprintf(str,"%02d",day);
									KM_LCD_Write_Str(str);
								}
							}
							if(!(GPIOC_IDR &(0X01<<10)))
							{
								t=4;
								KM_delayms_IT2(250);
								break;
							}
						
						}
					break;
						
				case 4:                                                     //FOR DATE
							KM_LCD_Write_Cmd(0xC4);
							KM_LCD_Write_Str(":00");
					while(1)
						{
						if(!(GPIOC_IDR &(0X01<<8)))
							{
								KM_delayms_IT2(250);
								date=date+1;
								if(date>=1 && date<32)
								{
								KM_LCD_Write_Cmd(0xC5);
								sprintf(str,"%02d",date);
								KM_LCD_Write_Str(str);
								}
								else
								{
									date=1;
									KM_LCD_Write_Cmd(0xC5);
									sprintf(str,"%02d",date);
									KM_LCD_Write_Str(str);
								}
								
							}
							if(!(GPIOC_IDR &(0X01<<9)))
							{
								KM_delayms_IT2(250);
								date = date-1;
								if(date>=1 && date<32)
								{
								KM_LCD_Write_Cmd(0xC5);
								sprintf(str,"%02d",date);
								KM_LCD_Write_Str(str);
								}
								else
								{
									date=31;
									KM_LCD_Write_Cmd(0xC5);
									sprintf(str,"%02d",date);
									KM_LCD_Write_Str(str);
								}
							}
							if(!(GPIOC_IDR &(0X01<<10)))
							{
								t=5;
								KM_delayms_IT2(250);
								break;
							}
						
						}
					break;
						
				case 5:                                             //FOR MONTH
							KM_LCD_Write_Cmd(0xC7);
							KM_LCD_Write_Str(":00");
					while(1)
						{
						if(!(GPIOC_IDR &(0X01<<8)))
							{
								KM_delayms_IT2(250);
								month=month+1;
								if(month>=1 && month<13)
								{
								KM_LCD_Write_Cmd(0xC8);
								sprintf(str,"%02d",month);
								KM_LCD_Write_Str(str);
								}
								else
								{
									month=1;
									KM_LCD_Write_Cmd(0xC8);
									sprintf(str,"%02d",month);
									KM_LCD_Write_Str(str);
								}
								
							}
							if(!(GPIOC_IDR &(0X01<<9)))
							{
								KM_delayms_IT2(250);
								month = month-1;
								if(month>=1 && month<13)
								{
								KM_LCD_Write_Cmd(0xC8);
								sprintf(str,"%02d",month);
								KM_LCD_Write_Str(str);
								}
								else
								{
									month=12;
									KM_LCD_Write_Cmd(0xC8);
									sprintf(str,"%02d",month);
									KM_LCD_Write_Str(str);
								}
							}
							if(!(GPIOC_IDR &(0X01<<10)))
							{
								t=6;
								KM_delayms_IT2(250);
								break;
							}
						}
						
					break;
							
				case 6:                                              //FOR YEAR
						KM_LCD_Write_Cmd(0xCA);
							KM_LCD_Write_Str(":00");
					while(1)
						{
						if(!(GPIOC_IDR &(0X01<<8)))
							{
								KM_delayms_IT2(250);
								year=year+1;
								if(year>=0 && year<100)
								{
								KM_LCD_Write_Cmd(0xCB);
								sprintf(str,"%02d",year);
								KM_LCD_Write_Str(str);
								}
								else
								{
									year=0;
									KM_LCD_Write_Cmd(0xCB);
									sprintf(str,"%02d",year);
									KM_LCD_Write_Str(str);
								}
								
							}
							if(!(GPIOC_IDR &(0X01<<9)))
							{
								KM_delayms_IT2(250);
								year = year-1;
								if(year>=0 && year<100)
								{
								KM_LCD_Write_Cmd(0xCB);
								sprintf(str,"%02d",year);
								KM_LCD_Write_Str(str);
								}
								else
								{
									year=99;
									KM_LCD_Write_Cmd(0xCB);
									sprintf(str,"%02d",year);
									KM_LCD_Write_Str(str);
								}
							}
							if(!(GPIOC_IDR &(0X01<<10)))
							{
								t=7;
								KM_delayms_IT2(250);
								break;
							}
						}	
					break;
							                           //COVERTING TO BCD AND STORING IN BUFFER ARRAY
				case 7: 
					buff[0]=DECIMAL_TO_BCD(sec);buff[1]=DECIMAL_TO_BCD(min);buff[2]=DECIMAL_TO_BCD(hour);
					buff[3]=DECIMAL_TO_BCD(day);buff[4]=DECIMAL_TO_BCD(date);buff[5]=DECIMAL_TO_BCD(month);buff[6]=DECIMAL_TO_BCD(year);
					t=8;
				
					IMR(10);                   //ENABLING  THE SW_ENT INTERRUPT
					break;
				
			}      //switch case end      
						
		} //main while end
			
		KM_I2C_Mem_Write(0x68,0x00,1,(unsigned char *)buff,7);           //WRITING TIME TO RTC
	
			KM_LCD_Write_Cmd(0x01);
		}

	
	
	
	
	
	
	
	
	
	/*================================================================================================
	                             DEVICE OPERATION
	==================================================================================================   
	*/
	
	
int main()
{
	int l,t;
	
	KM_I2C1_Init();
	KM_I2C1_Config();
	SYSTICK_init();
	KM_LCD_Init();
	
	
	//KM_I2C_IsDeviceReady();
	//KM_I2C_Mem_Write();
	//KM_I2C_Mem_Read();
	
	
//		l=KM_I2C_Mem_Write(0x68,0x00,1,buff,7);
//		if(l==1)
//		{
//			KM_LCD_Write_Cmd(0x01);
//			KM_LCD_Write_Str("write success");
//			KM_delayms_IT2(1000);
//		}
//		KM_LCD_Write_Cmd(0x01);
////		
	
/*
=======================================================
SWITCHES CONFIGURATION PART
====================================================
*/
	PORT_init(C);
	
	//initialization
	
	
	//APB2ENR_init(14,1);                 //SYSCFG clock initilaization  for ENT_SWT
	RCC_APB2ENR |=0x00004000;
	
	//configuration
	
	/*
	=========ENTER SWITCH PC10======================
	*/
	
	GPIOC_PUPDR &=(0x0);
	PUPDR_config(C,01,10);                //SW_ENT configuration for pull up
	
	SYSCFG_EXTICR3  |=0x00000200;        //load 0010 to SYSCFG_EXTICR3 register bit fileds 11-8 for enabling portC for interrupt
	IMR(10);                         //set 10th bit of EXTI_IMR register for enabling the interrupt line. 
	FTSR(10);                       //set 10th bit of EXTI_FTSR register for enabling the falling edge trigger mode
	NVIC_ISER1  |= 0x00000100;        //set 8th bit in ISER1 for enabling the interrupt request for PORTC 10th pin of external interrupt 
	
	/*
		=========UP&DOWN SWITCH PC8,PC9======================
		*/
	GPIOC_PUPDR |=(0x01<<16);                //SW_UP configuration for pull up
	GPIOC_PUPDR |=(0x01<<18);                //SW_DN configuration for pull up
	

	
//==========================
//        ADC PART
//=========================
	
	//Initialization
	PORT_init(C);                            //Clock to port C
	APB2ENR_init(8,1);                       //Clock to ADC1
	
	
	//Configuration
	GPIOC_MODER |=(0x00000003);                //PC0 as Analog mode
//	GPIOC_MODER |=(0x0000000C);               //PC1 as Analog mode
	//ADC_SQR1 |=(0x01<<20);                    //Length field
	ADC_SQR3 |=(0x0A);                       //PC0 as ADC_10 channel
//	ADC_SQR3 |=(0x160);                      //PC1 as ADC_11 channel
	//EOCS_config(1);
	//ADC_CR1 |=(0X01<<8);			        //SCAN mode ON
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
	

	
	
	
		
	/*===========================================================================================
	              	WIFI PART
		=====================================================================
	
	   CONFIGURATION COMMANDS
	============================================	
		             AT 
   ========================================
*/	
	USART6_outchar_str("AT\r\n");
//			if(!(WiFi_STR_response("OK")))
//		{ 
//			KM_LCD_Write_Cmd(0x01);
//			KM_LCD_Write_Str("NO WiFi reset the Board");
//			while(1);
//		}
//		else
//		{
//			KM_LCD_Write_Cmd(0x01);
//			KM_LCD_Write_Cmd(0xC0);
//			KM_LCD_Write_Str("DEVICE FOUND");
//		}
		KM_LCD_Write_Str("   WELCOME TO      KERNAL MASTERS");
		KM_delayms_IT2(2000);
		clearbuff();
	/*		
============================================	
        		 AT+RST
========================================
	*/
		
		
	USART6_outchar_str("AT+RST\r\n");
//		if(!(RST_response()))
//		{
//			KM_LCD_Write_Cmd(0x01);
//			KM_LCD_Write_Str("RST NOT OK");
//			
//		}
//		else
//		{
//			KM_LCD_Write_Cmd(0x01);
//			KM_LCD_Write_Cmd(0xC0);
//			KM_LCD_Write_Str("RST OK ");
//		}
//		clearbuff();
			
			KM_LCD_Write_Str("CONNECTING Wi_Fi");			
			KM_delayms_IT2(1000);

/*		
============================================	
        		 AT+CWJAP?
========================================
	*/
	

		
	USART6_outchar_str("AT+CWJAP?\r\n");
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
		clearbuff();
			KM_delayms_IT2(2000);
		
		USART6_outchar_str("AT+CWJAP=\"Power\",\"123456789\"\r\n");
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
		
		
		
		
		/*		
============================================	
        		 AT+CIPMUX
========================================
	*/
	
		
		USART6_outchar_str("AT+CIPMUX=0\r\n");
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
		clearbuff();
		KM_delayms_IT2(2000);
		
		
	/*		
============================================	
        		 AT+CIPMODE=0
========================================
	*/
		
		USART6_outchar_str("AT+CIPMODE=0\r\n");
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
		clearbuff();
		KM_delayms_IT2(2000);					
		KM_LCD_Write_Cmd(0x01);                //CLEARING DISPLAY
		
		//FOR TEMPERATURE VALUE
		
		KM_LCD_Write_Cmd(0x8A);
		KM_LCD_Write_Str("T:   C");
		
		KM_LCD_Write_Cmd(0x40);           //CUSTOM CHARACTER
		custom(c);
		KM_LCD_Write_Cmd(0x8E);
		KM_LCD_Write_Data(0);
		
	
	
	while(1)
	{
		
		Task1_ReadRTC_WriteLCD_1Sec();              //TASK 1
		tick++;
		
		//connect_wifi();
		if(tick==5)
		{
			tick=0;
			Task2_ReadLM35_WriteLCD_5Sec();           //TASK 2
		
			
			if(lm35_flag)
			{
			Task3_Wi_Fi_Tx();                       //TASK 3
				lm35_flag=0;
			}
		}
			
			Task4_Check_InternetStatus();          //TASK 4
			
			if(config_flag)
			{
				Task5_SWMS_Config();                  //TASK 5
			}
		
	}
		

	
}






//=====================================
//           ADC IRQ HANDLER
//=====================================

void ADC_IRQHandler(void)
{
		temp = (ADC_DR*330)/4096;
		lm35_flag=1;
}


//=====================================
//           SW_ENT IRQ HANDLER
//=====================================


void EXTI15_10_IRQHandler(void) 
{
	if(EXTI_PR &(0x01<<10))       //10th bit will be set if switch is pressed ,checking the status of that bit
	{
		
		EXTI_PR |=(0x01<<10);            //at the end of the ISR clear the EXTI_PR for accepting next interrupt
	
		config_flag=1;                      //FLAG CONDITION FOR TO ENTER INTO CONFIGURATION MODE
		EXTI_IMR &=~(0x01<<10);        //clearing IMR TO DISABLE INTERRUPT DURING THIS FUNCTION
	}
	
}







