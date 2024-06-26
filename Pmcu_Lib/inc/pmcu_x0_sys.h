/**
 * @file
 * @brief		系统配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#ifndef __PMCU_SYS_H_
#define __PMCU_SYS_H_

#include "pmcu_x0_config.h"

/** JTAG接口选择 */
typedef enum {
    JTAG_SEL_DISABLE = 0,	/*!< 不使能 */
    JTAG_SEL_GPIOA,			/*!< GPIOA组作为JTAG调试口 */
    JTAG_SEL_GPIOB,			/*!< GPIOB组作为JTAG调试口 */
} JTAG_SEL_E;


/**
* @brief  系统时钟使能
* @param  无
* @retval 无
* @par   说明
* -# 芯片启动后，需先使能系统时钟
*/
void plib_sys_clk_en(void);
	
/**
* @brief  系统复位
* @param  无
* @retval 无
* @par   说明
* -# 调用后，系统复位
*/
void plib_sys_reset(void);

/**
* @brief  系统总中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* -# 使能后，其他模块的中断才能触发
*/
void plib_sys_it_en(FUNC_EN_E ifEn);

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
void plib_sys_jtag_sel(JTAG_SEL_E sel);

#endif /* end of __PMCU_SYS_H_ */

