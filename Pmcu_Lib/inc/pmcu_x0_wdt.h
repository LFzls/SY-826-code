/**
 * @file
 * @brief		看门狗配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#ifndef __PMCU_WDT_H_
#define __PMCU_WDT_H_

#include "pmcu_x0_config.h"

/**
* @brief  看门狗溢出时间配置
* @param  Tim_ms 看门狗溢出时间，单位ms，最大值配置1500
* @retval 无
* @par   说明
* 无
*/
void plib_wdt_set_time(U16 Tim_ms);

/**
* @brief  看门狗开启
* @param  无
* @retval 无
* @par   说明
* 无
*/
void plib_wdt_open(void);

/**
* @brief  看门狗是否开启
* @param  无
* @retval  看门狗状态
* - 0 看门狗未开启
* - 非0 看门狗已开启
* @par   说明
* 无
*/
U8 plib_wdt_if_open(void);

/**
* @brief  看门狗关闭
* @param  无
* @retval 无
* @par   说明
* 无
*/
void plib_wdt_close(void);

/**
* @brief  看门狗喂狗
* @param  无
* @retval 无
* @par   说明
* 无
*/
void plib_wdt_reflesh(void);

#endif /* end of __PMCU_WDT_H_ */

