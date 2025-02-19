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
//#include "Systic.h"

int pot;
int main()
{
	//SYSTICK_init();
	PORT_init(C);                            //Clock to port C
	APB2ENR_init(8,1);                       //Clock to ADC1
	APB2ENR_init(14,1);                      //clock for SYSCFG
	SYSCFG_EXTICR3 |= (0X01<<13);
	GPIOC_MODER |=(0x0000000C);               //PC1 as Analog mode
	GPIOC_PUPDR |=(0X01<<22);                  //PIN 11 as input mode with pull up resistor for falling edge triggering
	
	ADC_SQR3 |=(0x0B);                      //PC1 as ADC_11 channel
	//ADC_CR1 |=(0x01<<8);                   //scan mode
	ADC_CR2 |=(0X0F000000);             //EXTSEL for external event select for regular group
	
	ADC_CR1 |=(0X01<<5);              //EOCIE ON
	ADC_CR2 |=(0X01<<10);              //EOCS ON
	NVIC_ISER0 |=(0X01<<18);           //ADC interrupt line
	ADC_CR2 |=(0x01<<29);              //EXTEN for external triggering enable for regular channels
	ADC_CR2 |=(0X01<<0);               //ADC ON
	
	
	while(1)
	{
		//ADC_CR2 |=(0X01<<0);               //ADC ON
		
		;
	}
	
}




void ADC_IRQHandler(void)
{
		//KM_delayms(20);
		pot = ADC_DR & 0x0FFF;
		//ADC_CR2 &=~(0X01<<0);      //ADC OFF
}
	

	
