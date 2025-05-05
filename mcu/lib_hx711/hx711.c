#include "hx711.h"

void Force_Sensor_Init(void) {
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitTypeDef GPIO_InitStructure;

  // PB3 (DOUT) as Input Pull-up
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // C� th? d�ng GPIO_Mode_IN_FLOATING n?u c� pull-up ngo�i
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // PB4 (PD_SCK) as Output Push-pull
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // �?t PD_SCK v? LOW d? s?n s�ng cho xung d?u ti�n
  GPIO_ResetBits(GPIOB, GPIO_Pin_4);
}

int32_t getHX711(void) {
  int32_t data = 0;

  while(GPIO_ReadInputDataBit(DT_PORT, DT_PIN) == 1) {};
  for(int8_t len=0; len<24 ; len++)
  {
    GPIO_SetBits(SCK_PORT, SCK_PIN);
    Timer3_Delay_us(1);
    data = data << 1;
    GPIO_ResetBits(SCK_PORT, SCK_PIN);
    Timer3_Delay_us(1);
    if(GPIO_ReadInputDataBit(DT_PORT, DT_PIN) == 1)
      data ++;
  }
  data = data ^ 0x800000;
  GPIO_SetBits(SCK_PORT, SCK_PIN);
  Timer3_Delay_us(1);
  GPIO_ResetBits(SCK_PORT, SCK_PIN);
  Timer3_Delay_us(1);
  return data;
}

int32_t weigh()
{
  int32_t  total = 0;
  int32_t  samples = 1;
  int milligram;
  float coefficient;
  for(uint16_t i = 0 ; i < samples ; i++)
  {
      total += getHX711();
  }
  int32_t average = (int32_t)(total / samples);
  coefficient = knownOriginal / knownHX711;
  milligram = (int)(average-tare)*coefficient;
  return milligram;
}

int32_t getForce(int32_t offset) {
//	int32_t ratio;
	float Force;
//	float ConfigForce;
	int32_t weight;
	weight = weigh(); // in milligram
	Force = weight - offset;
	Force = Force/1000;
	if(Force < -150000) {
		weight = weigh(); // in milligram
		Force = weight - offset;
		Force = Force/1000;
	}
	return Force;
}
