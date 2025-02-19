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


int main()
{
	char str[100]="  WELCOME TO ";
	char str1[100]=" KERNAL MASTERS";
  AHB1ENR_init(1);          //port B initialization
	
	
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
	KM_LCD_Write_Str(str);
	KM_LCD_Write_Cmd(0xC0);
	KM_LCD_Write_Str(str1);
	
	
	/*
	KM_LCD_Write_Data(0x57);
	KM_LCD_Write_Data(0x45);
	KM_LCD_Write_Data(0x4C);
	KM_LCD_Write_Data(0x43);
	KM_LCD_Write_Data(0x4F);
	KM_LCD_Write_Data(0x4D);
	KM_LCD_Write_Data(0x45);
	KM_LCD_Write_Data(0x20);
	KM_LCD_Write_Data(0x54);
	KM_LCD_Write_Data(0x4F);
	
	
	KM_LCD_Write_Cmd(0xC0);
	
	
	
	KM_LCD_Write_Data(0x4B);
	KM_LCD_Write_Data(0x45);
	KM_LCD_Write_Data(0x52);
	KM_LCD_Write_Data(0x4E);
	KM_LCD_Write_Data(0x41);
	KM_LCD_Write_Data(0x4C);
	KM_LCD_Write_Data(0x20);
	KM_LCD_Write_Data(0x4D);
	KM_LCD_Write_Data(0x41);
	KM_LCD_Write_Data(0x53);
	KM_LCD_Write_Data(0x54);
	KM_LCD_Write_Data(0x45);
	KM_LCD_Write_Data(0x52);
	KM_LCD_Write_Data(0x53);
	*/
}