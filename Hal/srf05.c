#include "srf05.h"

void SRF05_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;	
  	       
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
  GPIO_InitStructure.GPIO_Pin = TRIG_PIN;					 //PC0接TRIG
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		     //设为推挽输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	         
  GPIO_Init(TRIG_PORT, &GPIO_InitStructure);	                 //初始化外设GPIO 

  GPIO_InitStructure.GPIO_Pin = ECHO_PIN;				     //PC1接ECH0
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		 //设为输入
  GPIO_Init(ECHO_PORT,&GPIO_InitStructure);
}

int SRF05_StartMeasure(void)
{
	int temp, distance;
	
  GPIO_SetBits(TRIG_PORT,TRIG_PIN); 		  //送>10US的高电平
  DelayUs(20);		                      //延时20US
  GPIO_ResetBits(TRIG_PORT,TRIG_PIN);
  
  while(!GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	             //等待高电平
  TIM_Cmd(TIM2, ENABLE);                                             //开启时钟
  while(GPIO_ReadInputDataBit(ECHO_PORT,ECHO_PIN));	                 //等待低电平
  TIM_Cmd(TIM2, DISABLE);			                                 //定时器2失能
  temp = TIM_GetCounter(TIM2)*5*34/2000;  //计算距离
  TIM_SetCounter(TIM2,0);
	
	distance = temp/256 * 10 + temp%256;
	
	return distance;
}
