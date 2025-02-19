
#include "../inc/main.h"


void WiFi_init(void)
{
		MODER_config(C,10,6);           //Enabling PC6,PC7 as alternate function mode as they are connected to USART 6
	MODER_config(C,10,7);
	
	GPIOC_AFRL |= (0x88000000);           //selecting USART6 from Alternate function for PORT C
	RCC_APB2ENR |=(0X01<<5);             //Enabling clock for USART6
	
	
	USART6_BRR |=(0X8B);           //Baud rate  for WiFi
	
	
	USART6_CR1 |=(0X01<<13);        //USART6 ON
	USART6_CR1 |=(0X01<<2);         //RE ON
	USART6_CR1 |=(0X01<<3);					//TE ON

}




//================================
//WIFI OK RESPONSE
//=================================

char usart6_rxbuff[1500];



void clearbuff(void)
{
	int i;
	for(i=0;usart6_rxbuff[i]!='\0';i++)
	{
		usart6_rxbuff[i]=0;
	}
}

//RST respnse function
int RST_response(void)
{
	int i=0;
	while(i<1000)
	{
		usart6_rxbuff[i] = USART6_inchar_timeout();
		if(i>=5 && usart6_rxbuff[i-5] =='r' && usart6_rxbuff[i-4] =='e'&& usart6_rxbuff[i-3] =='a'&& usart6_rxbuff[i-2] =='d'&& usart6_rxbuff[i-1] =='y')
		{
			return 1;
		}
		i++;
	}
	KM_delayms_IT2(5000);
	return 0;
}






int  WiFi_OK_response(void)
{
	int i=0;
	char temp;
	
	while(1)
	{
		temp=USART6_inchar_timeout();
		if(temp==0)
		return 0;        //ERROR
		
		usart6_rxbuff[i]=temp;
		if((usart6_rxbuff[i]=='K') && (usart6_rxbuff[i-1]=='O'))
			return 1;        //SUCCESS
		i++;
		
	}
}



int  WiFi_STRok_response(void)
{
	int i=0;
	char temp;
	
	while(1)
	{
		temp=USART6_inchar_timeout();
		if(temp==0)
		return 0;        //ERROR
		
		usart6_rxbuff[i]=temp;
		if(mstrstr(usart6_rxbuff,"OK"))
			return 1;        //SUCCESS
		i++;
		
	}
}


int  WiFi_STR_response(char msg[])
{
	int i=0,j=300;
	char temp;
	
	while(j)
	{
		temp=USART6_inchar_timeout();
		usart6_rxbuff[i]=temp;
		i++;
		j--;
	}
	
		if(mstrstr(usart6_rxbuff,msg))
		{
			return 1;        //SUCCESS
		}
		else
			return 0;        //FAIL
}




int  WiFi_CWJAP_response(void)
{
	int i=0;
	char temp;
	
	while(1)
	{
		temp=USART6_inchar_timeout();
		if(temp==0)
		return 0;        //ERROR
		
		usart6_rxbuff[i]=temp;
		if((usart6_rxbuff[i]=='"') && (usart6_rxbuff[i-1]==':'))
			return 1;        //SUCCESS
		i++;
		
	}
}








//==============================
//STRSTR FUNCTION
//===============================
int mstrstr(char str[],char sub[])
{
	int i,j,k,l,le,c=0;
	for(i=0;sub[i]!='\0';i++);  //substring length
	le=i;
	
	for(i=0;i<=1500;i++)
	{
		j=0;
		if(sub[j]==str[i])
		{
			c++;
			for(k=i+1,l=j+1;str[k]==sub[l];k++,l++)
			{
				if(str[k]=='\0')
					break;
				c++;
			}
			
			}
		j++;
		}
	if(c==le)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}


/*
int mstrstr(char str[],char sub[])
{
	int i,j,k,l,le,c=0;
	for(i=0;sub[i]!='\0';i++);  //substring length
	le=i;
	
	for(i=0;str[i]!='\0';i++)
	{
		j=0;
		if(sub[j]==str[i])
		{
			c++;
			for(k=i+1,l=j+1;l<le;k++,l++)
			{
				if(sub[l]==str[k])
					c++;
			}
			
			}
		j++;
		}
	if(c==le)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}
*/





