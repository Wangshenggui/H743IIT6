#ifndef _KEY_H_
#define _KEY_H_

#include "main.h"


/*按键 ID枚举*/
typedef enum
{
	KEY_UP,
	KEY1,
	KEY0,
	KEY_COUNT           // 总数
} KEY_ID;

/*KEY极性枚举*/
typedef enum
{
	KEY_POLARITY_LOW,   // 低电平表示按下
	KEY_POLARITY_HIGH,  // 高电平表示按下
} KEY_POLARITY;

/*KEY状态枚举*/
typedef enum
{
	KEY_STATE_Release,		// 松开
	KEY_STATE_Press,		// 按下
	KEY_STATE_NONE			// 无事件
} KEY_STATE;

/*key初始化*/
void Key_Init(void);
/*获取按键电平状态*/
KEY_STATE Key_GetState(KEY_ID id);

#endif
