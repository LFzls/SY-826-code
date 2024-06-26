/**
 * @file
 * @brief		ADC����
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#include "pmcu_x0_adc.h"
#include "pmcu_x0_delay.h"

/**
* @brief  ADC��ʼ������
* @param  Sample_Rate ADC�����ʣ�ѡ�� \n
* @ref ADC_SAMPLE_380K \n
* @ref ADC_SAMPLE_190K \n
* @ref ADC_SAMPLE_95K \n
* @ref ADC_SAMPLE_47K \n
* @param  Pga_Gain ADC PGA���棬ѡ�� \n
* @ref ADC_PGA_GAIN_16 \n
* @ref ADC_PGA_GAIN_32 \n
* @param  Sample_Mode ADC����������ʽ��ѡ�� \n
* @ref ADC_MODE_SOFTWARE \n
* @ref ADC_MODE_PWM_TRIG \n
* @param  Pwm_Trig_Delay MOS PWM��������ʱ��MOS PWM�����ز�����ʱ���ã��������255��ʱ��=����ֵ*2/16000000
* @retval ��
* @par   ˵��
* ��
*/
void plib_adc_init(U8 Sample_Rate, ADC_PGA_GAIN_E Pga_Gain, ADC_SAMPLE_MODE_E Sample_Mode, U8 Pwm_Trig_Delay)
{
    //ADC������
    PREG_ADC_CTRL2 = (PREG_ADC_CTRL2 & 0xFC) | Sample_Rate;
    //ADC PGA����
    PREG_SENSOR_CTRL = ((PREG_SENSOR_CTRL & 0xFB) | (Pga_Gain << 2));

    //ADC ����������ʽ
    if (Sample_Mode == ADC_MODE_PWM_TRIG)
        PREG_ADC_CTRL2 |= 0x04;

    //MOS PWM��������ʱ��MOS PWM�����ز�����ʱ����
    if (Pwm_Trig_Delay)
        PREG_ADC_PWM_DLY = Pwm_Trig_Delay;
}

/**
* @brief  ADC��ʹ�ܿ���
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_adc_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_ADC_CTRL0 |= 0x01;
    else
        PREG_ADC_CTRL0 &= ~0x01;
}

/**
* @brief  ADCͨ��ʹ��
* @param  channel ADC����ͨ����ѡ������һ�������� \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT	\n
* @ref ADC_CHN2_VDD	\n
* @ref ADC_CHN3_GPIOB0	\n
* @ref ADC_CHN4_GPIOB1	\n
* @ref ADC_CHN5_GPIOB2	\n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* -# ADC�Ĳ������̶������ȼ�˳��ִ�У�ͨ��0���ȼ���ߣ�ͨ��6��ͣ���������ͨ��ADC����ʱ������н���ȴ����ȼ���͵�ͨ��������ɣ��ٽ������ݴ���
* -# �����ȿ���ADC��ʹ�ܣ�ͨ��ʹ�ܲ���Ч
* -# ʹ�������������ʱ��ÿ�β���������Ӳ�����Զ����ͨ��ʹ�ܣ������β�����������������Ҫ�ٴο���ͨ��ʹ��
* -# ʹ��MOS PWM��������ʱ������Ҫʹ��һ��ADCͨ��ʹ��
*/
void plib_adc_chn_en(U8 channel, FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_ADC_CTRL1 = channel;
    else
        PREG_ADC_CTRL1 &= ~channel;
}

/**
* @brief  ADCͨ���ж�ʹ��
* @param  channel ADC����ͨ����ѡ������һ�������� \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT	\n
* @ref ADC_CHN2_VDD	\n
* @ref ADC_CHN3_GPIOB0	\n
* @ref ADC_CHN4_GPIOB1	\n
* @ref ADC_CHN5_GPIOB2	\n
* @ref ADC_CHN_ALL	\n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* -# ADC�Ĳ������̶������ȼ�˳��ִ�У�ͨ��0���ȼ���ߣ�ͨ��6��ͣ���������ͨ��ADC����ʱ������н���ȴ����ȼ���͵�ͨ��������ɣ��ٽ������ݴ���
*/
void plib_adc_it_cfg(U8 channel, FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_ADC_CTRL0 = (PREG_ADC_CTRL0 & 0x01) | (channel << 1);
    else
        PREG_ADC_CTRL0 &= ~(channel << 1);
}

/**
* @brief  ADC�ж��Ƿ�ʹ��
* @param  channel ADC����ͨ����ѡ������һ�������� \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT	\n
* @ref ADC_CHN2_VDD	\n
* @ref ADC_CHN3_GPIOB0	\n
* @ref ADC_CHN4_GPIOB1	\n
* @ref ADC_CHN5_GPIOB2	\n
* @ref ADC_CHN_ALL	\n
* @retval  �¼��ж�ʹ��״̬
* - 0 δʹ��
* - ��0 ��ʹ��
* @par ˵��
* ��
*/
U8 plib_adc_it_ifen(U8 channel)
{
    return ((PREG_ADC_CTRL0 >> 1) & channel);
}

/**
* @brief  ADC MOS PWM��������ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_adc_pwm_trig_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_ADC_CTRL2 |= 0x04;
    else
        PREG_ADC_CTRL2 &= ~0x04;
}

/**
* @brief  ADC���ж�ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_adc_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE) {
        PBIT_ADC_TRIG = 1;
        PBIT_EX3 = 1;
    } else {
        PBIT_ADC_TRIG = 0;
        PBIT_EX3 = 0;
    }
}

/**
* @brief  ��ȡADC����״̬
* @param  channel ADC����ͨ����ѡ�� \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT	\n
* @ref ADC_CHN2_VDD	\n
* @ref ADC_CHN3_GPIOB0	\n
* @ref ADC_CHN4_GPIOB1	\n
* @ref ADC_CHN5_GPIOB2	\n
* @retval  ADC�������״̬
* - 0 ����δ���
* - ��0 ���������
* @par   ˵��
* -# ADC�Ĳ������̶������ȼ�˳��ִ�У�ͨ��0���ȼ���ߣ�ͨ��6��ͣ���������ͨ��ADC����ʱ������н���ȴ����ȼ���͵�ͨ��������ɣ��ٽ������ݴ���
*/
U8 plib_adc_get_flg(U8 channel)
{
    return (PREG_ADC_FLAG & channel);
}

/**
* @brief  ���ADCͨ����־
* @param  channel ADC����ͨ����ѡ�� \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT	\n
* @ref ADC_CHN2_VDD	\n
* @ref ADC_CHN3_GPIOB0	\n
* @ref ADC_CHN4_GPIOB1	\n
* @ref ADC_CHN5_GPIOB2	\n
* @ref ADC_CHN_ALL	\n
* @retval ��
* @par   ˵��
* ��
*/
void plib_adc_clr_flg(U8 channel)
{
    PREG_ADC_FLAG &= ~channel;
}

/**
* @brief  ADCͨ��0����������ģʽ����
* @param  pgasel ����ģʽ��ѡ�� \n
* @ref ADC_PGA_SEL_BYPASS PGA BYPASS������VOUT�����ѹʱʹ�� \n
* @ref ADC_PGA_SEL_x16	PGA����16�������������迹ʹ�� \n
* @ref ADC_PGA_SEL_x32	PGA����32�������������迹ʹ�� \n
* @retval ��
* @par   ˵��
* -# ���������迹ʱ��оƬ��VOUT�ܽŷų�50mA����
*/
void plib_adc_pga_sel(ADC_PGA_SEL_E pgasel)
{
    if (pgasel == ADC_PGA_SEL_BYPASS) {
        //�ر�CCO������BYPASS
        PREG_SENSOR_CTRL = (PREG_SENSOR_CTRL & 0xF8) | 0x02;
    } else if (pgasel == ADC_PGA_SEL_x16) {
        //�ر�BYPASS������CCO������16��
        PREG_SENSOR_CTRL = (PREG_SENSOR_CTRL & 0xF8) | 0x01;
    } else if (pgasel == ADC_PGA_SEL_x32) {
        //�ر�BYPASS������CCO������32��
        PREG_SENSOR_CTRL = (PREG_SENSOR_CTRL & 0xF8) | 0x05;
    }

    delay10us(1);	//��ʱ���ȴ�ģ���ȶ�
}

/**
* @brief  ADC��ȡͨ���������
* @param  channel ADC����ͨ����ѡ�� \n
* @ref ADC_CHN0_PGAOUT \n
* @ref ADC_CHN1_VBAT	\n
* @ref ADC_CHN2_VDD	\n
* @ref ADC_CHN3_GPIOB0	\n
* @ref ADC_CHN4_GPIOB1	\n
* @ref ADC_CHN5_GPIOB2	\n
* @retval ADC����ADֵ
* @par   ˵��
* ��
*/
U16 plib_adc_get_ad_value(U8 channel)
{
    if (channel & ADC_CHN0_PGAOUT) {
        return (U16)((PREG_ADC0_H << 8) | PREG_ADC0_L);
    } else if (channel & ADC_CHN1_VBAT) {
        return (U16)((PREG_ADC1_H << 8) | PREG_ADC1_L);
    } else if (channel & ADC_CHN2_VDD) {
        return (U16)((PREG_ADC2_H << 8) | PREG_ADC2_L);
    } else if (channel & ADC_CHN3_GPIOB0) {
        return (U16)((PREG_ADC3_H << 8) | PREG_ADC3_L);
    } else if (channel & ADC_CHN4_GPIOB1) {
        return (U16)((PREG_ADC4_H << 8) | PREG_ADC4_L);
    } else if (channel & ADC_CHN5_GPIOB2) {
        return (U16)((PREG_ADC5_H << 8) | PREG_ADC5_L);
    } else {
        return 0;
    }
}

/**
* @brief  ADCͨ���������ת���ɵ�ѹ
* @param  advalue ADC�������ADֵ
* @retval ת����ĵ�ѹ����λmV
* @par   ˵��
* -# ADC_CHN0_PGAOUT�����������迹��/ADC_CHN1_VBAT/ADC_CHN2_VDD/ADC_CHN3_GPIOB0/ADC_CHN4_GPIOB1/ADC_CHN5_GPIOB2��ʹ�ô�ת���ӿ�
*/
U32 plib_adc_get_volt_div2(U16 advalue)
{
    return ((U32)advalue * 275 >> 8);
}

/**
* @brief  ADCͨ���������ת���ɵ�ѹ
* @param  advalue ADC�������ADֵ
* @retval ת����ĵ�ѹ����λmV
* @par   ˵��
* -# ADC_CHN0_PGAOUT������VOUT�����ѹ��ʹ�ô�ת���ӿ�
*/
U32 plib_adc_get_volt_div4(U16 advalue)
{
    return ((U32)advalue * 550 >> 8);
}
