/**
 * @file
 * @brief       Watchdog middleware interface function
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#include "bsp_wdt.h"

/* Watchdog enable flag */
bit g_wdt_enable;

/**
* @brief  Feed the watchdog
* @retval None
* @par Note
* None
*/
void pmcu_wdt_feed(void)
{
    if (g_wdt_enable)
    {
        plib_wdt_reflesh();
    }
}

/**
* @brief  Watchdog initialization
* @param  ifEn Whether to enable \n
* @ref PLIB_ENABLE Enable \n
* @ref PLIB_DISABLE Disable \n
* @retval None
* @par Note
* None
*/
void pmcu_wdt_init(u8 ifEn)
{
    if (ifEn == PLIB_ENABLE)
    {
        plib_wdt_set_time(CFG_WDT_TIME);
        plib_wdt_open();
        g_wdt_enable = 1;
    }
    else
    {
        plib_wdt_close();
        g_wdt_enable = 0;
    }
}
