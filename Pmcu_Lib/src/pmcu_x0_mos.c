/**
 * @file
 * @brief		MOS PWM����
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.1
 * @par 		Copyright(c): All rights reserved.
 * @par 		�޸ļ�¼
 * @par 		1.admin��2023-09-05������MOS�����غ��½����ж��Ƿ�ʹ�ܽӿ� 
*/

#include "pmcu_x0_mos.h"

/**
* @brief  MOS PWM��ʼ������
* @param  Fclk_div ��Ƶϵ����ѡ�� \n
* @ref MOS_Fclk  \n
* @ref MOS_Fclk2  \n
* @ref MOS_Fclk4  \n
* @ref MOS_Fclk8  \n
* @ref MOS_Fclk16 \n
* @param  Period �������ã�����ֵ=16000000/ʱ�ӷ�Ƶϵ��/���Ƶ��
* @param  Duty ռ�ձ����ã�����ֵ=����*���ռ�ձ�
* @param  Ocp_Thd �����������������ֵ��ѡ�� \n
* @ref MOS_OCP_4A  \n
* @ref MOS_OCP_5A  \n
* @ref MOS_OCP_6A  \n
* @ref MOS_OCP_7A  \n
* @param  OcpEn ���������������ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @param  OtpEn ����������±���ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_mos_init(MOS_FCLK_E Fclk_div, U16 Period, U16 Duty, MOS_OCP_THD_E Ocp_Thd, FUNC_EN_E OcpEn, FUNC_EN_E OtpEn)
{
    //�����������������ֵ
    PREG_MOS_CFG = (PREG_MOS_CFG & 0xF3) | (Ocp_Thd << 2);

    //���������������ʹ��
    if (OcpEn == PLIB_ENABLE)
        PREG_MOS_CTRL |= 0x40;
    else
        PREG_MOS_CTRL &= ~0x40;

    //����������±���ʹ��
    if (OtpEn == PLIB_ENABLE)
        PREG_MOS_CTRL |= 0x80;
    else
        PREG_MOS_CTRL &= ~0x80;

    //��Ƶϵ��
    PREG_MOS_CTRL = (PREG_MOS_CTRL & 0xF8) | Fclk_div;
    //��������
    PREG_MOS_PERIOD_L = (U8)(Period & 0xFF);
    PREG_MOS_PERIOD_H = (U8)(Period >> 8);
    //ռ�ձ����ã�����ֵ
    PREG_MOS_DUTY_L = (U8)(Duty & 0xFF);
    PREG_MOS_DUTY_H = (U8)(Duty >> 8);
}

/**
* @brief  ����MOS������ʼ������
* @param  Exmos1 ��/��MOS����ͬ��ʹ��λ��ʹ���ⲿNMOSʱ����PLIB_ENABLE����ȷ���ⲿNMOS���ڲ�NMOS�ȵ�ͨ \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @param  Exmos2 ��/��MOS����ͬ������ʹ��λ����Exmos1=PLIB_ENABLEʱ��������Ч \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @param  Speed1 ��/��MOS���ʹ�����/�½�б��1����Exmos1=PLIB_ENABLEʱ��������Ч \n
* @ref MOS_SPEED4 \n
* @ref MOS_SPEED3 \n
* @ref MOS_SPEED2 \n
* @ref MOS_SPEED1 \n
* @param  Speed2 ��/��MOS���ʹ�����/�½�б��2����Exmos1=PLIB_ENABLEʱ��������Ч \n
* @ref MOS_SPEED4 \n
* @ref MOS_SPEED3 \n
* @retval ��
* @par   ˵��
* -# ����˵������MOS��ָʹ��MOS_EXT�ܽ�����
*/
void plib_exmos_init(FUNC_EN_E Exmos1, FUNC_EN_E Exmos2, MOS_SPEED_E Speed1, MOS_SPEED_E Speed2)
{
    if (Exmos1 == PLIB_ENABLE) {
        PREG_MOS_CTRL |= 0x20;
        //��/��MOS���ʹ�����/�½�б��1
        //��/��MOS���ʹ�����/�½�б��2
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
* @brief  MOS PWM���ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_mos_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_MOS_CTRL |= 0x08;
    else
        PREG_MOS_CTRL &= ~0x08;
}

/**
* @brief  MOS PWMռ�ձ�����
* @param  duty ռ�ձ����ã�����ֵ=����*���ռ�ձ�
* @retval ��
* @par   ˵��
* ��
*/
void plib_mos_set_duty(U16 duty)
{
    PREG_MOS_DUTY_L = (U8)(duty & 0xFF);
    PREG_MOS_DUTY_H = (U8)(duty >> 8);
}

/**
* @brief  ��ȡMOS�¼�״̬
* @param  event MOS�ж��¼��� \n
* @ref MOS_TRIG_RISING  \n
* @ref MOS_TRIG_FALLING  \n
* @retval  �¼�����״̬
* - 0 δ������Ӧ״̬
* - ��0 �����˶�Ӧ״̬
* @par   ˵��
* ��
*/
U8 plib_mos_get_flg(U8 event)
{
    return (PREG_MOS_IEN & event);
}

/**
* @brief  ���MOS�¼�״̬
* @param  event MOS�ж��¼��� \n
* @ref MOS_TRIG_RISING  \n
* @ref MOS_TRIG_FALLING  \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_mos_clr_flg(U8 event)
{
    PREG_MOS_IEN &= ~event;
}


/**
* @brief  MOS�ж�ʹ��
* @param  event MOS�ж��¼��� \n
* @ref MOS_TRIG_RISING  \n
* @ref MOS_TRIG_FALLING  \n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @par   ˵��
* ��
*/
void plib_mos_it_cfg(U8 event, FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_MOS_IEN = (PREG_MOS_IEN & 0xF3) | (event << 2);
    else
        PREG_MOS_IEN &= ~(event << 2);
}

/**
* @brief  MOS�ж��Ƿ�ʹ��
* @param  event MOS�ж��¼��� \n
* @ref MOS_TRIG_RISING  \n
* @ref MOS_TRIG_FALLING  \n
* @retval  �¼��ж�ʹ��״̬
* - 0 δʹ��
* - ��0 ��ʹ��
* @par ˵��
* ��
*/
U8 plib_mos_it_ifen(U8 event)
{
    return (PREG_MOS_IEN & (event << 2));
}

/**
* @brief  MOS���ж�ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* -# MOS PWM����/�½��غ�PWM0/1����һ���ж�ʹ��
*/
void plib_mos_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EX5 = 1;
    else
        PBIT_EX5 = 0;
}

/**
* @brief  ��ȡMOS�쳣�¼�״̬
* @param  event �쳣�ж��¼��� \n
* @ref MOS_OCP  \n
* @ref MOS_OTP  \n
* @retval  �¼�����״̬
* - 0 δ������Ӧ״̬
* - ��0 �����˶�Ӧ״̬
* @par   ˵��
* ��
*/
U8 plib_mos_get_abn_flg(U8 event)
{
    return (PREG_CHG_FLAG & (event >> 2));
}

/**
* @brief  ���MOS�쳣�¼�״̬
* @param  event �쳣�ж��¼��� \n
* @ref MOS_OCP  \n
* @ref MOS_OTP  \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_mos_clr_abn_flg(U8 event)
{
    PREG_CHG_FLAG &= ~(event >> 2);
}

/**
* @brief  MOS�쳣�ж�ʹ��
* @param  event �쳣�ж��¼��� \n
* @ref MOS_OCP  \n
* @ref MOS_OTP  \n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @par   ˵��
* ��
*/
void plib_mos_abn_it_cfg(U8 event, FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_CHG_CTRL = (PREG_CHG_CTRL & 0x9F) | event;
    else
        PREG_CHG_CTRL &= ~event;
}

/**
* @brief  MOS�쳣���ж�ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_mos_abn_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EX6 = 1;
    else
        PBIT_EX6 = 0;
}

/**
* @brief  ��⸺�ز��״̬
* @param  ��
* @retval ����״̬
* - 0 ����δ����
* - ��0 �����ѽ���
* @par   ˵��
* ��
*/
U8 plib_mos_get_plug_flg(void)
{
    return (PREG_SENSOR_CTRL & 0x10);
}

/**
* @brief  ��ȡOCP������MOS���״̬
* @param  ��
* @retval MOS����״̬
* - 0 δ����
* - ��0 ����OCP��������
* @par   ˵��
* -# ��MOS PWM����ҳ���OCP�쳣ʱ���ڲ�Ӳ���Զ����棬�ر�MOS PWM�����
* -# ���ٵȴ�1ms�󣬿�ͨ��plib_mos_ocp_unlock()������
* -# OCP�쳣�ѽ����MOS PWM��������������������λ��λ
*/
U8 plib_mos_get_ocp_lock(void)
{
    return (PREG_MOS_IEN & 0x10);
}

/**
* @brief  OCP�쳣���������MOS���
* @param  ��
* @retval ��
* @par   ˵��
* -# OCP�쳣�ѽ����MOS PWM����������������������MOS
*/
void plib_mos_ocp_unlock(void)
{
    PREG_MOS_IEN &= ~0x10;
}
