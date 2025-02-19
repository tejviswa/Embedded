
/*
Program     : Read SW_ENT, if switch is press RED LED is ON otherwise RED LED is OFF. Note that RED LED
							should remain ON for the duration switch is kept pressed i.e. RED LED should turn OFF when switch is released.
File name   : lab_exp_5
Author      : Tejo prapulla
Date        : 11/11/24

Board       : Raayanmini
Controller  : STM32F401RBT6
Version     : 4.0

Pins Used   : PB13, PC10
*/

#include "stm32f401rbt6.h"
#include "gpio.h"




int main()
{
	//Phase1: Device Initialization
	PORTB_init();                                  //initialization function call
	PORTC_init();
	
	//Phase2: Device Configuration
	PORTB13_config();                                 //portB configuration function call
	PORTC_PUPDR10_config();                           //configuring pull up resistor for 10th pin
	//GPIOB_ODR |=(0x01<<13);                          //Set the 13th bit of ODR register to TURN OFF the RED led

	while(1)                                         //super loop
	{
		//Phase3: Device Operation
		if(!(GPIOC_IDR &(0X01<<10)))                    //checking status of the GPIOC_IDR register 10th bit field
		{
		GPIOB_ODR &=~(0x01<<13);                        //clearing the 13th bit of ODR register to TURN ON the RED LED
		}
		GPIOB_ODR |=(0x01<<13);													//Set the 13th bit of ODR register to TURN OFF the RED led
		//delay(3);                                   //generating delay
	}
	return 0;
}






