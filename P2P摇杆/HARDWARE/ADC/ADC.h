#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"

#define ADC1_DR_Address ((u32)0x4001244C)  //
void P2P_Init(void);      //ADC��ʼ��

void ADC_DMA_Init(void); //DMA��ʼ��

void ADC_GPIO_Init(void); //GPIO��ʼ��

#endif
