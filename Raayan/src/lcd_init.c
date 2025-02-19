


#include "main.h"


void KM_LCD_Init(void)
{
	PORT_init(B);
	MODER_config(1,01,0);
	MODER_config(1,01,1);
	MODER_config(1,01,2);
	MODER_config(1,01,3);
	MODER_config(1,01,4);
	MODER_config(1,01,5);
	MODER_config(1,01,8);
	
	KM_delayms_IT2(20);
	KM_LCD_Write_Cmd (0x33);
	KM_delayms_IT2(2);
	KM_LCD_Write_Cmd (0x32);
	KM_LCD_Write_Cmd (0x0C);
	KM_LCD_Write_Cmd (0x01);

}


void KM_LCD_Write_Cmd(unsigned char cmd)
{
	
	GPIOB_ODR &=~(0x01<<4);                  //loading RS with 0  for Instructions
	write_high_nibble(cmd);
	write_low_nibble(cmd);
	
}

void KM_LCD_Write_Data(unsigned char data)
{
	GPIOB_ODR |=(0x01<<4);                  //loading RS with 1  for data
	write_high_nibble(data);
	write_low_nibble(data);
	
}


void KM_LCD_Write_Str(char *ptr)
{
	int i;
	GPIOB_ODR |=(0x01<<4);                  //loading RS with 1  for data	
	for(i=0;ptr[i]!='\0';i++)
	{
		if(i==16)
		{
			KM_LCD_Write_Cmd(0xC0);
		}
		KM_LCD_Write_Data(ptr[i]);
	}
}
		

void write_high_nibble( unsigned char data )
{
	GPIOB_ODR &=(0xFFFFFFF0);
	data=data>>4;
	GPIOB_ODR  |= data & 0x01<<0;
	GPIOB_ODR  |= data & 0x01<<1;
	GPIOB_ODR  |= data & 0x01<<2;
	GPIOB_ODR  |= data & 0x01<<3;
	ODR(1,1,8);                   //loading EN with 1 
	KM_delayms_IT2(10);
	ODR(1,0,8);                   //loading EN with 0 
}


void write_low_nibble( unsigned char data )
{
	GPIOB_ODR &=(0xFFFFFFF0);
	data = data&0x0F;
	GPIOB_ODR  |= data & 0x01<<0;
	GPIOB_ODR  |= data & 0x01<<1; 
	GPIOB_ODR  |= data & 0x01<<2;
	GPIOB_ODR  |= data & 0x01<<3;
	ODR(1,1,8);                   //loading EN with 1 
	KM_delayms_IT2(10);
	ODR(1,0,8);                   //loading EN with 0 
}


void scrolling_left(char *ptr)
{
	int i;
	GPIOB_ODR |=(0x01<<4);                  //loading RS with 1  for data	
	for(i=0;ptr[i]!='\0';i++)
	{
		write_high_nibble(ptr[i]);
		write_low_nibble(ptr[i]);
	}
	
	while(1)
	{
		KM_LCD_Write_Cmd(0x18);
		KM_delayms_IT2(1000);
	}

}


void scrolling_left2(char *ptr)
{
	int i;
	GPIOB_ODR |=(0x01<<4);                  //loading RS with 1  for data	
	for(i=0;ptr[i]!='\0';i++)
	{
		if(i==11)
		{
			KM_LCD_Write_Cmd(0xD9);
			
		}
		KM_LCD_Write_Data(ptr[i]);
	}
	
	while(1)
	{
		KM_LCD_Write_Cmd(0x07);
		KM_delayms_IT2(1000);
	}

}



//itoa function
	
void itoa(char s[],int x)
{
	int y,j,l,i=0;
	char ch;
	while(x)
	{
		y=x%10;
		s[i]=y+'0';
		x=x/10;
		i++;
	}
	s[i]='\0';
	
	for(i=0;s[i]!='\0';i++);
	l=i;
	for(i=0,j=l-1;j>0;i++,j--)
	{
		ch=s[i];
		s[i]=s[j];
		s[j]=ch;
	}

}


void custom (char arr[])
{
	int i;
for(i=0;i<8;i++)
	{
		KM_LCD_Write_Data(arr[i]);
	}
}