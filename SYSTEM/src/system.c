#include "system.h"

/*********重定向printf**********/
/*不适用半主机模式*/ 
#pragma import(__use_no_semihosting)
/*定义_sys_exit()以避免使用半主机模式*/    
void _sys_exit(int x) 
{
	x = x; 
}
/*标准库需要的支持函数*/
struct __FILE
{
	int handle;
};
FILE __stdout;

/*重定向printf*/
int fputc(int ch, FILE *p)
{
//	uint8_t data = (uint8_t)ch;  // 先把字符存到变量
//	while(CDC_Transmit_FS(&data, 1) != USBD_OK);
	return ch;
}
/**************************************/

/**************************************/
/*使能CPU的L1-Cache*/
void Cache_Enable(void)
{
	SCB_EnableICache();//使能I-Cache
	SCB_EnableDCache();//使能D-Cache   
	SCB->CACR|=1<<2;   //强制D-Cache透写,如不开启,实际使用中可能遇到各种问题	
}
/**************************************/

