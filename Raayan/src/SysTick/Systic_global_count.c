/*
	Program      :  Initialize Sys Tick interrupt handler with 1 m sec delay and create a timer global variable to initialize zero. and increment timer global variable inside Sys Tick Handler. In the super loop, wait until the timer global variable reaches 100, once it reaches 100 then toggle RED LED and clear the timer global variable.
                  
	File Name    : 
	Author       :  Tejo prapulla
	Date         : 15-NOV-2024
	
 	Board        : RaayanMini
	Controller   : STM32F401RBT6
	Version      : 4.0
	
	Pins Used    : PORT B 13th pin
	               
*/

#define RCC_AHB1ENR *((int *)0x40023830)
#define GPIOB_MODER *((int *)0x40020400)
#define GPIOB_ODR   *((int *)0x40020414)
#define STK_CTRL    *((int *)0xE000E010)
#define STK_LOAD    *((int *)0xE000E014)
#define STK_VAL     *((int *)0xE000E018)
	
//Initilization 
void RED_LED_Init(void)
{
	RCC_AHB1ENR |= (0x1<<1);       //Enable the clock signal for GPIO PORTs
}

//Configuration
void RED_LED_Config(void)
{
	GPIOB_MODER &= (0xF3FFFFFF);  //Clearing 27th, 26th pins
	GPIOB_MODER |= (0X04000000);   //Load 01 to 27th, 26th bitfeild to set GPIO PORT B in output direction
}

//System timer intialization
void SYS_TICK_Init(void)
{
	STK_CTRL |= 0X07;              //0th and 2nd bitfeilds to set the frequency and system timer
	STK_VAL  |= 0X01;              //Reset the timer with any value
	STK_LOAD |= 16000;           //hardware delay for 100msec
}
int c=0;
int main()
{
	//Phase 1:Device Initialization
	RED_LED_Init();
	//Phase 2:Device Configuration
	RED_LED_Config();
	SYS_TICK_Init();
	
	while(1)
	{
		//device operation
		if(c==100)
		{
			GPIOB_ODR ^= (0x01<<13);
			c=0;
		}
		
	}
}
void SysTick_Handler()
{
	c++;
}

