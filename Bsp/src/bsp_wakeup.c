/**
 * @file
 * @brief       Sleep and wake-up middleware interface functions
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#include "bsp_wakeup.h"

/**
* @brief  Sleep initialization
* @param  None
* @retval None
* @par  GPIO/MIC depends on specific interrupt events for wake-up, which are implemented in their respective peripheral initialization
* None
*/
void pmcu_wakeup_init(void)
{
    plib_wk_init(CFG_WK_SRC, CFG_WK_SRC_TIME);
}
