#include "main.h"

/**
 * @brief peripheral initialization
 *
 */
void bsy_sys_init(void)
{
#if CFG_TIM0_EN
    /* TIM0 init*/
    pmcu_tim0_init();
#endif

#if CFG_TIM1_EN
    /* TIM1 init */
    pmcu_tim1_init();
#endif

#if CFG_MOTOR_EN
    /* MOTOR init */
    pmcu_motor_init();
#endif

    /* MOS init */
    pmcu_mos_init();
    /* GPIO init*/
    pmcu_gpio_init();

#if CFG_PWM0_CTRL_EN
    /* PWM0 init, Ctrl LED output */
    pmcu_pwm0_init();
#endif
#if CFG_PWM1_CTRL_EN
    /* PWM1 init, Ctrl LED output */
    pmcu_pwm1_init();
#endif

#if CFG_UART_HW_EN
    /* UART init */
    pmcu_uart_init();
    pmcu_uart_buf_init();
#endif

    /* CHG init */
    pmcu_chg_init();
    /* ADC init */
    pmcu_adc_init();

#if CFG_WDT_EN
    /* watchdog init */
    pmcu_wdt_init(PLIB_ENABLE);
#endif

    /* System interrupt enable */
    plib_sys_it_en(PLIB_ENABLE);
}

/**
 * @brief local Basic functionality state initialization
 *
 */
void local_init(void)
{
    g_sys.status_sys = SYSTEM_IDLE; //Default standby after power on  ???????
    g_rl_det[0].rl_plug = plib_mos_get_plug_flg() ? 1 : 0; //Get rload plug status after power on ?????????

#if CFG_MIC_TYPE == 2   //¿ª¹ØßäÍ·¼ì²â  
    //Get key status after power on
    g_key_power_on = _PIN_MIC;
#endif
	
    if (reset_src_get() == RST_TYPE_LVR)
    {
        g_sys.flg_lvr = 1;

#if CFG_SYS_UVLS_EN
        LED_Show_RLSHORT();  //LVR reset, Short circuit light
#else
        LED_Show_Por(); //power on
#endif /* end of #if CFG_SYS_UVLS_EN */
        AM_DBG_PRINTF("LVR, Power on\r\n");
    }
    else
    {
        battery_get_volt_init();
        g_userdata_t.output_mode = OUTPUT_MODE_MOS_NONE;

        LED_Show_Por(); //power on
        AM_DBG_PRINTF("POR, Power on\r\n");

        reset_src_clear(); // Clr reset flg
#if CFG_OIL_CAL_EN
        smoke_info_init();
#endif
    }

#if CFG_SYS_LOCK_EN
#if CFG_SYS_LOCK_MODE == 1
    g_sys.lock_sys = 1; //Lock system
#endif /* end of CFG_SYS_LOCK_MODE == 1 */
#endif /* end of #if CFG_SYS_LOCK_EN */
}

/**
 * @brief local main functionality process
 *
 */
void local_process(void)
{
    while (1)
    {
        /* 1ms timer */
        if (g_sys.time.timer_1ms)
        {
            g_sys.time.timer_1ms = 0;
        }

        /* 10ms timer */
        if (util_timepass_check(&g_sys.time.timer_10ms, 10))
        {
            /* Feed wdt*/
            pmcu_wdt_feed();

            /* Key and mic scan process*/
#if CFG_MIC_EN
            mic_scan();
            AM_DBG_PRINTF("%d, %d\r\n", (u16)plib_mic_get_init_value(), (u16)plib_mic_get_cur_value());
#endif
#if CFG_KEY_EN
            key_scan();
#endif
            /* rload detection */
#if CFG_RLOAD_PLUG_EN
            rload_det();
#endif

            /* LED display process */
#if CFG_UI_LED_EN
            led_ctrl_handler();
#endif

#if CFG_UI_SCREEN_EN
            screen_ctrl_handler();
#endif

            /* USB charge and discharge process */
            usb_charger_process();
        }

        /* manager main process */
        manager_process();

#if CFG_UART_BOOTING_EN
        /* uart booting process */
        pmcu_uart_booting();
#endif
    }
}
