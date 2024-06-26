/**
 * @file
 * @brief       PWM middleware interface functions
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#include "bsp_pwm.h"

/**
* @brief  MOTOR PWM initialization
* @retval None
* @par   Explanation
* -# Default output, duty cycle set to 0
*/
void pmcu_motor_init(void)
{
    plib_motor_set_duty(CFG_MOTOR_DUTY);
    plib_motor_en(PLIB_DISABLE);
}

/**
* @brief  MOS PWM initialization
* @retval None
* @par   Explanation
* -# Default output, duty cycle set to 0
*/
void pmcu_mos_init(void)
{
#if CFG_MOSEXT_EN
    plib_exmos_init(PLIB_ENABLE, PLIB_DISABLE, CFG_MOS_GRADE_SPEED1, CFG_MOS_GRADE_SPEED2);
#endif

    plib_mos_init(MOS_Fclk16, CFG_MOS_PWM_PERIOD, 0, CFG_MOS_OCP_THD, CFG_MOS_OCP_EN, CFG_MOS_OTP_EN);
    plib_mos_en(PLIB_ENABLE);

    //使能MOS PWM上升沿中断，用于控制调压
    plib_mos_it_cfg(MOS_TRIG_RISING, PLIB_ENABLE);
    plib_mos_it_en(PLIB_ENABLE);
}

/**
* @brief  Clear MOS ABN
* @retval None
* @par   Explanation
* None
*/
void pmcu_mos_abn_clr(void)
{
#if CFG_MOS_OCP_EN

    //Clr OCP
    while (plib_mos_get_ocp_lock())
    {
        plib_mos_clr_abn_flg(MOS_OCP);
        plib_mos_ocp_unlock();
    }

#endif

#if CFG_MOS_OTP_EN
    //Clr OTP
    plib_mos_clr_abn_flg(MOS_OTP);
#endif
}

/**
* @brief  PWM0 initialization
* @retval None
* @par   Explanation
* -# Default output, duty cycle set to 0
*/
void pmcu_pwm0_init(void)
{
    plib_pwm_init(PWM_SEL0, CFG_PWM0_FCLK_SET, CFG_PWM0_PERIOD, 0, 0, 0, CFG_PWM0_NEGATE_EN);
    plib_pwm_en(PWM_SEL0, PLIB_ENABLE);
}

/**
* @brief  PWM1 initialization
* @retval None
* @par   Explanation
* -# Default output, duty cycle set to 0
*/
void pmcu_pwm1_init(void)
{
    plib_pwm_init(PWM_SEL1, CFG_PWM1_FCLK_SET, CFG_PWM1_PERIOD, 0, 0, 0, CFG_PWM1_NEGATE_EN);
    plib_pwm_en(PWM_SEL1, PLIB_ENABLE);
}

#if CFG_IT_PWM_EN
/**
* @brief  PWM interrupt handler
* @retval None
* @par   Explanation
* -# MOS PWM/PWM0 Channel 0/PWM1 Channel 0 share this interrupt
*/
void pmcu_pwm_irq_handler() interrupt 12
{
    if(plib_mos_get_flg(MOS_TRIG_RISING) && plib_mos_it_ifen(MOS_TRIG_RISING))
    {
        plib_mos_clr_flg(MOS_TRIG_RISING);

        //置位上升沿标志位，以触发ADC采样，实现调压
        g_out_s.chn[0].pwm_ris_flg = 1;
    }
}
#endif

#if CFG_IT_MOS_ABN_EN
/**
* @brief  Power output abnormal protection interrupt handler
* @retval None
* @par   Explanation
* None
*/
void pmcu_mos_abn_irq_handler() interrupt 13
{
}
#endif
