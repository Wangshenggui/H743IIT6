#include "key.h"
#include "module_auto_init.h"


/*key结构体*/
struct Key_Structure
{
	GPIO_TypeDef* GPIOx;        // KEY端口
	uint16_t GPIO_Pin;          // KEY引脚
	KEY_POLARITY polarity;      // KEY极性按下时电平状态
};
/*定义按键ID注册表*/
const struct Key_Structure key_registry[KEY_COUNT] = 
{
	[KEY_UP]	= {key_up_GPIO_Port, key_up_Pin, KEY_POLARITY_HIGH},
	[KEY1]		= {key1_GPIO_Port,   key1_Pin,   KEY_POLARITY_LOW},
	[KEY0]		= {key0_GPIO_Port,   key0_Pin,   KEY_POLARITY_LOW},
};

/*bsp层自动初始化*/
void bsp_key_init()
{
	// 初始化KEY
	Key_Init();
}
INIT_BSP(bsp_key_init);


/*key初始化*/
void Key_Init()
{
	// 时钟和IO模式配置\
	...

	for(uint8_t id = 0; id<KEY_COUNT; id++)
	{

	}
}

/*获取按键电平状态*/
KEY_STATE Key_GetState(KEY_ID id)
{
	if (id >= KEY_COUNT) return KEY_STATE_NONE;

	KEY_STATE state = KEY_STATE_Release;
	// 低电平按下
	if(key_registry[id].polarity == KEY_POLARITY_LOW)
	{
		state = (HAL_GPIO_ReadPin(key_registry[id].GPIOx, key_registry[id].GPIO_Pin) == GPIO_PIN_RESET)\
			?KEY_STATE_Press:KEY_STATE_Release;
	}
	else
	{
		state = (HAL_GPIO_ReadPin(key_registry[id].GPIOx, key_registry[id].GPIO_Pin) == GPIO_PIN_SET)\
			?KEY_STATE_Press:KEY_STATE_Release;
	}

	return state;
}



