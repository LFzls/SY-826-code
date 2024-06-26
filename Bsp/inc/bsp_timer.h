/**
 * @file
 * @brief       Middleware interface functions for timers control. (Timer-based functions for system timing and other purposes)
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#ifndef __BSP_TIMER_H__
#define __BSP_TIMER_H__

#include "pmcu_x0_include.h"

// External variables
extern volatile U16 idata g_sys_tick;

// External functions
void pmcu_tim0_init(void);
void pmcu_tim1_init(void);

#endif /* end of __BSP_TIMER_H__ */
