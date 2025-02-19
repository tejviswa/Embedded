/*
Program     :ADC mini project
File name   :
Author      : Tejo prapulla
Date        :

Board       : Raayanmini
Controller  : STM32F401RBT6
Version     :4.0

Pins Used   :
*/

#include "main.h"

int temp;
int pot;
int channel=10;



int main()
{
	
	char s1[50];
	char s2[50];
	char c[8]={0x1C,0x14,0x1C,0x00,0x00,0x00,0x00,0x00};
	
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
	ADC_CR1 |=(0X01<<8);			//SCAN mode ON
	ADC_CR1 |=(0X01<<5);              //EOCIE ON
	ADC_CR2 |=(0X01<<10);              //EOCS ON
	
	//ADC_CR2 |= (0X01<<1);
	NVIC_ISER0 |=(0X01<<18);           //ADC interrupt line
	
	ADC_CR2 |=0x01;                 // ADC  ON
	
	
	
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
	
		
	//device operation
	while(1)
	{
		ADC_CR2 |=0x01<<30;             //SWSTART ON
		KM_delayms_IT2(100);
		itoa(s1,temp);
	
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
			
		
		itoa(s2,pot);
		KM_LCD_Write_Cmd(0xC6);
		KM_LCD_Write_Str(s2);
	}
	
}

void ADC_IRQHandler(void)
{
	if(channel==10)
	{
		temp = (ADC_DR);//*330)/4096;
		KM_delayms_IT2(100);
		channel=11;
	}
	else if(channel==11)
	{
		pot = ADC_DR & 0x0FFF;
		channel=10;
	}
	
	
}
