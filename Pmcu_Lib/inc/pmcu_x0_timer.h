/**
 * @file
 * @brief		定时器配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.1
 * @par 		Copyright(c): All rights reserved.
 * @par 		修改记录
 * @par 		1.admin，2023-08-21，修正库封装方式，减少代码空间 
*/

#ifndef __PMCU_TIMER_H_
#define __PMCU_TIMER_H_

#include "pmcu_x0_config.h"

/** 定时器工作模式配置 */
typedef enum {
    TIM_MODE_0 = 0,					/*!< 定时器工作模式0，13bit不可重载，最大定时6ms */
    TIM_MODE_1,                 	/*!< 定时器工作模式1，16bit不可重载，最大定时49ms */
    TIM_MODE_2,                 	/*!< 定时器工作模式2，16bit可重载，最大定时49ms */
} TIM_Mode_E;

/**
* @brief  定时器0初始化函数
* @param  TIM_Mode 定时器的工作模式，选择： \n
* @ref TIM_MODE_0 \n
* @ref TIM_MODE_1 \n
* @ref TIM_MODE_2 \n
* @param  TIM_Period 定时器的定时时间，单位us；TIM_MODE_0最大定时时间为6ms，TIM_MODE_1和TIM_MODE_2最大定时时间为49ms
* @param  TIM_En 定时器的启动使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @param  TIM_IntEn 定时器的中断使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_tim0_init(TIM_Mode_E TIM_Mode, U16 TIM_Times, FUNC_EN_E TIM_En, FUNC_EN_E TIM_IntEn);

/**
* @brief  定时器0重装初值
* @param  TIM_Mode 定时器的工作模式，选择： \n
* @ref TIM_MODE_0 \n
* @ref TIM_MODE_1 \n
* @param  TIM_Times 定时器的定时时间，单位us；TIM_MODE_0最大定时时间为6ms，TIM_MODE_1最大定时时间为49ms
* @retval 无
* @par   说明
* -# 仅在TIM_MODE_0和TIM_MODE_1工作模式下使用
*/
void plib_tim0_reload(TIM_Mode_E TIM_Mode, U16 TIM_Times);

/**
* @brief  Timer0是否启动定时
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_tim0_en(FUNC_EN_E ifEn);

/**
* @brief  Timer0中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* 无
*/
void plib_tim0_it_en(FUNC_EN_E ifEn);

/**
* @brief  定时器1初始化函数
* @param  TIM_Mode 定时器的工作模式，选择： \n
* @ref TIM_MODE_0 \n
* @ref TIM_MODE_1 \n
* @ref TIM_MODE_2 \n
* @param  TIM_Period 定时器的定时时间，单位us；TIM_MODE_0最大定时时间为6ms，TIM_MODE_1和TIM_MODE_2最大定时时间为49ms
* @param  TIM_En 定时器的启动使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @param  TIM_IntEn 定时器的中断使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_tim1_init(TIM_Mode_E TIM_Mode, U16 TIM_Times, FUNC_EN_E TIM_En, FUNC_EN_E TIM_IntEn);

/**
* @brief  定时器1重装初值
* @param  TIM_Mode 定时器的工作模式，选择： \n
* @ref TIM_MODE_0 \n
* @ref TIM_MODE_1 \n
* @param  TIM_Times 定时器的定时时间，单位us；TIM_MODE_0最大定时时间为6ms，TIM_MODE_1最大定时时间为49ms
* @retval 无
* @par   说明
* -# 仅在TIM_MODE_0和TIM_MODE_1工作模式下使用
*/
void plib_tim1_reload(TIM_Mode_E TIM_Mode, U16 TIM_Times);

/**
* @brief  Timer1是否启动定时
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_tim1_en(FUNC_EN_E ifEn);

/**
* @brief  Timer1中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* 无
*/
void plib_tim1_it_en(FUNC_EN_E ifEn);

#endif /* end of __PMCU_TIMER_H_ */

