/**
 * @file
 * @brief       Charging middleware interface functions
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#include "bsp_charge.h"

/**
* @brief  Charging initialization function
* @retval None
* @par   Explanation
* None
*/
void pmcu_chg_init(void)
{
    plib_chg_init(PLIB_ENABLE, CFG_CHG_ISET, CFG_CHG_FULL_ISET, CFG_SYS_UVLS);
    plib_chg_en(PLIB_ENABLE);
}

#if CFG_IT_CHG_EN
/**
* @brief  Charging interrupt handler
* @param  None
* @retval None
* @par   Explanation
* None
*/
void pmcu_chg_irq_handler() interrupt 8
{
    if (plib_chg_it_ifen(CHG_IEN_USB) && plib_chg_get_flg(CHG_USB_OUT))
    {
        plib_chg_clr_flg(CHG_USB_OUT);
    }

    if (plib_chg_it_ifen(CHG_IEN_USB) && plib_chg_get_flg(CHG_USB_IN))
    {
        plib_chg_clr_flg(CHG_USB_IN);
    }

    if (plib_chg_it_ifen(CHG_IEN_CHGST) && plib_chg_get_flg(CHG_CHG_ST_IF))
    {
        plib_chg_clr_flg(CHG_CHG_ST_IF);
    }
}
#endif
