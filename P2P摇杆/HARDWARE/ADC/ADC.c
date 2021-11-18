#include "ADC.h"
#include "delay.h"

u16 ADC_DMA_IN[2];
void P2P_Init()
{
 ADC_InitTypeDef ADC_InitStructure; 
 ADC_GPIO_Init();
 ADC_DMA_Init();
// RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
 ADC_DeInit(ADC1);  

 ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC����ģʽ:ADC1�����ڶ���ģʽ                                                                                           
 ADC_InitStructure.ADC_ScanConvMode = ENABLE; //������ɨ��ģʽ
 ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //ADC����������ɨ��ģʽ
 ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //��ʹ���ⲿ����ת��
 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC�����Ҷ���
 ADC_InitStructure.ADC_NbrOfChannel = 2; //˳����й���ת����ADCͨ������Ŀ
 ADC_Init(ADC1, &ADC_InitStructure); //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
  
 ADC_RegularChannelConfig(ADC1,ADC_Channel_6,1,ADC_SampleTime_55Cycles5);
 ADC_RegularChannelConfig(ADC1,ADC_Channel_7,2,ADC_SampleTime_55Cycles5);
 /*ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_28Cycles5);
 ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_28Cycles5);*/
 ADC_Cmd(ADC1, ENABLE); //ʹ��ָ����ADC
 ADC_DMACmd(ADC1,ENABLE);
 
 ADC_ResetCalibration(ADC1); //ʹ�ܸ�λУ׼  
 while(ADC_GetResetCalibrationStatus(ADC1)); //�ȴ���λУ׼����
 ADC_StartCalibration(ADC1);  //����ADУ׼
 while(ADC_GetCalibrationStatus(ADC1));  //�ȴ�У׼����
 ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

void ADC_DMA_Init(void)
{
  DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr=ADC1_DR_Address; //DMAԴ��ַ
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&ADC_DMA_IN;    //DMAĿ���ַ
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;          //�����䣬Դ��ַ->Ŀ���ַ
	DMA_InitStructure.DMA_BufferSize=2;                       //������������Ϊ�������־���32λ
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ����ģʽ�����DMA������������Ҫѡ���ַ�������˳�ֻ��ADC1�����Բ���ʹ��
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;    //�ڴ������ʽ��DMA����һ���ڴ�Ͳ���ʹ��
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //ÿ�β��������ݳ���
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;            //ѭ������ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium ;  //���ȼ� ��
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;               //��������֮�以����� ��
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);                           //DMAͨ��ʹ��
}

void ADC_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
