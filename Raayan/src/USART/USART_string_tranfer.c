
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

char ch;
char ch1;


void USART2_outchar(unsigned char ch)
{
	while(!(USART2_SR & (0X01<<7)));
	USART2_DR = ch;
}

void USART2_outchar_str(char *ch)
{
	int i=0;
	while(ch[i]!='\0')
	{
		USART2_outchar(ch[i]);
	  i++;
	}
	USART2_outchar('\n');
	USART2_outchar('\r');
	
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


int main()
{
	
	//INITIALIZATION
	PORT_init(A);
	PORT_init(B);
	PORT_init(C);
	SYSTICK_init();
	
	// CONFIGURATION
//	MODER_config(B,01,13);          //PB13,PB14 as ouput mode for LEDS's
//	MODER_config(B,01,14);
//	GPIOB_ODR |=(0X01<<13);
//	GPIOB_ODR |=(0X01<<14);
	
//	PUPDR_config(C,01,8);          //PC8,PC9 configuring PULL UP resistors
//	PUPDR_config(C,01,9);
		PUPDR_config(C,01,10);					//PC10 configuring PULL UP resistors
	
	MODER_config(A,10,2);           //Enabling PA2,PA3 as alternate function mode 
	MODER_config(A,10,3);						//as they are connected to USART pins TX and RX
	
	//Enabling hardware interrrupt for ENT_SW
	SYSCFG_EXTICR3  |=(0x01<<9);
	FTSR(10);
	IMR(10);
	NVIC_ISER1      |=(0X01<<8);  //NVIC ON for ENT_SW
	
	
	GPIOA_AFRL |= (0x7700);           //selecting USART2 from Alternate function for PORT C
	RCC_APB1ENR |=(0X01<<17);             //Enabling clock for USART
	
	
	USART2_BRR |=(0X683);           //Baud rate 
	
	USART2_CR1 |=(0X01<<13);        //USART ON
	USART2_CR1 |=(0X01<<2);         //RE ON
	USART2_CR1 |=(0X01<<3);					//TE ON
	
	USART2_CR1 |=(0X01<<7);					//TXEIE ON
	USART2_CR1 |=(0X01<<5);					//RXEIE ON
	NVIC_ISER1 |= (0X01<<6);         //NVIC ON for USART
	
	
	
	
	//DEVICE OPERATION
	
	while(1)
	{
		;
			
	}
}

void USART2_IRQHandler (void)
{
		USART2_outchar_str("TEJO");
}




//void USART2_IRQHandler(void)
//{
//	if((USART2_SR & (0X01<<7)))
//	{
//		if(!(GPIOC_IDR &(0X01<<8)))
//		{
//			KM_delayms(100);
//			ch='R';
//			USART2_DR =ch;
//		}
//		else if(!(GPIOC_IDR &(0X01<<9)))
//		{
//			KM_delayms(100);
//			ch='G';
//			USART2_DR =ch;
//		}
//	}
//	if((USART2_SR & (0X01<<5)))
//	{
//		ch = USART2_DR;
//		
//		if(ch=='R')
//		{
//			GPIOB_ODR ^=(0X01<<13);
//		}
//		else if(ch=='G')
//		{
//			GPIOB_ODR ^=(0X01<<14);
//		}		
//	}
//}



