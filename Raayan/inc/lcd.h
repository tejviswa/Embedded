void KM_LCD_Init(void);
void KM_LCD_Write_Cmd(unsigned char);
void KM_LCD_Write_Data(unsigned char);
void KM_LCD_Write_Str(char *);
void write_high_nibble( unsigned char data );
void write_low_nibble( unsigned char data );
void scrolling_left(char *ptr);
void scrolling_left2(char *ptr);
void custom (char arr[]);


void itoa(char s[],int x);