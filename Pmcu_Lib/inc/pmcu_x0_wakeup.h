/**
 * @file
 * @brief		睡眠唤醒配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#ifndef __PMCU_WAKEUP_H_
#define __PMCU_WAKEUP_H_

#include "pmcu_x0_config.h"

#define	WK_SRC_GPIO  		((U8)0x01)		/*!< GPIO边沿唤醒源 */
#define	WK_SRC_PLUG  		((U8)0x02)		/*!< 负载拔插唤醒源 */
#define	WK_SRC_USB  		((U8)0x04)      /*!< USB拔插唤醒源 */
#define	WK_SRC_CHG_FULL  	((U8)0x08)      /*!< 充电满充唤醒源 */
#define	WK_SRC_MIC  		((U8)0x10)      /*!< MIC事件唤醒源 */
#define	WK_SRC_TIMER  		((U8)0x80)      /*!< 定时唤醒源 */

/**
* @brief  系统进入睡眠模式
* @param  无
* @retval 无
* @par    说明
* @par    说明
* -# 为避免睡眠漏电，睡眠前需要把所有IO配置成内部下拉模式（芯片外部无上拉前提下）
*/
void plib_wk_sleep(void);

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
void plib_wk_init(U8 Src, U8 Timer_cfg);

#endif /* end of __PMCU_WAKEUP_H_ */

