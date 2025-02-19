/*
Program     : Lab Experiment 3: Whenever SW_UP is pressed RED LED is ON, whenever SW_DN is pressed GREEN LED is ON.
Assign breakpoints after if condition and click run button in debugger window. Whenever SW1/SW2 presses
program stops at any one of the breakpoint
File name   : lab_exp_2
Author      : Tejo prapulla
Date        : 11/11/24

Board       : Raayanmini
Controller  : STM32F401RBT6
Version     : 4.0

Pins Used   : PC8,PC9  PB13,PB14
*/

#include "stm32f401rbt6.h"
#include "gpio.h"



int main()
{
	//Phase1: Device Initialization
	PORTB_init();                                    //PORTB initialization
	PORTC_init();																			//PORTC initialization
	
	//Phase2: Device Configuration
	PORTB13_config();                                 //portB13th pin configuration function call
	PORTB14_config();																//portB14th pin configuration function call
	PORTC_PUPDR8_config();                           //configuring pull up resistor for 8th pin
	PORTC_PUPDR9_config();													 //configuring pull up resistor for 9th pin
	GPIOB_ODR |=(0x01<<13);                          //Set the 13th bit of ODR register to TURN OFF the RED led
	GPIOB_ODR |=(0x01<<14);														//Set the 14th bit of ODR register to TURN OFF the GREEN led
	while(1)                                         //super loop
	{
		//Phase3: Device Operation
		if(!(GPIOC_IDR &(0X01<<8)))                    //checking status of the GPIOC_IDR register 8th bit field
		{
		GPIOB_ODR &=~(0x01<<13);                        //clearing the 13th bit of ODR register to TURN ON the RED LED
			
		}
		if(!(GPIOC_IDR &(0X01<<9)))                    //checking status of the GPIOC_IDR register 9th bit field
		{
		GPIOB_ODR &=~(0x01<<14);                        //clearing the 14th bit of ODR register to TURN ON the GREEN LED
			
		}				
		//delay(10);                                   //generating delay
	}
	return 0;
}
