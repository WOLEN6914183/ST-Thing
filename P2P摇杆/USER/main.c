#include "led.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"
#include "ADC.h"
#include <stdio.h>

//ALIENTEK Mini STM32开发板范例代码2
//按键输入实验		   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
	u8 key;
	extern u16 ADC_DMA_IN[2];
 int main(void)
 {	
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	 	//初始化与LED连接的硬件接口
	KEY_Init();          	//初始化与按键连接的硬件接口
	P2P_Init();
	uart_init(115200);
	printf("System Init OK ...\r\n"); 
	while(1)
	{
		
		key = KEY_Scan(0);
	  if(ADC_DMA_IN[0]>=2120 || ADC_DMA_IN[0]<=1900 || ADC_DMA_IN[1]>=2120 || ADC_DMA_IN[1]<=1900)
		{
		  printf("Vrx value is %d\n",ADC_DMA_IN[0]);
			delay_ms(500);
			printf("Vry value is %d\n",ADC_DMA_IN[1]);
			delay_ms(500);
		}

		if(key==KEY1)
		{
			printf("KEY1_PRES...\r\n");
			delay_ms(50);
		}
	} 
}		 

