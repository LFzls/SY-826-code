/**
 * @file
 * @brief		GPIO配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.1
 * @par 		Copyright(c): All rights reserved.
 * @par 		1.admin，2023-08-21，修正plib_gpio_init()接口，GPIOC0/GPIOC1内部弱上/下拉配置相反问题 
 * @par 		2.admin，2023-09-07，增加接口plib_gpio_mode() 
*/

#ifndef __PMCU_GPIO_H_
#define __PMCU_GPIO_H_

#include "pmcu_x0_config.h"

#define	GPIO_GroupA  	((U8)0x01)		/*!< GPIOA组 */
#define	GPIO_GroupB  	((U8)0x02)		/*!< GPIOB组 */
#define	GPIO_GroupC  	((U8)0x04)		/*!< GPIOC组 */

#define	GPIO_Pin_0  		((U8)0x01)		/*!< GPIO PIN0 */
#define	GPIO_Pin_1  		((U8)0x02)      /*!< GPIO PIN1 */
#define	GPIO_Pin_2  		((U8)0x04)      /*!< GPIO PIN2 */
#define	GPIO_Pin_3  		((U8)0x08)      /*!< GPIO PIN3 */
#define	GPIO_Pin_All  		((U8)0x0F)      /*!< GPIO 所有PIN */

#define	GPIO_LED_0  		((U8)0x01)		/*!< LED PIN0 */
#define	GPIO_LED_1  		((U8)0x02)		/*!< LED PIN1 */
#define	GPIO_LED_2  		((U8)0x04)		/*!< LED PIN2 */
#define	GPIO_LED_All  		((U8)0x07)		/*!< LED 所有PIN */

#define	GPIO_LED_4MA  		((U8)0x00) 		/*!< LED 驱动电流4mA */
#define	GPIO_LED_8MA  		((U8)0x08)		/*!< LED 驱动电流8mA */
#define	GPIO_LED_21MA  		((U8)0x10)		/*!< LED 驱动电流21mA */
#define	GPIO_LED_29MA  		((U8)0x18)		/*!< LED 驱动电流29mA */

/** GPIO输入输出模式 */
typedef enum {
    GPIO_IOMode_FLOATING = 0,			/*!< 浮空，输入输出使能均关闭 */
    GPIO_IOMode_IN_FLOATING = 1,		/*!< 浮空输入 */
    GPIO_IOMode_Out_PP = 2,				/*!< PP输出 */
    GPIO_IOMode_Out_OD = 3,				/*!< OD输出 */
} GPIO_IOMode_E;

/** GPIO内部上下拉模式 */
typedef enum {
    GPIO_PUPDMode_None = 0,				/*!< 无上下拉 */
    GPIO_PUPDMode_PD = 1,				/*!< 内部弱下拉 */
    GPIO_PUPDMode_PU = 2,				/*!< 内部弱上拉 */
} GPIO_PDPUMode_E;

/** GPIO PP输出驱动能力 */
typedef enum {
    GPIO_Driver_Weak = 0,				/*!< 弱驱 */
    GPIO_Driver_Strength = 1,			/*!< 强驱 */
} GPIO_DRIVER_E;

/** GPIO复用配置 */
typedef enum {
    GPIO_PinMux_IO = 0,					/*!< IO */
    GPIO_PinMux_PWM0_0,                 /*!< PWM0的0通道 */
    GPIO_PinMux_PWM0_1,                 /*!< PWM0的1通道 */
    GPIO_PinMux_PWM0_2,                 /*!< PWM0的2通道 */
    GPIO_PinMux_PWM1_0,	                /*!< PWM1的0通道 */
    GPIO_PinMux_PWM1_1,	                /*!< PWM1的1通道 */
    GPIO_PinMux_PWM1_2,		            /*!< PWM1的2通道 */
    GPIO_PinMux_ADC,                    /*!< ADC输入 */
    GPIO_PinMux_UART,                   /*!< UART通讯接口 */
    GPIO_PinMux_LED,	                /*!< LED驱动输出 */
} GPIO_PINMUX_E;

/**
* @brief  GPIO初始化函数
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  PinmuxMode GPIO复用模式，选择： \n
* @ref GPIO_PinMux_IO \n
* @ref GPIO_PinMux_PWM0_0 \n
* @ref GPIO_PinMux_PWM0_1 \n
* @ref GPIO_PinMux_PWM0_2 \n
* @ref GPIO_PinMux_PWM1_0 \n
* @ref GPIO_PinMux_PWM1_1 \n
* @ref GPIO_PinMux_PWM1_2 \n
* @ref GPIO_PinMux_ADC    \n
* @ref GPIO_PinMux_UART   \n
* @ref GPIO_PinMux_LED    \n
* @param  IOMode GPIO输入输出模式，选择： \n
* @ref GPIO_IOMode_FLOATING    \n
* @ref GPIO_IOMode_IN_FLOATING   \n
* @ref GPIO_IOMode_Out_PP    \n
* @ref GPIO_IOMode_Out_OD    \n
* @param  PUPDMode GPIO内部上下拉模式，选择： \n
* @ref GPIO_PUPDMode_None \n
* @ref GPIO_PUPDMode_PD \n
* @ref GPIO_PUPDMode_PU \n
* @param  PPDriver PP输出时，GPIO驱动能力，选择： \n
* @ref GPIO_Driver_Weak \n
* @ref GPIO_Driver_Strength \n
* @retval 无
* @par   说明
* 无
* @par 修改记录
* -# admin，2023-08-21，修正GPIOC0/GPIOC1内部弱上/下拉配置相反问题
*/
void plib_gpio_init(U8 Gpiox, U8 Pinx, GPIO_PINMUX_E PinmuxMode, GPIO_IOMode_E IOMode, GPIO_PDPUMode_E PUPDMode, GPIO_DRIVER_E PPDriver);

/**
* @brief  GPIO输出模式配置函数
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  IOMode GPIO输入输出模式，选择： \n
* @ref GPIO_IOMode_FLOATING    \n
* @ref GPIO_IOMode_IN_FLOATING   \n
* @ref GPIO_IOMode_Out_PP    \n
* @ref GPIO_IOMode_Out_OD    \n
* @retval 无
* @par   说明
* 无
* @par 修改记录
* -# admin，2023-09-07，新增
*/
void plib_gpio_mode(U8 Gpiox, U8 Pinx, GPIO_IOMode_E IOMode); 
	
/**
* @brief  GPIO输出使能
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_output_en(U8 Gpiox, U8 Pinx, FUNC_EN_E ifEn);

/**
* @brief  GPIO输入使能
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_input_en(U8 Gpiox, U8 Pinx, FUNC_EN_E ifEn);

/**
* @brief  GPIO输出高电平
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  level 输出电平 \n
* @ref PLIB_HIGH 高电平 \n
* @ref PLIB_LOW 低电平 \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_set_value(U8 GPIOx, U8 Pinx, IO_LEVEL_E level);

/**
  * @brief  GPIO获取输入电平
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @retval  事件触发状态
* - PLIB_LOW 低电平
* - PLIB_HIGH 高电平
* @par   说明
* 无
*/
U8 plib_gpio_get_value(U8 GPIOx, U8 Pinx);

/**
* @brief  GPIO 输入中断
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* -# 若使能睡眠唤醒的GPIO事件唤醒，该中断使能配置，同时作为睡眠唤醒事件
*/
void plib_gpio_it_cfg(U8 Gpiox, U8 Pinx, FUNC_EN_E ifEn);

/**
* @brief  GPIO 总中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_it_en(FUNC_EN_E ifEn);

/**
* @brief  GPIOA1/GPIOA2/GPIOA3 用作LED时的，驱动电流配置
* @param  LEDCurr LED驱动电流档位，选择： \n
* @ref GPIO_LED_4MA \n
* @ref GPIO_LED_8MA \n
* @ref GPIO_LED_21MA \n
* @ref GPIO_LED_29MA \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_set_led_curr(U8 LEDCurr);

/**
* @brief  LED输出使能
* @param  LED_Numbe LED号 \n
* @ref GPIO_LED_0 \n
* @ref GPIO_LED_1 \n
* @ref GPIO_LED_2 \n
* @ref GPIO_LED_All \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_led_output_en(U8 LED_Number, FUNC_EN_E ifEn);

#endif /* end of __PMCU_GPIO_H_ */

