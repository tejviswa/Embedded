
#include "main.h"



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













//STRSTR FUNCTION
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








void WiFi_init(void)
{
	 
		KM_delayms_IT2(500);
	
		USART6_outchar_str("AT\r\n");
			if(!(WiFi_STRok_response()))
		{ 
			KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("no wifi");
			while(1);
		}
		else
		{
			KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("DEVICE OK");
		}
		
		KM_delayms_IT2(5000);
	
		USART6_outchar_str("AT+RST\r\n");
		KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("CHECKING RST");
		KM_delayms_IT2(5000);
		
		
		USART6_outchar_str("AT+CWMODE=3\r\n");
			
		if(!(WiFi_STRok_response()))
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("CW MODE NOT OK");
		}
		else
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("AT+CWMODE=3");
		}
		KM_delayms_IT2(500);
		
	/*		
		USART6_outchar_str("AT+CWJAP=\"KM-2.4G\",\"9963111084\"\r\n");
		if(!(WiFi_OK_response()))
		{
			KM_LCD_Write_Str("WIFI NOT CONNECTED");
		}
		else
		{
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("WIFI CONNECTED");
		}
		
		KM_delayms_IT2(3000);
		
		*/
		
		USART6_outchar_str("AT+CIPMUX=0\r\n");
		if(!(WiFi_STRok_response()))
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("CIPMUX NO RESPONSE");
		}
		else
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("AT+CIPMUX=0");
		}
		KM_delayms_IT2(5000);
		
		
	/*	
		USART6_outchar_str("AT+CIFSR\r\n");
		if(!(WiFi_OK_response()))
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str(" CIFSR NO RESPONSE");
		}
		else
		{KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("AT+CIFSR");
		}
			KM_delayms_IT2(3000);
		*/
	
		
		
		
//		USART6_outchar_str("AT+CWLAP\r\n");
//		KM_delayms_IT2_IT2(3000);
		
		USART6_outchar_str("AT+CIPMODE=0\r\n");
		
		if(!(WiFi_STRok_response()))
		{
			KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Str("CIPMODE NO RESPONSE");
		}
		else
		{
			KM_LCD_Write_Cmd(0x01);
			KM_LCD_Write_Cmd(0xC0);
			KM_LCD_Write_Str("AT+CIPMODE=0");
		}
			KM_delayms_IT2(5000);

}


void WiFi_config(void)
{
		USART6_outchar_str("AT+CIPSTATUS\r\n");
		KM_delayms_IT2(300);
		USART6_outchar_str("AT+CIPSTART=\"TCP\",\"142.93.218.33\",80\r\n");
		KM_delayms_IT2(300);
		USART6_outchar_str("AT+CIPSEND=40\r\n");	
		KM_delayms_IT2(300);
		USART6_outchar_str("GET /page.php?temp=%f&hum=%f&dev=1\r\n\r\n");
		KM_delayms_IT2(300);
		USART6_outchar_str("AT+CIPSTATUS");
		KM_delayms_IT2(300);
		USART6_outchar_str("AT+CIPCLOSE\r\n");
}