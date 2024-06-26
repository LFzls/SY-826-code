/**
 * @file
 * @brief       Charging middleware interface functions
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/


#ifndef __BSP_CHARGE_H__
#define __BSP_CHARGE_H__


#include "pmcu_x0_include.h"

typedef enum {
    USB_OUT = 0,
    USB_IN_UVP,
    USB_IN_OVP,
    USB_IN_CHGING_TC,
    USB_IN_CHGING_CC,
    USB_IN_CHGING_CV,
    USB_IN_CHGING_FULL,
    USB_IN_CHGING_RESTART,
} USB_TypeEnum;

// External functions
void pmcu_chg_init(void);
#endif /* end of __BSP_CHARGE_H__ */
