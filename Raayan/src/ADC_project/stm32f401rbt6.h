/*
Filename : stm32f401rbt6.h
descrpition : Contains board specific details(base addresses and physical addresses of devices)

PHYSICAL ADDRESS OF REGISTER = BASE ADDRESS OF DEVICE  +  OFFSET ADDRESS OF REGISTER 

*/


//BASE ADDRESSES OF PERIPPHERAL BUS
#define APB1_BASE_ADDR   0x40000000
#define APB2_BASE_ADDR   0x40010000
#define AHB1_BASE_ADDR   0x40020000
#define AHB2_BASE_ADDR   0x50000000

//BASE ADDRESS OF RCC
#define RCC_BASE_ADDR   0X40023800



//BASE ADDRESSES OF GPIO PORTS
#define GPIOA_BASE_ADDR  AHB1_BASE_ADDR
#define GPIOB_BASE_ADDR  0x40020400
#define GPIOC_BASE_ADDR  0x40020800


//BASE ADDRESS OF SYSTEM CONFIG
#define SYSCFG_BASE_ADDR  0x40013800

//BASE ADDRESS OF EXTERNAL INTERRUPT
#define EXTI_BASE_ADDR   0x40013C00

	
//BASE ADDR OF NVIC
#define NVIC_BASE_ADDR  0xE000E100 



//ADC BASE ADDRESSES
#define ADC_BASE_ADDR 0x40012000

//USART BASE ADDRESSES
#define USART2_BASE_ADDR   0X40004400

//I2C BASE ADDRESSES


//SPI BASE ADDRESSES

//===============================PHYSICAL ADDRESS========================
//RCC     APB1ENR,APB2ENR
#define RCC_AHB1ENR      *(int*)(RCC_BASE_ADDR + 0x30)            //offest is 0x30 for GPIO ports
#define RCC_APB2ENR      *(int*)(RCC_BASE_ADDR + 0x44)
#define	RCC_APB1ENR      *(int*)(RCC_BASE_ADDR + 0x40)
	
//PHY OF SYSTick timer
#define STK_CTRL    *((int *)0xE000E010)
#define STK_LOAD    *((int *)0xE000E014)
#define STK_VAL     *((int *)0xE000E018)

//PHY ADDR OF ADC Registers
#define ADC_SR     *(int*)(ADC_BASE_ADDR + 0x00)
#define ADC_CR1    *(int*)(ADC_BASE_ADDR + 0x04)
#define ADC_CR2    *(int*)(ADC_BASE_ADDR + 0x08)
#define ADC_SQR1   *(int*)(ADC_BASE_ADDR + 0x2C)
#define ADC_SQR2   *(int*)(ADC_BASE_ADDR + 0x30)
#define ADC_SQR3   *(int*)(ADC_BASE_ADDR + 0x34)
#define ADC_DR     *(int*)(ADC_BASE_ADDR + 0x4C)
#define ADC_SMPR1  *(int*)(ADC_BASE_ADDR + 0x10)
#define ADC_SMPR2  *(int*)(ADC_BASE_ADDR + 0x0C) 	


//PHY ADDR OF  USART2 REGISTERS
#define USART2_SR   *(int*)(USART2_BASE_ADDR + 0x00)
#define USART2_DR   *(int*)(USART2_BASE_ADDR + 0x04)
#define USART2_BRR   *(int*)(USART2_BASE_ADDR + 0x08)
#define USART2_CR1   *(int*)(USART2_BASE_ADDR + 0x0C)



//PHY ADDR OF SYSCFG
#define SYSCFG_EXTICR3  *(int*)(SYSCFG_BASE_ADDR + 0x10)
	
//PHY ADDR OF EXTERNAL INTERRUPTS
#define EXTI_IMR      *(int*)(EXTI_BASE_ADDR +0X00)
#define EXTI_PR       *(int*)(EXTI_BASE_ADDR +0X14)
#define EXTI_FTSR     *(int*)(EXTI_BASE_ADDR +0X0C)

//PHY ADDR OF NVIC_ISER
#define NVIC_ISER0    *(int*)(NVIC_BASE_ADDR +0X00)
#define NVIC_ISER1    *(int*)(NVIC_BASE_ADDR +0X04)
	

//GPIOA    MODER,ODR,IDR,PUPDR
#define GPIOA_MODER   *(int*)(GPIOA_BASE_ADDR + 0x00)
#define GPIOA_ODR     *(int*)(GPIOA_BASE_ADDR + 0x14)
#define GPIOA_PUPDR   *(int*)(GPIOA_BASE_ADDR + 0x0C)
#define GPIOA_IDR     *(int*)(GPIOA_BASE_ADDR + 0x10)
#define GPIOA_AFRL    *(int*)(GPIOA_BASE_ADDR + 0x20)
#define GPIOA_AFRH    *(int*)(GPIOA_BASE_ADDR + 0x24)


//GPIOB    MODER,ODR,IDR,PUPDR
#define GPIOB_MODER   *(int*)(GPIOB_BASE_ADDR + 0x00)
#define GPIOB_ODR     *(int*)(GPIOB_BASE_ADDR + 0x14)
#define GPIOB_PUPDR   *(int*)(GPIOB_BASE_ADDR + 0x0C)
#define GPIOB_IDR     *(int*)(GPIOB_BASE_ADDR + 0x10)


//GPIOC    MODER,ODR,IDR,PUPDR
#define GPIOC_MODER   *(int*)(GPIOC_BASE_ADDR + 0x00)
#define GPIOC_ODR     *(int*)(GPIOC_BASE_ADDR + 0x14)
#define GPIOC_PUPDR   *(int*)(GPIOC_BASE_ADDR + 0x0C)
#define GPIOC_IDR     *(int*)(GPIOC_BASE_ADDR + 0x10)
	






