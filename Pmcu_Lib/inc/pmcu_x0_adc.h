/**
 * @file
 * @brief		ADC配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#ifndef __PMCU_ADC_H_
#define __PMCU_ADC_H_

#include "pmcu_x0_config.h"

#define ADC_CHN0_PGAOUT				((U8)0x01)  /* ADC通道0 PGA_OUT */
#define ADC_CHN1_VBAT				((U8)0x02)  /* ADC通道1 VBAT */
#define ADC_CHN2_VDD				((U8)0x04)  /* ADC通道2 VDD */
#define ADC_CHN3_GPIOB0				((U8)0x08)  /* ADC通道3 PBIT_GPIOB0 */
#define ADC_CHN4_GPIOB1				((U8)0x10)  /* ADC通道4 PBIT_GPIOB1 */
#define ADC_CHN5_GPIOB2				((U8)0x20)  /* ADC通道5 PBIT_GPIOB2 */
#define ADC_CHN_ALL					((U8)0x3F)  /* ADC所有通道 */

/** ADC采样率 */
typedef enum {
    ADC_SAMPLE_380K = 0,		/*!< 380K */
    ADC_SAMPLE_190K,			/*!< 190K */
    ADC_SAMPLE_95K,				/*!< 95K */
    ADC_SAMPLE_47K,				/*!< 47K */
} ADC_SAMPLE_RATE_E;

/** PGA 增益 */
typedef enum {
    ADC_PGA_GAIN_16 = 0,		/*!< 16倍 */
    ADC_PGA_GAIN_32,			/*!< 32倍 */
} ADC_PGA_GAIN_E;

/** ADC采样触发方式 */
typedef enum {
    ADC_MODE_SOFTWARE = 0,		/*!< 软件触发，每使能一次通道，触发一次采样 */
    ADC_MODE_PWM_TRIG,			/*!< 功率输出触发，MOS PWM输出上升沿触发采样 */
} ADC_SAMPLE_MODE_E;

/** ADC通道0 采样设置 */
typedef enum {
    ADC_PGA_SEL_BYPASS = 0,		/*!< PGA BYPASS，采样VOUT输出电压时使用 */
    ADC_PGA_SEL_x16,			/*!< PGA增益16倍，采样负载阻抗使用 */
    ADC_PGA_SEL_x32,			/*!< PGA增益32倍，采样负载阻抗使用 */
} ADC_PGA_SEL_E;

/**
* @brief  ADC初始化函数
* @param  Sample_Rate ADC采样率，选择： \n
* @ref ADC_SAMPLE_380K \n
* @ref ADC_SAMPLE_190K \n
* @ref ADC_SAMPLE_95K \n
* @ref ADC_SAMPLE_47K \n
* @param  Pga_Gain ADC PGA增益，选择： \n
* @ref ADC_PGA_GAIN_16 \n
* @ref ADC_PGA_GAIN_32 \n
* @param  Sample_Mode ADC采样触发方式，选择： \n
* @ref ADC_MODE_SOFTWARE \n
* @ref ADC_MODE_PWM_TRIG \n
* @param  Pwm_Trig_Delay MOS PWM触发采样时，MOS PWM上升沿采样延时设置，最大配置255，时长=配置值*2/16000000
* @retval 无
* @par   说明
* 无
*/
void plib_adc_init(U8 Sample_Rate, ADC_PGA_GAIN_E Pga_Gain, ADC_SAMPLE_MODE_E Sample_Mode, U8 Pwm_Trig_Delay);

/**
* @brief  ADC总使能开关
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_adc_en(FUNC_EN_E ifEn);

/**
* @brief  ADC通道使能
* @param  channel ADC采样通道，选择以下一个或多个： \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT \n
* @ref ADC_CHN2_VDD \n
* @ref ADC_CHN3_GPIOB0 \n
* @ref ADC_CHN4_GPIOB1 \n
* @ref ADC_CHN5_GPIOB2 \n
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* -# 必须先开启ADC总使能，通道使能才生效
* -# 使用软件触发采样时，每次采样结束，硬件会自动清除通道使能，若需多次采样，采样结束后需要再次开启通道使能
* -# 使用MOS PWM触发采样时，仅需要使能一次ADC通道使能
*/
void plib_adc_chn_en(U8 channel, FUNC_EN_E ifEn);

/**
* @brief  ADC通道中断使能
* @param  channel ADC采样通道，选择以下一个或多个: \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT	\n
* @ref ADC_CHN2_VDD	\n
* @ref ADC_CHN3_GPIOB0	\n
* @ref ADC_CHN4_GPIOB1	\n
* @ref ADC_CHN5_GPIOB2	\n
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* -# ADC的采样按固定的优先级顺序执行，通道0优先级最高，通道6最低，当开启多通道ADC采样时，软件中建议等待优先级最低的通道采样完成，再进行数据处理
*/
void plib_adc_it_cfg(U8 channel, FUNC_EN_E ifEn);

/**
* @brief  ADC中断是否使能
* @param  channel ADC采样通道，选择以下一个或多个： \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT	\n
* @ref ADC_CHN2_VDD	\n
* @ref ADC_CHN3_GPIOB0	\n
* @ref ADC_CHN4_GPIOB1	\n
* @ref ADC_CHN5_GPIOB2	\n
* @ref ADC_CHN_ALL	\n
* @retval  事件中断使能状态
* - 0 未使能
* - 非0 已使能
* @par 说明
* 无
*/
U8 plib_adc_it_ifen(U8 channel);

/**
* @brief  ADC MOS PWM触发采样使能
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_adc_pwm_trig_en(FUNC_EN_E ifEn);

/**
* @brief  ADC总中断使能
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_adc_it_en(FUNC_EN_E ifEn);

/**
* @brief  获取ADC采样状态
* @param  channel ADC采样通道，选择: \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT	\n
* @ref ADC_CHN2_VDD	\n
* @ref ADC_CHN3_GPIOB0	\n
* @ref ADC_CHN4_GPIOB1	\n
* @ref ADC_CHN5_GPIOB2	\n
* @ref ADC_CHN_ALL	\n
* @retval  ADC采样完成状态
* - 0 采样未完成
* - 非0 采样已完成
* @par   说明
* -# ADC的采样按固定的优先级顺序执行，通道0优先级最高，通道6最低，当开启多通道ADC采样时，软件中建议等待优先级最低的通道采样完成，再进行数据处理
*/
U8 plib_adc_get_flg(U8 channel);

/**
* @brief  清除ADC通道标志
* @param  channel ADC采样通道，选择： \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT	\n
* @ref ADC_CHN2_VDD	\n
* @ref ADC_CHN3_GPIOB0	\n
* @ref ADC_CHN4_GPIOB1	\n
* @ref ADC_CHN5_GPIOB2	\n
* @retval 无
* @par   说明
* 无
*/
void plib_adc_clr_flg(U8 channel);

/**
* @brief  ADC获取通道采样结果
* @param  channel ADC采样通道，选择： \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT	\n
* @ref ADC_CHN2_VDD	\n
* @ref ADC_CHN3_GPIOB0	\n
* @ref ADC_CHN4_GPIOB1	\n
* @ref ADC_CHN5_GPIOB2	\n
* @retval 十六进制的采样结果
* @par   说明
* 无
*/
U16 plib_adc_get_ad_value(U8 channel);

/**
* @brief  ADC通道0采样，采样模式设置
* @param  pgasel 采样模式，选择： \n
* @ref ADC_PGA_SEL_BYPASS PGA BYPASS，采样VOUT输出电压时使用 \n
* @ref ADC_PGA_SEL_x16	PGA增益16倍，采样负载阻抗使用 \n
* @ref ADC_PGA_SEL_x32	PGA增益32倍，采样负载阻抗使用 \n
* @retval 无
* @par   说明
* -# 采样负载阻抗时，芯片从VOUT管脚放出50mA电流
*/
void plib_adc_pga_sel(ADC_PGA_SEL_E pgasel);

/**
* @brief  ADC通道采样结果转换成电压
* @param  advalue ADC采样结果AD值
* @retval 转换后的电压，单位mV
* @par   说明
* -# ADC_CHN0_PGAOUT（采样负载阻抗）/ADC_CHN1_VBAT/ADC_CHN2_VDD/ADC_CHN3_GPIOB0/ADC_CHN4_GPIOB1/ADC_CHN5_GPIOB2，使用此转换接口
*/
U32 plib_adc_get_volt_div2(U16 advalue);

/**
* @brief  ADC通道采样结果转换成电压
* @param  advalue ADC采样结果AD值
* @retval 转换后的电压，单位mV
* @par   说明
* -# ADC_CHN0_PGAOUT（采样VOUT输出电压）使用此转换接口
*/
U32 plib_adc_get_volt_div4(U16 advalue);

#endif /* end of __PMCU_ADC_H_ */
