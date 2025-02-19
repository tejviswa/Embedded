//--------------------------------------
//USART2 FILES
//--------------------------------------
void USART2_outchar(unsigned char ch);
void USART2_outchar_str(char *ch);

unsigned char USART2_inchar(void);
unsigned char USART2_inchar_nonblocking(void);


//STRING SEARCH FUNCTION
int my_strstr(char str[],char sub[]);


//-----------------------------------------
//USART6 FILES
//-----------------------------------------
void USART6_outchar(unsigned char ch);
void USART6_outchar_str(char *ch);

unsigned char USART6_inchar(void);
unsigned char USART6_inchar_nonblocking(void);
unsigned char USART6_inchar_timeout(void);