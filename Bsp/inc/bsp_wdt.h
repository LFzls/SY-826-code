/**
 * @file
 * @brief       Middleware interface functions for watchdog timer control.
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#ifndef __BSP_WDT_H__
#define __BSP_WDT_H__


#include "pmcu_x0_include.h"
#include "user_typedef.h"

extern bit g_wdt_enable;
void pmcu_wdt_feed(void);
void pmcu_wdt_init(u8 ifEn);

#endif
