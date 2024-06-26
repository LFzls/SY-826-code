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

#include "pmcu_x0_timer.h"

#define TIMERx_Tim_Load_13bit(us)		(U16)(8192 - (U16)((16 * (us)/12)))
#define TIMERx_Tim_Load_16_bit(us)		(U16)(65536 - (U16)((16 * (us)/12)))
#define TIMERx_Cal_TH(timemode, us)	(timemode == TIM_MODE_0)? (U8)(TIMERx_Tim_Load_13bit(us) >> 5) : (U8)(TIMERx_Tim_Load_16_bit(us) >> 8)
#define TIMERx_Cal_TL(timemode, us)	(timemode == TIM_MODE_0)? (U8)(TIMERx_Tim_Load_13bit(us) & 0xFF) : (U8)(TIMERx_Tim_Load_16_bit(us) & 0xFF)

/**
* @brief  定时器0初始化函数
* @param  TIM_Mode 定时器的工作模式，选择： \n
* @ref TIM_MODE_0 \n
* @ref TIM_MODE_1 \n
* @ref TIM_MODE_2 \n
* @param  TIM_Times 定时器的定时时间，单位us；TIM_MODE_0最大定时时间为6ms，TIM_MODE_1和TIM_MODE_2最大定时时间为49ms
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
void plib_tim0_init(TIM_Mode_E TIM_Mode, U16 TIM_Times, FUNC_EN_E TIM_En, FUNC_EN_E TIM_IntEn)
{
    //工作模式
    PREG_TMOD = (PREG_TMOD & 0xFC) | TIM_Mode;
	
    //配置定时值，不区分模式，均写重载寄存器，仅模式2会使用
    PREG_CRCH0 = PREG_TH0 = TIMERx_Cal_TH(TIM_Mode, TIM_Times);
    PREG_CRCL0 = PREG_TL0 = TIMERx_Cal_TL(TIM_Mode, TIM_Times);
	
    //启动定时器
    PBIT_TR0 = TIM_En;
    //使能定时器中断
    PBIT_ET0 = TIM_IntEn;
}

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
void plib_tim0_reload(TIM_Mode_E TIM_Mode, U16 TIM_Times)
{
    //配置定时值
    PREG_TH0 = TIMERx_Cal_TH(TIM_Mode, TIM_Times);
    PREG_TL0 = TIMERx_Cal_TL(TIM_Mode, TIM_Times);	
}

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
void plib_tim1_init(TIM_Mode_E TIM_Mode, U16 TIM_Times, FUNC_EN_E TIM_En, FUNC_EN_E TIM_IntEn)
{
    //工作模式
    PREG_TMOD = (PREG_TMOD & 0xCF) | (TIM_Mode << 4);
	
    //配置定时值，不区分模式，均写重载寄存器，仅模式2会使用
    PREG_CRCH1 = PREG_TH1 = TIMERx_Cal_TH(TIM_Mode, TIM_Times);
    PREG_CRCL1 = PREG_TL1 = TIMERx_Cal_TL(TIM_Mode, TIM_Times);
	
    //启动定时器
    PBIT_TR1 = TIM_En;
    //使能定时器中断
    PBIT_ET1 = TIM_IntEn;
}

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
void plib_tim1_reload(TIM_Mode_E TIM_Mode, U16 TIM_Times)
{
    //配置定时值
    PREG_TH1 = TIMERx_Cal_TH(TIM_Mode, TIM_Times);
    PREG_TL1 = TIMERx_Cal_TL(TIM_Mode, TIM_Times);	
}


/**
* @brief  Timer0是否启动定时
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_tim0_en(FUNC_EN_E ifEn)
{
    PBIT_TR0 = ifEn;
}

/**
* @brief  Timer0中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* 无
*/
void plib_tim0_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_ET0 = 1;
    else
        PBIT_ET0 = 0;
}

/**
* @brief  Timer1是否启动定时
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_tim1_en(FUNC_EN_E ifEn)
{
    PBIT_TR1 = ifEn;
}

/**
* @brief  Timer1中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* 无
*/
void plib_tim1_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_ET1 = 1;
    else
        PBIT_ET1 = 0;
}
