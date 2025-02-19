
#include "../inc/main.h"


void KM_ADC_Init(void)
{
	PORT_init(C);                            //Clock to port C
	APB2ENR_init(8,1);                       //Clock to ADC1
	SYSTICK_init();
	KM_LCD_Init();
	
	//Configuration
	GPIOC_MODER |=(0x00000003);                //PC0 as Analog mode
	GPIOC_MODER |=(0x0000000C);               //PC1 as Analog mode
	ADC_SQR1 |=(0x01<<20);                    //Length field
	ADC_SQR3 |=(0x0A);                       //PC0 as ADC_10 channel
	ADC_SQR3 |=(0x160);                      //PC1 as ADC_11 channel
	//EOCS_config(1);
	ADC_CR1 |=(0X01<<8);			        //SCAN mode ON
	ADC_CR1 |=(0X01<<5);              //EOCIE ON
	ADC_CR2 |=(0X01<<10);              //EOCS ON
	
	//ADC_CR2 |= (0X01<<1);
	NVIC_ISER0 |=(0X01<<18);           //ADC interrupt line
	
	ADC_CR2 |=0x01;                 // ADC  ON

}



extern int temp;
void KM_ADC_Read(void)
{
	temp = (ADC_DR*330)/4096;
}
