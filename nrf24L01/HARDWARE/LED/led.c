#include "led.h"

/***********************************************************************************
* LED��ʼ��
*
*
*
************************************************************************************/
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;		//LED0-->PA.8 LED1-->PA.3�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					        //�����趨������ʼ��GPIOA.8

}
 
