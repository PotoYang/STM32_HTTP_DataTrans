#include "tim2.h"

/*TIM2中断向量初始化*/
void TIM2_NVIC_Configuration()
{
	NVIC_InitTypeDef NVICInitStructure; 
    
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  													
  NVICInitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
  NVICInitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVICInitStructure.NVIC_IRQChannelSubPriority = 3;	
  NVICInitStructure.NVIC_IRQChannelCmd = ENABLE;
	
  NVIC_Init(&NVICInitStructure);
}

/*TIM2初始化*/
void TIM2_Configuration()
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
  
	TIM_DeInit(TIM2);
  TIM_TimeBaseStructure.TIM_Period=65535;		 								/* 自动重装载寄存器周期的值(计数值) */
  TIM_TimeBaseStructure.TIM_Prescaler= (360 - 1);				                /* 时钟预分频数 72M/360 */
  TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 		                /* 采样分频 */
  TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;                   /* 向上计数模式 */
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
}
