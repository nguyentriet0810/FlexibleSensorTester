#ifndef __BUTTON__
#define __BUTTON__

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_exti.h>

#define Button_Port   GPIOB
#define Button_Hold   GPIO_Pin_3  
#define Button_Choose GPIO_Pin_4
#define Button_Top    GPIO_Pin_5
#define Button_Bottom GPIO_Pin_6
#define Button_Plus   GPIO_Pin_7
#define Button_Sub    GPIO_Pin_8

typedef enum {
	Page_Defaut   = 0,
	Page_Start    = 1,
	Page_Settings = 2,
	Page_Options  = 3,
	Page_Alarm    = 4,
} Page_Type;

typedef struct {
  uint8_t y_coord;              // Current Y_coord value
  Page_Type next_page;          // Page      
} Button_Choose_Page_Action;

//typedef struct {
//  uint8_t y_coord;              // Current Y_coord value      
//	void (*action)(uint8_t *);         // action function
//} Button_Choose_Options_Action;

typedef struct {
  Page_Type current_page;       // Page     
	uint8_t y_coord_top_limit;
	void (*action)(uint16_t *);   // action function
} Button_Top_Action;

typedef struct {
  Page_Type current_page;       // Page     
	uint8_t y_coord_bot_limit;
	void (*action)(uint16_t *);   // action function
} Button_Bottom_Action;

typedef struct {
	uint8_t y_coord;              // Current Y_coord value
  Page_Type current_page;       // Page     
	void (*action)(uint16_t *);         // action function
} Button_Plus_Action;

typedef struct {
	uint8_t y_coord;              // Current Y_coord value
  Page_Type current_page;       // Page     
	void (*action)(uint16_t *);         // action function
} Button_Sub_Action;

extern uint16_t X_Coordinate, Y_Coordinate;

extern const Button_Choose_Page_Action page_actions[];
extern const Button_Top_Action         top_actions[];
extern const Button_Bottom_Action      bottom_actions[];
extern const Button_Plus_Action        plus_actions[];
extern const Button_Sub_Action         sub_actions[];

void action_nothing(void);
void action_start(void);
void action_top(uint16_t *coordinate);
void action_bottom(uint16_t *coordinate);
void action_plus(uint16_t *value);
void action_sub(uint16_t *value);

void Button_GPIO_Init(void);
void test_button_Init(void);

#endif /*__BUTTON__*/
