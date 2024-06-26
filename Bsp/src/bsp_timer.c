/**
 * @file
 * @brief       Timer middleware interface function
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#include "bsp_timer.h"
#include "bsp_adc.h"
#include "volt_out.h"

/* Global system tick */
volatile U16 idata g_sys_tick;

#if CFG_TIM0_EN
/**
* @brief  Timer0 initialization
* @param  cnt Timing duration, unit us, maximum value 49000 \n
* @retval None
* @par   Note
* None
*/
void pmcu_tim0_init(void)
{
    plib_tim0_init(TIM_MODE_2, CFG_TIM0_CNT, PLIB_ENABLE, PLIB_ENABLE);
}

/**
* @brief  Timer0 interrupt handling function
* @param  None
* @retval None
* @par   Note
* None
*/
void pmcu_tim0_irq_handler() interrupt 1 using 2
{
    static xdata U8 tim_xus;

    if(++tim_xus >= 5)
    {
        tim_xus = 0;

        g_sys_tick++;
        //1ms timing flag
        g_sys.time.timer_1ms = 1;

//幻彩灯测试
#if CFG_UI_MAGIC_LED_TEST_EN
        magic_led_test();
#endif
    }


#if CFG_UI_SCREEN_EN
#if CFG_UI_SCREEN_SOFT_PWM_BREATH_EN
    screen_soft_pwm_process();
#endif
    screen_driver_scan_loop();
#endif
}
#endif

#if CFG_TIM1_EN
/**
* @brief  Timer1 initialization
* @param  cnt Timing duration, unit us, maximum value 49000 \n
* @retval None
* @par   Note
* None
*/
void pmcu_tim1_init(void)
{
    plib_tim1_init(TIM_MODE_2, CFG_TIM1_CNT, PLIB_ENABLE, PLIB_ENABLE);
}

/**
 * @brief Control volt by timer
 */
static void pmcu_inner_ctrl_by_tim(void)
{
    if(g_out_s.chn[0].pwm_ris_flg)
    {
        //inner mos
        if(++g_out_s.chn[0].pwm_open_dly == CFG_MOS_OPEN_DELAY)
        {
            g_out_s.chn[0].pwm_open_dly = 0;
            //清零上升沿标志位，等待下一次启动调压
            g_out_s.chn[0].pwm_ris_flg = 0;

            //触发ADC采样，结果在主循环流程中获取
            plib_adc_clr_flg(ADC_CHN0_PGAOUT | ADC_CHN1_VBAT);
            plib_adc_chn_en(ADC_CHN0_PGAOUT | ADC_CHN1_VBAT, PLIB_ENABLE); //使能VOUT和电池通道采样

            g_out_s.chn[0].pwm_open_flg = 1;
        }
    }
}

/**
 * @brief Control volt by timer
 */
static void pmcu_ext_ctrl_by_tim(void)
{
    if(g_out_s.chn[1].pwm_ris_flg)
    {
        //ext mos
        if(g_out_s.chn[1].pwm_duty == 0)
        {
            g_out_s.chn[1].pwm_open_dly = 0;
            ExtMOS_Output(DISABLE);
        }
        else
        {
            if (g_out_s.chn[1].pwm_open_dly < CFG_EXTMOS_PWM_PERIOD)
            {
                g_out_s.chn[1].pwm_open_dly++;
            }
            else
            {
                g_out_s.chn[1].pwm_open_dly = 1;
            }

            if (g_out_s.chn[1].pwm_open_dly <= g_out_s.chn[1].pwm_duty )
            {
                ExtMOS_Output(ENABLE);
            }
            else
            {
                ExtMOS_Output(DISABLE);
            }

            if (g_out_s.chn[1].pwm_open_dly == CFG_EXTMOS_OPEN_DELAY)
            {
                //清零上升沿标志位，等待下一次启动调压
                g_out_s.chn[1].pwm_ris_flg = 0;

                //触发ADC采样，结果在主循环流程中获取
                plib_adc_clr_flg(CFG_EXTMOS_ADC_CHN | ADC_CHN1_VBAT);
                plib_adc_chn_en(CFG_EXTMOS_ADC_CHN | ADC_CHN1_VBAT, PLIB_ENABLE); //使能VOUT和电池通道采样

                g_out_s.chn[1].pwm_open_flg  = 1;
            }
        }
    }
}

/**
* @brief  Timer1 interrupt handling function
* @param  None
* @retval None
* @par   Note
* None
*/
void pmcu_tim1_irq_handler() interrupt 3 using 2
{
    switch(g_out_s.ouput_mode)
    {
    case OUTPUT_MODE_INMOS_ONLY:
        pmcu_inner_ctrl_by_tim();
        break;

    case OUTPUT_MODE_EXMOS_ONLY:
        pmcu_ext_ctrl_by_tim();
        break;

    case OUTPUT_MODE_MOS_BOTH:
        pmcu_inner_ctrl_by_tim();
        pmcu_ext_ctrl_by_tim();
        break;

    default:
        break;
    }
}
#endif