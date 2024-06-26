/**
 * @file
 * @brief		充电配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.1
 * @par 		Copyright(c): All rights reserved.
 * @par 		修改记录
 * @par 		1.admin，2023-09-06，增加plib_chg_ifen()接口，修正plib_chg_init()IBCEn参数设置
*/

#ifndef __PMCU_CHARGE_H_
#define __PMCU_CHARGE_H_

#include "pmcu_x0_config.h"

#define CHG_IEN_CHGST 		((U8)0x10)	/*!< 充电中断：充电开启或停止 */
#define CHG_IEN_USB 		((U8)0x08)	/*!< 充电中断：USB拔插 */

#define CHG_CHG_ST_IF 		((U8)0x04)	/*!< 充电事件：充电开启或停止 */
#define CHG_USB_IN 			((U8)0x02)	/*!< 充电事件：USB接入 */
#define CHG_USB_OUT 		((U8)0x01)	/*!< 充电事件：USB拔出 */

#define CHG_S_RECHARGE 		((U8)0x80)	/*!< 充电状态：复充 */
#define CHG_S_USBOVP 		((U8)0x40)	/*!< 充电状态：USB过压 */
#define CHG_S_USBUVP 		((U8)0x20)  /*!< 充电状态：USB欠压 */
#define CHG_S_TC 			((U8)0x10)  /*!< 充电状态：涓流充电 */
#define CHG_S_CC 			((U8)0x08)  /*!< 充电状态：恒流充电 */
#define CHG_S_CV 			((U8)0x04)  /*!< 充电状态：恒压充电 */
#define CHG_S_FULL 			((U8)0x02)  /*!< 充电状态：满充 */
#define CHG_S_USB_IN 		((U8)0x01)  /*!< 充电状态：USB接入 */

/** 电池输入欠压保护电压 */
typedef enum {
    CHG_UVLS_2_3V = 0,		/*!< 2.3V */
    CHG_UVLS_2_4V,			/*!< 2.4V */
    CHG_UVLS_2_5V,			/*!< 2.5V */
    CHG_UVLS_2_6V,			/*!< 2.6V */
} VCC_UV_E;

/** 恒流充电电流 */
typedef enum {
    CHG_ISET_250MA = 0,		/*!< 250mA */
    CHG_ISET_300MA,     	/*!< 300mA */
    CHG_ISET_350MA,     	/*!< 350mA */
    CHG_ISET_400MA,     	/*!< 400mA */
    CHG_ISET_450MA,     	/*!< 450mA */
    CHG_ISET_500MA,			/*!< 500mA */
    CHG_ISET_550MA,     	/*!< 550mA */
    CHG_ISET_600MA,     	/*!< 600mA */
    CHG_ISET_650MA,     	/*!< 650mA */
    CHG_ISET_700MA,     	/*!< 700mA */
    CHG_ISET_750MA,    		/*!< 750mA */
} CHG_ISET_E;

/** 满充截至电流 */
typedef enum {
    CHG_FULL_ISET_20 = 0,	/*!< 恒流电流的20% */
    CHG_FULL_ISET_10,		/*!< 恒流电流的10% */
} CHG_FULL_E;

/**
* @brief  充电初始化函数
* @param  IBCEn 充满复充前，是否有充电电流控制\n
* @ref PLIB_ENABLE 使能，无充电电流 \n
* @ref PLIB_DISABLE 不使能，有充电电流 \n
* @param  CCCurrent 恒流充电电流，选择： \n
*@ref CHG_ISET_250MA \n
*@ref CHG_ISET_300MA \n
*@ref CHG_ISET_350MA \n
*@ref CHG_ISET_400MA \n
*@ref CHG_ISET_450MA \n
*@ref CHG_ISET_500MA \n
*@ref CHG_ISET_550MA \n
*@ref CHG_ISET_600MA \n
*@ref CHG_ISET_650MA \n
*@ref CHG_ISET_700MA \n
*@ref CHG_ISET_750MA \n
* @param  FullCurrent 满充截至电流 \n
*@ref CHG_FULL_ISET_20 \n
*@ref CHG_FULL_ISET_10 \n
* @param  UVVoltage 电池输入欠压保护电压 \n
*@ref CHG_UVLS_2_3V \n
*@ref CHG_UVLS_2_4V \n
*@ref CHG_UVLS_2_5V \n
*@ref CHG_UVLS_2_6V \n
* @par   说明
* 无
*/
void plib_chg_init(FUNC_EN_E IBCEn, CHG_ISET_E CCCurrent, CHG_FULL_E FullCurrent, VCC_UV_E UVVoltage);

/**
  * @brief  充电使能
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* -# 软件关闭充电后，若重新接入USB，满足充电条件，会重新开启充电
*/
void plib_chg_en(FUNC_EN_E ifEn);

/**
* @brief  充电是否使能
* @retval  充电使能状态
* - 0 未使能
* - 非0 已使能
* @par 说明
* 无
*/
U8 plib_chg_ifen(void);
	
/**
* @brief  设置恒流充电电流
* @param  Current 恒流充电电流，选择： \n
* @ref CHG_ISET_250MA \n
* @ref CHG_ISET_300MA \n
* @ref CHG_ISET_350MA \n
* @ref CHG_ISET_400MA \n
* @ref CHG_ISET_450MA \n
* @ref CHG_ISET_500MA \n
* @ref CHG_ISET_550MA \n
* @ref CHG_ISET_600MA \n
* @ref CHG_ISET_650MA \n
* @ref CHG_ISET_700MA \n
* @ref CHG_ISET_750MA \n
* @par   说明
* -# 支持充电过程中修改充电电流
*/
void plib_chg_set_cc_current(CHG_ISET_E Current);

/**
* @brief  充电中断使能
* @param  event 充电事件，选择以下一个或多个： \n
* @ref CHG_IEN_CHGST \n
* @ref CHG_IEN_USB	\n
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_chg_it_cfg(U8 event, FUNC_EN_E ifEn);

/**
* @brief  充电中断是否使能
* @param  event 充电事件，选择以下一个或多个： \n
* @ref CHG_IEN_CHGST \n
* @ref CHG_IEN_USB	\n\n
* @retval  事件中断使能状态
* - 0 未使能
* - 非0 已使能
* @par 说明
* 无
*/
U8 plib_chg_it_ifen(U8 event);

/**
* @brief  充电总中断使能
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_chg_it_en(FUNC_EN_E ifEn);

/**
* @brief  获取充电事件状态
* @param  event 充电事件，选择： \n
* @ref CHG_CHG_ST_IF \n
* @ref CHG_USB_IN	\n
* @ref CHG_USB_OUT	\n
* @retval  事件触发状态
* - 0 事件未触发
* - 非0 事件已触发
* @par   说明
* 无
*/
U8 plib_chg_get_flg(U8 event);

/**
* @brief  清除充电事件标志
* @param  event 充电事件，选择： \n
* @ref CHG_CHG_ST_IF \n
* @ref CHG_USB_IN	\n
* @ref CHG_USB_OUT	\n
* @retval 无
* @par   说明
* 无
*/
void plib_chg_clr_flg(U8 event);

/**
* @brief  获取充电当前状态
* @param  flg 充电状态，选择： \n
* @ref CHG_S_RECHARGE \n
* @ref CHG_S_USBOVP	\n
* @ref CHG_S_USBUVP	\n
* @ref CHG_S_TC \n
* @ref CHG_S_CC	\n
* @ref CHG_S_CV	\n
* @ref CHG_S_FULL \n
* @ref CHG_S_USB_IN	\n
* @retval 充电当前所处状态
* @par   说明
* 无
*/
U8 plib_chg_get_status(U8 flg);

#endif /* end of __PMCU_CHARGE_H_ */

