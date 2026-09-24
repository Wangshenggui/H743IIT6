#ifndef MODULE_AUTO_INIT_H
#define MODULE_AUTO_INIT_H

#include <stdint.h>

typedef void (*init_fn_t)(void);

typedef struct
{
    const char *name;
    uint32_t level;
    init_fn_t fn;
} initcall_t;

/* init levels */
typedef enum
{
	INIT_LEVEL_SYS,			// 系统层
	INIT_LEVEL_BSP_EARLY,   // BSP 最早
	INIT_LEVEL_BSP,         // BSP
	INIT_LEVEL_BSP_LATE,    // BSP 最晚
	INIT_LEVEL_MID,			// 中间驱动层
	INIT_LEVEL_APP,			// 应用层
	INIT_LEVEL_COUNT
} Init_Level_Enum;

/* export macro */
#define INIT_EXPORT(fn, lvl)                    \
    const initcall_t __init_##fn               \
    __attribute__((used))                      \
    __attribute__((section("INITCALL"))) =     \
    {                                          \
        #fn, lvl, fn                           \
    }

/* wrappers */
#define INIT_SYS(fn)        INIT_EXPORT(fn, INIT_LEVEL_SYS)
#define INIT_BSP_EARLY(fn)  INIT_EXPORT(fn, INIT_LEVEL_BSP_EARLY)
#define INIT_BSP(fn)        INIT_EXPORT(fn, INIT_LEVEL_BSP)
#define INIT_BSP_LATE(fn)   INIT_EXPORT(fn, INIT_LEVEL_BSP_LATE)
#define INIT_MID(fn)        INIT_EXPORT(fn, INIT_LEVEL_MID)
#define INIT_APP(fn)        INIT_EXPORT(fn, INIT_LEVEL_APP)

void auto_initcalls(void);

#endif
