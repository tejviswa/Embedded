/*
 * USART6.h
 *
 *  Created on: Dec 29, 2024
 *      Author: LENOVO
 */

#ifndef INC_USART6_H_
#define INC_USART6_H_

void Wifi_Init(void);
void Wifi_Transmit(void);
void AT_Cmd(void);
void Rst_Cmd(void);
void Set_Wifi_Mode_Cmd(void);
void Connect_Wifi_Cmd(void);
void Mux_Mode_Cmd(void);
void Mode_Selection_Cmd(void);
int Check_Wifi_Response(void);
void sendcmds_wifi_init(void);


#endif /* INC_USART6_H_ */
