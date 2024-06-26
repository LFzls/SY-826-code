#include "manager.h"

idata struct system_info g_sys;

/**
 * @brief Processes system messages in idle state
 * @param key The key event to process
 */
static void msg_proce_idle(u8 key)
{
    if (key > EVENT_NONE && key < EVENT_MAX)
    {
        util_timepass_init(g_sys.time.timesleep);    // Valid key, sleep delay
    }

    switch (key)
    {
    case EVENT_MIC_START:
#if CFG_MIC_FIRE_EN
        //充电中若不允许吸烟，则直接返回
#if (CFG_CHG_SMOKE_EN == 0)
        if(_ChgBit.in)
        {
            return;
        }

#endif
        g_sys.status_sys = SYSTEM_FIRE_START;
#endif
        break;

    case EVENT_KEY_PRESS:

#if CFG_KEY_FIRE_EN
        //充电中若不允许吸烟，则直接返回
#if (CFG_CHG_SMOKE_EN == 0)
        if(_ChgBit.in)
        {
            return;
        }

#endif
        g_sys.status_sys = SYSTEM_FIRE_START;
#endif
        break;

    case EVENT_LOCK_CHILD:
        if(g_sys.lock_child)
        {
            g_sys.lock_child = 0;
            LED_Show_UnLock_Child();
        }
        else
        {
            g_sys.lock_child = 1;
            LED_Show_Lock_Child();
        }

        g_sys.status_sys = SYSTEM_FIRE_STOP;
        break;

    case EVENT_LOCK_SYS:
        if(g_sys.lock_sys)
        {
            g_sys.lock_sys = 0;
            LED_Show_UnLock_Sys();
        }

        break;

    case EVENT_BAT_LOW:
        batlow_force_zero();
        LED_Show_BatLow();
        break;

    case EVENT_USB_INPUT:
        LED_Show_USB_IN_1st();
        break;

    case EVENT_USB_CHRGING:
        LED_Show_USB_CHARGING();
        //用于测试模式下打印电压和百分比
        AM_FACTORY_PRINTF("Chg: %d, %d, %d\r\n", (u16)g_battery.volt.idle, (u16)g_userdata_t.real_level, (u16)g_userdata_t.show_level);
        break;

    case EVENT_USB_REMOVE:
        LED_Show_USB_Remove();
        g_battery.chg_time = 0; //USB拔出，充电时间清零
#if CFG_CHG_REFLESH_MIC_VALUE_EN
        plib_mic_reflesh_ini_value();
#endif
        //用于测试模式下打印电压和百分比
        AM_FACTORY_PRINTF("Chg: %d, %d, %d\r\n", (u16)g_battery.volt.idle, (u16)g_userdata_t.real_level, (u16)g_userdata_t.show_level);
        break;

    case EVENT_USB_FULL:
        LED_SHow_USB_FULL_1st();
#if CFG_CHG_REFLESH_MIC_VALUE_EN
        plib_mic_reflesh_ini_value();
#endif
        //用于测试模式下打印电压和百分比
        AM_FACTORY_PRINTF("Chg: %d, %d, %d\r\n", (u16)g_battery.volt.idle, (u16)g_userdata_t.real_level, (u16)g_userdata_t.show_level);

        break;

    case EVENT_USB_RECHRG:
        LED_Show_USB_CHARGING();
        break;

    case EVENT_HEATER_INPUT:
        g_rl_det[0].rl_plug = 1;
        LED_Show_RL_IN();
        break;

    case EVENT_HEATER_REMOVE:
        g_rl_det[0].rl_plug = 0;
        LED_Show_RL_OUT();
        break;

    default:
        break;
    }
}

/**
 * @brief Processes system messages related to firing events
 * @param key The key code of the event to process
 */
static void msg_proce_firing(u8 key)
{
    switch (key)
    {
    case EVENT_FIRE_STOP:
        plib_chg_en(PLIB_ENABLE);
        g_sys.status_sys = SYSTEM_FIRE_STOP;      // Switch state to output off
        break;

    case EVENT_KEY_RELEASE:
#if CFG_KEY_FIRE_EN
        util_queue_push(EVENT_FIRE_STOP);
        LED_Show_FireStop();
#endif
        break;

    case EVENT_MIC_STOP:
#if CFG_MIC_FIRE_EN
        util_queue_push(EVENT_FIRE_STOP);
        LED_Show_FireStop();
#endif
        break;

    case EVENT_USB_INPUT:
        plib_chg_en(PLIB_DISABLE);
        break;

    case EVENT_BAT_LOW:
        util_queue_push(EVENT_FIRE_STOP);
        batlow_force_zero();
        LED_Show_BatLow();
        break;

    case EVENT_HEATER_SHORT:
        util_queue_push(EVENT_FIRE_STOP);
        LED_Show_RLSHORT();
        break;

    case EVENT_HEATER_OPEN:
        util_queue_push(EVENT_FIRE_STOP);
        LED_Show_RLOPEN();
        break;

    case EVENT_HEATER_DRY:
        util_queue_push(EVENT_FIRE_STOP);
        LED_Show_RLDRY();
        break;

    case EVENT_CHIP_OTP:
        util_queue_push(EVENT_FIRE_STOP);
        LED_Show_ChipOTP();
        break;

    case EVENT_FIRE_OTP:
        util_queue_push(EVENT_FIRE_STOP);
        LED_Show_OT();
        break;

    default:
        break;
    }
}

/**
 * @brief Processes system messages related to error start events
 * @param key The key code of the event to process
 */
static void msg_proce_err_start(u8 key)
{
    switch (key)
    {
    case EVENT_BAT_LOW:
        util_queue_push(EVENT_FIRE_STOP);
        batlow_force_zero();
        LED_Show_BatLow();
        break;

    case EVENT_HEATER_SHORT:
        util_queue_push(EVENT_FIRE_STOP);
        LED_Show_RLSHORT();
        break;

    case EVENT_HEATER_OPEN:
        util_queue_push(EVENT_FIRE_STOP);
        LED_Show_RLOPEN();
        break;

    default:
        break;
    }
}

/**
 * @brief Controls error handling during firing events
 */
static void manager_err_firing(void)
{
#if CFG_BAT_UV_FIRE_EN

    if (g_battery.volt.fire < CFG_BAT_UV_FIRING_THD)
    {
        util_queue_push(EVENT_BAT_LOW);
        return;
    }

#endif

#if CFG_MOS_OCP_EN

    if(plib_mos_get_abn_flg(MOS_OCP) || g_rl_det[0].status == RL_SHORT)
    {
        util_queue_push(EVENT_HEATER_SHORT);
        AM_DBG_PRINTF("ocp\r\n");
    }

#endif

#if CFG_MOS_OTP_EN

    if(plib_mos_get_abn_flg(MOS_OTP))
    {
        util_queue_push(EVENT_CHIP_OTP);
    }

#endif

#if CFG_SMOKE_TIMEOUT_EN

    if (util_time_passing(g_sys.time.firing) >= CFG_SMOKE_TIMEOUT_TIME)
    {
        util_queue_push(EVENT_FIRE_OTP);
    }

#endif
}

/**
 * @brief Controls error handling during idle events
 */
static void manager_err_dile(void)
{

}

/**
 * @brief Controls error handling during start events
 * @return Returns 1 if an error occurred, otherwise returns 0
 */
static u8 manager_err_start(void)
{
#if CFG_BAT_UV_FIRE_EN

    if (g_battery.volt.idle < CFG_BAT_UV_IDLE_THD)
    {
        util_queue_push(EVENT_BAT_LOW);
        return 1;
    }

#endif

#if CFG_RLOAD_OPEN_PRO_EN

    if (g_rl_det[0].status == RL_OPEN)
    {
        util_queue_push(EVENT_HEATER_OPEN);
        return 1;
    }

#endif

#if CFG_RLOAD_SHORT_PRO_EN

    if (g_rl_det[0].status == RL_SHORT)
    {
        util_queue_push(EVENT_HEATER_SHORT);
        return 1;
    }

#endif

#if CFG_VOUT_CNH_MAX==2 || CFG_VOUT_CNH_MAX==3

#if CFG_RLOAD_OPEN_PRO_EN

    if (g_rl_det[1].status == RL_OPEN)
    {
        util_queue_push(EVENT_HEATER_OPEN);
        return 1;
    }

#endif /* end of #if CFG_RLOAD_OPEN_PRO_EN */

#if CFG_RLOAD_SHORT_PRO_EN

    if (g_rl_det[1].status == RL_SHORT || g_rl_det[1].status == RL_LOW)
    {
        util_queue_push(EVENT_HEATER_SHORT);
        return 1;
    }

#endif /* end of #if CFG_RLOAD_SHORT_PRO_EN */

#endif /* end of #if CFG_VOUT_CNH_MAX==2 */

    return 0;
}


/**
 * @brief Controls ADC sampling based on system state
 * @param sysstate The current system state
 * @return Returns 1 if data is ready, otherwise returns 0
 */
static u8 manager_ctrl_adc(SYSTEM_STATE sysstate)
{
    u8 dataOK = 0;
    u16 iii = 0;
    u8 j = 8;

    switch (sysstate)
    {
    case SYSTEM_IDLE:            // Idle state message processing
#if CFG_BAT_UPDATE_IDLE_EN

        if(g_out_s.chn[0].fire_on || g_out_s.chn[1].fire_on)
        {
            break;
        }

        if (util_timepass_check(&g_sys.time.bat_dly, 10))
        {
            if(g_battery.sample_delay)
            {
                --g_battery.sample_delay;
            }
        }

        if(g_battery.sample_delay == 0) //定时获取电量，充电时，由充电进程控制获取
        {
            if (util_timepass_check(&g_sys.time.bat_volt_update, CFG_BAT_IDLE_UPDATA_TIME))
            {
                battery_get_volt();     // Get battery volt
                get_battery_level();    // Get battery level
                dataOK = 1;
            }
        }

#endif
        break;

    case SYSTEM_POWEROFF:
        break;

    case SYSTEM_FIRE_START:
        //Get rload resistance
        rload_get_inmos_ohm(ADC_PGA_SEL_x16);
#if CFG_VOUT_CNH_MAX==2 || CFG_VOUT_CNH_MAX==3
        rload_get_exmos_ohm();
#endif
        break;

    case SYSTEM_FIRE_RUNNING:
        if (g_out_s.chn[0].pwm_open_flg)
        {
            g_out_s.chn[0].pwm_open_flg = 0;

            if(plib_adc_get_flg(ADC_CHN0_PGAOUT))
            {
                plib_adc_clr_flg(ADC_CHN0_PGAOUT);
                g_out_s.chn[0].v_mos_out = plib_adc_get_ad_value(ADC_CHN0_PGAOUT);
                g_out_s.chn[0].v_mos_out = plib_adc_get_volt_div4(g_out_s.chn[0].v_mos_out);
            }

            if(plib_adc_get_flg(ADC_CHN1_VBAT))
            {
                plib_adc_clr_flg(ADC_CHN1_VBAT);
                g_battery.advalue = plib_adc_get_ad_value(ADC_CHN1_VBAT);
                g_battery.volt.now = plib_adc_get_volt_div2(g_battery.advalue);
                g_battery.volt.fire = g_battery.volt.now;
            }

            //AM_DBG_PRINTF("V1=%d, V2=%d, O1=%d\r\n", (u16)g_battery.volt.idle, (u16)g_battery.volt.fire, (u16)g_out_s.chn[0].v_mos_out);
            dataOK = 1;
        }
        else if (g_out_s.chn[1].pwm_open_flg)
        {
            g_out_s.chn[1].pwm_open_flg = 0;

            if(plib_adc_get_flg(CFG_EXTMOS_ADC_CHN))
            {
                plib_adc_clr_flg(CFG_EXTMOS_ADC_CHN);
                g_out_s.chn[1].v_mos_out = plib_adc_get_ad_value(CFG_EXTMOS_ADC_CHN);
                g_out_s.chn[1].v_mos_out = plib_adc_get_volt_div2(g_out_s.chn[1].v_mos_out);
            }

            if(plib_adc_get_flg(ADC_CHN1_VBAT))
            {
                plib_adc_clr_flg(ADC_CHN1_VBAT);
                g_battery.advalue = plib_adc_get_ad_value(ADC_CHN1_VBAT);
                g_battery.volt.now = plib_adc_get_volt_div2(g_battery.advalue);
                g_battery.volt.fire = g_battery.volt.now;
            }

            //AM_DBG_PRINTF("V1=%d, V2=%d, O1=%d\r\n", (u16)g_battery.volt.idle, (u16)g_battery.volt.fire, (u16)g_out_s.chn[1].v_mos_out);
            dataOK = 1;
        }
        else
        {
            dataOK = 0;
        }

        break;

    case SYSTEM_FIRE_STOP_ERR:
        break;

    case SYSTEM_FIRE_STOP:
        break;

    default:
        break;
    }

    return dataOK;
}

/**
 * @brief Controls the entire smoking process state machine, run in the main program loop
 *
 */
void manager_process(void)    // According to the new requirements, smoking must be done within the maximum time specified by the PC.
{
    u8 xdata key;

    g_sys.event = util_queue_pull(&g_event_queue); //Take data from the message queue
    key = g_sys.event;

    switch (g_sys.status_sys)
    {
    case SYSTEM_IDLE:
        msg_proce_idle(key);    //Message processing during idle
        manager_ctrl_adc(SYSTEM_IDLE); // Collect battery voltage
        manager_err_dile();    //Idle state error handling

#if CFG_LONG_SLEEP_EN
        pm_sleep_process(CFG_LONG_SLEEP_TIME);    // Enter sleep
#endif
        break;

    case SYSTEM_FIRE_START:
        if(g_sys.lock_child || g_sys.lock_sys)  //lock status
        {
            g_sys.status_sys = SYSTEM_FIRE_START_ERR;
            break;
        }

        //报警灯效，不可被吸烟打断
        if(g_led_show_type == LED_SHOW_TYPE_POR ||
                g_led_show_type == LED_SHOW_TYPE_FIRE_OT ||
                g_led_show_type == LED_SHOW_TYPE_RL_SHORT ||
                g_led_show_type == LED_SHOW_TYPE_RL_OPEN ||
                g_led_show_type == LED_SHOW_TYPE_BATLOW)
        {
            g_sys.status_sys = SYSTEM_FIRE_START_ERR;
            break;
        }

        plib_chg_en(PLIB_DISABLE); // Turn off charging first

        manager_ctrl_adc(SYSTEM_FIRE_START); // Collect heating resistance value before smoking

        if (manager_err_start())   // Error handling before smoking
        {
            g_sys.status_sys = SYSTEM_FIRE_START_ERR;
            break;
        }

        //用于测试模式下打印电压和百分比
        AM_FACTORY_PRINTF("Out: %d, %d, %d\r\n", (u16)g_battery.volt.idle, (u16)g_userdata_t.real_level, (u16)g_userdata_t.show_level);

        out_fire_start();                           // Initial output control
        util_timepass_init(g_sys.time.firing);      // Smoking duration timing
        g_battery.volt.fire = g_battery.volt.idle - 100; // Prepare initial voltage to prevent protection when entering
        g_sys.status_sys = SYSTEM_FIRE_RUNNING;     // Switch to heating mode after startup
        break;

    case SYSTEM_FIRE_START_ERR:
        msg_proce_err_start(key);
        out_fire_stop();                // Stop smoking
        g_sys.status_sys = SYSTEM_IDLE;  // Switch to idle state after output is off
        break;

    case SYSTEM_FIRE_RUNNING:
#if CFG_OIL_CAL_EN
        oil_value_update();     //Update oil value
#endif

        battery_fire_time_update();
        msg_proce_firing(key);        // Message processing during smoking
        manager_err_firing();         // Error handling during smoking

        if (manager_ctrl_adc(SYSTEM_FIRE_RUNNING))
        {
//输出时检测负载开路或恒功率时，在输出中，间隔采样负载大小
#if CFG_VOUT_DET_RL_EN || (CFG_MOS_OUT_MODE==3)
            if(rload_det_firing())
            {
                break;
            }

#endif

#if (CFG_MOS_OUT_MODE==3)   //Constant power mode       
            out_ctrl_cw();
#endif

            out_ctrl_cv();  //Constant voltage mode
        }

        break;

    case SYSTEM_FIRE_STOP_ERR:
        out_fire_stop();
        g_sys.status_sys = SYSTEM_IDLE;
        break;

    case SYSTEM_FIRE_STOP:
        out_fire_stop();
        g_sys.status_sys = SYSTEM_IDLE;
        break;

    default:
        break;
    }
}


