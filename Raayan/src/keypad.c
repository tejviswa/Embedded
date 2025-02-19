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


#define ROW 4
#define COL 3

#include "main.h"

char keypad[4][3]={'1','2','3',
									'4','5','6',
									'7','8','9',
									'*','0','#'};

void matrix_keypad_init(void)
{
	PORT_init(A);
	PORT_init(C);
	
	
	MODER_config(A,00,0);        //INPUT MODE PORT A PINS
	MODER_config(A,00,1);
	MODER_config(A,00,4);
	MODER_config(A,00,5);
	
	PUPDR_config(A,01,0);       //PULL UP FOR PORT A PINS
	PUPDR_config(A,01,1);
	PUPDR_config(A,01,4);
	PUPDR_config(A,01,5);
	
	MODER_config(C,01,0);       //OUTPUT MODE PORTC PINS
	MODER_config(C,01,1);
	MODER_config(C,01,2);
	
	GPIOC_ODR |=(0X01<<0);       //BY DEFAULT THE PINS VAULE WILL BE 0 SO MAKING IT HIGH
	GPIOC_ODR |=(0X01<<1);
	GPIOC_ODR |=(0X01<<2);
	
}




char key_scan()
{
	int i,j;
	
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{
			GPIOC_ODR &= ~(0X01<<i);       //CLEARING ODR
			
			if(!(GPIOA_IDR & (0X01<<0)))
			{
				GPIOC_ODR |= (0X01<<i);        //SET BECAUSE NEED TO ACCEPT ANOTHER INPUT
				return keypad[j][i];
			}
			if(!(GPIOA_IDR & (0X01<<1)))
			{
				GPIOC_ODR |= (0X01<<i);       //SET
				return keypad[j][i];
			}
			if(!(GPIOA_IDR & (0X01<<4)))
			{
				GPIOC_ODR |= (0X01<<i);				//SET
				return keypad[j][i];
			}
			if(!(GPIOA_IDR & (0X01<<5)))
			{
				GPIOC_ODR |= (0X01<<i);					//SET
				return keypad[j][i];
			}
			
		}
	}
	
	return 0;
}
	


char key_scan1()
{
	int i,j;
	int arr[4]={0,1,4,5};
	
	for(i=0;i<COL;i++)        //columns 3
	{
		GPIOC_ODR &= ~(0X01<<i);       //CLEARING ODR
		
		for(j=0;j<ROW;j++)       //rows 4
		{
			if((GPIOA_IDR & (0X01<<arr[j]))==0)
			{
				GPIOC_ODR |= (0X01<<i);					//SET
				return keypad[j][i];
				
			}
		}
		
		GPIOC_ODR |= (0X01<<i);					//SET
				
	}
	return 0;
}
				
			
			
		


	
	int main()
	{
		char ch;
		SYSTICK_init();
		KM_LCD_Init();
		
		matrix_keypad_init();
		
		KM_LCD_Write_Cmd(0x80);
		while(1)
		{
			ch=key_scan1();
			if(ch!=0)
			{
				KM_LCD_Write_Data(ch);
			}
			KM_delayms_IT2(150);
		}
		
	}

