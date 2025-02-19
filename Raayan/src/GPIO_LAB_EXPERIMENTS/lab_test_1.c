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

#define  RCC_AHB1ENR *((int *)0x40023830)
#define  GPIOB_MODER *((int *)0x40020400)
#define  GPIOB_ODR   *((int *)0x40020414)
#define  GPIOB_ODR1   *((int *)0x40020414)
#define  GPIOB_ODR2   *((int *)0x40020414)	

void init()
{
	RCC_AHB1ENR |=(0x01<<1);
}

void config()
{
	GPIOB_MODER &= (0XC0FFFFFF);            //clearing MODER bits 29-24
	GPIOB_MODER |= (0x15000000);            //loading data to set output mode for 1 
}

void delay(int n)
{
	int i;
	for(i=0;i<171000*n;i++);                 //delay for 100ms
}

void buzzer()
{
	int i;
	for(i=0;i<5;i++)
	{
		GPIOB_ODR1 |=(0x01<<12);
		delay(1);
		GPIOB_ODR1 &=~(0x01<<12);
		delay(1);
	}
}

int main()
{
	init ();
	
	config();
	
	while(1)
	{
		GPIOB_ODR &=~(0x01<<13);
		buzzer();
		GPIOB_ODR |=(0x01<<13);
		GPIOB_ODR2 &=~(0x01<<14);
		delay(20);
		GPIOB_ODR2 |=(0x01<<14);

	}
	return 0;
}
		
	



		
	
	
