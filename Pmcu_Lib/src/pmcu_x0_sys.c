/**
 * @file
 * @brief		系统配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#include "pmcu_x0_sys.h"

/**
* @brief  系统时钟使能
* @param  无
* @retval 无
* @par   说明
* -# 芯片启动后，需先使能系统时钟
*/
void plib_sys_clk_en(void)
{
	//芯片时钟配置为0x00
	PREG_CLK_SEL = PREG_CLK_SEL & 0xFC | 0x00;	
}

/**
* @brief  系统复位
* @param  无
* @retval 无
* @par   说明
* -# 调用后，系统复位
*/
void plib_sys_reset(void)
{
    PREG_CLK_SEL |= 0x04;
}

/**
* @brief  系统总中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* -# 使能后，其他模块的中断才能触发
*/
void plib_sys_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EAL = 1;
    else
        PBIT_EAL = 0;
}

/**
* @brief  JTAG调试接口选择
* @param  sel JTAG调试后功能，选择： \n
* @ref JTAG_SEL_DISABLE \n
* @ref JTAG_SEL_GPIOA	\n
* @ref JTAG_SEL_GPIOB	\n
* @retval 无
* @par   说明
* -# 使能后，其他模块的中断才能触发
*/
void plib_sys_jtag_sel(JTAG_SEL_E sel)
{
    PREG_SYS_CTRL = (PREG_SYS_CTRL & 0xFC) | sel;
}
