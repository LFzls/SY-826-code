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
#include "pmcu_x0_pwm.h"

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
void plib_pwm_init(PWM_SEL_E pwmsel, PWM_FCLK_E Fclk_div, U8 Period, U8 CH0_Duty, U8 CH1_Duty, U8 CH2_Duty, U8 ifNegate)
{
    if (pwmsel == PWM_SEL0) {
        //分频系数
        PREG_PWM0_CTRL = (PREG_PWM0_CTRL & 0xF8) | Fclk_div;

        //极性翻转
        if (ifNegate == PLIB_ENABLE)
            PREG_PWM0_CTRL |= 0x08;
        else
            PREG_PWM0_CTRL &= ~0x08;

        //占空比配置
        PREG_PWM0_DUTY_CH0 = CH0_Duty;
        PREG_PWM0_DUTY_CH1 = CH1_Duty;
        PREG_PWM0_DUTY_CH2 = CH2_Duty;
        //周期配置
        PREG_PWM0_PERIOD = Period;
    } else if (pwmsel == PWM_SEL1) {
        //分频系数
        PREG_PWM1_CTRL = (PREG_PWM1_CTRL & 0xF8) | Fclk_div;

        //极性翻转
        if (ifNegate == PLIB_ENABLE)
            PREG_PWM1_CTRL |= 0x08;
        else
            PREG_PWM1_CTRL &= ~0x08;

        //占空比配置
        PREG_PWM1_DUTY_CH0 = CH0_Duty;
        PREG_PWM1_DUTY_CH1 = CH1_Duty;
        PREG_PWM1_DUTY_CH2 = CH2_Duty;
        //周期配置
        PREG_PWM1_PERIOD = Period;
    }
}


/**
* @brief  PWM输出使能
* @param  pwmsel PWM组选择： \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_pwm_en(PWM_SEL_E pwmsel, FUNC_EN_E ifEn)
{
    if (pwmsel == PWM_SEL0) {
        if (ifEn == PLIB_ENABLE)
            PREG_PWM0_CTRL |= 0x10;
        else
            PREG_PWM0_CTRL &= ~0x10;
    } else if (pwmsel == PWM_SEL1) {
        if (ifEn == PLIB_ENABLE)
            PREG_PWM1_CTRL |= 0x10;
        else
            PREG_PWM1_CTRL &= ~0x10;
    }
}

/**
* @brief  PWM输出极性反转使能
* @param  pwmsel PWM组选择： \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_pwm_negate_en(PWM_SEL_E pwmsel, FUNC_EN_E ifEn)
{
    if (pwmsel == PWM_SEL0) {
        if (ifEn == PLIB_ENABLE)
            PREG_PWM0_CTRL |= 0x08;
        else
            PREG_PWM0_CTRL &= ~0x08;
    } else if (pwmsel == PWM_SEL1) {
        if (ifEn == PLIB_ENABLE)
            PREG_PWM1_CTRL |= 0x08;
        else
            PREG_PWM1_CTRL &= ~0x08;
    }
}

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
void plib_pwm_set_chn_duty(PWM_SEL_E pwmsel, U8 duty0, U8 duty1, U8 duty2)
{
    if (pwmsel == PWM_SEL0) {
        //配置占空比
        PREG_PWM0_DUTY_CH0 = duty0;
        PREG_PWM0_DUTY_CH1 = duty1;
        PREG_PWM0_DUTY_CH2 = duty2;
        //配置一次周期，生效
        PREG_PWM0_PERIOD = PREG_PWM0_PERIOD;
    } else if (pwmsel == PWM_SEL1) {
        //配置占空比
        PREG_PWM1_DUTY_CH0 = duty0;
        PREG_PWM1_DUTY_CH1 = duty1;
        PREG_PWM1_DUTY_CH2 = duty2;
        //配置一次周期，生效
        PREG_PWM1_PERIOD = PREG_PWM1_PERIOD;
    }
}

/**
* @brief  PWM中断使能
* @param  pwmsel PWM组选择： \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  event PWM中断事件： \n
* @ref PWM_TRIG_RISING  \n
* @ref PWM_TRIG_FALLING  \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* -# 仅通道0会触发上升沿和下降沿中断，且100%占空比时，不会触发中断
*/
void plib_pwm_it_cfg(PWM_SEL_E pwmsel, U8 event, FUNC_EN_E ifEn)
{
    if (pwmsel == PWM_SEL0) {
        if (ifEn == PLIB_ENABLE)
            PREG_PWM_IEN = (PREG_PWM_IEN & 0xCF) | (event << 4);
        else
            PREG_PWM_IEN &= ~(event << 4);
    } else if (pwmsel == PWM_SEL1) {
        if (ifEn == PLIB_ENABLE)
            PREG_PWM_IEN = (PREG_PWM_IEN & 0x3F) | (event << 6);
        else
            PREG_PWM_IEN &= ~(event << 6);
    }
}

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
U8 plib_pwm_it_ifen(PWM_SEL_E pwmsel, U8 event)
{
    if (pwmsel == PWM_SEL0) 
		return (PREG_PWM_IEN & (event << 4));
    else if (pwmsel == PWM_SEL1) 
		return (PREG_PWM_IEN & (event << 6));
    else
		return 0;
}

/**
* @brief  PWM总中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* -# 与MOS PWM共用一个中断使能
*/
void plib_pwm_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EX5 = 1;
    else
        PBIT_EX5 = 0;
}

/**
* @brief  获取PWM事件状态
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
U8 plib_pwm_get_flg(PWM_SEL_E pwmsel, U8 event)
{
    if (pwmsel == PWM_SEL0) {
        return (PREG_PWM_IEN & (event << 0));
    } else if (pwmsel == PWM_SEL1) {
        return (PREG_PWM_IEN & (event << 2));
    } else {
        return 0;
    }
}

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
void plib_pwm_clr_flg(PWM_SEL_E pwmsel, U8 event)
{
    if (pwmsel == PWM_SEL0) {
        PREG_PWM_IEN &= ~(event << 0);
    } else if (pwmsel == PWM_SEL1) {
        PREG_PWM_IEN &= ~(event << 2);
    }
}

