/**
 * @file
 * @brief		MIC����
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.1
 * @par 		Copyright(c): All rights reserved.
 * @par 		�޸ļ�¼
 * @par 		1.admin��2023-08-21���������װ��ʽ�����ٴ���ռ�
*/

#include "pmcu_x0_delay.h"
#include "pmcu_x0_mic.h"

/**
* @brief  ʹ����ͷ����
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par    ˵��
* -# �޸�MIC����ʱ����Ҫ�ȹر�MICʹ��
* -# MICʹ�ܺ���Ҫ��ʱ300ms���ȴ�MIC�����ȶ�
*/
void plib_mic_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_MIC_CTRL0 |= 0x01;
    else
		PREG_MIC_CTRL0 &= ~0x01;
    delay10us(15);
}

/**
* @brief  MIC��ʼ������
* @param  Event MIC�¼��������ж�ʹ�ܣ�ѡ�����²����� \n
* @ref MIC_ALL_ON \n
* @ref MIC_ABNORMAL \n
* @ref MIC_SAMPLE \n
* @ref MIC_BLOW \n
* @ref MIC_INHALE_TIMEOUT \n
* @ref MIC_INHALE_RELEASE \n
* @ref MIC_INHALE \n
* @ref MIC_REFLESH_VALUE \n
* @ref MIC_BLOW_RELEASE \n
* @ref MIC_ALL_OFF	    \n
* @param  Mic_Curr ��ͷ��������ѡ�� \n
* @ref MIC_CURR_160NA \n
* @ref MIC_CURR_320NA \n
* @param  Sample_Time ��ͷ����ʱ�䣬ѡ�� \n
* @ref MIC_SAMPLE_TIME_45MS \n
* @ref MIC_SAMPLE_TIME_35MS \n
* @ref MIC_SAMPLE_TIME_23MS \n
* @ref MIC_SAMPLE_TIME_57MS \n
* @param  Timeout ��ͷ������ʱʱ�䣬ѡ�� \n
* @ref MIC_TIMEOUT_2_5 \n
* @ref MIC_TIMEOUT_5 \n
* @ref MIC_TIMEOUT_10 \n
* @ref MIC_TIMEOUT_20 \n
* @retval ��
* @par    ˵��
* -# �޸�MIC����ʱ����Ҫ�ȹر�MICʹ��
* -# ��ʹ��˯�߻��ѵ�MIC�¼����ѣ�MIC_IntEn���ж�ʹ�ܣ�ͬʱ��Ϊ˯�߻����¼�
* -# ����MIC_BLOW�ʹ����ͷ�MIC_BLOW_RELEASE����һ���ж�ʹ�ܿ���
*/
void plib_mic_init(U8 Event, U8 Mic_Curr, U8 Sample_Time, MIC_TIMEOUT_E Timeout)
{
    //����MIC������
    PREG_SENSOR_CTRL = (PREG_SENSOR_CTRL & 0xF7) | Mic_Curr;
	
    //����MIC����ʱ��
    PREG_MIC_TRIG1 = (PREG_MIC_TRIG1 & 0x9F) | Sample_Time;
	
    //����MIC��ʱʱ��
    PREG_MIC_CTRL1 = (PREG_MIC_CTRL1 & 0xFC) | Timeout;
	
    //����MIC�ж�
    PREG_MIC_CTRL0 = (PREG_MIC_CTRL0 & 0x01) | (Event & 0xFE);

	delay10us(15);	
}

/**
* @brief  MIC��ʼ������
* @param  Trig1 MIC��һ��ֵ�����÷�Χ0~31�����̱���Ϊ������ֵ/1024
* @param  Trig2 MIC�ڶ���ֵ�����÷�Χ0~255�����̱���Ϊ������ֵ/1024
* @retval ��
* @par    ˵��
* ��
*/
void plib_mic_set_trig(U8 Trig1, U8 Trig2)
{
    //�������̵�һ��ֵ
    if (Trig1 > 31)
        Trig1 = 31;
    PREG_MIC_TRIG1 = (PREG_MIC_TRIG1 & 0xE0) | Trig1;
	
    //�������̵ڶ���ֵ
    if (Trig2 > 255)
        Trig2 = 255;
   PREG_MIC_TRIG2 = Trig2;
   
	delay10us(15);	
}

/**
* @brief  MIC�ж�����
* @param  Event MIC�¼��������ж�ʹ�ܣ�ѡ�����²����� \n
* @ref MIC_ALL_ON \n
* @ref MIC_ABNORMAL \n
* @ref MIC_SAMPLE \n
* @ref MIC_BLOW \n
* @ref MIC_INHALE_TIMEOUT \n
* @ref MIC_INHALE_RELEASE \n
* @ref MIC_INHALE \n
* @ref MIC_REFLESH_VALUE \n
* @ref MIC_BLOW_RELEASE \n
* @ref MIC_ALL_OFF	    \n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par    ˵��
* -# ��ʹ��˯�߻��ѵ�MIC�¼����ѣ�MIC_IntEn���ж�ʹ�ܣ�ͬʱ��Ϊ˯�߻����¼�
* -# ����MIC_BLOW�ʹ����ͷ�MIC_BLOW_RELEASE����һ���ж�ʹ�ܿ���
*/
void plib_mic_it_cfg(U8 Event, FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE) 
        PREG_MIC_CTRL0 = (PREG_MIC_CTRL0 & 0x01) | (Event & 0xFE);
    else 
        PREG_MIC_CTRL0 &= ~(Event & 0xFE);
   
	delay10us(15);
}

/**
* @brief  MIC�ж��Ƿ�ʹ��
* @param  Event MIC�¼��������ж�ʹ�ܣ�ѡ�����²����� \n
* @ref MIC_ALL_ON \n
* @ref MIC_ABNORMAL \n
* @ref MIC_SAMPLE \n
* @ref MIC_BLOW \n
* @ref MIC_INHALE_TIMEOUT \n
* @ref MIC_INHALE_RELEASE \n
* @ref MIC_INHALE \n
* @ref MIC_REFLESH_VALUE \n
* @ref MIC_BLOW_RELEASE \n
* @ref MIC_ALL_OFF	    \n
* @retval  �¼��ж�ʹ��״̬
* - 0 δʹ��
* - ��0 ��ʹ��
* @par ˵��
* ��
*/
U8 plib_mic_it_ifen(U8 Event)
{
    return (PREG_MIC_CTRL0 & Event);
}


/**
* @brief  MIC���ж�ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_mic_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EX0 = 1;
    else
        PBIT_EX0 = 0;
}

/**
* @brief  ������ͷ��һ��ֵ
* @param  TrigValue MIC��һ��ֵ�����÷�Χ0~31�����̱���Ϊ������ֵ/1024
* @retval ��
* @par    ˵��
* -# �ýӿڽ���MICʹ��300ms�󣬵�����Ч
*/
void plib_mic_set_trig1(U8 TrigValue)
{
    //�������̵�һ��ֵ
    if (TrigValue > 31)
        TrigValue = 31;

    PREG_MIC_TRIG1 = (PREG_MIC_TRIG1 & 0xE0) | TrigValue;
    delay10us(15);
}

/**
* @brief  ��ȡ��ͷ��һ��ֵ
* @param  ��
* @retval ��ǰ���õ�MIC��һ��ֵ
* @par   ˵��
* ��
*/
U8 plib_mic_get_trig1(void)
{
    return (PREG_MIC_TRIG1 & 0x1F);
}

/**
* @brief  ������ͷ�ڶ���ֵ
* @param  TrigValue MIC�ڶ���ֵ�����÷�Χ0~255�����̱���Ϊ������ֵ/1024
* @retval ��
* @par    ˵��
* -# �ýӿڽ���MICʹ��300ms�󣬵�����Ч
*/
void plib_mic_set_trig2(U8 TrigValue)
{
    if (TrigValue > 255)
        TrigValue = 255;
    PREG_MIC_TRIG2 = TrigValue;
    delay10us(15);
}

/**
* @brief  ��ȡ��ͷ�ڶ���ֵ
* @param  ��
* @retval ��ǰ���õ�MIC�ڶ���ֵ
* @par   ˵��
* ��
*/
U8 plib_mic_get_trig2(void)
{
    return (PREG_MIC_TRIG2);
}

/**
* @brief  ��ȡ��ͷ��ֵ
* @param  ��
* @retval ��ǰ��ͷ�ĳ�ֵ
* @par   ˵��
* ��
*/
U16 plib_mic_get_init_value(void)
{
    return ((PREG_MIC_INI1 << 8) | PREG_MIC_INI0);
}

/**
* @brief  ��ȡ��ͷʵʱ����ֵ
* @param  ��
* @retval ��ǰ��ͷ��ʵʱ����ֵ
* @par   ˵��
* ��
*/
U16 plib_mic_get_cur_value(void)
{
    return ((PREG_MIC_VAL1 << 8) | PREG_MIC_VAL0);
}

/**
* @brief  ��ȡMIC�¼�״̬
* @param  Event MIC�¼���ѡ�����²����� \n
* @ref MIC_ALL_ON \n
* @ref MIC_ABNORMAL \n
* @ref MIC_SAMPLE \n
* @ref MIC_BLOW \n
* @ref MIC_INHALE_TIMEOUT \n
* @ref MIC_INHALE_RELEASE \n
* @ref MIC_INHALE \n
* @ref MIC_REFLESH_VALUE \n
* @ref MIC_BLOW_RELEASE \n
* @ref MIC_ALL_OFF	    \n
* @retval  �¼�����״̬
* - 0 δ�������¼�
* - ��0 �Ѵ������¼�
* @par   ˵��
* ��
*/
U8 plib_mic_get_flg(U8 Event)
{
    return (PREG_MIC_FLAG & Event);
}

/**
* @brief  ���MIC�¼�״̬
* @param  Event MIC�¼���ѡ�����²����� \n
* @ref MIC_ALL_ON \n
* @ref MIC_ABNORMAL \n
* @ref MIC_SAMPLE \n
* @ref MIC_BLOW \n
* @ref MIC_INHALE_TIMEOUT \n
* @ref MIC_INHALE_RELEASE \n
* @ref MIC_INHALE \n
* @ref MIC_REFLESH_VALUE \n
* @ref MIC_BLOW_RELEASE \n
* @ref MIC_ALL_OFF	    \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_mic_clr_flg(U8 Event)
{
    PREG_MIC_FLAG &= ~Event;
}

/**
* @brief  ��������������̳�ֵ
* @param  ��
* @retval ��
* @par    ˵��
* -# �ýڿڿ���������ʱ�̣���������һ����ͷ���̳�ֵ
*/
void plib_mic_reflesh_ini_value()
{
	//ʹ��MCUģʽ
    PREG_MIC_CTRL1 = (PREG_MIC_CTRL1 & 0xFB) | 0x04;
	delay10us(15);
	
	//ʹ��MCU�������³�ֵ
    PREG_MIC_CTRL1 = (PREG_MIC_CTRL1 & 0xF7) | 0x08;
	delay10us(15);
	
	//�ر�MCUģʽ
    PREG_MIC_CTRL1 = PREG_MIC_CTRL1 & 0xF3;	
	delay10us(15);
}

/**
* @brief  MIC����ģʽ
* @param  mode MIC����ģʽ��ѡ�����²����� \n
* @ref MIC_CTRL_MODE_HW \n
* @ref MIC_CTRL_MODE_SW \n
* @retval ��
* @par    ˵��
* -# �ýڿ���������MIC����ģʽ���л������ģʽ����ͷ�Զ����³�ֵʹ�ܽ�ʧЧ
*/
void plib_mic_ctrl_mode(U8 mode)
{
	if(mode == MIC_CTRL_MODE_SW)
	{
		PREG_MIC_CTRL1 = (PREG_MIC_CTRL1 & 0xFB) | 0x04;
	}
	else
	{
		PREG_MIC_CTRL1 = PREG_MIC_CTRL1 & 0xF3;
	}
	delay10us(15);	
}

