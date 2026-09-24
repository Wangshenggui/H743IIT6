#include "module_auto_init.h"

/* ============ 链接器符号声明 ============ */
extern const initcall_t Image$$INITCALL_REGION$$Base;
extern const initcall_t Image$$INITCALL_REGION$$Limit;

/**
 * 执行所有初始化函数（按等级分层执行）
 */
void auto_initcalls(void)
{
    const initcall_t *p;      /* 遍历指针 */
    uint32_t level;           /* 当前处理的等级 */
    
    /* 
     * 按等级从低到高依次处理
     */
    for (level = 0; level < INIT_LEVEL_COUNT; level += 1)
    {
        /* 
         * 遍历整个INITCALL段,找出所有属于当前等级的初始化条目
         */
        for (p = &Image$$INITCALL_REGION$$Base;
             p < &Image$$INITCALL_REGION$$Limit;
             p++)
        {
            /* 检查等级是否匹配 */
            if (p->level == level)
            {
                /* 检查函数指针是否有效 */
                if (p->fn)
                {
                    /* 执行初始化函数 */
                    p->fn();
                }
            }
        }
    }
}
