
#include "main.h"

#define  RXNE      (0X01<<0)
#define  TXE       (0X01<<1)
#define SPI2_INIT   RCC_APB1ENR |=(0x01<<14); 

//unsigned char ch3;

void SPI2_init(void)
{
	PORT_init(B);                         //clock to port B
	PORT_init(C);														//clock to port C
	SPI2_INIT                               //clock to SPI2
}


void SPI2_config(void)
{
	
	MODER_config(C,10,2);									//PC2 AS ALTERNATE FUNCTION MODE
	MODER_config(C,10,3);									//PC3 AS ALTERNATE FUNCTION MODE
	MODER_config(C,01,4);									//PC4 AS output FUNCTION MODE
	MODER_config(B,10,10);               //PB10 AS ALTERNATE FUNCTION MODE
	
	GPIOC_AFRL |=(0X00000500);          //FOR PC2 AS SPI2_SCK
	GPIOC_AFRL |=(0X00005000);		      //FOR PC3 AS SPI2_MISO
	GPIOC_AFRH |=(0X00000500);		      //FOR PB10 AS SPI2_MOSI
	
	
	SPI2_CR1 |=(0X00000000);          //3,4,5 BITS FOR BAUD RATE CONTROL
	
	SPI2_CR1 &=~(0X01<<11);          //11TH BIT '0' FOR 8BIT DATA FORMAT : This bit should be written only when SPI is disabled (SPE = ‘0’)
	
	
	SPI2_CR1 &=~(0X01<<0);          //O(CPHA),1(CPOL) BITS FOR '0' 
	SPI2_CR1 &=~(0X01<<1);
	
	
	SPI2_CR1 |=(0X01<<9);          //FOR SSM(SOFTWARE SLAVE MANAGEMENT)
	SPI2_CR1 |=(0X01<<8);          //FOR SSI(INTERNAL SLAVE SELECT)
	SPI2_CR1 |=(0X01<<2);          //TO SELECT MASTER MODE
	//SPI2_CR2 |=(0x01<<4);
	SPI2_CR1 |=(0X01<<6);               //SPI ENABLE

}


void SPI2_Slave_Bus_Init1(void)
{
	RCC_APB1ENR |=(0x01<<14);        //Enable the clock for SPI2
	GPIOC_AFRL |= 0x00000500;     //convert as SPI2 MISO
	GPIOC_AFRL |= 0x00005000;     //convert as SPI2 MOSI
	GPIOB_AFRH |= 0x00000500;     //convert as SPI2 SCK
	
	SPI2_CR1   |= 0x00000000;     //set baud rate by clearing 3,4,5 bit fields

	SPI2_CR1   &= ~(0x01<<11);    //set the data frame format by clearing the 11 bit field
	SPI2_CR1   &= ~(0x01<<0);     //CPHA = 0
	SPI2_CR1   &= ~(0x01<<1);     //CPOL = 0
	//SPI2_CR1   |=   0x01<<2;      //set as MASTER

	SPI2_CR1   |=   0x01<<9;      //set as software slave mode
	SPI2_CR1   &=   ~(0x01<<8);   //clear the Internal slave select
	//SPI2_CR2   |=   0x01<<4;      //SPI TI mode  
	SPI2_CR1   &=   ~(0x01<<2);      
	SPI2_CR2   |=   0x01<<6;      //enable interupt pin for receiver
	SPI2_CR1   |=   0x01<<6;      //SPI2 enable
}


void SPI2_outchar(char ch)
{
	while(!(SPI2_SR & TXE));
	SPI2_DR = ch;
}


void SPI2_outchar_str(char *ch)
{
	int i=0;
	while(ch[i]!='\0')
	{
		SPI2_outchar(ch[i]);
	  i++;
	}
}




unsigned char SPI2_inchar(void)
{
	while(!(SPI2_SR & RXNE));
	return SPI2_DR;
}


unsigned char SPI2_inchar_timeout(void)
{
	int i=100000;
	while(i)
	{
		i--;
		if(SPI2_SR & RXNE)
		{
			return SPI2_DR ;
		}
	}
	return 0;
}



//unsigned char SPI2_inchar_nonblocking(void)
//{
//	if(SPI2_SR & RXNE)
//		ch3=SPI2_DR;
//		return  ch3 ;
//}







