#include "key_control.h"
#include "system.h"

/*定义key状态机结构体*/
static KEY_FSM_Structure *key_up_fsm;
static KEY_FSM_Structure *key1_fsm;
static KEY_FSM_Structure *key0_fsm;

/*按键单击回调函数*/
void Key_Click_Callback(KEY_ID id);
/*按键双击回调函数*/
void Key_DoubleClick_Callback(KEY_ID id);
/*按键长按回调函数*/
void Key_LongPress_Callback(KEY_ID id);
/*按键长按重复回调函数*/
void Key_LongPressRepeat_Callback(KEY_ID id);

/*注册按键状态机*/
/*app层自动初始化*/
void app_key_fsm_init()
{
  // 配置状态机结构体
	KEY_FSM_Config cfg = 
	{
		.id = KEY_UP,
		.get_state = Key_GetState,
		.long_press_time = 1000,    // 长按触发时间
		.long_repeat_time = 200,    // 连续触发周期
		.double_click_time = 300,   // 双击窗口，0表示禁用双击
		.click_callback = Key_Click_Callback,
		.double_click_callback = Key_DoubleClick_Callback,
		.long_press_callback = Key_LongPress_Callback,
		.long_repeat_callback = Key_LongPressRepeat_Callback,
	};
	
	// 初始化KEY状态机
	cfg.id = KEY_UP;
	key_up_fsm = KEY_FSM_Init(&cfg);
	cfg.id = KEY1;
	key1_fsm = KEY_FSM_Init(&cfg);
	cfg.id = KEY0;
	key0_fsm = KEY_FSM_Init(&cfg);
}
INIT_APP(app_key_fsm_init);

/*key状态机调用*/
void app_key_fsm_run(uint32_t tick)
{
	KEY_FSM_Run(key_up_fsm, tick);
	KEY_FSM_Run(key1_fsm, tick);
	KEY_FSM_Run(key0_fsm, tick);
}

/*按键单击回调函数*/
void Key_Click_Callback(KEY_ID id)
{
	switch(id)
	{
		case(KEY_UP):
		{
			LED_FSM_SetBlinkEvent(led_green_fsm, 500, 500);
		}
		break;
		case(KEY1):
		{
			LED_FSM_SetBlinkEvent(led_green_fsm, 10, 500);
		}
		break;
		case(KEY0):
		{
			LED_FSM_SetBlinkEvent(led_green_fsm, 500, 10);
		}
		break;
		
		default:
		{
			
		}
		break;
	}
}

/*按键双击回调函数*/
void Key_DoubleClick_Callback(KEY_ID id)
{
	switch(id)
	{
		case(KEY_UP):
		{
			LED_FSM_SetBlinkEvent(led_red_fsm, 500, 500);
		}
		break;
		case(KEY1):
		{
			LED_FSM_SetBlinkEvent(led_red_fsm, 10, 500);
		}
		break;
		case(KEY0):
		{
			LED_FSM_SetBlinkEvent(led_red_fsm, 500, 10);
		}
		break;
		
		default:
		{
			
		}
		break;
	}
}

/*按键长按回调函数*/
void Key_LongPress_Callback(KEY_ID id)
{
	switch(id)
	{
		case(KEY_UP):
		{
			
		}
		break;
		case(KEY1):
		{
			
		}
		break;
		case(KEY0):
		{
			
		}
		break;
		
		default:
		{
			
		}
		break;
	}
}

/*按键长按重复回调函数*/
void Key_LongPressRepeat_Callback(KEY_ID id)
{
	switch(id)
	{
		case(KEY_UP):
		{
			
		}
		break;
		
		default:
		{
			
		}
		break;
	}
}



