#ifndef _SYSTEM_H
#define _SYSTEM_H

/************框架头文件加载************/
#include "module_auto_init.h"
#include "malloc.h"
/**************************************/

/***********SYSTEM头文件加载***********/
#include "main.h"
#include <stdio.h>
#include <string.h>
/**************************************/

/*************BSP头文件加载************/
#include "led.h"
/**************************************/

/*************MID头文件加载************/
#include "led_fsm.h"
/**************************************/

/*************APP头文件加载************/

/**************************************/

/*************Utils头文件加载************/

/**************************************/

// 调试使能
#define DEBUG_ENABLE
// Ansi彩色输出
#define DEBUG_COLOR_ENABLE

#ifdef DEBUG_COLOR_ENABLE
    #define COLOR_RED     "\033[31m"
    #define COLOR_GREEN   "\033[32m"
    #define COLOR_YELLOW  "\033[33m"
    #define COLOR_CYAN    "\033[36m"
    #define COLOR_RESET   "\033[0m"
#else
    #define COLOR_RED     ""
    #define COLOR_GREEN   ""
    #define COLOR_YELLOW  ""
    #define COLOR_CYAN    ""
    #define COLOR_RESET   ""
#endif

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : \
                      strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)

#ifdef DEBUG_ENABLE
    /* 普通调试输出 */
    #define debug_printf(fmt, ...) \
    do { \
        printf("[%s:%d] [%u]: " fmt, __FILENAME__, __LINE__, \
            HAL_GetTick(), ##__VA_ARGS__); \
    } while(0)

    /* INFO 级别（绿色）*/
    #define debug_info(fmt, ...) \
        do { \
            printf(COLOR_GREEN "[INFO] [%u] [%s:%d]: " fmt COLOR_RESET, \
                HAL_GetTick(), __FILENAME__, __LINE__, ##__VA_ARGS__); \
        } while(0)

    /* WARN 级别（黄色）*/
    #define debug_warn(fmt, ...) \
        do { \
            printf(COLOR_YELLOW "[WARN] [%u] [%s:%d]: " fmt COLOR_RESET, \
                HAL_GetTick(), __FILENAME__, __LINE__, ##__VA_ARGS__); \
        } while(0)

    /* ERROR 级别（红色）*/
    #define debug_error(fmt, ...) \
        do { \
            printf(COLOR_RED "[ERROR] [%u] [%s:%d]: " fmt COLOR_RESET, \
                HAL_GetTick(), __FILENAME__, __LINE__, ##__VA_ARGS__); \
        } while(0)

#else
    #define debug_printf(fmt, ...) ((void)0)
    #define debug_info(fmt, ...)   ((void)0)
    #define debug_warn(fmt, ...)   ((void)0)
    #define debug_error(fmt, ...)  ((void)0)
#endif
    


#endif

