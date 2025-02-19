
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

char ch='A';
int data=1000;

void USART2_outchar(unsigned char ch)
{
	while(!(USART2_SR & (0X01<<7)));
	USART2_DR = ch;
}


unsigned char USART2_inchar(void)
{
	while(!(USART2_SR & (0X01<<5)));
	ch = USART2_DR & 0xFF;
	return ch;
}

unsigned char USART2_inchar_nonblocking(void)
{
	if((USART2_SR & (0X01<<5)))
	{
		ch = USART2_DR & 0xFF;
	}
	return ch;
}

unsigned char USART2_inchar_timeout(void)
{
		while(data)
			data--;
		if(data==0)
			return '1';
		else
		{
			ch= USART2_DR & 0xFF;
			return '0';
		}
}



int main()
{
	
	//INITIALIZATION
	PORT_init(A);
	MODER_config(A,10,2);
	MODER_config(A,10,3);
	GPIOA_AFRL |= (0x7700);
	RCC_APB1ENR |=(0X01<<17);                //enabling clock for USART
	
	//CONFIGURATION
	USART2_BRR |=(0X683);           //Baud rate 
	
	USART2_CR1 |=(0X01<<13);        //USART ON
	USART2_CR1 |=(0X01<<2);         //RE ON
	USART2_CR1 |=(0X01<<3);					//TE ON
	
//	USART2_CR1 |=(0X01<<7);					//TXEIE ON
	USART2_CR1 |=(0X01<<5);					//RXEIE ON
	NVIC_ISER1 |= (0X01<<6);         //NVIC ON 
	
	
	//DEVICE OPERATION
	while(1)
	{
		USART2_outchar('A');
		ch++;
		//KM_delayms(500);
	}
}


void USART2_IRQHandler(void)
{ 
	 ch=USART2_DR;
}




