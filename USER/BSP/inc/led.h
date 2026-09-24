#ifndef _LED_H_
#define _LED_H_

#include "main.h"


/*LED ID枚举*/
typedef enum
{
	LED_GREEN,
	LED_RED,
	LED_COUNT           // 总数
} LED_ID;

/*LED极性枚举*/
typedef enum
{
	LED_POLARITY_LOW = 0,   // 低电平点亮（GPIO_RESET = 亮）
	LED_POLARITY_HIGH = 1,  // 高电平点亮（GPIO_SET = 亮）
} LED_POLARITY;

/*LED状态枚举*/
typedef enum
{
	LED_STATE_OFF,
	LED_STATE_ON
} LED_STATE;

/*前向声明，防止外部修改*/
typedef struct LED_Structure LED_Structure;

/*初始化LED*/
void LED_Init(void);
/*设置LED状态*/
void LED_SetState(LED_ID id, LED_STATE state);
/*LED切换状态*/
void LED_Toggle(LED_ID id);

#endif
