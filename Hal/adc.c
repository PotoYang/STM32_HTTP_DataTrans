#include "adc.h"

#define ADC1_DR_Address    ((u32)0x4001244C)

extern volatile unsigned int adcConvertedValue = 0;

void ADC_Config(void)
{
	RCC_Configuration();
	GPIO_Configuration();
	ADC_Configuration();
	DMA_Configuration();
}

void RCC_Configuration(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIOInitStructure;
      
	GPIOInitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIOInitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIOInitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOC, &GPIOInitStructure); 
}

void ADC_Configuration(void)
{
	ADC_InitTypeDef ADCInitStructure;
	
	ADCInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADCInitStructure.ADC_ScanConvMode = ENABLE;
	ADCInitStructure.ADC_ContinuousConvMode = ENABLE;
	ADCInitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; 
	ADCInitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADCInitStructure.ADC_NbrOfChannel = 1;
	
	ADC_Init(ADC1, &ADCInitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 1, ADC_SampleTime_55Cycles5);
	ADC_DMACmd(ADC1, ENABLE);
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

void DMA_Configuration(void)
{
	DMA_InitTypeDef DMAInitStructure;
	
	DMA_DeInit(DMA1_Channel1);
	
	DMAInitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;
	DMAInitStructure.DMA_MemoryBaseAddr = (u32)&adcConvertedValue;
	DMAInitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMAInitStructure.DMA_BufferSize = 1;
	DMAInitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMAInitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
	DMAInitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMAInitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMAInitStructure.DMA_Mode = DMA_Mode_Circular;
	DMAInitStructure.DMA_Priority = DMA_Priority_High;
	DMAInitStructure.DMA_M2M = DMA_M2M_Disable;
	
	DMA_Init(DMA1_Channel1, &DMAInitStructure);
	DMA_Cmd(DMA1_Channel1, ENABLE);
}
