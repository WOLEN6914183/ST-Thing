#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "spi.h"
#include "24l01.h"   

 int main(void)
 { 
	u8 key,mode;			 
	delay_init();	    	 														//��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	// �����ж����ȼ�����2
	uart_init(9600);	 															//���ڳ�ʼ��Ϊ9600
	LED_Init();		  																//��ʼ����LED���ӵ�Ӳ���ӿ�	
 	KEY_Init();																			//������ʼ��
 	NRF24L01_Init();    														//��ʼ��NRF24L01
	while(NRF24L01_Check())                        //���NRF24L01�Ƿ���λ.
	{
    printf("NRF24L01 statue error ..........\n");
	}
	printf("NRF24L01 statue success...........\n");
		 
  /*********************************ģʽѡ��***********************************/	 
 	while(1)																			
	{
		printf("Waiting user slect mode.........\n");
		delay_ms(500);
		key=KEY_Scan(0);
		if(key==KEY0_PRES)       //����ģʽ
		{
			mode=0;  
      LED0=1;
      printf("NRF24L01 was slected RX-MODE........\n");			
			break;
		}
		else if(key==KEY1_PRES)  //����ģʽ
		{
			mode=1;
			LED0=1;
			printf("NRF24L01 was slected TX-MODE.......\n");
			break;
		}  
	} 
/********************************************************************************/	

/*************************************����ģʽ***********************************/
	
	if(mode==0)//RXģʽ
	{	
		u8 tmp_buf[4];
		int i;
		NRF24L01_RX_Mode();		  
		printf("Enter RX function........\n");
		while(1)
		{	  		    		    				 
			printf("Waitting recved by TX-MODE-NRF24L01.......\n");
			delay_ms(500);
			if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
			{
        LED0=0;
				LED1=1;
				printf("recv is success !!!!!\n");
				for(i=0;i<=3;i++)
				{
				  printf("recv tmp_buf value is %02x\n",tmp_buf[i]);
				  delay_ms(500);
				}
			}else  LED0=0;			
		}	
	}
/***************************************����ģʽ**************************************/
	if(mode==1)
	{	
		int i;
    printf("Enter TX function........\n");		
		NRF24L01_TX_Mode();	
		while(1)
		{	 
      u8 Tx_buf[4]={0,1,2,3};	
      u8 tx_return;			
			printf("Waitting user send data..........\n");
		  delay_ms(200);
			tx_return=NRF24L01_TxPacket(Tx_buf);
			printf("TX return value is %x20\n",tx_return);
			printf("123\n");
			 if(tx_return==TX_OK)
				 {
					  LED0=0;
				    LED1=1;
					 for(i=0;i<=3;i++)
					 {
					   printf("send success value %x20\n",Tx_buf[i]);
						 delay_ms(800);
					 }
					  
					  printf("Data was sended.......\n");
				 }								 
				 else LED0=0;			 
		}
	} 
}
/*****************************************************************************************/


