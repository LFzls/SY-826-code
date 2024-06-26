/**
 * @file
 * @brief		PWM����
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.1
 * @par 		Copyright(c): All rights reserved.
 * @par 		�޸ļ�¼
 * @par 		1.admin��2023-09-05������PWM�����غ��½����ж��Ƿ�ʹ�ܽӿ� 
*/
#include "pmcu_x0_pwm.h"

/**
* @brief  PWM��ʼ������
* @param  pwmsel PWM��ѡ�� \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  Fclk_div ��Ƶϵ����ѡ�� \n
* @ref PWM_FCLK1  \n
* @ref PWM_FCLK2  \n
* @ref PWM_FCLK4  \n
* @ref PWM_FCLK8  \n
* @ref PWM_FCLK16 \n
* @ref PWM_FCLK32 \n
* @ref PWM_FCLK64 \n
* @ref PWM_FCLK128 \n
* @param  Period �������ã�����ֵ=16000000/ʱ�ӷ�Ƶϵ��/���Ƶ��
* @param  CH0_Duty ͨ��0ռ�ձ����ã�����ֵ=����*���ռ�ձ�
* @param  CH1_Duty ͨ��1ռ�ձ����ã�����ֵ=����*���ռ�ձ�
* @param  CH2_Duty ͨ��2ռ�ձ����ã�����ֵ=����*���ռ�ձ�
* @param  ifNegate �Ƿ�ʹ�ܼ��Է�ת \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_pwm_init(PWM_SEL_E pwmsel, PWM_FCLK_E Fclk_div, U8 Period, U8 CH0_Duty, U8 CH1_Duty, U8 CH2_Duty, U8 ifNegate)
{
    if (pwmsel == PWM_SEL0) {
        //��Ƶϵ��
        PREG_PWM0_CTRL = (PREG_PWM0_CTRL & 0xF8) | Fclk_div;

        //���Է�ת
        if (ifNegate == PLIB_ENABLE)
            PREG_PWM0_CTRL |= 0x08;
        else
            PREG_PWM0_CTRL &= ~0x08;

        //ռ�ձ�����
        PREG_PWM0_DUTY_CH0 = CH0_Duty;
        PREG_PWM0_DUTY_CH1 = CH1_Duty;
        PREG_PWM0_DUTY_CH2 = CH2_Duty;
        //��������
        PREG_PWM0_PERIOD = Period;
    } else if (pwmsel == PWM_SEL1) {
        //��Ƶϵ��
        PREG_PWM1_CTRL = (PREG_PWM1_CTRL & 0xF8) | Fclk_div;

        //���Է�ת
        if (ifNegate == PLIB_ENABLE)
            PREG_PWM1_CTRL |= 0x08;
        else
            PREG_PWM1_CTRL &= ~0x08;

        //ռ�ձ�����
        PREG_PWM1_DUTY_CH0 = CH0_Duty;
        PREG_PWM1_DUTY_CH1 = CH1_Duty;
        PREG_PWM1_DUTY_CH2 = CH2_Duty;
        //��������
        PREG_PWM1_PERIOD = Period;
    }
}


/**
* @brief  PWM���ʹ��
* @param  pwmsel PWM��ѡ�� \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
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
* @brief  PWM������Է�תʹ��
* @param  pwmsel PWM��ѡ�� \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
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
* @brief  ͬʱ���ã�PWM���ռ�ձ�����
* @param  pwmsel PWM��ѡ�� \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  duty0 ͨ��0ռ�ձ����ã�����ֵ=����*���ռ�ձ�
* @param  duty1 ͨ��1ռ�ձ����ã�����ֵ=����*���ռ�ձ�
* @param  duty2 ͨ��2ռ�ձ����ã�����ֵ=����*���ռ�ձ�
* @retval ��
* @par   ˵��
* -# ��ʹ�õ�ͨ��������Ϊ0����
*/
void plib_pwm_set_chn_duty(PWM_SEL_E pwmsel, U8 duty0, U8 duty1, U8 duty2)
{
    if (pwmsel == PWM_SEL0) {
        //����ռ�ձ�
        PREG_PWM0_DUTY_CH0 = duty0;
        PREG_PWM0_DUTY_CH1 = duty1;
        PREG_PWM0_DUTY_CH2 = duty2;
        //����һ�����ڣ���Ч
        PREG_PWM0_PERIOD = PREG_PWM0_PERIOD;
    } else if (pwmsel == PWM_SEL1) {
        //����ռ�ձ�
        PREG_PWM1_DUTY_CH0 = duty0;
        PREG_PWM1_DUTY_CH1 = duty1;
        PREG_PWM1_DUTY_CH2 = duty2;
        //����һ�����ڣ���Ч
        PREG_PWM1_PERIOD = PREG_PWM1_PERIOD;
    }
}

/**
* @brief  PWM�ж�ʹ��
* @param  pwmsel PWM��ѡ�� \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  event PWM�ж��¼��� \n
* @ref PWM_TRIG_RISING  \n
* @ref PWM_TRIG_FALLING  \n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* -# ��ͨ��0�ᴥ�������غ��½����жϣ���100%ռ�ձ�ʱ�����ᴥ���ж�
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
* @brief  PWM�ж��Ƿ�ʹ��
* @param  pwmsel PWM��ѡ�� \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  event PWM�ж��¼��� \n
* @ref PWM_TRIG_RISING  \n
* @ref PWM_TRIG_FALLING  \n
* @retval  �¼��ж�ʹ��״̬
* - 0 δʹ��
* - ��0 ��ʹ��
* @par ˵��
* ��
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
* @brief  PWM���ж�ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* -# ��MOS PWM����һ���ж�ʹ��
*/
void plib_pwm_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EX5 = 1;
    else
        PBIT_EX5 = 0;
}

/**
* @brief  ��ȡPWM�¼�״̬
* @param  pwmsel PWM��ѡ�� \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  event PWM�ж��¼��� \n
* @ref PWM_TRIG_RISING  \n
* @ref PWM_TRIG_FALLING  \n
* @retval  �¼�����״̬
* - 0 δ������Ӧ״̬
* - ��0 �����˶�Ӧ״̬
* @par   ˵��
* -# ��ͨ��0�ᴥ�������غ��½���״̬
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
* @brief  ���PWM�¼�״̬
* @param  pwmsel PWM��ѡ�� \n
* @ref PWM_SEL0  \n
* @ref PWM_SEL1  \n
* @param  event PWM�ж��¼��� \n
* @ref PWM_TRIG_RISING  \n
* @ref PWM_TRIG_FALLING  \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_pwm_clr_flg(PWM_SEL_E pwmsel, U8 event)
{
    if (pwmsel == PWM_SEL0) {
        PREG_PWM_IEN &= ~(event << 0);
    } else if (pwmsel == PWM_SEL1) {
        PREG_PWM_IEN &= ~(event << 2);
    }
}

