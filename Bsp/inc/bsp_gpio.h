/**
 * @file
 * @brief       GPIO middleware interface functions
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__
#include "pmcu_x0_include.h"

#define _SET_COM_OUTPP(port, pin) plib_gpio_mode(port, pin, GPIO_IOMode_Out_PP)
#define SET_COM_OUTPP(port, pin) _SET_COM_OUTPP(port, pin)

#define _SET_COM_INNONE(port, pin) plib_gpio_output_en(port, pin, PLIB_DISABLE)
#define SET_COM_INNONE(port, pin) _SET_COM_INNONE(port, pin)

#define _SET_COM_OUTVALUE(port, pin, value) plib_gpio_set_value(port, pin, value)
#define SET_COM_OUTVALUE(port, pin, value) { _SET_COM_OUTVALUE(port, pin, value); _SET_COM_OUTPP(port, pin); }

// External functions
void pmcu_gpio_init(void);

#endif /* end of __BSP_GPIO_H__ */
