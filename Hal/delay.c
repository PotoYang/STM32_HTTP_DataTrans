#include "stm32f10x.h"

#include "delay.h"

unsigned char UsCount = 0;
unsigned short MsCount = 0;

void Delay_Init()
{

	SysTick->CTRL &= ~(1 << 2); //选择时钟为HCLK(72MHz)/8		103--9MHz
	
	UsCount = 9;
	
	MsCount = UsCount * 1000;

}

//此时钟(21MHz)最大延时798915us
void DelayUs(unsigned short us)
{

	unsigned int ctrlResult = 0;
	
	us &= 0x00FFFFFF; //取低24位
	
	SysTick->LOAD = us * UsCount;
	SysTick->VAL = 0;
	SysTick->CTRL = 1; //使能倒计数器
	
	do
	{
		ctrlResult = SysTick->CTRL;
	}
	while((ctrlResult & 0x01) && !(ctrlResult & (1 << 16))); //保证在运行、检查是否倒计数到0
	
	SysTick->CTRL = 0; //关闭倒计数器
	SysTick->VAL = 0;

}

void DelayXms(unsigned short ms)
{

	unsigned int ctrlResult = 0;
	
	if(ms == 0)
		return;
	
	ms &= 0x00FFFFFF; //取低24位
	
	SysTick->LOAD = ms * MsCount;
	SysTick->VAL = 0;
	SysTick->CTRL = 1; //使能倒计数器
	
	do
	{
		ctrlResult = SysTick->CTRL;
	}
	while((ctrlResult & 0x01) && !(ctrlResult & (1 << 16))); //保证在运行、检查是否倒计数到0
	
	SysTick->CTRL = 0; //关闭倒计数器
	SysTick->VAL = 0;

}

//ms可以再uint范围内
void DelayMs(unsigned short ms)
{

	unsigned char repeat = 0;
	unsigned short remain = 0;
	
	repeat = ms / 500;
	remain = ms % 500;
	
	while(repeat)
	{
		DelayXms(500);
		repeat--;
	}
	
	if(remain)
		DelayXms(remain);

}
