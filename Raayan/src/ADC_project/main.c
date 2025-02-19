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



#include "stm32f401rbt6.h"
#include "gpios.h"
#include "Systic.h"
#include "lcd.h"
#include "adc.h"

int temp;
int main()
{
	
	char s1[50];
	char c[8]={0x1C,0x14,0x1C,0x00,0x00,0x00,0x00,0x00};
	
	//Initialization
	PORT_init(C);                            //Clock to port C
	SYSTICK_init();
	
	//Configuration
	KM_ADC_Init();                            //ADC configuration	
	KM_LCD_Init();
	
	KM_LCD_Write_Str("Temperature:");
	
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
		KM_delayms(5);
		ADC_CR2 |=0x01<<30;
		itoa(s1,temp);
		KM_LCD_Write_Cmd(0x8C);
		KM_LCD_Write_Str(s1);
	}
	
}

void ADC_IRQHandler(void)
{
	KM_ADC_Read();
}
