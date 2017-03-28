#ifndef _ADC_H_
#define _ADC_H_

#include "stm32f10x.h"
#include <stdio.h>
#include "stm32f10x_dma.h"

extern void ADC_Config(void);

void RCC_Configuration(void);

void GPIO_Configuration(void);

void ADC_Configuration(void);

void DMA_Configuration(void);

extern volatile unsigned int adcConvertedValue;

#endif
