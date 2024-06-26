/**
 * @file
 * @brief		PWM配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.1
 * @par 		Copyright(c): All rights reserved.
 * @par 		修改记录
 * @par 		1.admin，2023-09-05，增加PWM上升沿和下降沿中断是否使能接口  
*/

#ifndef __PMCU_PWM_H_
#define __PMCU_PWM_H_

#include "pmcu_x0_config.h"

#define PWM_TRIG_RISING 	((U8)0x01)	/* PWM上升沿事件 */
#define PWM_TRIG_FALLING	((U8)0x02)	/* PWM下降沿事件 */

/** PWM组选择 */
typedef enum {
    PWM_SEL0 = 0,			/*!< PWM0 */
    PWM_SEL1,				/*!< PWM1 */
} PWM_SEL_E;

/** PWM通道选择 */
typedef enum {
    PWM_CH0 = 0,			/*!< 通道0 */
    PWM_CH1,				/*!< 通道1 */
    PWM_CH2,				/*!< 通道2 */
} PWM_CHN_E;

/** PWM输出时钟分频系数 */
typedef enum {
    PWM_FCLK1 = 0,		/*!< 1分频，最小输出频率：62745Hz */
    PWM_FCLK2,			/*!< 2分频，最小输出频率：31373Hz */
    PWM_FCLK4,          /*!< 4分频，最小输出频率：15686Hz */
    PWM_FCLK8,          /*!< 8分频，最小输出频率：7843Hz */
    PWM_FCLK16,         /*!< 16分频，最小输出频率：3922Hz */
    PWM_FCLK32,         /*!< 32分频，最小输出频率：1960Hz */
    PWM_FCLK64,         /*!< 64分频，最小输出频率：980Hz */
    PWM_FCLK128,        /*!< 128分频，最小输出频率：490Hz */
} PWM_FCLK_E;

/**
* @brief  PWM初始化函数
* @param  pwmsel PWM组选择： \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  Fclk_div 分频系数，选择： \n
* @ref PWM_FCLK1  \n
* @ref PWM_FCLK2  \n
* @ref PWM_FCLK4  \n
* @ref PWM_FCLK8  \n
* @ref PWM_FCLK16 \n
* @ref PWM_FCLK32 \n
* @ref PWM_FCLK64 \n
* @ref PWM_FCLK128 \n
* @param  Period 周期配置，配置值=16000000/时钟分频系数/输出频率
* @param  CH0_Duty 通道0占空比配置，配置值=周期*输出占空比
* @param  CH1_Duty 通道1占空比配置，配置值=周期*输出占空比
* @param  CH2_Duty 通道2占空比配置，配置值=周期*输出占空比
* @param  ifNegate 是否使能极性反转 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_pwm_init(PWM_SEL_E pwmsel, PWM_FCLK_E Fclk_div, U8 Period, U8 CH0_Duty, U8 CH1_Duty, U8 CH2_Duty, U8 ifNegate);

/**
* @brief  PWM输出使能
* @param  pwmsel PWM组选择： \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_pwm_en(PWM_SEL_E pwmsel, FUNC_EN_E ifEn);

/**
* @brief  PWM输出极性反转使能
* @param  pwmsel PWM组选择： \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_pwm_negate_en(PWM_SEL_E pwmsel, FUNC_EN_E ifEn);

/**
* @brief  同时设置，PWM输出占空比设置
* @param  pwmsel PWM组选择： \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  duty0 通道0占空比配置，配置值=周期*输出占空比
* @param  duty1 通道1占空比配置，配置值=周期*输出占空比
* @param  duty2 通道2占空比配置，配置值=周期*输出占空比
* @retval 无
* @par   说明
* -# 不使用的通道，配置为0即可
*/
void plib_pwm_set_chn_duty(PWM_SEL_E pwmsel, U8 duty0, U8 duty1, U8 duty2);

/**
* @brief  PWM中断使能
* @param  pwmsel PWM组选择： \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  event PWM中断事件： \n
* @ref PWM_TRIG_RISING  \n
* @ref PWM_TRIG_FALLING  \n
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* -# 仅通道0会触发上升沿和下降沿中断，且100%占空比时，不会触发中断
*/
void plib_pwm_it_cfg(PWM_SEL_E pwmsel, U8 event, FUNC_EN_E ifEn);

/**
* @brief  PWM中断是否使能
* @param  pwmsel PWM组选择： \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  event PWM中断事件： \n
* @ref PWM_TRIG_RISING  \n
* @ref PWM_TRIG_FALLING  \n
* @retval  事件中断使能状态
* - 0 未使能
* - 非0 已使能
* @par 说明
* 无
*/
U8 plib_pwm_it_ifen(PWM_SEL_E pwmsel, U8 event);

/**
* @brief  PWM总中断使能
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* -# 与MOS PWM共用一个中断使能
*/
void plib_pwm_it_en(FUNC_EN_E ifEn);

/**
* @brief  PWM事件状态
* @param  pwmsel PWM组选择： \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  event PWM中断事件： \n
* @ref PWM_TRIG_RISING  \n
* @ref PWM_TRIG_FALLING  \n
* @retval  事件触发状态
* - 0 未触发对应状态
* - 非0 触发了对应状态
* @par   说明
* -# 仅通道0会触发上升沿和下降沿状态
*/
U8 plib_pwm_get_flg(PWM_SEL_E pwmsel, U8 event);

/**
* @brief  清除PWM事件状态
* @param  pwmsel PWM组选择： \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  event PWM中断事件： \n
* @ref PWM_TRIG_RISING  \n
* @ref PWM_TRIG_FALLING  \n
* @retval 无
* @par   说明
* 无
*/
void plib_pwm_clr_flg(PWM_SEL_E pwmsel, U8 event);

#endif /* end of __PMCU_PWM_H_ */

