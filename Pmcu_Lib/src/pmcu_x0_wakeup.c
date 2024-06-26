/**
 * @file
 * @brief		睡眠唤醒配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/
#include "pmcu_x0_wakeup.h"

/**
  * @brief  系统进入睡眠模式
  * @param  无
  * @retval 无
  * @par   说明
		   无
  */
void plib_wk_sleep(void)
{
    PREG_WK_CTRL |= 0x80;

    while (!(PREG_WK_CTRL & 0x80));			//等待系统允许进入睡眠

    PREG_PCON |= 0x80; 			//系统进入睡眠
}

/**
* @brief  唤醒源配置
* @param  Src 唤醒源使能，选择以下一个或多个： \n
* @ref WK_SRC_GPIO \n
* @ref WK_SRC_PLUG \n
* @ref WK_SRC_USB \n
* @ref WK_SRC_CHG_FULL \n
* @ref WK_SRC_MIC \n
* @ref WK_SRC_TIMER \n
* @param  Timer_cfg 使能定时唤醒时，配置定时时长，最大配置值为127，时长=配置值*7.76ms，不使用时配置为0
* @retval 无
* @par   说明
* -# 若使能WK_SRC_TIMER唤醒源，需要设置Timer_cfg唤醒时间
* -# 若使能WK_SRC_MIC唤醒源，需要调用plib_mic_it_cfg()设置具体的MIC唤醒事件
* -# 若使能WK_SRC_GPIO唤醒源，需要调用plib_gpio_it_cfg()设置具体哪个IO唤醒，且需要调用plib_gpio_init()设置IO为输入模式
*/
void plib_wk_init(U8 Src, U8 Timer_cfg)
{
    //定时睡眠唤醒
    if (Src & WK_SRC_TIMER)
        PREG_WK_TIMER_CFG = 0x80 | (Timer_cfg & 0x7F);
    else
        PREG_WK_TIMER_CFG = 0x01;

    //一级唤醒源配置
    PREG_WK_CTRL = (PREG_WK_CTRL & 0xE0) | (Src & 0x7F);
}
