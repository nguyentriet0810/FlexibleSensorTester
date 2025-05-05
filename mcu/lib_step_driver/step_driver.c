#include "step_driver.h"

void Step_Driver_Init(void)	 {
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;

	//Config PA7, PA6, PA5, PA4, PA3, PA2, PA0 as output push-ull
  GPIO_InitStructure.GPIO_Pin = Step_Enable | Micro_Step_1 | Micro_Step_2 | Micro_Step_3 | Step_Reset | Step_Sleep | Step_Dir;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(Step_Port, &GPIO_InitStructure);
	
	//config PA1 as AFIO PWM
	GPIO_InitStructure.GPIO_Pin = Step_Pul;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(Step_Port, &GPIO_InitStructure);
	
	GPIO_ResetBits(Step_Port, Micro_Step_1 | Micro_Step_2 | Micro_Step_3 | Step_Dir);
	GPIO_SetBits(Step_Port, Step_Enable | Step_Reset | Step_Sleep);
}
