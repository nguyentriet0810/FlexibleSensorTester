#ifndef __STEP_DRIVER__
#define __STEP_DRIVER__

#include <stdint.h>

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

#include "timer.h"

#define Step_Port    GPIOA
#define Step_Enable  GPIO_Pin_7
#define Micro_Step_1 GPIO_Pin_6
#define Micro_Step_2 GPIO_Pin_5
#define Micro_Step_3 GPIO_Pin_4
#define Step_Reset   GPIO_Pin_3
#define Step_Sleep   GPIO_Pin_2
#define Step_Pul     GPIO_Pin_1
#define Step_Dir     GPIO_Pin_0

void Step_Driver_Init(void);

#endif /*__STEP_DRIVER__*/
