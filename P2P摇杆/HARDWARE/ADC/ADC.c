#include "ADC.h"
#include "delay.h"

u16 ADC_DMA_IN[2];
void P2P_Init()
{
 ADC_InitTypeDef ADC_InitStructure; 
 ADC_GPIO_Init();
 ADC_DMA_Init();
// RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
 ADC_DeInit(ADC1);  

 ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC工作模式:ADC1工作在独立模式                                                                                           
 ADC_InitStructure.ADC_ScanConvMode = ENABLE; //工作在扫描模式
 ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //ADC工作在连续扫描模式
 ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //不使用外部触发转换
 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; //ADC数据右对齐
 ADC_InitStructure.ADC_NbrOfChannel = 2; //顺序进行规则转换的ADC通道的数目
 ADC_Init(ADC1, &ADC_InitStructure); //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
  
 ADC_RegularChannelConfig(ADC1,ADC_Channel_6,1,ADC_SampleTime_55Cycles5);
 ADC_RegularChannelConfig(ADC1,ADC_Channel_7,2,ADC_SampleTime_55Cycles5);
 /*ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_28Cycles5);
 ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_28Cycles5);*/
 ADC_Cmd(ADC1, ENABLE); //使能指定的ADC
 ADC_DMACmd(ADC1,ENABLE);
 
 ADC_ResetCalibration(ADC1); //使能复位校准  
 while(ADC_GetResetCalibrationStatus(ADC1)); //等待复位校准结束
 ADC_StartCalibration(ADC1);  //开启AD校准
 while(ADC_GetCalibrationStatus(ADC1));  //等待校准结束
 ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}

void ADC_DMA_Init(void)
{
  DMA_InitTypeDef DMA_InitStructure;
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr=ADC1_DR_Address; //DMA源地址
	DMA_InitStructure.DMA_MemoryBaseAddr=(u32)&ADC_DMA_IN;    //DMA目标地址
	DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;          //单向传输，源地址->目标地址
	DMA_InitStructure.DMA_BufferSize=2;                       //缓冲区区长度为两个半字就是32位
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址递增模式，如果DMA与多个外设相连要选择地址递增，此出只与ADC1用所以不用使能
	DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;    //内存递增方式，DMA访问一个内存就不用使能
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //每次操作的数据长度
	DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;            //循环传输模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium ;  //优先级 高
	DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;               //两个变量之间互相访问 否
	DMA_Init(DMA1_Channel1,&DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1,ENABLE);                           //DMA通道使能
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
