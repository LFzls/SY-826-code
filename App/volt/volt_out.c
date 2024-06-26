#include "volt_out.h"

/* Global output structure */
idata struct output_ctrl g_out_s;

/**
 * @brief Switch the output channel
 */
void output_mos_change(void)
{
#if CFG_VOUT_CNH_MAX==1 //仅内部单发
    g_userdata_t.output_mode = g_out_s.ouput_mode = OUTPUT_MODE_INMOS_ONLY;
    AM_DBG_PRINTF("inmos\r\n");

#elif CFG_VOUT_CNH_MAX==2   //仅外部单发
    g_userdata_t.output_mode = g_out_s.ouput_mode = OUTPUT_MODE_EXMOS_ONLY;
    AM_DBG_PRINTF("exmos\r\n");

#else   //双发，切换   

    //选择双发同时输出
    if(g_userdata_t.output_mode == OUTPUT_MODE_MOS_BOTH)
    {
        g_userdata_t.output_mode = g_out_s.ouput_mode = OUTPUT_MODE_INMOS_ONLY;
        AM_DBG_PRINTF("inmos\r\n");
    }
    else if(g_userdata_t.output_mode == OUTPUT_MODE_INMOS_ONLY)    //当前为内部MOS，接下来切为外部MOS输出
    {
        g_userdata_t.output_mode = g_out_s.ouput_mode = OUTPUT_MODE_EXMOS_ONLY;
        AM_DBG_PRINTF("exmos\r\n");
    }
    else if(g_userdata_t.output_mode == OUTPUT_MODE_EXMOS_ONLY)    //当前为内部MOS，接下来切为外部MOS输出
    {
        g_userdata_t.output_mode = g_out_s.ouput_mode = OUTPUT_MODE_MOS_BOTH;
        AM_DBG_PRINTF("both\r\n");
    }
    else    //切为内部MOS输出
    {
        g_userdata_t.output_mode = g_out_s.ouput_mode = OUTPUT_MODE_INMOS_ONLY;
        AM_DBG_PRINTF("inmos\r\n");
    }

#endif
}

/**
 * @brief Start the fire output
 */
static void out_fire_inner_start(void)
{
    g_out_s.chn[0].pwm_open_dly = 0;
    g_out_s.chn[0].pwm_open_flg = 0;
    plib_mos_set_duty(CFG_MOS_PWM_PERIOD / 2);  //先以一半占空比输出，造MOS PWM上升沿，以触发ADC采样

    //输出目标值在切换双发输出时设置
    g_out_s.chn[0].v_user_set = CFG_MOS_OUTPUT_TARGET + CFG_MOS_OUTPUT_TARGET_FIX; //输出目标值
    g_out_s.chn[0].fire_on = 1;
}

/**
 * @brief Start the fire output
 */
static void out_fire_inner_ctrl_cv(void)
{
    u16 xdata duty;

    duty = (u16)(((u32)g_out_s.chn[0].v_user_set * CFG_MOS_PWM_PERIOD) / g_out_s.chn[0].v_mos_out);

    //恒有效或恒功率
#if (CFG_MOS_OUT_MODE==1) || (CFG_MOS_OUT_MODE==3)
    duty = (u32)duty * g_out_s.chn[0].v_user_set / g_out_s.chn[0].v_mos_out;
#endif

    if (duty >= CFG_MOS_PWM_PERIOD_MAX)
    {
        g_out_s.chn[0].pwm_duty = CFG_MOS_PWM_PERIOD_MAX;
    }
    else if (duty < CFG_MOS_PWM_PERIOD_MIN)
    {
        g_out_s.chn[0].pwm_duty = CFG_MOS_PWM_PERIOD_MIN;
    }
    else
    {
        g_out_s.chn[0].pwm_duty = duty;
    }

    plib_mos_set_duty(g_out_s.chn[0].pwm_duty);
    AM_DBG_PRINTF("T1:%d, V:%d, D:%d\r\n", (u16)g_out_s.chn[0].v_user_set, (u16)g_out_s.chn[0].v_mos_out, (u16)((u32)g_out_s.chn[0].pwm_duty * 100 / CFG_MOS_PWM_PERIOD));
}

/**
 * @brief Start the fire output
 */
static void out_fire_inner_stop(void)
{
    g_out_s.chn[0].pwm_duty = 0;
    plib_mos_set_duty(0);
    g_out_s.chn[0].fire_on = 0;

    //X*10ms后，才检测负载插拔，避免功率输出对负载插拔影响
    g_rl_det[0].plug_delay = 20;
}

/**
 * @brief Start the fire output
 */
static void out_fire_ext_start(void)
{
    g_out_s.chn[1].pwm_open_dly = 0;
    g_out_s.chn[1].pwm_open_flg = 0;
    g_out_s.chn[1].pwm_duty = CFG_EXTMOS_PWM_PERIOD / 2; //先以一半占空比输出，造MOS PWM上升沿，以触发ADC采样

    //输出目标值在切换双发输出时设置
    g_out_s.chn[1].v_user_set = CFG_EXTMOS_OUTPUT_TARGET + CFG_EXTMOS_OUTPUT_TARGET_FIX; //输出目标值
    g_out_s.chn[1].fire_on = 1;

    //置位上升沿标志位，开始触发调压
    g_out_s.chn[1].pwm_ris_flg = 1;
}

/**
 * @brief Start the fire output
 */
static void out_fire_ext_ctrl_cv(void)
{
    u16 xdata duty;

    duty = (u16)(((u32)g_out_s.chn[1].v_user_set * CFG_EXTMOS_PWM_PERIOD) / g_out_s.chn[1].v_mos_out);

    //恒有效或恒功率
#if (CFG_EXTMOS_OUT_MODE==1) || (CFG_EXTMOS_OUT_MODE==3)
    duty = (u32)duty * g_out_s.chn[1].v_user_set / g_out_s.chn[1].v_mos_out;
#endif

    if (duty >= CFG_EXTMOS_PWM_PERIOD_MAX)
    {
        g_out_s.chn[1].pwm_duty = CFG_EXTMOS_PWM_PERIOD_MAX;
    }
    else if (duty < CFG_EXTMOS_PWM_PERIOD_MIN)
    {
        g_out_s.chn[1].pwm_duty = CFG_EXTMOS_PWM_PERIOD_MIN;
    }
    else
    {
        g_out_s.chn[1].pwm_duty = duty;
    }

    //再次置位上升沿标志位，开始触发调压
    g_out_s.chn[1].pwm_ris_flg = 1;

    AM_DBG_PRINTF("T2:%d, V:%d, D:%d\r\n", (u16)g_out_s.chn[1].v_user_set, (u16)g_out_s.chn[1].v_mos_out, (u16)((u32)g_out_s.chn[1].pwm_duty * 100 / CFG_EXTMOS_PWM_PERIOD));
}

/**
 * @brief Start the fire output
 */
static void out_fire_ext_stop(void)
{
    g_out_s.chn[1].pwm_duty = 0;
    ExtMOS_Output(DISABLE);
    g_out_s.chn[1].fire_on = 0;
}

/**
 * @brief Start the fire output
 */
void out_fire_start(void)
{
    /* Switch output chn */
    output_mos_change();

    /* Clear ABN */
    pmcu_mos_abn_clr();

    reset_src_set(); // Set reset flg

    switch(g_out_s.ouput_mode)
    {
    case OUTPUT_MODE_INMOS_ONLY:
        out_fire_inner_start();
        break;

    case OUTPUT_MODE_EXMOS_ONLY:
        out_fire_ext_start();
        break;

    case OUTPUT_MODE_MOS_BOTH:
        out_fire_inner_start();
        out_fire_ext_start();
        break;

    default:
        break;
    }

    LED_Show_FireStart();


}

/**
 * @brief Stop the fire output
 */
void out_fire_stop(void)
{
    switch(g_out_s.ouput_mode)
    {
    case OUTPUT_MODE_INMOS_ONLY:
        out_fire_inner_stop();
        break;

    case OUTPUT_MODE_EXMOS_ONLY:
        out_fire_ext_stop();
        break;

    case OUTPUT_MODE_MOS_BOTH:
        out_fire_inner_stop();
        out_fire_ext_stop();
        break;

    default:
        break;
    }

    /* 吸烟结束，1S后才允许采集电池电压 */
    g_battery.sample_delay = CFG_OUTPUT_STOP_UPDATE_BATTERY_TIME;

    /* Enable chg */
    plib_chg_en(PLIB_ENABLE);

    reset_src_clear(); // Clr reset flg
}

/**
 * @brief Voltage output control
 */
void out_ctrl_cv(void)
{
    switch(g_out_s.ouput_mode)
    {
    case OUTPUT_MODE_INMOS_ONLY:
        out_fire_inner_ctrl_cv();
        break;

    case OUTPUT_MODE_EXMOS_ONLY:
        out_fire_ext_ctrl_cv();
        break;

    case OUTPUT_MODE_MOS_BOTH:
        out_fire_inner_ctrl_cv();
        out_fire_ext_ctrl_cv();
        break;

    default:
        break;
    }
}

/**
 * @brief Control the constant power output
 */
void out_ctrl_cw(void)
{
    g_out_s.chn[0].v_user_set = sqrt((u32)(CFG_MOS_OUTPUT_TARGET + CFG_MOS_OUTPUT_TARGET_FIX) * g_rl_det[0].ohm);
}

