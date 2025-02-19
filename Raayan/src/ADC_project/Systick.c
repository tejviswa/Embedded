
#include "stm32f401rbt6.h"


//System timer intialization
void SYSTICK_init(void)
{
	STK_CTRL |= 0X07;              //0th and 2nd bitfeilds to set the frequency and system timer
	STK_VAL |=0X05;
	STK_LOAD |=16000;
}





//Delay functions using Systick Delay
void KM_delayms(int n)
{
	STK_LOAD |=(16000*n);
	while(!(STK_CTRL & (0x01<<16)));
}



void KM_delayus(int n)
{
	STK_LOAD |=(16*n);
	while(!(STK_CTRL & (0x01<<16)));
}



int flag;
 int count;

void KM_delayms_IT(int n)
{
	
	STK_LOAD |=(16000*n);
	while(!(flag));
	flag=0;
}

void KM_delayus_IT(int n)
{
	STK_LOAD |=(16*n);
	while(!(flag));
	flag=0;
}

void KM_delayms_IT2(int x)
{
	int j;
	j=count+x;
	while(j>count);
}


void SysTick_Handler(void)
{
	flag=1;
	count++;
}









