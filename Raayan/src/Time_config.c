

#include "main.h"
#include "../inc/I2c.h"

void Time_config (void);

unsigned char rec[10];
unsigned char time[10];

int config_flag;

char sec=0,min=0,hour=0,day=0,date=0,month=0,year=0;


char buff[10];

char str[10];




int l;

void EXTI15_10_IRQHandler(void) 
{
	if(EXTI_PR &(0x01<<10))       //10th bit will be set if switch is preseced ,checking the status of that bit
	{
		
		EXTI_PR |=(0x01<<10);            //at the end of the ISR clear the EXTI_PR for accepting next interrupt
	
		config_flag=1;                      //FLAG CONDITION FOR TO ENTER INTO CONFIGURATION MODE
		EXTI_IMR &=~(0x01<<10);        //clearing IMR TO DISABLE INTERRUPT DURING THIS FUNCTION
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


	void Task1_ReadRTC_WriteLCD_1Sec(void)
	{
	
		
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

	
	




int main()
{
	int l,t;
	
	
	KM_I2C1_Init();   //port
	KM_I2C1_Config();
	SYSTICK_init();
	KM_LCD_Init();   //port B also initialized in this
	
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
	
	

	
	
	
	
	
	
	
	while(1)
	{
		
		if(config_flag)
		{
			Time_config();
		}

		
		Task1_ReadRTC_WriteLCD_1Sec();
		
	
	}		
}


void Time_config (void)
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
			
		l=KM_I2C_Mem_Write(0x68,0x00,1,buff,7);           //WRITING TIME TO RTC
	
			KM_LCD_Write_Cmd(0x01);
		}
			
		

			
	
		

	
	
	