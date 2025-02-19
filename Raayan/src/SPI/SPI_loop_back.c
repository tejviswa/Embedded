



/*
Program     :SPI loop back ckecking
File name   :
Author      : Tejo prapulla
Date        :

Board       : Raayanmini
Controller  : STM32F401RBT6
Version     :  4.0

Pins Used   :
*/


#include "../inc/main.h"

char ch='A';
char ch2;



#define  RXNE    (0X01<<0)
#define  TXE     (0X01<<1)





void SPI2_outchar(char ch)
{
	while(!(SPI2_SR & (0X01<<1)));           //TXE
	SPI2_DR = ch;
}


unsigned char SPI2_inchar_nonblocking(void)
{
	char ch3;
	if(SPI2_SR & (0X01<<0))       //RXNE
		ch3 = SPI2_DR;
	return  ch3 ;
}





int main()
{
		
	//DEVICE INITIALIZATION
	SYSTICK_init();
	//SPI2_init();
	
	PORT_init(B);                         //clock to port B
	PORT_init(C);														//clock to port C
	RCC_APB1ENR |=(0x01<<14);                 //clock to SPI2


	
	//Device configuration
	
	//SPI2_config();
	MODER_config(C,10,2);									//PC2 AS ALTERNATE FUNCTION MODE
	MODER_config(C,10,3);									//PC3 AS ALTERNATE FUNCTION MODE
	MODER_config(C,01,4);									//PC4 AS output FUNCTION MODE
	MODER_config(B,10,10);               //PB10 AS ALTERNATE FUNCTION MODE
	
	GPIOC_AFRL |=(0X00000500);          //FOR PC2 AS SPI2_MISO
	GPIOC_AFRL |=(0X00005000);		      //FOR PC3 AS SPI2_MOSI
	GPIOB_AFRH |=(0X00000500);		      //FOR PB10 AS SPI2_SCK
	
	
	//SPI2_CR1 |=(0X00000000);          //3,4,5 BITS FOR BAUD RATE CONTROL
	
	SPI2_CR1 &=~(0X01<<11);          //11TH BIT '0' FOR 8BIT DATA FORMAT : This bit should be written only when SPI is disabled (SPE = ‘0’)
	
	
	SPI2_CR1 &=~(0X01<<0);          //O(CPHA),1(CPOL) BITS FOR '0' 
	SPI2_CR1 &=~(0X01<<1);
	
	
	SPI2_CR1 |=(0X01<<9);          //FOR SSM(SOFTWARE SLAVE MANAGEMENT)
	SPI2_CR1 |=(0X01<<8);          //FOR SSI(INTERNAL SLAVE SELECT)
	SPI2_CR1 |=(0X01<<2);          //TO SELECT MASTER MODE
	//SPI2_CR2 |=(0x01<<4);
	SPI2_CR1 |=(0X01<<6);               //SPI ENABLE

	

	//device operation

	while(1)
	{
		SPI2_outchar(ch);
		//SPI2_DR=ch;
		
		//ch2=SPI2_DR;
		SPI2_inchar_nonblocking();
			
		KM_delayms_IT2(1000);
		ch++;
	}
	
	
}
