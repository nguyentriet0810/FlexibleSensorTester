#ifndef __HX711__
#define __HX711__

#include <stdio.h>
#include <stdint.h>

#include <stm32f10x.h>
#include <stm32f10x_gpio.h>

#include "timer.h"

#define DT_PIN GPIO_Pin_3
#define DT_PORT GPIOB
#define SCK_PIN GPIO_Pin_4
#define SCK_PORT GPIOB

#define tare                8354131U 
#define knownOriginal       11910000U
#define knownHX711          609140U
#define knownOriginalForce  44950U

typedef struct {
	int32_t weight;
	int32_t offset;
	int32_t force;
} LoadCell_typedef;

extern LoadCell_typedef data;

void Force_Sensor_Init(void);
int32_t getHX711(void);
int32_t weigh(void);
int32_t getForce(int32_t offset);

#endif /*__HX711__*/
