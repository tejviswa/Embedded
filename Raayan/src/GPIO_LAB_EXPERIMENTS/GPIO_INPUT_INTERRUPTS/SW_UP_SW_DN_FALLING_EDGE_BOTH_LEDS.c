/*
Program     : WAP to request interrupt on the falling edge of SW_ENT(-ve level logic),
							whenever Enter switch pressed,increment counter global variable and Toggle RED LED in ISR. 
File name   : gpio_interrupts
Author      : Tejo prapulla
Date        : 12/11/24

Board       : Raayanmini
Controller  : STM32F401RBT6
Version     : 4.0

Pins Used   : PORT_B13, PORT_C10
*/

#include "stm32f401rbt6.h"
#include "gpios.h"
int count;
int main()
{
	//initialization
	
	AHB1ENR_init(1);                    //portB initilaization
	AHB1ENR_init(2);                    //portC initilaization
	
	//APB2ENR_init(14,1);                 //SYSCFG initilaization
	RCC_APB2ENR |=0x00004000;
	
	//configuration
	MODER_config(1,01,13);              //Red LED configuration
	MODER_config(1,01,14);              //Green LED configuration
	PUPDR_config(2,01,8);                //SW_UP configuration for pull up
	PUPDR_config(2,01,9);                //SW_DN configuration for pull up
	SYSCFG_EXTICR3  |=0x000000220;        //load 0010 to SYSCFG_EXTICR3 register bit fileds 7-4 &3-0 for enabling portC for interrupt
	IMR(8);                          //set 8th bit of EXTI_IMR register for enabling the interrupt line. 
	IMR(9);                          //set 9th bit of EXTI_IMR register for enabling the interrupt line. 

	FTSR(8);                        //set 8th bit of EXTI_FTSR register for enabling the falling edge trigger mode
	FTSR(9);                        //set 9th bit of EXTI_FTSR register for enabling the falling edge trigger mode
	
	NVIC_ISER0  |=(0x01<<23);         //set 23rd bit in ISER1 for enabling the interrupt request for PORTC 10th pin of external interrupt 
	
	GPIOB_ODR |=(0x01<<13);           //initially the LED will be ON after Initialization so turning it OFF
	GPIOB_ODR |=(0x01<<14);           //initially the LED will be ON after Initialization so turning it OFF
	
	while(1)
	{
		//device operation
		;
	}
}

void EXTI9_5_IRQHandler(void) 
{
	if(EXTI_PR &(0x01<<8))       //8th bit will be set if switch is pressed ,checking the status of that bit
	{
		GPIOB_ODR &=~(0x01<<13);        // RED_LED ON
	}
	
	if(EXTI_PR &(0x01<<9))       //9th bit will be set if switch is pressed ,checking the status of that bit
	{
		GPIOB_ODR &=~(0x01<<14);        // GREEN_LED ON
	}
	EXTI_PR |=(0x01<<8);            //at the end of the ISR clear the coresponding EXTI_PR for accepting next interrupt
	EXTI_PR |=(0x01<<9);            //at the end of the ISR clear the coresponding EXTI_PR for accepting next interrupt
	
}
