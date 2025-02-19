/*
Program     :
File name   :
Author      : Tejo prapulla
Date        :

Board       : Raayanmini
Controller  : STM32F401RBT6
Version     : 4.0

Pins Used   :
*/

#include "stm32f401rbt6.h"
#include "gpios.h"

int main()
{
	//phase 1 : initialization
	AHB1ENR_init(1);
	AHB1ENR_init(2);
	
	RCC_APB2ENR |=0x00004000;
	
	//phase 2 : Configuration
	
	MODER_config(1,01,12);
	PUPDR_config(2,01,8);
	PUPDR_config(2,01,9);
	
	SYSCFG_EXTICR3 |=0x00000022;
	
	IMR(8);
	IMR(9);
	FTSR(8);
	FTSR(9);
	
	NVIC_ISER0 |= (0x01<<23);
	
	while(1)
	{
		//phase 3: device operation
		
		;
	}
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_PR &(0x01<<8))
	{
		GPIOB_ODR |=(0x01<<12);
		
	}
	if(EXTI_PR &(0x01<<9))
	{
		GPIOB_ODR &=~(0x01<<12);
		
	}
	EXTI_PR &=~(0x01<<8);
	EXTI_PR &=~(0x01<<9);
}
	
	
	

	




