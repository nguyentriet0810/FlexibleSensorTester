#ifndef __COM__
#define __COM__

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_usart.h>

#define USART1_BUFFER_SIZE 27

/*
Typedef Transmit Data to MCU 16 byte
|--------|--------|--------|--------|--------|--------|--------|
|	1 byte | 1 byte | 1 byte | 4 byte | 4 byte | 1 byte | 4 byte |
|        |        |        |        |        |        |        |
|--------|--------|--------|--------|--------|--------|--------|
Command  Pull mode Res mode Length   Times    Blance   Speed
uint8_t  uint8_t   uint8_t  uint8_t  uint8_t  uint8_t  uint8_t
*/

/*
Typedef Receive Data form MCU 27 byte
|----------|----------|----------|----------|----------|----------|
|	1 byte   | 5 byte   | 10 byte  | 5 byte   | 5 byte   | 1 byte   |
|          |          |          |          |          |          |         
|----------|----------|----------|----------|----------|----------|
Command    Force      Resistor   Length     Times      Mode     
uint8_t    uint8_t    uint8_t    uint8_t    uint8_t    uint8_t    
*/

#define USART3_BUFFER_SIZE 15
/*
Typedef Transmit Data to PC 15 byte
|----------|----------|----------|----------|----------|----------|----------|
|	1 byte   | 1 byte   | 1 byte   | 3 byte   | 4 byte   | 1 byte   | 4 byte   |
|          |          |          |          |          |          |          |
|----------|----------|----------|----------|----------|----------|----------|
Command    Pull mode  Res mode   Length     Times      Blance     Speed
uint8_t    uint8_t    uint8_t    uint8_t    uint8_t    uint8_t    uint8_t
*/

/*
Typedef Receive Data form PC 15 byte
|----------|----------|----------|----------|----------|----------|----------|
|	1 byte   | 1 byte   | 1 byte   | 3 byte   | 4 byte   | 1 byte   | 4 byte   |
|          |          |          |          |          |          |          |
|----------|----------|----------|----------|----------|----------|----------|
Command    Pull mode  Res mode   Length     Times      Blance     Speed
uint8_t    uint8_t    uint8_t    uint8_t    uint8_t    uint8_t    uint8_t
*/
typedef enum {
	ACK  = 1,
	NACK = 0,
} USART_STATE;

extern uint8_t buffer_mcu_data[];
extern uint8_t buffer_pc_data[];

extern volatile uint8_t current_mcu_data;
extern volatile uint8_t current_pc_data;

extern uint8_t g_buffer_mcu_flag;
extern uint8_t g_buffer_pc_flag;

void Usart1_GPIO_Init(void);
void Usart1_Init(void);
void Usart3_Init(void);
void Usart1_SendChar(char c);
void Usart3_SendChar(char c);
void Usart1_SendString(const char *str);
void Usart3_SendString(const char *str);
void Usart1_printf(const char *format, ...);
void Usart3_printf(const char *format, ...);
char* float_to_string(float value, int precision);
#endif /*__COM__*/
