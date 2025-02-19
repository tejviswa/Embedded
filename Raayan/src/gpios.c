#include "stm32f401rbt6.h"


void PORT_init(int port)
{
	switch(port)
	{
		case 0:RCC_AHB1ENR |=(0x01<<0);break;
		case 1:RCC_AHB1ENR |=(0x01<<1);break;
		case 2:RCC_AHB1ENR |=(0x01<<2);break;
	}
}



void AHB1ENR_init(int port)
{
	switch(port)
	{
		case 0:RCC_AHB1ENR |=(0x01<<0);break;
		case 1:RCC_AHB1ENR |=(0x01<<1);break;
		case 2:RCC_AHB1ENR |=(0x01<<2);break;
	}
}
	

void APB2ENR_init(int device,int mode)
{
	if(mode==1)
		RCC_APB2ENR |=(0x01<<device);
	if(mode==0)
		RCC_APB2ENR &=~(0x01<<device);
	
}

void FTSR(int pin)
{
	EXTI_FTSR |= (0x01<<pin);
}

void IMR(int pin)
{
	EXTI_IMR |= (0x01<<pin);
}


void MODER_config(int port,int mode,int pin)
{
	switch(port)
	{
	  case 0: switch(mode)
						{
							case 00:
								GPIOA_MODER &=~(0x00000003<<pin*2);
								GPIOA_MODER  |=(0X00000000<<pin*2);break;
							case 01:
								GPIOA_MODER &=~(0x00000003<<pin*2);
								GPIOA_MODER  |=(0X00000001<<pin*2);break;
							case 10:
								GPIOA_MODER &=~(0x00000003<<pin*2);
								GPIOA_MODER  |=(0X00000002<<pin*2);break;
							case 11:
								GPIOA_MODER &=~(0x00000003<<pin*2);
								GPIOA_MODER  |=(0X00000003<<pin*2);break;
							}
						break;
		
		case 1: switch(mode)
						{
							case 00:
								GPIOB_MODER &=~(0x00000003<<pin*2);
								GPIOB_MODER  |=(0X00000000<<pin*2);break;
							case 01:
								GPIOB_MODER &=~(0x00000003<<pin*2);
								GPIOB_MODER  |=(0X00000001<<pin*2);break;
							case 10:
								GPIOB_MODER &=~(0x00000003<<pin*2);
								GPIOB_MODER  |=(0X00000002<<pin*2);break;
							case 11:
								GPIOB_MODER &=~(0x00000003<<pin*2);
								GPIOB_MODER  |=(0X00000003<<pin*2);break;
							}
						break;
							
		case 2: switch(mode)
						{
							case 00:
								GPIOC_MODER &=~(0x00000003<<pin*2);
								GPIOC_MODER  |=(0X00000000<<pin*2);break;
							case 01:
								GPIOC_MODER &=~(0x00000003<<pin*2);
								GPIOC_MODER  |=(0X00000001<<pin*2);break;
							case 10:
								GPIOC_MODER &=~(0x00000003<<pin*2);
								GPIOC_MODER  |=(0X00000002<<pin*2);break;
							case 11:
								GPIOC_MODER &=~(0x00000003<<pin*2);
								GPIOC_MODER  |=(0X00000003<<pin*2);break;
							}
						break;
	}
}


void PUPDR_config(int port,int mode,int pin)
{
	switch(port)
	{
	  case 0: switch(mode)
						{
							case 00:
								GPIOA_PUPDR &=~(0x00000003<<pin*2);
								GPIOA_PUPDR  |=(0X00000000<<pin*2);break;
							case 01:
								GPIOA_PUPDR &=~(0x00000003<<pin*2);
								GPIOA_PUPDR  |=(0X00000001<<pin*2);break;
							case 10:
								GPIOA_PUPDR &=~(0x00000003<<pin*2);
								GPIOA_PUPDR  |=(0X00000002<<pin*2);break;
							case 11:
								GPIOA_PUPDR &=~(0x00000003<<pin*2);
								GPIOA_PUPDR  |=(0X00000003<<pin*2);break;
							}
						break;
		case 1: switch(mode)
						{
							case 00:
								GPIOB_PUPDR &=~(0x00000003<<pin*2);
								GPIOB_PUPDR  |=(0X00000000<<pin*2);break;
							case 01:
								GPIOB_PUPDR &=~(0x00000003<<pin*2);
								GPIOB_PUPDR  |=(0X00000001<<pin*2);break;
							case 10:
								GPIOB_PUPDR &=~(0x00000003<<pin*2);
								GPIOB_PUPDR  |=(0X00000002<<pin*2);break;
							case 11:
								GPIOB_PUPDR &=~(0x00000003<<pin*2);
								GPIOB_PUPDR  |=(0X00000003<<pin*2);break;
							}
						break;
			case 2: switch(mode)
						{
							case 00:
								GPIOC_PUPDR &=~(0x00000003<<pin*2);
								GPIOC_PUPDR  |=(0X00000000<<pin*2);break;
							case 01:
								GPIOC_PUPDR &=~(0x00000003<<pin*2);
								GPIOC_PUPDR  |=(0X00000001<<pin*2);break;
							case 10:
								GPIOC_PUPDR &=~(0x00000003<<pin*2);
								GPIOC_PUPDR  |=(0X00000002<<pin*2);break;
							case 11:
								GPIOC_PUPDR &=~(0x00000003<<pin*2);
								GPIOC_PUPDR  |=(0X00000003<<pin*2);break;
							}
						break;
				}
}


void ODR(int port,int mode,int pin)
{
	switch(port)
	{
		case 0:
			switch(mode)
			{
				case 0:GPIOA_ODR &=~(0X01<<pin);break;
				case 1:GPIOA_ODR |= (0X01<<pin);break;
			}
			break;
			
		case 1:
			switch(mode)
			{
				case 0:GPIOB_ODR &=~(0X01<<pin);break;
				case 1:GPIOB_ODR |= (0X01<<pin);break;
			}
			break;
			
		case 2:
			switch(mode)
			{
				case 0:GPIOC_ODR &=~(0X01<<pin);break;
				case 1:GPIOC_ODR |= (0X01<<pin);break;
			}
			break;
		}
	}
		
		
		





