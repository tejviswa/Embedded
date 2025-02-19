

#include"stm32f401rbt6.h"

#define A 0
#define B 1
#define C 2

void delay(int);
void PORT_init(int);
void AHB1ENR_init(int device,int mode);
void AHB2ENR_init(int device,int mode);
void APB1ENR_init(int device,int mode);
void APB2ENR_init(int device,int mode);

void FTSR(int pin);
void IMR(int pin);

void MODER_config(int,int,int);
void PUPDR_config(int,int,int);
void ODR(int port,int mode,int pin);
//void MODER_config(int port,int mode,int pin);