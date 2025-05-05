#ifndef __OS__
#define __OS__

#include <stm32f10x.h>

#include <stdint.h>

#include "timer.h"
#include "step_driver.h"

//khai bao so thread toi da co the co trong os
#define NUM_OF_THREADS	7
//khai bao vung stack cho moi thread
#define STACK_SIZE 			400

//khoi tao tan so cho systick	
#define BUS_FREQ 			72000000

//tao macro de bat ngat cho systick
#define INTCTRL (*((volatile uint32_t *)0XE000ED04))
#define PENDSTSET   (1<<26)

#define USART1_BUFFER_SIZE 16

/*
Typedef Receive Data form VCU 16 byte
|--------|--------|--------|--------|--------|--------|--------|
|	1 byte | 1 byte | 1 byte | 4 byte | 4 byte | 1 byte | 4 byte |
|        |        |        |        |        |        |        |
|--------|--------|--------|--------|--------|--------|--------|
Command  Pull mode Res mode Length   Times    Blance   Speed
uint8_t  uint8_t   uint8_t  uint8_t  uint8_t  uint8_t  uint8_t
*/

/*
Typedef Transmit Data to VCU 27 byte
|----------|----------|----------|----------|----------|----------|
|	1 byte   | 5 byte   | 10 byte  | 5 byte   | 5 byte   | 1 byte   |
|          |          |10so+2tp  |          |          |          |         
|----------|----------|----------|----------|----------|----------|
Command    Force      Resistor   Length     Times      Mode     
uint8_t    int32_t    uint32_t   uint8_t    uint8_t    uint8_t    
*/

//TCB Struct
struct tcb{
	uint32_t *stackPt;
	struct tcb* nextPt;
	uint32_t Sleep;
};

//tao kieu du lieu tcbType
typedef struct tcb tcbType;

extern tcbType tcbs[NUM_OF_THREADS];
extern uint32_t current_num_of_thread;
extern uint8_t buffer_usart1_data[];
extern uint8_t Sema_usart1_handler;

void osKernelInit(void);
void osKernelLaunch(uint8_t quanta);
void osSchedulerLaunch(void);
void osKernelStackInit(int i);
uint8_t osKernelAdd1Thread(void (*task)(void));
void osSchedulerRoundRobin(void);
void osThreadYield(void);
void osSemaphore_Init(uint8_t *semaphore, uint8_t val);
void osSemaphore_Give(uint8_t *semaphore);
void osCooperative_Wait(uint8_t *semaphore);
void osThreadsSleep(uint32_t sleeptime);

#endif /*__OS__*/
