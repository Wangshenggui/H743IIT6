#ifndef _UTILS_TIME_H_
#define _UTILS_TIME_H_

#include "main.h"


/*计算时间差*/
static inline uint32_t get_tick_diff(uint32_t current, uint32_t previous)
{
    return current - previous;
}


#endif
