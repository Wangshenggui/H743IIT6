#include "led.h"
#include "module_auto_init.h"


/*LED结构体*/
struct LED_Structure
{
	GPIO_TypeDef* GPIOx;        // LED端口
	uint16_t GPIO_Pin;          // LED引脚
	LED_POLARITY polarity;      // LED极性
};
/*led注册表*/
const LED_Structure led_registry[LED_COUNT] =
{
	// ID    =    端口    引脚    点亮电平
	[LED_GREEN]	= {led_green_GPIO_Port,	led_green_Pin,	LED_POLARITY_LOW},
	[LED_RED]		= {led_red_GPIO_Port,		led_red_Pin,		LED_POLARITY_LOW},
};

/*bsp层自动初始化*/
void bsp_led_init()
{
	// 初始化LED
	LED_Init();
}
INIT_BSP(bsp_led_init);

/*初始化LED*/
void LED_Init(void)
{
	// 时钟和IO模式配置\
	...
	
	for(uint8_t id = 0; id<LED_COUNT; id++)
	{
		// 初始化默认关闭
		LED_SetState((LED_ID)id, LED_STATE_OFF);
	}
}

/*设置LED状态*/
void LED_SetState(LED_ID id, LED_STATE state)
{
	if (id >= LED_COUNT) return;

	GPIO_PinState pin_state;
	if (led_registry[id].polarity == LED_POLARITY_LOW)
	{
		pin_state = (state == LED_STATE_ON) ? GPIO_PIN_RESET : GPIO_PIN_SET;
	}
	else
	{
		pin_state = (state == LED_STATE_ON) ? GPIO_PIN_SET : GPIO_PIN_RESET;
	}
	HAL_GPIO_WritePin(led_registry[id].GPIOx, led_registry[id].GPIO_Pin, pin_state);
}

/*LED切换状态*/
void LED_Toggle(LED_ID id)
{
	if (id >= LED_COUNT) return;
	
	HAL_GPIO_TogglePin(led_registry[id].GPIOx, led_registry[id].GPIO_Pin);
}

