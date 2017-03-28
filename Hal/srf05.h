#ifndef _SRF05_H_
#define _SRF05_H_

#include "delay.h"
#include "tim2.h"

#define TRIG_PORT GPIOC
#define ECHO_PORT GPIOC
#define TRIG_PIN  GPIO_Pin_0
#define ECHO_PIN  GPIO_Pin_1

extern void SRF05_Init(void);

extern int SRF05_StartMeasure(void);

#endif
