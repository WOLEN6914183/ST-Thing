#include "spi.h" 	
#include "usart.h"
#include "delay.h"
  
//SpeedSet:
//SPI_BaudRatePrescaler_2   2分频   (SPI 36M@sys 72M)
//SPI_BaudRatePrescaler_8   8分频   (SPI 9M@sys 72M)
//SPI_BaudRatePrescaler_16  16分频  (SPI 4.5M@sys 72M)
//SPI_BaudRatePrescaler_256 256分频 (SPI 281.25K@sys 72M)
  
void SPI1_SetSpeed(u8 SpeedSet)
{
	//SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
  	//SPI_Init(SPI1, &SPI_InitStructure);
//	SPI_Cmd(SPI1,ENABLE);
	SPI2->CR1&=0XFFC7; 
	SPI2->CR1|=SpeedSet;	//设置SPI1速度  
	//SPI1->CR1|=1<<6; 		//SPI设备使能 
	SPI_Cmd(SPI2,ENABLE);
} 


//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI1_ReadWriteByte(u8 TxData)
{					 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查发送缓冲区是否为空
		SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个数据
	printf("1111111111111 \n");
	

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)//检查接收缓冲区是否为空
		return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据			
	
}
