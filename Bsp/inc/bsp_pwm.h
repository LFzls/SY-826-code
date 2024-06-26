/**
 * @file
 * @brief       Middleware interface functions for PWM control (Pulse Width Modulation)
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#ifndef __BSP_PWM_H_
#define __BSP_PWM_H_

#include "pmcu_x0_include.h"
#include "volt_out.h"

#define LED_PWM1_PERIOD (255)   // PWM Period for LED 1

// External functions
void pmcu_motor_init(void);
void pmcu_mos_init(void);
void pmcu_mos_abn_clr(void);
void pmcu_pwm0_init(void);
void pmcu_pwm1_init(void);

#endif /* end of __BSP_TIMER_H__ */
