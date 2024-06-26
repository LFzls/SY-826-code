/**
 * @file
 * @brief       ADC middleware interface functions
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#include "bsp_adc.h"
#include "bsp_wdt.h"

bit g_bsp_adc_flag;          // ADC sampling completion flag


/**
* @brief  ADC initialization function
* @retval None
* @par   Explanation
* None
*/
void pmcu_adc_init(void)
{
    //Configure ADC parameters
    plib_adc_init(ADC_SAMPLE_380K, ADC_PGA_GAIN_16, ADC_MODE_SOFTWARE, 250);
    //Enable ADC
    plib_adc_en(PLIB_ENABLE);
}

/**
* @brief  ADC single-channel sampling
* @param  channel ADC sampling channel, choose one or more from the following: \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT    \n
* @ref ADC_CHN2_VDD \n
* @ref ADC_CHN3_GPIOB0  \n
* @ref ADC_CHN4_GPIOB1  \n
* @ref ADC_CHN5_GPIOB2  \n
* @retval ADC sample value (AD value)
* @par   Explanation
* None
*/
u16 pmcu_adc_sample_1ch(u8 channel)
{
    u16 timeout = 0;
    //Clear status
    plib_adc_clr_flg(channel);
    //Enable ADC channel and trigger software sampling
    plib_adc_chn_en(channel, PLIB_ENABLE);

    //Wait for sampling completion
    while (!plib_adc_get_flg(channel) && timeout < 2000)
    {
        timeout++;

        //If watchdog is enabled, keep refreshing it
        pmcu_wdt_feed();
    }

    //Clear status
    plib_adc_clr_flg(channel);
    //Get data
    return plib_adc_get_ad_value(channel);
}

/**
* @brief  ADC multi-channel sampling
* @param  channel ADC sampling channel, choose one or more from the following: \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT    \n
* @ref ADC_CHN2_VDD \n
* @ref ADC_CHN3_GPIOB0  \n
* @ref ADC_CHN4_GPIOB1  \n
* @ref ADC_CHN5_GPIOB2  \n
* @retval None
* @par   Explanation
* None
*/
void pmcu_adc_sample_nch(u8 channel)
{
    u16 timeout = 0;
    //Clear status
    plib_adc_clr_flg(channel);
    //Enable ADC channel and trigger software sampling
    plib_adc_chn_en(channel, PLIB_ENABLE);

    //Wait for sampling completion
    while ((plib_adc_get_flg(channel) != channel) && timeout < 2000)
    {
        timeout++;

        //If watchdog is enabled, keep refreshing it
        pmcu_wdt_feed();
    }
}

/**
* @brief  ADC single-channel sampling with interrupt
* @param  channel ADC sampling channel, choose one or more from the following: \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT    \n
* @ref ADC_CHN2_VDD \n
* @ref ADC_CHN3_GPIOB0  \n
* @ref ADC_CHN4_GPIOB1  \n
* @ref ADC_CHN5_GPIOB2  \n
* @retval ADC sample value (AD value)
* @par   Explanation
* None
*/
u16 pmcu_adc_sample_1ch_it(u8 channel)
{
    u16 timeout = 0;
    //ADC sampling completion flag, assigned in the interrupt handler
    g_bsp_adc_flag = 0;
    //Enable channel interrupt
    plib_adc_it_cfg(channel, PLIB_ENABLE);
    plib_adc_it_en(PLIB_ENABLE);
    //Enable ADC channel and trigger software sampling
    plib_adc_clr_flg(channel);
    plib_adc_chn_en(channel, PLIB_ENABLE);

    //Wait for sampling completion g_bsp_adc_flag=0;
    while ((g_bsp_adc_flag == 0) && timeout < 2000)
    {
        timeout++;

        //If watchdog is enabled, keep refreshing it
        pmcu_wdt_feed();
    }

    //Clear status
    plib_adc_clr_flg(channel);
    //Get data
    return plib_adc_get_ad_value(channel);
}

/**
* @brief  ADC multi-channel sampling with interrupt
* @param  channel ADC sampling channel, choose one or more from the following: \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT    \n
* @ref ADC_CHN2_VDD \n
* @ref ADC_CHN3_GPIOB0  \n
* @ref ADC_CHN4_GPIOB1  \n
* @ref ADC_CHN5_GPIOB2  \n
* @retval None
* @par   Explanation
* None
*/
void pmcu_adc_sample_nch_it(u8 channel)
{
    //ADC sampling completion flag, assigned in the interrupt handler
    g_bsp_adc_flag = 0;
    //Enable channel interrupt
    plib_adc_it_cfg(channel, PLIB_ENABLE);
    plib_adc_it_en(PLIB_ENABLE);
    //Enable ADC channel and trigger software sampling
    plib_adc_clr_flg(channel);
    plib_adc_chn_en(channel, PLIB_ENABLE);
    //Wait for the interrupt to complete
}


/**
* @brief  ADC single-channel sampling N times and get the average value
* @param  channel ADC sampling channel, choose one or more from the following: \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT    \n
* @ref ADC_CHN2_VDD \n
* @ref ADC_CHN3_GPIOB0  \n
* @ref ADC_CHN4_GPIOB1  \n
* @ref ADC_CHN5_GPIOB2  \n
* @param  cnt Number of samples
* @retval ADC sample value (AD value)
* @par   Explanation
* None
*/
u16 pmcu_adc_sample_1ch_mul(u8 channel, u8 cnt)
{
    u8 i = 0;
    u16 wADD = 0;

    while (1)
    {
        wADD += pmcu_adc_sample_1ch(channel);

        if ((++i)&cnt)
        {
            break;
        }
    }

    return wADD / cnt;
}

#if CFG_IT_ADC_EN
/**
* @brief  ADC interrupt handler
* @param  None
* @retval None
* @par   Explanation
* None
*/
void pmcu_adc_irq_handler() interrupt 10
{
    u16 timeout = 0;

    //Wait for sampling completion. Wait for all enabled channels' conversion completion flags to be set
    while ((plib_adc_it_ifen(ADC_CHN_ALL) != plib_adc_get_flg(ADC_CHN_ALL)) && timeout < 2000)
    {
        timeout++;

        //If watchdog is enabled, keep refreshing it
        pmcu_wdt_feed();
    }

    //Sampling completion flag
    g_bsp_adc_flag = 1;
    //Sampling completed, clear status
    plib_adc_clr_flg(ADC_CHN_ALL);
}
#endif
