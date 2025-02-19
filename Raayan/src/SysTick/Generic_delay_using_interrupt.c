/*
	Program      : Toggle PB13 (RED LED) every 100 msec delay using a SysTick timer using 16 MHZ system clock source.
                 Test the minimum and maximum delays of the 16MHZ timer.
                 Draw flowcharts and write an embedded C program for the below 2 methods
                
                 b. interrupt method 
	File Name    : 
	Author       :  Tejo prapulla
	Date         :  15-NOV-2024
	
 	Board        : RaayanMini
	Controller   : STM32F401RBT6
	Version      : 4.0
	
	Pins Used    : PORT B 13th pin
	               
*/

#include "stm32f401rbt6.h"
#include "Systic.h"

//#define RCC_AHB1ENR *((int *)0x40023830)
//#define GPIOB_MODER *((int *)0x40020400)
//#define GPIOB_ODR   *((int *)0x40020414)
//#define STK_CTRL    *((int *)0xE000E010)
//#define STK_LOAD    *((int *)0xE000E014)
//#define STK_VAL     *((int *)0xE000E018)
	
//Initilization 
void RED_LED_Init(void)
{
	RCC_AHB1ENR |= (0x1<<1);       //Enable the clock signal for GPIO PORTs
}

//Configuration
void RED_LED_Config(void)
{
	GPIOB_MODER &= (0xF3FFFFFF);  //Clearing 27th, 26th pins
	GPIOB_MODER |= (0X04000000);   //Load 01 to 27th, 26th bitfeild to set GPIO PORT B in output direction
	GPIOB_MODER &=~(0x01<<28);
	GPIOB_MODER |= (0x01<<28);
}

////System timer intialization
//void SYS_TICK_Init(void)
//{
//	STK_CTRL |= 0X07;              //0th and 2nd bitfeilds to set the frequency and system timer
//	STK_VAL |=0X05;
//	STK_LOAD |=16000;
//}
//void KM_delayms_IT(int n)
//{
//	
//	STK_LOAD |=(16000*n);
//	while(!(flag));
//	flag=0;
//}

//void KM_delayus_IT(int n)
//{
//	STK_LOAD |=(16*n);
//	while(!(flag));
//	flag=0;
//}

//void KM_delayms(int n)
//{
//	STK_LOAD |=(16000*n);
//	while(!(STK_CTRL & (0x01<<16)));
//}



//void KM_delayus(int n)
//{
//	STK_LOAD |=(16*n);
//	while(!(STK_CTRL & (0x01<<16)));
//}

//void KM_delayms_IT2(int x)
//{
//	int j;
//	j=count+x;
//	while(j>count);
//}






int main()
{
	//Phase 1:Device Initialization
	RED_LED_Init();
	//Phase 2:Device Configuration
	RED_LED_Config();
	SYSTICK_init();
	
	while(1)
	{
		GPIOB_ODR ^= (0x01<<13);
		KM_delayms_IT(100);
	
		GPIOB_ODR ^= (0x01<<14);
		KM_delayms_IT(100);
		
	}
}




