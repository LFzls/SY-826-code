#include "led_ctrl.h"

xdata struct led_ctrl g_led_s;

/**
 * @brief Process LED periods for flashing LED.
 * @param index The index of the LED.
 * @param num The number of the LED.
 */
void led_period_process(void)
{
    if(g_led_s.run < g_led_s.onoff) //LED已显示的时长，小于设置时长，持续增加
    {
        g_led_s.run++;
    }
    else    //当前LED显示时长已达到设置值
    {
        g_led_s.run = 0;

        if(g_led_s.cnt > 0)
        {
            g_led_s.cnt--;

            if(g_led_s.cnt == 0)    //灯显已完成
            {
                if(g_led_s.mode == LED_MODE_BREATH) //呼吸时，g_led_s.cnt不清0，以持续呼吸
                {
                    g_led_s.cnt = 2;
                }
                else
                {
                    g_led_s.mode = LED_MODE_OFF;
                }
            }
        }
    }
}

/**
 * @brief Set LED status and control parameters for a specific group of LEDs.
 */
void led_set_ctrl_info(LED_MODE_E mode, u8 Period_Onff, u8 Loop_Times, u8 ch_Mark)
{
    u16 xdata run_new;

    //当前为闪烁灯效，且上次灯效未结束，如正处于常亮，则闪烁次数+1.因为要先灭再亮
    if(mode == LED_MODE_FLASH && g_led_s.mode != LED_MODE_OFF && g_led_s.mode != LED_MODE_UNDEFINE)
    {
        g_led_s.cnt = Loop_Times * 2 + 1;
    }
    else
    {
        g_led_s.cnt = Loop_Times * 2;
    }

    run_new = (u32)(g_led_s.run * Period_Onff) / g_led_s.onoff;
    g_led_s.mode = mode;            //当前灯效模式
    g_led_s.onoff = Period_Onff;    //闪灯周期时间
    g_led_s.led_mask = ch_Mark;     //哪些LED点亮

    //当前正处于亮灯模式，且接下来灯效为呼吸、渐亮、渐灭、呼吸跑马（反向）等效果时，则从当前灯效开始显示
    if(g_led_s.run &&
            (g_led_s.mode == LED_MODE_BREATH ||
             g_led_s.mode == LED_MODE_BREATH_OFF))
    {
        g_led_s.run = g_led_s.onoff - run_new;
    }
    else
    {
        g_led_s.run = 0;
    }
}

/**
 * @brief Set LED bright.
 */
void led_set_bright(u8 color_msk, u8 duty)
{
    u8 xdata chn0_duty, chn1_duty, chn2_duty, chn3_duty, chn4_duty, chn5_duty;

    chn0_duty = (color_msk & LED0_MASK) ? duty : 0;
    chn1_duty = (color_msk & LED1_MASK) ? duty : 0;
    chn2_duty = (color_msk & LED2_MASK) ? duty : 0;
    chn3_duty = (color_msk & LED3_MASK) ? duty : 0;
    chn4_duty = (color_msk & LED4_MASK) ? duty : 0;
    chn5_duty = (color_msk & LED5_MASK) ? duty : 0;
    plib_pwm_set_chn_duty(PWM_SEL0, chn0_duty, chn1_duty, chn2_duty);
    plib_pwm_set_chn_duty(PWM_SEL1, chn3_duty, chn4_duty, chn5_duty);
}

/**
 * @brief Process the LED status every 10 milliseconds.
 */
void led_ctrl_handler(void)
{
    u8 xdata tmp;

    switch (g_led_s.mode)
    {
    case LED_MODE_UNDEFINE:
        break;

    case LED_MODE_OFF:
        if(USB_IS_IN_CHARGING)
        {
            util_queue_push(EVENT_USB_CHRGING);
        }
        else
        {
            g_led_show_type = LED_SHOW_TYPE_OFF;
            led_all_off(g_led_s.led_mask);
            g_led_s.is_on = 0;
        }

        break;

    case LED_MODE_ON:
        led_all_on(g_led_s.led_mask);
        g_led_s.is_on = 1;
        break;

    case LED_MODE_FLASH:
        if(g_led_s.cnt & 1)
        {
            led_all_off(g_led_s.led_mask);
            g_led_s.is_on = 0;
        }
        else
        {
            led_all_on(g_led_s.led_mask);
            g_led_s.is_on = 1;
        }

        led_period_process();
        break;

    case LED_MODE_BREATH:
        if(g_led_s.cnt & 1)
        {
            tmp = led_cal_duty_breath_dn();
            g_led_s.is_on = 0;
        }
        else
        {
            tmp = led_cal_duty_breath_up();
            g_led_s.is_on = 1;
        }

        led_set_bright(g_led_s.led_mask, tmp);
        led_period_process();
        break;

    case LED_MODE_BREATH_ON:
        if(g_led_s.run < g_led_s.onoff)
        {
            g_led_s.run++;
            tmp = led_cal_duty_breath_up();
            led_set_bright(g_led_s.led_mask, tmp);
        }

        g_led_s.is_on = 1;
        break;

    case LED_MODE_BREATH_OFF:
        if(g_led_s.run < g_led_s.onoff)
        {
            g_led_s.run++;
            tmp = led_cal_duty_breath_dn();
            led_set_bright(g_led_s.led_mask, tmp);
        }
        else
        {
            g_led_s.mode = LED_MODE_OFF;
        }

        g_led_s.is_on = 0;
        break;

    case LED_MODE_ON_OFF:   //常亮后，熄灭
        led_all_on(g_led_s.led_mask);

        if(g_led_s.run < g_led_s.onoff)
        {
            g_led_s.run++;
        }
        else
        {
            g_led_s.mode = LED_MODE_OFF;
        }

        break;	
		
    default:
        break;
    }
}
