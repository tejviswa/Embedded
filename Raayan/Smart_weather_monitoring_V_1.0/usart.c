#include "../inc/main.h"


 char ch;


//-----------------------------------------
//FUNCTIONS FOR USART2
//-----------------------------------
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



//----------------------------------------------
//FUNCTIONS FOR USART6
//--------------------------------------------


void USART6_outchar(unsigned char ch)
{
	while(!(USART6_SR & (0X01<<7)));
	USART6_DR = ch;
}



void USART6_outchar_str(char *ch)
{
	int i=0;
	while(ch[i]!='\0')
	{
		USART6_outchar(ch[i]);
	  i++;
	}
	USART6_outchar('\n');
	USART6_outchar('\r');
}



unsigned char USART6_inchar_timeout(void)
{
	int i=10000;
	while(i)
	{
		i--;
		if(USART6_SR & 0X01<<5)
		{
			return USART6_DR & 0xFF;
		}
	}
	return 0;
}



unsigned char USART6_inchar_nonblocking(void)
{
	if((USART6_SR & (0X01<<5)))
		return  USART6_DR & 0xFF;
	else 
		return 0;
}














/*
int my_strstr(char str[],char sub[])
{
	int l,in,k,j,i;

	for(i=0;sub[i]!='\0';i++);
	l=i-1;

	for(i=0;str[i]!='\0';i+l)
	{
		for(j=l,k=i;j>=0;j--,k++)
		{
			if(sub[j]==str[k])
				in=k;
			return in;
		}
	}
}
*/

