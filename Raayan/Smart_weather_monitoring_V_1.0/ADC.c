
#include "../inc/main.h"

void KM_ADC_Init(void)
{
	//Initialization
	PORT_init(C);                            //Clock to port C
	APB2ENR_init(8,1);                       //Clock to ADC1
	SYSTICK_init();
	KM_LCD_Init();
}

void KM_ADC_config(void)
{
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
	                     
}



int temp;
int channel=10;
int pot;

char s1[50],s2[50];



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







//=====================================
//           ADC IRQ HANDLER
//=====================================

void ADC_IRQHandler(void)
{
	if(channel==10)
	{
		temp = (ADC_DR*330)/4096;
		//KM_delayms_IT2(100);
		channel=11;
	}
	else if(channel==11)
	{
		pot = ADC_DR & 0x0FFF;
		channel=10;
	}
	
}
