/**
 * @file
 * @brief       ADC middleware interface functions
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

#include "pmcu_x0_include.h"
#include "util_filter.h"

extern bit g_bsp_adc_flag;          // ADC sampling completion flag

// External functions
void pmcu_adc_init(void);
u16 pmcu_adc_sample_1ch(u8 channel);
void pmcu_adc_sample_nch(u8 channel);
u16 pmcu_adc_sample_1ch_it(u8 channel);
void pmcu_adc_sample_nch_it(u8 channel);
u16 pmcu_adc_sample_1ch_mul(u8 channel, u8 cnt);

#endif /* end of __BSP_ADC_H_ */
