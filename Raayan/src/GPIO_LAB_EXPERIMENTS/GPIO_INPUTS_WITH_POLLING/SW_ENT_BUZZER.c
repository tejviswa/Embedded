
/*
Program     : Whenever SW_ENT Press turn ON BUZZER up to 250msec and Turn OFF BUZZER.
File name   : lab_exp_5
Author      : Tejo prapulla
Date        : 11/11/24

Board       : Raayanmini
Controller  : STM32F401RBT6
Version     : 4.0

Pins Used   : PB12, PC10
*/

#include "stm32f401rbt6.h"
#include "gpios.h"

int main()
{
	//Phase1: Device Initialization
	AHB1ENR_init(1);                                  //initialization function call
	AHB1ENR_init(2);
	
	//Phase2: Device Configuration
	MODER_config(1,01,12);                                 //portB configuration function call
	PUPDR_config(2,01,10);                           //configuring pull up resistor for 10th pin
	

	while(1)                                         //super loop
	{
		//Phase3: Device Operation
		if(!(GPIOC_IDR &(0X01<<10)))                    //checking status of the GPIOC_IDR register 10th bit field
		{
		GPIOB_ODR |=(0x01<<12);                        //Set the 12th bit of ODR register to TURN ON the BUZZER
		delay(5);                                        //generating delay of 250ms
		}
		GPIOB_ODR &=~(0x01<<12);													//Clearing the 12th bit of ODR register to TURN OFF the BUZZER
	}
	
}


