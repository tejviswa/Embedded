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

#include "stm32f401rbt6.h"
#include "gpios.h"
#include "lcd.h"
#include "Systic.h"


int main()
{
	int i;
	char str[100]="   WELCOME TO    KERNAL MASTERS";
	char str2[20]={0x0A,0x0A,0x0A,0x04,0x1B,0x1B,0x0E,0x04}; 
  AHB1ENR_init(1);          //port B initialization
	
	SYSTICK_init();
	
	//configuration
	MODER_config(1,01,0);
	MODER_config(1,01,1);
	MODER_config(1,01,2);
	MODER_config(1,01,3);
	MODER_config(1,01,4);
	MODER_config(1,01,5);
	MODER_config(1,01,8);
	
	//device operation
	
	KM_LCD_Init();
	//KM_LCD_Write_Cmd(0x8F);
	//KM_LCD_Write_Str(str);
	
	//custom charcater generation
	KM_LCD_Write_Cmd(0x40);
	custom(str2);
	
	KM_LCD_Write_Cmd(0x86);
	KM_LCD_Write_Data(0);
	
	
	//KM_LCD_Write_Cmd(0x07);
	//KM_LCD_Write_Cmd(0x07);
	//KM_LCD_Write_Cmd(0x07);
	
	
}