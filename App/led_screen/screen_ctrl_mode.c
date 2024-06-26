#include "screen_ctrl_mode.h"

#define CURRENT_CTRL_CNT_IS_ODD   (screen_ctrl_t.cnt & 0x1)

SCREEN_CTRL_T xdata screen_ctrl_t;
SCR_PWM_T xdata g_scr_pwm_t;

bit ctrl_period_process(void)
{
    if(screen_ctrl_t.run < screen_ctrl_t.period)
    {
        screen_ctrl_t.run++;
        return 0;
    }
    else
    {
        screen_ctrl_t.run = 0;

        if(screen_ctrl_t.cnt > 0)
        {
            screen_ctrl_t.cnt--;

            if(1 == screen_ctrl_t.onoff_after_flash)
            {
                if(screen_ctrl_t.cnt == 0)
                {
                    screen_ctrl_t.mode = SCREEN_MODE_ON;
                }
            }
            else if(0 == screen_ctrl_t.onoff_after_flash)
            {
                if(screen_ctrl_t.cnt == 1)  //避免最后闪一下
                {
                    screen_ctrl_t.mode = SCREEN_MODE_OFF;
                }
            }
            else if(2 == screen_ctrl_t.onoff_after_flash)
            {
                if(screen_ctrl_t.cnt == 0)
                {
                    screen_ctrl_t.cnt = 2;
                }
            }
        }
    }

    return 1;
}

//设置模式前，请先设置要显示的数字或图标
void screen_set_ctrl_info(SCREEN_MODE_E mode, u16 period, u8 loop_times, u32 ch_Mark, u32 ch_Mark2, u8 flash_on)
{
#if CFG_UI_SCREEN_SOFT_PWM_BREATH_EN
    u16 xdata run_new;
    run_new = (u32)(screen_ctrl_t.run * period) / screen_ctrl_t.period;
#endif

    if (screen_ctrl_t.is_on && mode == SCREEN_MODE_FLASH)
    {
        screen_ctrl_t.delay = 30;   //如果设置闪烁模式前，屏幕是亮的，先灭屏
    }
    else
    {
        screen_ctrl_t.delay = 0;
    }

    screen_ctrl_t.cnt = loop_times * 2;

    screen_ctrl_t.ctrl_bak  = g_screen_status_u.hex[0];      //先备份当前状态
    screen_ctrl_t.ctrl_bak2  = g_screen_status_u.hex[1];      //先备份当前状态
    screen_ctrl_t.mode      = mode;
    screen_ctrl_t.period    = period;
    screen_ctrl_t.ctrl_mask = ch_Mark;
    screen_ctrl_t.ctrl_mask2 = ch_Mark2;
    screen_ctrl_t.run       = 0;
    screen_ctrl_t.onoff_after_flash   = flash_on;       //0：闪完后熄灭  1：闪后常亮   2：一直闪
    //tiny_printf("mode: %d\r\n",(u16)screen_ctrl_t.mode);

    if(screen_ctrl_t.delay)
    {
        LEDSCREEN_SET_STATUS(0, 0);
    }

#if CFG_UI_SCREEN_SOFT_PWM_BREATH_EN

    if(SCREEN_MODE_BREATH == mode)
    {
        /**模拟pwm配置**/
        g_scr_pwm_t.period = SCR_PWM_PERIOD;    //模拟pwm配置
        g_scr_pwm_t.duty = 0;    //呼吸从0开始
        //screen_ctrl_t.run = run_new;
    }

#endif
}

/**
 * @brief Set screen bright.
 */
static void screen_set_bright(u32 mask, u32 mask2)
{
    g_screen_status_u.hex[0] = mask;
    g_screen_status_u.hex[1] = mask2;
}

/**
 * @brief Set screen marquee.
 */
static void marquee_process(void)
{
    static MARQUEE_MASS_E mass_last;

    if (++mass_last == MARQUEE_MASS_NUM)
    {
        mass_last = MARQUEE_MASS_0;
    }

    screen_set_marquee(mass_last);
}


void screen_soft_pwm_process(void)
{
    if(SCREEN_MODE_BREATH != screen_ctrl_t.mode)
    {
        return;
    }

    if(g_scr_pwm_t.run < g_scr_pwm_t.duty) ///置1
    {
        g_screen_status_u.hex[0] = screen_ctrl_t.ctrl_bak;
        g_screen_status_u.hex[1] = screen_ctrl_t.ctrl_bak2;
    }
    else      //清零
    {
        g_screen_status_u.hex[0] &= ~(screen_ctrl_t.ctrl_mask);
        g_screen_status_u.hex[1] &= ~(screen_ctrl_t.ctrl_mask2);
    }


    if(++g_scr_pwm_t.run == SCR_PWM_PERIOD)
    {
        g_scr_pwm_t.run = 0;
    }

}

/**
 * @brief Process the LED status every 10 milliseconds.
 */
void screen_ctrl_handler(void)
{
    u16 idata duty;

    if(screen_ctrl_t.delay)
    {
        if(screen_ctrl_t.delay == 1)
        {
            screen_set_bright(screen_ctrl_t.ctrl_bak, screen_ctrl_t.ctrl_bak2);
        }

        screen_ctrl_t.delay--;

        return;
    }

    switch (screen_ctrl_t.mode)
    {
    case SCREEN_MODE_UNDEFINE:
        break;

    case SCREEN_MODE_OFF:
        if(g_led_show_type == LED_SHOW_TYPE_POR)    //上电闪灯完成时，重新获取一次电量
        {
            battery_get_volt_init();
        }

        if(USB_IS_IN_CHARGING)
        {
            util_queue_push(EVENT_USB_CHRGING);
        }
        else
        {
            g_led_show_type = LED_SHOW_TYPE_OFF;
            LEDSCREEN_SET_STATUS(0, 0);   //强制清屏
            screen_ctrl_t.is_on = 0;
        }

        break;

    case SCREEN_MODE_ON:
        screen_set_bright(screen_ctrl_t.ctrl_bak, screen_ctrl_t.ctrl_bak2);
        screen_ctrl_t.is_on = 1;
        break;

    case SCREEN_MODE_HOLD:
        screen_ctrl_t.is_on = 1;
        ctrl_period_process();
        break;

    case SCREEN_MODE_FLASH:
        if(ctrl_period_process())
        {
            if(CURRENT_CTRL_CNT_IS_ODD)     //默认从息屏开始
            {
                g_screen_status_u.hex[0] &= ~(screen_ctrl_t.ctrl_mask);
                g_screen_status_u.hex[1] &= ~(screen_ctrl_t.ctrl_mask2);
                screen_set_bright(g_screen_status_u.hex[0], g_screen_status_u.hex[1]);
                screen_ctrl_t.is_on = 0;
            }
            else
            {
                screen_set_bright(screen_ctrl_t.ctrl_bak, screen_ctrl_t.ctrl_bak2);
                screen_ctrl_t.is_on = 1;
            }
        }

        break;

    case SCREEN_MODE_MARQUEE:
        screen_ctrl_t.is_on = 1;

        if (ctrl_period_process())
        {
            marquee_process();
        }

        break;

    case SCREEN_MODE_BREATH:
#if CFG_UI_SCREEN_SOFT_PWM_BREATH_EN
        screen_ctrl_t.is_on = 1;

        if(screen_ctrl_t.cnt & 1)
        {
            duty = SCR_CAL_DUTY_BREATH_DN();
            //AM_DBG_PRINTF("dduty: %d, %d, %d\r\n",(u16)screen_ctrl_t.run,(u16)duty,(u16)screen_ctrl_t.period);
        }
        else
        {
            duty = SCR_CAL_DUTY_BREATH_UP();
            //AM_DBG_PRINTF("uduty: %d, %d, %d\r\n",(u16)screen_ctrl_t.run,(u16)duty,(u16)screen_ctrl_t.period);
        }

        g_scr_pwm_t.duty = duty;
        ctrl_period_process();
#endif
        break;

    default:
        break;
    }
}
