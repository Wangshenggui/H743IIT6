#include "system.h"

/*********USB VPC重定向printf**********/
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

