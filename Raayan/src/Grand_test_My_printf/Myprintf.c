

#include <stdio.h>
#include <stdarg.h>
#include "main.h"

void Myprintf(char *,...); //Our printf function
char* convert(unsigned int, int); //Convert integer number into octal, hex, etc.

extern char ch;

void USART2_init(void)
{
	PORT_init(A);
	
	MODER_config(A,10,2);           //Enabling PA2,PA3 as alternate function mode 
	MODER_config(A,10,3);						//as they are connected to USART pins TX and RX
	
	
	
	
	GPIOA_AFRL |= (0x7700);           //selecting USART2 from Alternate function for PORT C
	RCC_APB1ENR |=(0X01<<17);             //Enabling clock for USART
	
	
	USART2_BRR |=(0X683);           //Baud rate 
	
	USART2_CR1 |=(0X01<<13);        //USART ON
	USART2_CR1 |=(0X01<<2);         //RE ON
	USART2_CR1 |=(0X01<<3);					//TE ON
	
//	USART2_CR1 |=(0X01<<7);					//TXEIE ON
	USART2_CR1 |=(0X01<<5);					//RXEIE ON
	NVIC_ISER1 |= (0X01<<6);         //NVIC ON for USART
	
	
}



void USART2_IRQHandler (void)
{
		ch=USART2_DR;
}









int main()
{
	char ch2='A';
	int d=10;
	char s[20]="TEJO";
	
	USART2_init();
	//USART2_outchar_str("TEJO");
	
	Myprintf("\n\r decimal      %d",d);
	Myprintf(" \n\r char       %c",ch2);
	Myprintf("  \n\r string   %s",s);
	Myprintf("   \n\r hexa   %x",15);
	Myprintf("    \n\r octa %o",9);
	return 0;
}


void Myprintf(char* format,...)
{
		char *traverse;
		unsigned int i;
		char *s;
		
		//Module 1: Initializing Myprintf's arguments
		va_list arg;
		va_start(arg, format);
	
		for(traverse = format; *traverse != '\0'; traverse++)
		{
			while(*traverse!='%')
			{
				USART2_outchar(*traverse);
				traverse++;
			}
			traverse++;
		
			

			//Module 2: Fetching and executing arguments
			switch(*traverse)
			{
				case 'c': i = va_arg(arg,int); //Fetch char argument
									USART2_outchar(i);
									break;

				case 'd' : i = va_arg(arg,int); //Fetch Decimal/Integer
									if(i<0)
									{
										i=-i;
										USART2_outchar('-');
									}
									USART2_outchar_str(convert(i,10));
									break;
									
				case 'o':i = va_arg(arg,unsigned int); //Fetch Octal representation
									USART2_outchar_str(convert(i,8));
									break;
									
				case 's' :s = va_arg(arg,char *); //Fetch string
									USART2_outchar_str(s);
									break;
									
				case 'x':i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
									USART2_outchar_str(convert(i,16));
									break;
									
								}
							}
		//Module 3: Closing argument list to necessary clean-up
		va_end(arg);
						}

						
char *convert(unsigned int num, int base)
{
	char Representation[]= "0123456789ABCDEF";
	char buffer[50];
	char *ptr;
	ptr = &buffer[49];
	*ptr = '\0';
	
	do
	{
		*--ptr = Representation[num%base];
		num /= base;
	}while(num != 0);
	
	return(ptr);
}
		












































