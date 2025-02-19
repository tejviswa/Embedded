
#include "main.h"

#define START_BIT        (I2C1_CR1 |=(0x01<<8))
#define STOP_BIT         (I2C1_CR1 |=(0x01<<9))

#define START_BIT_FLAG   (I2C1_SR1 &(0x01<<0))
#define BUSY_FLAG        (I2C1_SR2 &(0x01<<1))
#define ADDR_FLAG        (I2C1_SR1 & (0x01<<1))
#define AF_FLAG 				 (I2C1_SR1 & (0x01<<10))
#define TXE_FLAG   			 (I2C1_SR1 & (0X01<<7))

int i,k=0;
int temp;
int dum;
int arr[5];

unsigned char buff[8]={12,2};

void I2C1_init(void)
{
	//INITIALIZATION
	
	
	PORT_init(B);                         //clock to port B
	
	MODER_config(B,10,6);               //PB6 AS ALTERNATE FUNCTION MODE
	MODER_config(B,10,7);               //PB7 AS ALTERNATE FUNCTION MODE
	
	GPIOB_AFRL |=(0x40000000);          //FOR PB6 AS I2C1_SCL
	GPIOB_AFRL |=(0x04000000);          //FOR PB7 AS I2C1_SDA
	
	GPIOB_PUPDR &=(0x0);
	
	PUPDR_config(B,01,6);              // PULL UP  FOR PB6 
	PUPDR_config(B,01,7);             //PULL UP FOR PB7
	
	//GPIOB_SPEEDR |=(0X02<<12);          //HIGH SPEED FOR PB6
	//GPIOB_SPEEDR |=(0X02<<14);					//HIGH SPEED FOR PB7
	
	GPIOB_OTYPER |=(0x01<<6);            //OPEN DRAIN FOR PB6
	GPIOB_OTYPER |=(0x01<<7);							//OPEN DRAIN FOR PB7

}


void I2C1_config(void)
{
		//CONFIGURATION
	RCC_APB1ENR |=(0x01<<21);                 //CLOCK TO I2C1
	I2C1_CCR =(0x50);                  //for 100Khz
	I2C1_CR2 =(0x10);                   //peripheral clock frequency 16MHz
			
	I2C1_CR1 |=(0x01<<10);                     //Ack enable
	I2C1_TRISE =(0x11);               //for SDA and SCL to be idle
	
	I2C1_CR1 |=(0x01);                 //for PE enable
		
}




int KM_I2C1_IsDeviceReady(short int DevAddr,int Timeout)
{
	int j;
	while(BUSY_FLAG);                   //BUSY FLAG 0 INDICATES NO COMMUNICATION ONGOING THEN WE CAN CHECK THE AVAILABLE DEVICES
	I2C1_CR1 &=~(0x01);                 //for PE disable
	I2C1_CR1 |=(0x01);                 //for PE enable
	I2C1_CR1 |=(0x01<<10);               //Ack enable
	
	START_BIT;        							 //SET START BIT
	
	while(!START_BIT_FLAG);    //checking SB bit to check whether the start condition is generated or not
	
	dum = I2C1_SR1;
	dum = I2C1_SR2;
	
	
	I2C1_DR =(DevAddr<<1);     //loading device address to data register
	
	for(j=0;j<Timeout;j++)
	{
	while(!(ADDR_FLAG) && !(AF_FLAG));
	if(ADDR_FLAG)
	{
		dum = I2C1_SR1;
		dum = I2C1_SR2;
		STOP_BIT;
		return 0;
	}
	}
	STOP_BIT;
	return 1;
}
	
	
int DECIMAL_TO_BCD(unsigned int x)
{
	int res,res1,res2;
	res1=x%10;
	res2=x/10;
	res=res1|(res2<<4);
	
	return res;
}
	

void KM_I2C_scan(void)
{
	             
	for(i=0;i<128;i++)              //SLAVE DEVICE ADDR IS 7_BIT LENGTH SO CHECKING FOR 2^7=128 SUPPORTED DEVICES
	{
		temp = KM_I2C1_IsDeviceReady(i,1000);
		if(temp==0)
		{
			KM_LCD_Write_Cmd(0x01);
		
			arr[k]=i;
			if(i==0x50)
				KM_LCD_Write_Str("EEPROM FOUND");
			KM_delayms_IT2(2000);
			KM_LCD_Write_Cmd(0x01);
			if(i==0x68)
				KM_LCD_Write_Str("RTC FOUND");
			KM_delayms_IT2(2000);
			k++;
		}
		
	}
	
}




int KM_I2C1_RTC_MemWrite(short int DevAddr,short int MemAddr,short int MemAddrSize,unsigned char *data,short int length)
{
	//=======================
	//SCAN MODE
	//=========================
	
	while(BUSY_FLAG);                   //BUSY FLAG 0 INDICATES NO COMMUNICATION ONGOING THEN WE CAN CHECK THE AVAILABLE DEVICES
	I2C1_CR1 &=~(0x01);                 //for PE disable
	I2C1_CR1 |=(0x01);                 //for PE enable
	I2C1_CR1 |=(0x01<<10);               //Ack enable
	
	START_BIT;        							 //SET START BIT
	
	while(!START_BIT_FLAG);    //checking SB bit to check whether the start condition is generated or not
	
	dum = I2C1_SR1;
	dum = I2C1_SR2;
	
	
	I2C1_DR =(DevAddr<<1);     //loading device address to data register
	
	
	while(!(ADDR_FLAG) && !(AF_FLAG));
	if(ADDR_FLAG)
	{
	KM_LCD_Write_Cmd(0x01);
	KM_LCD_Write_Str("RTC FOUND");
	KM_delayms_IT2(1000);
	}
	
	//==============================
	// RTC WRITE
	//==============================
	
	dum = I2C1_SR1;
	dum = I2C1_SR2;
	
	while(!TXE_FLAG);        //CHECKING TXE FLAG
	
	dum = I2C1_SR1;
	dum = I2C1_SR2;
	
	I2C1_DR = MemAddr;         //loading MemAddr to Data register

	for(i=0;i<length;i++)
	{
		while(!TXE_FLAG);            //CHECKING TXE FLAG

		I2C1_DR = DECIMAL_TO_BCD(data[i]);
		while(!(I2C1_SR1 & (0X01<<2)));        //BTF FLAG CHECKING
	}
	
	STOP_BIT;
	return 0;
}



int main()
{
	int l;
	//DEVICE OPERATION
	
	I2C1_init();
	I2C1_config();
	SYSTICK_init();
	KM_LCD_Init();
	
	
	while(1)
	{
		//l=KM_I2C1_RTC_MemWrite(0x68,0x00,1,buff,2);
		KM_I2C_scan();
		if(l==0)
		{
			KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("write success");
			KM_delayms_IT2(1000);
		}
	}
	
}










