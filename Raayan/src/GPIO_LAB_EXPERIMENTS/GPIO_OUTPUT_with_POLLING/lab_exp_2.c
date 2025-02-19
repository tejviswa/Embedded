/*
Program     : Airplane wing Lights blinking Delays
							USER LED1 (GREEN): ON (50msec), OFF (50msec), ON (50msec), OFF (150msec) periodically.
							USER LED2 (RED): ON (50msec), OFF (250msec), ON (50msec), OFF (500msec) periodically.
File name   : Lab_exp_2
Author      : Tejo prapulla
Date        : 09/11/24

Board       : Raayanmini
Controller  : STM32F401RBT6
Version     : 4.0

Pins Used   : PortB 13&14
*/

#include "stm32f401rbt6.h"
#include "gpio.h"
	




void delay(int n)
{
	int i;
	for(i=0;i<71500*n;i++);                        //generating  software delay of 50ms
}


int main()
{

	//Phase1: Device Initialization
	PORTB_init();                                  //initialization function call
	
	//Phase2: Device Configuration
	PORTB13_config();                                 //configuration function call
	PORTB14_config();





	while(1)                                         //super loop
	{
		//Phase3: Device Operation
		
		GPIOB_ODR &=~(0x01<<14);               //clearing the 14th bit of ODR register to TURN ON the Green LED
		delay(1);															//generating delay  50ms
		
		GPIOB_ODR |=(0x01<<14);               //Set the 14th bit of ODR register to TURN OFF the Green led
		delay(1);                            //generating delay 50ms
		
		GPIOB_ODR &=~(0x01<<14);           //clearing the 14th bit of ODR register to TURN ON the Green LED
		delay(1);													//generating delay  50ms
		
		GPIOB_ODR |=(0x01<<14);           //Set the 14th bit of ODR register to TURN OFF the Green led
		delay(3);                         //generating delay 50ms
		
		GPIOB_ODR &=~(0x01<<13);          //clearing the 13th bit of ODR register to TURN ON the RED LED
		delay(1);						   						//generating delay  50ms
		
		GPIOB_ODR |=(0x01<<13);            //Set the 13th bit of ODR register to TURN OFF the RED led
		delay(5);                         //generating delay 50ms
	
		GPIOB_ODR &=~(0x01<<13);           //clearing the 13th bit of ODR register to TURN ON the REED LED
		delay(1);													 //generating delay  50ms
		
		GPIOB_ODR |=(0x01<<13);             //Set the 13th bit of ODR register to TURN OFF the RED led
		delay(10);                         //generating delay 50ms
		
		}
		
		return 0;
		}