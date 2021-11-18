#include "spi.h" 	
#include "usart.h"
#include "delay.h"
  
//SpeedSet:
//SPI_BaudRatePrescaler_2   2��Ƶ   (SPI 36M@sys 72M)
//SPI_BaudRatePrescaler_8   8��Ƶ   (SPI 9M@sys 72M)
//SPI_BaudRatePrescaler_16  16��Ƶ  (SPI 4.5M@sys 72M)
//SPI_BaudRatePrescaler_256 256��Ƶ (SPI 281.25K@sys 72M)
  
void SPI1_SetSpeed(u8 SpeedSet)
{
	//SPI_InitStructure.SPI_BaudRatePrescaler = SpeedSet ;
  	//SPI_Init(SPI1, &SPI_InitStructure);
//	SPI_Cmd(SPI1,ENABLE);
	SPI2->CR1&=0XFFC7; 
	SPI2->CR1|=SpeedSet;	//����SPI1�ٶ�  
	//SPI1->CR1|=1<<6; 		//SPI�豸ʹ�� 
	SPI_Cmd(SPI2,ENABLE);
} 


//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI1_ReadWriteByte(u8 TxData)
{					 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //��鷢�ͻ������Ƿ�Ϊ��
		SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
	printf("1111111111111 \n");
	

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)//�����ջ������Ƿ�Ϊ��
		return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����			
	
}
