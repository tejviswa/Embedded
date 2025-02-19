/*
 * 16x2_LCD.h
 *
 *  Created on: Dec 29, 2024
 *      Author: LENOVO
 */

#ifndef INC_16X2_LCD_H_
#define INC_16X2_LCD_H_

#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0

void KM_LCD_Init(void);
void KM_Write_High_Nibble(unsigned char data);
void KM_Write_Low_Nibble(unsigned char data);
void KM_LCD_Write_Cmd(unsigned char data);
void KM_LCD_Write_Data(unsigned char data);
void KM_LCD_Write_Str(char *data);
void custom_degree(void);
void itoa(char s[],int x);
int DECIMAL_TO_BCD(unsigned int x);
int BCD_TO_DECIMAL(unsigned int x);

#endif /* INC_16X2_LCD_H_ */

