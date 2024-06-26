/**
 * @file
 * @brief       Microphone middleware interface functions
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/


#include "bsp_mic.h"

/**
* @brief  Microphone initialization function
* @retval None
* @par   Explanation
* None
*/
void pmcu_mic_init(void)
{
#if CFG_MIC_TYPE == 0 || CFG_MIC_TYPE == 1 //Electret Microphone
    //MIC parameter initialization
    plib_mic_en(PLIB_DISABLE);
    plib_mic_init(CFG_MIC_IT, CFG_MIC_MIC_CURR, CFG_MIC_SAMPLE_TIME, CFG_MIC_INHALE_TIMEOUT);
    plib_mic_en(PLIB_ENABLE);
    delay_ms(320);
    //Set the first and second thresholds
    plib_mic_set_trig(CFG_MIC_TRIG1_THD, CFG_MIC_TRIG2_THD);
    //MIC global interrupt enable
    //plib_mic_it_en(PLIB_ENABLE);
#else   //Custom Switch Microphone, disable capacitance MIC module to reduce power consumption
    //Disable the microphone
    plib_mic_en(PLIB_DISABLE);
#endif
}

#if CFG_IT_MIC_EN
/**
  * @brief  Microphone interrupt handler
  * @param  none
  * @retval none
  */
void pmcu_mic_irq_handler() interrupt 0
{
    if (plib_mic_get_flg(MIC_INHALE_RELEASE) && plib_mic_it_ifen(MIC_INHALE_RELEASE))
    {
        plib_mic_clr_flg(MIC_INHALE_RELEASE);
    }

    if (plib_mic_get_flg(MIC_INHALE) && plib_mic_it_ifen(MIC_INHALE))
    {
        plib_mic_clr_flg(MIC_INHALE);
    }
}
#endif
