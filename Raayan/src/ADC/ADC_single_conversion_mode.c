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


void ADC_SQR3_config()
{
	ADC_SQR3 |= (0X0B);
}
void EOCS_config(int mode)
{
	if(mode==1)
	ADC_CR2 |=0x01<<10;
	if(mode==0)
	ADC_CR2 &=~(0X01<<10);
}

void ADC_config(int mode)
{
	if(mode==1)
	ADC_CR2 |=0x01;
	if(mode==0)
	ADC_CR2 &=~(0X01);
}
int data;
int main()
{
	//Initialization
	PORT_init(2);
	APB1ENR_init(8,1);
	SYSTICK_init();
	
	//Configuration
	GPIOC_MODER |=(0x0000000C);
	ADC_SQR3_config();
	EOCS_config(1);
	ADC_config(1);                 //ON ADC
	ADC_CR2 |=0x01<<30;
	
	//device operation
	while(1)
	{
		ADC_CR2 |=0x01<<30;
		while(!(ADC_SR & (0x01<<1)));
		data = ADC_DR &0x0FFF;
		KM_delayms(100);
		
	}
	
	
}