#ifndef _KEY_FSM_H_
#define _KEY_FSM_H_

#include "main.h"
#include "key.h"


/*最大状态机数量(用于静态内存池分配)*/
#define KEY_FSM_MAX_NUM 3

/*默认消抖时间(ms)*/
#define KEY_DEBOUNCE_DELAY  10

/*上锁时长*/
#define KEY_LOCK_DELAY  300

/*KEY FSM状态枚举*/
typedef enum
{
	KEY_FSM_STATE_IDLE,                     // 空闲
	KEY_FSM_STATE_PRESS,                    // 按下
	KEY_FSM_STATE_PRESS_DEBOUNCE,           // 按下消抖
	KEY_FSM_STATE_RELEASE,                  // 松开
	KEY_FSM_STATE_RELEASE_DEBOUNCE,         // 松开消抖
	KEY_FSM_STATE_CLICK,                    // 单击
	KEY_FSM_STATE_CLICK_WAIT,               // 等待第二次按下
	KEY_FSM_STATE_DOUBLE_PRESS_DEBOUNCE,    // 第二次按下消抖
	KEY_FSM_STATE_DOUBLE_RELEASE_DEBOUNCE,  // 第二次松开消抖
	KEY_FSM_STATE_DOUBLE,                   // 双击
	KEY_FSM_STATE_LONG,                     // 长按
	KEY_FSM_STATE_LONG_REPEAT,              // 长按重复
	KEY_FSM_STATE_LOCK,                     // 状态机上锁
	KEY_FSM_STATE_COUNT
} KEY_FSM_STATE;


/*定义点击回调函数类型*/
typedef void (*Click_Callback)(KEY_ID id);
typedef void (*DoubleClick_Callback)(KEY_ID id);
typedef void (*LongPress_Callback)(KEY_ID id);
typedef void (*LongPressRepeat_Callback)(KEY_ID id);

/*状态机配置结构体*/
typedef struct
{
	KEY_ID id;									// id
	KEY_STATE (*get_state)(KEY_ID);				// 获取状态函数
	uint32_t long_press_time;                   // 长按触发时间
	uint32_t long_repeat_time;                  // 长按重复触发时间
	uint32_t double_click_time;                 // 双击窗口
	Click_Callback            click_callback;					// 单击回调
	DoubleClick_Callback      double_click_callback;	// 双击回调
	LongPress_Callback        long_press_callback;		// 长按回调
	LongPressRepeat_Callback  long_repeat_callback;		// 连续长按回调
} KEY_FSM_Config;

/*前向声明，防止外部修改*/
typedef struct KEY_FSM_Structure KEY_FSM_Structure;

/*按键状态机初始化*/
KEY_FSM_Structure *KEY_FSM_Init(const KEY_FSM_Config *cfg);
/*按键状态机轮询*/
void KEY_FSM_Run(KEY_FSM_Structure* fsm, uint32_t tick);

#endif
