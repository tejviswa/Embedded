/*
Program     : Toggle RED LED ON time is 50ms and RED LED OFF time is 1300ms
File name   : Lab_exp_1
Author      : Tejo prapulla
Date        : 9/11/24

Board       : Raayanmini
Controller  : STM32F401RBT6
Version     : 4.0

Pins Used   : PortB 13th pin
*/


#include "stm32f401rbt6.h"
#include "gpio.h"


void delay(int n)
{
	int i;
	for(i=0;i<71400*n;i++);                        //generating  software delay
}

int main()
{
	//Phase1: Device Initialization
	PORTB_init();                                  //initialization function call
	
	//Phase2: Device Configuration
	PORTB13_config();                                 //configuration function call
	
	while(1)                                         //super loop
	{
		//Phase3: Device Operation
		GPIOB_ODR &=~(0x01<<13);                    //clearing the 13th bit of ODR register to TURN ON the RED LED
		delay(1);		                                //generating delay 50ms
		
		GPIOB_ODR |=(0x01<<13);                    //Set the 13th bit of ODR register to TURN OFF the RED led
		delay(26);                                   //generating delay 1300ms
	}
	return 0;
}









