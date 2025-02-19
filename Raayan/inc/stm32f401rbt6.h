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
#define USART6_BASE_ADDR   0X40011400

//I2C BASE ADDRESSES
#define I2C1_BASE_ADDR     0X40005400
#define I2C2_BASE_ADDR     0X40005800
#define I2C3_BASE_ADDR     0X40005C00

//SPI BASE ADDRESSES
#define SPI1_BASE_ADDR    0X40013000
#define SPI2_BASE_ADDR    0X40003800


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


//PHY ADDR OF  USART6 REGISTERS
#define USART6_SR   *(int*)(USART6_BASE_ADDR + 0x00)
#define USART6_DR   *(int*)(USART6_BASE_ADDR + 0x04)
#define USART6_BRR   *(int*)(USART6_BASE_ADDR + 0x08)
#define USART6_CR1   *(int*)(USART6_BASE_ADDR + 0x0C)


//PHY ADDR OF SPI1
#define SPI1_CR1       *(int*)(SPI1_BASE_ADDR + 0x00)
#define SPI1_CR2       *(int*)(SPI1_BASE_ADDR + 0x04)
#define SPI1_SR        *(int*)(SPI1_BASE_ADDR + 0x08)
#define SPI1_DR        *(int*)(SPI1_BASE_ADDR + 0x0C)
#define SPI1_CRCPR     *(int*)(SPI1_BASE_ADDR + 0x10)
#define SPI1_RXCRCR    *(int*)(SPI1_BASE_ADDR + 0x14)
#define SPI1_TXCRCR    *(int*)(SPI1_BASE_ADDR + 0x18)
#define SPI1_I2SCFGR   *(int*)(SPI1_BASE_ADDR + 0x1C)
#define SPI1_I2SPR     *(int*)(SPI1_BASE_ADDR + 0x20)


//PHY ADDR OF SPI2
#define SPI2_CR1       *(int*)(SPI2_BASE_ADDR + 0x00)
#define SPI2_CR2       *(int*)(SPI2_BASE_ADDR + 0x04)
#define SPI2_SR        *(int*)(SPI2_BASE_ADDR + 0x08)
#define SPI2_DR        *(int*)(SPI2_BASE_ADDR + 0x0C)
#define SPI2_CRCPR     *(int*)(SPI2_BASE_ADDR + 0x10)
#define SPI2_RXCRCR    *(int*)(SPI2_BASE_ADDR + 0x14)
#define SPI2_TXCRCR    *(int*)(SPI2_BASE_ADDR + 0x18)
#define SPI2_I2SCFGR   *(int*)(SPI2_BASE_ADDR + 0x1C)
#define SPI2_I2SPR     *(int*)(SPI2_BASE_ADDR + 0x20)
	
/*
===========================================================
               PHY ADDR OF I2C
===========================================================
-------------
     I2C1
-------------
*/
#define I2C1_CR1       *(int*)(I2C1_BASE_ADDR + 0x00)
#define I2C1_CR2       *(int*)(I2C1_BASE_ADDR + 0x04)
#define I2C1_OAR1      *(int*)(I2C1_BASE_ADDR + 0x08)
#define I2C1_OAR2      *(int*)(I2C1_BASE_ADDR + 0x0C)
#define I2C1_DR        *(int*)(I2C1_BASE_ADDR + 0x10)
#define I2C1_SR1       *(int*)(I2C1_BASE_ADDR + 0x14)
#define I2C1_SR2       *(int*)(I2C1_BASE_ADDR + 0x18)
#define I2C1_CCR       *(int*)(I2C1_BASE_ADDR + 0x1C)
#define I2C1_TRISE     *(int*)(I2C1_BASE_ADDR + 0x20)
#define I2C1_FLTR      *(int*)(I2C1_BASE_ADDR + 0x24)

/*
-------------
     I2C2
-------------
*/
#define I2C2_CR1       *(int*)(I2C2_BASE_ADDR + 0x00)
#define I2C2_CR2       *(int*)(I2C2_BASE_ADDR + 0x04)
#define I2C2_OAR1      *(int*)(I2C2_BASE_ADDR + 0x08)
#define I2C2_OAR2      *(int*)(I2C2_BASE_ADDR + 0x0C)
#define I2C2_DR        *(int*)(I2C2_BASE_ADDR + 0x10)
#define I2C2_SR1       *(int*)(I2C2_BASE_ADDR + 0x14)
#define I2C2_SR2       *(int*)(I2C2_BASE_ADDR + 0x18)
#define I2C2_CCR       *(int*)(I2C2_BASE_ADDR + 0x1C)
#define I2C2_TRISE     *(int*)(I2C2_BASE_ADDR + 0x20)
#define I2C2_FLTR      *(int*)(I2C2_BASE_ADDR + 0x24)



//PHY ADDR OF SYSCFG
#define SYSCFG_EXTICR3  *(int*)(SYSCFG_BASE_ADDR + 0x10)
	
//PHY ADDR OF EXTERNAL INTERRUPTS
#define EXTI_IMR      *(int*)(EXTI_BASE_ADDR +0X00)
#define EXTI_PR       *(int*)(EXTI_BASE_ADDR +0X14)
#define EXTI_FTSR     *(int*)(EXTI_BASE_ADDR +0X0C)

//PHY ADDR OF NVIC_ISER
#define NVIC_ISER0    *(int*)(NVIC_BASE_ADDR +0X00)
#define NVIC_ISER1    *(int*)(NVIC_BASE_ADDR +0X04)
#define NVIC_ISER2    *(int*)(NVIC_BASE_ADDR +0X08)	
#define NVIC_ISER3    *(int*)(NVIC_BASE_ADDR +0X0C)

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
#define GPIOB_AFRL    *(int*)(GPIOB_BASE_ADDR + 0x20)
#define GPIOB_AFRH    *(int*)(GPIOB_BASE_ADDR + 0x24)
#define GPIOB_SPEEDR  *(int*)(GPIOB_BASE_ADDR + 0x08)
#define GPIOB_OTYPER  *(int*)(GPIOB_BASE_ADDR + 0x04)



//GPIOC    MODER,ODR,IDR,PUPDR
#define GPIOC_MODER   *(int*)(GPIOC_BASE_ADDR + 0x00)
#define GPIOC_ODR     *(int*)(GPIOC_BASE_ADDR + 0x14)
#define GPIOC_PUPDR   *(int*)(GPIOC_BASE_ADDR + 0x0C)
#define GPIOC_IDR     *(int*)(GPIOC_BASE_ADDR + 0x10)
#define GPIOC_AFRL    *(int*)(GPIOC_BASE_ADDR + 0x20)
#define GPIOC_AFRH    *(int*)(GPIOC_BASE_ADDR + 0x24)








