#include "led.h"

/***********************************************************************************
* LED初始化
*
*
*
************************************************************************************/
void LED_Init(void)
{
 GPIO_InitTypeDef  GPIO_InitStructure;	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PA端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;		//LED0-->PA.8 LED1-->PA.3端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		  //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					        //根据设定参数初始化GPIOA.8

}
 
