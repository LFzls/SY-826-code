/**************************************************************************************************
 Collection method:
 1. Built-in MOS internal resistance for simple heating wire resistance judgment
 2. External 3R shunt resistor for accurate collection of heating wire resistance
 Collection port:
 1. Built-in MOS can use built-in VOUT_FB pin
 2. Due to capacitor reasons, it is recommended to use external AD_RL_H / AD_RL_L for 3R method
 Use 3R standard resistor and load series circuit
 Measure the accurate load resistance value
 RL_H: ADC sampling value of the end of 3R connected to the battery
 RL_L: ADC sampling value of the end of 3R connected to the load
 The result is in local variables, in mΩ
 **************************************************************************************************/
#include "rl_det.h"

/* Global RL struct */
idata struct rl_det_data g_rl_det[2];
struct piple_state g_rl_piple;

/**
* @brief  Load access detection
* @retval None
* @par   Explanation
* None
*/
void rload_det(void)
{
    //吸烟中，不检测负载插拔
    if(g_out_s.chn[0].fire_on)
    {
        return;
    }

    if(g_rl_det[0].plug_delay)
    {
        --g_rl_det[0].plug_delay;
    }

    if(g_rl_det[0].plug_delay == 0)
    {
        if(plib_mos_get_plug_flg())
        {
            if(g_rl_det[0].rl_plug == 0)
            {
                util_queue_push(EVENT_HEATER_INPUT);
                g_rl_det[0].rl_plug = 1;
                AM_DBG_PRINTF("plug in\r\n");
            }
        }
        else if(g_rl_det[0].rl_plug == 1)
        {
            util_queue_push(EVENT_HEATER_REMOVE);
            g_rl_det[0].rl_plug = 0;
            AM_DBG_PRINTF("plug out\r\n");
        }
    }
}

/**
 * @brief Gets the constant current value of the load.
 * @param gain_sel The gain selection for the PGA.
 */
void rload_get_inmos_ohm(u8 gain_sel)
{
    u16 xdata ad_rl;

    /* Turn off power output and enable load detection */
    plib_mos_en(PLIB_DISABLE);
    plib_adc_pga_sel(gain_sel);
    delay10us(50);
    ad_rl = pmcu_adc_sample_1ch_mul(ADC_CHN0_PGAOUT, 4); //N times conversion and average result calculation
    ad_rl = plib_adc_get_volt_div2(ad_rl);              //Get PGA output voltage
    plib_adc_pga_sel(ADC_PGA_SEL_BYPASS);
    plib_mos_en(PLIB_ENABLE);

    if (gain_sel == ADC_PGA_SEL_x16)
    {
        ad_rl = ad_rl * 10 / 8;
    }
    else
    {
        ad_rl = ad_rl * 10 / 16;
    }

    if (ad_rl < CFG_RL_VALUE_SHORT)
    {
        g_rl_det[0].ohm = 0;
        g_rl_det[0].status = RL_SHORT;
    }
    else if (ad_rl > CFG_RL_VALUE_OPEN)
    {
        g_rl_det[0].ohm = 9999;
        g_rl_det[0].status = RL_OPEN;
    }
    else
    {
        g_rl_det[0].ohm = ad_rl;
        g_rl_det[0].status = RL_NORMAL;
    }

    AM_DBG_PRINTF("ohm=%d, sta=%d\r\n", (u16)ad_rl, (u16)g_rl_det[0].status);
}

/**
 * @brief Detect the rload
 */
static u8 rload_det_inner_firing(void)
{
    rload_get_inmos_ohm(ADC_PGA_SEL_x16);

#if CFG_RLOAD_OPEN_PRO_EN

    if(g_rl_det[0].status == RL_OPEN)
    {
        util_queue_push(EVENT_HEATER_OPEN);
        AM_DBG_PRINTF("rl open\r\n");
        return 1;
    }

#endif

    return 0;
}

/**
 * @brief Detect the rload
 */
static u8 rload_det_ext_firing(void)
{
#if CFG_RLOAD_OPEN_PRO_EN

    if((g_battery.volt.idle - g_battery.volt.fire) < 50)
    {
        g_rl_det[1].ohm = 9999;
        g_rl_det[1].status = RL_OPEN;
        util_queue_push(EVENT_HEATER_OPEN);
        AM_DBG_PRINTF("rl open\r\n");
        return 1;
    }

#endif

    return 0;
}

/**
 * @brief Dry burn prevention test
 * @param none
 */
u8 rload_det_firing(void)
{
    u8 xdata ret = 0;

    if (util_timepass_check(&g_sys.time.dry_det, CFG_VOUT_DET_RL_TIME))
    {
        switch(g_out_s.ouput_mode)
        {
        case OUTPUT_MODE_INMOS_ONLY:
            ret = rload_det_inner_firing();
            break;

        case OUTPUT_MODE_EXMOS_ONLY:
            ret = rload_det_ext_firing();
            break;

        case OUTPUT_MODE_MOS_BOTH:
            ret = rload_det_inner_firing();
            ret += rload_det_ext_firing();
            break;

        default:
            ret = 0;
            break;
        }
    }

    return ret;
}

/**
 * @brief Gets the constant current value of the load.
 */
void rload_get_exmos_ohm(void)
{
    u16 xdata ad_vbat, ad_rl;
#if CFG_PIN_EXTMOS_RL_DET_NONE
    g_rl_det[1].ohm = 1000;   //无测阻电路时，给一个默认的阻值
    g_rl_det[1].status = RL_NORMAL;
#else
    //* Turn off power output and enable load detection */
    plib_mos_en(PLIB_DISABLE);
    g_out_s.chn[1].pwm_duty = 0;
    ExtMOS_Output(DISABLE);

    EXT_RLOAD_DET_EN_Output(ENABLE);
    delay_ms(5);

    ad_vbat = pmcu_adc_sample_1ch(ADC_CHN1_VBAT);
    ad_vbat = plib_adc_get_volt_div2(ad_vbat);
    ad_rl = pmcu_adc_sample_1ch(CFG_EXTMOS_ADC_CHN);
    ad_rl = plib_adc_get_volt_div2(ad_rl);

    EXT_RLOAD_DET_EN_Output(DISABLE);
    delay_ms(5);
    plib_mos_en(PLIB_ENABLE);

    ad_rl = (u32)ad_rl * EXT_RL_DIV_VALUE / (ad_vbat - ad_rl);

    if (ad_rl < CFG_RL_VALUE_SHORT)
    {
        g_rl_det[1].ohm = 0;
        g_rl_det[1].status = RL_SHORT;
    }
    else if (ad_rl > CFG_RL_VALUE_OPEN)
    {
        g_rl_det[1].ohm = 9999;
        g_rl_det[1].status = RL_OPEN;
    }
    else
    {
        g_rl_det[1].ohm = ad_rl;
        g_rl_det[1].status = RL_NORMAL;
    }

#endif
    AM_DBG_PRINTF("e_ohm=%d, sta=%d\r\n", (u16)ad_rl, (u16)g_rl_det[1].status);
}
