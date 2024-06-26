/**
 * @file
 * @brief		MOTOR配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#ifndef __PMCU_MOTOR_H_
#define __PMCU_MOTOR_H_

#include "pmcu_x0_config.h"

/** MOTOR输出占空比 */
typedef enum {
    MOTOR_DUTY_0 = 0,		/*!< 0%   */
    MOTOR_DUTY_7,			/*!< 7%   */
    MOTOR_DUTY_13,			/*!< 13%  */
    MOTOR_DUTY_20,			/*!< 20%  */
    MOTOR_DUTY_27,			/*!< 27%  */
    MOTOR_DUTY_33,			/*!< 33%  */
    MOTOR_DUTY_40,			/*!< 40%  */
    MOTOR_DUTY_47,			/*!< 47%  */
    MOTOR_DUTY_53,			/*!< 53%  */
    MOTOR_DUTY_60,			/*!< 60%  */
    MOTOR_DUTY_67,			/*!< 67%  */
    MOTOR_DUTY_73,			/*!< 73%  */
    MOTOR_DUTY_80,			/*!< 80%  */
    MOTOR_DUTY_87,			/*!< 87%  */
    MOTOR_DUTY_93,			/*!< 93%  */
    MOTOR_DUTY_100,			/*!< 100% */
} MOTOR_DUTY_E;

/**
* @brief  MOTOR PWM输出使能
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_motor_en(FUNC_EN_E ifEn);

/**
* @brief  MOTOR输出占空比设置
* @param  duty 占空比设置，选择： \n
*@ref MOTOR_DUTY_0  \n
*@ref MOTOR_DUTY_7  \n
*@ref MOTOR_DUTY_13 \n
*@ref MOTOR_DUTY_20 \n
*@ref MOTOR_DUTY_27 \n
*@ref MOTOR_DUTY_33 \n
*@ref MOTOR_DUTY_40 \n
*@ref MOTOR_DUTY_47 \n
*@ref MOTOR_DUTY_53 \n
*@ref MOTOR_DUTY_60 \n
*@ref MOTOR_DUTY_67 \n
*@ref MOTOR_DUTY_73 \n
*@ref MOTOR_DUTY_80 \n
*@ref MOTOR_DUTY_87 \n
*@ref MOTOR_DUTY_93 \n
*@ref MOTOR_DUTY_100 \n
* @retval 无
* @par   说明
* 无
*/
void plib_motor_set_duty(MOTOR_DUTY_E duty);

#endif /* end of __PMCU_MOTOR_H_ */

