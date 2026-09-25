#include "led_fsm.h"
#include "module_auto_init.h"
#include "utils_time.h"

/*LED FSM结构体定义*/
struct LED_FSM_Structure
{
	LED_ID id;   				// led操作id
	void (*set_state)(LED_ID, LED_STATE);	// 设置LED状态
	LED_FSM_EVENT event;        // 当前事件
	LED_FSM_STATE state;        // 当前状态
	uint32_t blink_on_tick;     // 闪烁常亮计时
	uint32_t blink_off_tick;    // 闪烁熄灭计时
	uint32_t blink_on_time;     // 闪烁常亮时间(ms)
	uint32_t blink_off_time;    // 闪烁熄灭时间(ms)
};
/*定义LED状态机结构体*/
LED_FSM_Structure *led_green_fsm;
LED_FSM_Structure *led_red_fsm;

/*分配静态内存池*/
static LED_FSM_Structure fsm_pool[LED_FSM_MAX_NUM];
static uint8_t fsm_used = 0;	// 第一块内存开始分配

/* 编译期断言：池大小必须装得下所有 LED */
#define STATIC_ASSERT(cond, msg) typedef char static_assert_##msg[(cond) ? 1 : -1]
STATIC_ASSERT(LED_COUNT <= LED_FSM_MAX_NUM, led_fsm_pool_too_small);

/*mid层自动初始化*/
void mid_led_fsm_init()
{
	// 初始化LED状态机
	LED_FSM_Config cfg;
	
	// 初始化GREEN
	cfg.id = LED_GREEN;
	cfg.set_state = LED_SetState;
	led_green_fsm	= LED_FSM_Init(&cfg);
	
	// 初始化RED
	cfg.id = LED_RED;
	led_red_fsm		= LED_FSM_Init(&cfg);

	// 初始设置关闭LED
	LED_FSM_SetOFFEvent(led_green_fsm);
}
INIT_MID(mid_led_fsm_init);


/*内联到代码，计算LED时间差*/
static inline uint32_t led_get_tick_diff(uint32_t current, uint32_t previous)
{
	return current - previous;
}

/*LED状态机初始化*/
LED_FSM_Structure *LED_FSM_Init(const LED_FSM_Config *cfg)
{
	if (cfg == NULL)
	{
		return NULL;
	}
	if (fsm_used >= LED_FSM_MAX_NUM)
	{
		return NULL;                 // 池满
	}
	// 从静态缓冲区分配
	LED_FSM_Structure *fsm = &fsm_pool[fsm_used++];

	fsm->event = LED_FSM_EVENT_OFF;
	fsm->state = LED_FSM_STATE_OFF;
	fsm->blink_on_tick = 0;
	fsm->blink_off_tick = 0;
	fsm->blink_on_time = 0;
	fsm->blink_off_time = 0;
	// 操作led id
	fsm->id = cfg->id;
	fsm->set_state = cfg->set_state;

	return fsm;
}

/*设置led闪烁*/
void LED_FSM_SetBlinkEvent(LED_FSM_Structure* fsm, uint32_t on_time, uint32_t off_time)
{
	if (fsm == NULL)
	{
		return;
	}
	if (on_time == 0 || off_time == 0)
	{
		return;
	}
	if (fsm->event == LED_FSM_EVENT_BLINK &&
			fsm->blink_on_time == on_time &&
			fsm->blink_off_time == off_time)
	{
		return;
	}
	fsm->event = LED_FSM_EVENT_BLINK;
	fsm->state = LED_FSM_STATE_COUNT;   // 用来判断第一次进入闪烁
	fsm->blink_on_tick = 0;
	fsm->blink_off_tick = 0;
	fsm->blink_on_time = on_time;
	fsm->blink_off_time = off_time;
}

/*led状态切换*/
void LED_FSM_SetToggleEvent(LED_FSM_Structure* fsm)
{
	if (fsm == NULL)
	{
		return;
	}
	fsm->event = LED_FSM_EVENT_TOGGLE;
}

/*关闭led*/
void LED_FSM_SetOFFEvent(LED_FSM_Structure* fsm)
{
	if (fsm == NULL)
	{
		return;
	}
	fsm->event = LED_FSM_EVENT_OFF;
	fsm->state = LED_FSM_STATE_OFF;
}

/*开启led*/
void LED_FSM_SetONEvent(LED_FSM_Structure* fsm)
{
	if (fsm == NULL)
	{
		return;
	}
	fsm->event = LED_FSM_EVENT_ON;
	fsm->state = LED_FSM_STATE_ON;
}

/*LED状态机运行处理函数*/
void LED_FSM_Run(LED_FSM_Structure* fsm, uint32_t tick)
{
	if (fsm == NULL)
	{
		return;
	}
	switch(fsm->event)
	{
		// 关闭事件
		case(LED_FSM_EVENT_OFF):
		{
			fsm->set_state(fsm->id,LED_STATE_OFF);
			fsm->state = LED_FSM_STATE_OFF;
			fsm->event = LED_FSM_EVENT_IDLE;    // 只执行一次
		}
		break;

		// 开启事件
		case(LED_FSM_EVENT_ON):
		{
			fsm->set_state(fsm->id,LED_STATE_ON);
			fsm->state = LED_FSM_STATE_ON;
			fsm->event = LED_FSM_EVENT_IDLE;    // 只执行一次
		}
		break;

		// 闪烁事件
		case(LED_FSM_EVENT_BLINK):
		{
			// 首次进入闪烁状态
			if((fsm->state != LED_FSM_STATE_ON) \
				&& (fsm->state != LED_FSM_STATE_OFF))
			{
				fsm->set_state(fsm->id, LED_STATE_ON);
				fsm->blink_on_tick = tick;  // 记录开始亮的时间
				fsm->state = LED_FSM_STATE_ON;
			}
			else if(fsm->state == LED_FSM_STATE_OFF)
			{
				// 当前是灭的状态，检查是否该亮了
				if(led_get_tick_diff(tick, fsm->blink_off_tick) >= fsm->blink_off_time)
				{
					fsm->set_state(fsm->id, LED_STATE_ON);
					fsm->blink_on_tick = tick;  // 记录开始亮的时间
					fsm->state = LED_FSM_STATE_ON;
				}
			}
			else if(fsm->state == LED_FSM_STATE_ON)
			{
				// 当前是亮的状态，检查是否该灭了
				if(led_get_tick_diff(tick, fsm->blink_on_tick) >= fsm->blink_on_time)
				{
					fsm->set_state(fsm->id, LED_STATE_OFF);
					fsm->blink_off_tick = tick;   // 记录开始灭的时间
					fsm->state = LED_FSM_STATE_OFF;
				}
			}
		}
		break;

		// 切换事件
		case(LED_FSM_EVENT_TOGGLE):
		{
			if (fsm->state == LED_FSM_STATE_ON)
			{
				fsm->set_state(fsm->id, LED_STATE_OFF);
				fsm->state = LED_FSM_STATE_OFF;
			}
			else
			{
				fsm->set_state(fsm->id, LED_STATE_ON);
				fsm->state = LED_FSM_STATE_ON;
			}
			fsm->event = LED_FSM_EVENT_IDLE;
		}
		break;

		// 默认事件(无事件)
		default:
		{

		}
		break;
	}
}

