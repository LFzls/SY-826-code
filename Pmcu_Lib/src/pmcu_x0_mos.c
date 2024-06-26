/**
 * @file
 * @brief		MOS PWM配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.1
 * @par 		Copyright(c): All rights reserved.
 * @par 		修改记录
 * @par 		1.admin，2023-09-05，增加MOS上升沿和下降沿中断是否使能接口 
*/

#include "pmcu_x0_mos.h"

/**
* @brief  MOS PWM初始化函数
* @param  Fclk_div 分频系数，选择： \n
* @ref MOS_Fclk  \n
* @ref MOS_Fclk2  \n
* @ref MOS_Fclk4  \n
* @ref MOS_Fclk8  \n
* @ref MOS_Fclk16 \n
* @param  Period 周期配置，配置值=16000000/时钟分频系数/输出频率
* @param  Duty 占空比配置，配置值=周期*输出占空比
* @param  Ocp_Thd 功率输出过流保护阈值，选择： \n
* @ref MOS_OCP_4A  \n
* @ref MOS_OCP_5A  \n
* @ref MOS_OCP_6A  \n
* @ref MOS_OCP_7A  \n
* @param  OcpEn 功率输出过流保护使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @param  OtpEn 功率输出过温保护使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_mos_init(MOS_FCLK_E Fclk_div, U16 Period, U16 Duty, MOS_OCP_THD_E Ocp_Thd, FUNC_EN_E OcpEn, FUNC_EN_E OtpEn)
{
    //功率输出过流保护阈值
    PREG_MOS_CFG = (PREG_MOS_CFG & 0xF3) | (Ocp_Thd << 2);

    //功率输出过流保护使能
    if (OcpEn == PLIB_ENABLE)
        PREG_MOS_CTRL |= 0x40;
    else
        PREG_MOS_CTRL &= ~0x40;

    //功率输出过温保护使能
    if (OtpEn == PLIB_ENABLE)
        PREG_MOS_CTRL |= 0x80;
    else
        PREG_MOS_CTRL &= ~0x80;

    //分频系数
    PREG_MOS_CTRL = (PREG_MOS_CTRL & 0xF8) | Fclk_div;
    //周期配置
    PREG_MOS_PERIOD_L = (U8)(Period & 0xFF);
    PREG_MOS_PERIOD_H = (U8)(Period >> 8);
    //占空比配置，配置值
    PREG_MOS_DUTY_L = (U8)(Duty & 0xFF);
    PREG_MOS_DUTY_H = (U8)(Duty >> 8);
}

/**
* @brief  外扩MOS驱动初始化函数
* @param  Exmos1 内/外MOS开关同步使能位，使用外部NMOS时必须PLIB_ENABLE，以确保外部NMOS比内部NMOS先导通 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @param  Exmos2 内/外MOS开关同步附加使能位，仅Exmos1=PLIB_ENABLE时，配置有效 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @param  Speed1 内/外MOS功率管上升/下降斜率1，仅Exmos1=PLIB_ENABLE时，配置有效 \n
* @ref MOS_SPEED4 \n
* @ref MOS_SPEED3 \n
* @ref MOS_SPEED2 \n
* @ref MOS_SPEED1 \n
* @param  Speed2 内/外MOS功率管上升/下降斜率2，仅Exmos1=PLIB_ENABLE时，配置有效 \n
* @ref MOS_SPEED4 \n
* @ref MOS_SPEED3 \n
* @retval 无
* @par   说明
* -# 这里说的外扩MOS是指使用MOS_EXT管脚驱动
*/
void plib_exmos_init(FUNC_EN_E Exmos1, FUNC_EN_E Exmos2, MOS_SPEED_E Speed1, MOS_SPEED_E Speed2)
{
    if (Exmos1 == PLIB_ENABLE) {
        PREG_MOS_CTRL |= 0x20;
        //内/外MOS功率管上升/下降斜率1
        //内/外MOS功率管上升/下降斜率2
        PREG_MOS_CFG = (PREG_MOS_CFG & 0x0F) | (Speed1 << 4) | (Speed2 << 6);

        if (Exmos2 == PLIB_ENABLE)
            PREG_MOS_CTRL |= 0x10;
        else
            PREG_MOS_CTRL &= ~0x10;
    } else {
        PREG_MOS_CTRL &= ~0x20;
    }
}

/**
* @brief  MOS PWM输出使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_mos_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_MOS_CTRL |= 0x08;
    else
        PREG_MOS_CTRL &= ~0x08;
}

/**
* @brief  MOS PWM占空比配置
* @param  duty 占空比配置，配置值=周期*输出占空比
* @retval 无
* @par   说明
* 无
*/
void plib_mos_set_duty(U16 duty)
{
    PREG_MOS_DUTY_L = (U8)(duty & 0xFF);
    PREG_MOS_DUTY_H = (U8)(duty >> 8);
}

/**
* @brief  获取MOS事件状态
* @param  event MOS中断事件： \n
* @ref MOS_TRIG_RISING  \n
* @ref MOS_TRIG_FALLING  \n
* @retval  事件触发状态
* - 0 未触发对应状态
* - 非0 触发了对应状态
* @par   说明
* 无
*/
U8 plib_mos_get_flg(U8 event)
{
    return (PREG_MOS_IEN & event);
}

/**
* @brief  清除MOS事件状态
* @param  event MOS中断事件： \n
* @ref MOS_TRIG_RISING  \n
* @ref MOS_TRIG_FALLING  \n
* @retval 无
* @par   说明
* 无
*/
void plib_mos_clr_flg(U8 event)
{
    PREG_MOS_IEN &= ~event;
}


/**
* @brief  MOS中断使能
* @param  event MOS中断事件： \n
* @ref MOS_TRIG_RISING  \n
* @ref MOS_TRIG_FALLING  \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @par   说明
* 无
*/
void plib_mos_it_cfg(U8 event, FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_MOS_IEN = (PREG_MOS_IEN & 0xF3) | (event << 2);
    else
        PREG_MOS_IEN &= ~(event << 2);
}

/**
* @brief  MOS中断是否使能
* @param  event MOS中断事件： \n
* @ref MOS_TRIG_RISING  \n
* @ref MOS_TRIG_FALLING  \n
* @retval  事件中断使能状态
* - 0 未使能
* - 非0 已使能
* @par 说明
* 无
*/
U8 plib_mos_it_ifen(U8 event)
{
    return (PREG_MOS_IEN & (event << 2));
}

/**
* @brief  MOS总中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* -# MOS PWM上升/下降沿和PWM0/1共用一个中断使能
*/
void plib_mos_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EX5 = 1;
    else
        PBIT_EX5 = 0;
}

/**
* @brief  获取MOS异常事件状态
* @param  event 异常中断事件： \n
* @ref MOS_OCP  \n
* @ref MOS_OTP  \n
* @retval  事件触发状态
* - 0 未触发对应状态
* - 非0 触发了对应状态
* @par   说明
* 无
*/
U8 plib_mos_get_abn_flg(U8 event)
{
    return (PREG_CHG_FLAG & (event >> 2));
}

/**
* @brief  清除MOS异常事件状态
* @param  event 异常中断事件： \n
* @ref MOS_OCP  \n
* @ref MOS_OTP  \n
* @retval 无
* @par   说明
* 无
*/
void plib_mos_clr_abn_flg(U8 event)
{
    PREG_CHG_FLAG &= ~(event >> 2);
}

/**
* @brief  MOS异常中断使能
* @param  event 异常中断事件： \n
* @ref MOS_OCP  \n
* @ref MOS_OTP  \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @par   说明
* 无
*/
void plib_mos_abn_it_cfg(U8 event, FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_CHG_CTRL = (PREG_CHG_CTRL & 0x9F) | event;
    else
        PREG_CHG_CTRL &= ~event;
}

/**
* @brief  MOS异常总中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_mos_abn_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EX6 = 1;
    else
        PBIT_EX6 = 0;
}

/**
* @brief  检测负载插拔状态
* @param  无
* @retval 负载状态
* - 0 负载未接入
* - 非0 负载已接入
* @par   说明
* 无
*/
U8 plib_mos_get_plug_flg(void)
{
    return (PREG_SENSOR_CTRL & 0x10);
}

/**
* @brief  获取OCP锁定，MOS输出状态
* @param  无
* @retval MOS锁定状态
* - 0 未锁定
* - 非0 出现OCP，已锁定
* @par   说明
* -# 当MOS PWM输出且出现OCP异常时，内部硬件自动锁存，关闭MOS PWM输出。
* -# 至少等待1ms后，可通过plib_mos_ocp_unlock()解锁，
* -# OCP异常已解除，MOS PWM则继续输出，否则会继续置位此位
*/
U8 plib_mos_get_ocp_lock(void)
{
    return (PREG_MOS_IEN & 0x10);
}

/**
* @brief  OCP异常解除，解锁MOS输出
* @param  无
* @retval 无
* @par   说明
* -# OCP异常已解除，MOS PWM则继续输出，否则会继续锁定MOS
*/
void plib_mos_ocp_unlock(void)
{
    PREG_MOS_IEN &= ~0x10;
}
