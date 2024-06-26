/**
 * @file
 * @brief		��ʱ������
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.1
 * @par 		Copyright(c): All rights reserved.
 * @par 		�޸ļ�¼
 * @par 		1.admin��2023-08-21���������װ��ʽ�����ٴ���ռ�
*/

#include "pmcu_x0_timer.h"

#define TIMERx_Tim_Load_13bit(us)		(U16)(8192 - (U16)((16 * (us)/12)))
#define TIMERx_Tim_Load_16_bit(us)		(U16)(65536 - (U16)((16 * (us)/12)))
#define TIMERx_Cal_TH(timemode, us)	(timemode == TIM_MODE_0)? (U8)(TIMERx_Tim_Load_13bit(us) >> 5) : (U8)(TIMERx_Tim_Load_16_bit(us) >> 8)
#define TIMERx_Cal_TL(timemode, us)	(timemode == TIM_MODE_0)? (U8)(TIMERx_Tim_Load_13bit(us) & 0xFF) : (U8)(TIMERx_Tim_Load_16_bit(us) & 0xFF)

/**
* @brief  ��ʱ��0��ʼ������
* @param  TIM_Mode ��ʱ���Ĺ���ģʽ��ѡ�� \n
* @ref TIM_MODE_0 \n
* @ref TIM_MODE_1 \n
* @ref TIM_MODE_2 \n
* @param  TIM_Times ��ʱ���Ķ�ʱʱ�䣬��λus��TIM_MODE_0���ʱʱ��Ϊ6ms��TIM_MODE_1��TIM_MODE_2���ʱʱ��Ϊ49ms
* @param  TIM_En ��ʱ��������ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @param  TIM_IntEn ��ʱ�����ж�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_tim0_init(TIM_Mode_E TIM_Mode, U16 TIM_Times, FUNC_EN_E TIM_En, FUNC_EN_E TIM_IntEn)
{
    //����ģʽ
    PREG_TMOD = (PREG_TMOD & 0xFC) | TIM_Mode;
	
    //���ö�ʱֵ��������ģʽ����д���ؼĴ�������ģʽ2��ʹ��
    PREG_CRCH0 = PREG_TH0 = TIMERx_Cal_TH(TIM_Mode, TIM_Times);
    PREG_CRCL0 = PREG_TL0 = TIMERx_Cal_TL(TIM_Mode, TIM_Times);
	
    //������ʱ��
    PBIT_TR0 = TIM_En;
    //ʹ�ܶ�ʱ���ж�
    PBIT_ET0 = TIM_IntEn;
}

/**
* @brief  ��ʱ��0��װ��ֵ
* @param  TIM_Mode ��ʱ���Ĺ���ģʽ��ѡ�� \n
* @ref TIM_MODE_0 \n
* @ref TIM_MODE_1 \n
* @param  TIM_Times ��ʱ���Ķ�ʱʱ�䣬��λus��TIM_MODE_0���ʱʱ��Ϊ6ms��TIM_MODE_1���ʱʱ��Ϊ49ms
* @retval ��
* @par   ˵��
* -# ����TIM_MODE_0��TIM_MODE_1����ģʽ��ʹ��
*/
void plib_tim0_reload(TIM_Mode_E TIM_Mode, U16 TIM_Times)
{
    //���ö�ʱֵ
    PREG_TH0 = TIMERx_Cal_TH(TIM_Mode, TIM_Times);
    PREG_TL0 = TIMERx_Cal_TL(TIM_Mode, TIM_Times);	
}

/**
* @brief  ��ʱ��1��ʼ������
* @param  TIM_Mode ��ʱ���Ĺ���ģʽ��ѡ�� \n
* @ref TIM_MODE_0 \n
* @ref TIM_MODE_1 \n
* @ref TIM_MODE_2 \n
* @param  TIM_Period ��ʱ���Ķ�ʱʱ�䣬��λus��TIM_MODE_0���ʱʱ��Ϊ6ms��TIM_MODE_1��TIM_MODE_2���ʱʱ��Ϊ49ms
* @param  TIM_En ��ʱ��������ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @param  TIM_IntEn ��ʱ�����ж�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_tim1_init(TIM_Mode_E TIM_Mode, U16 TIM_Times, FUNC_EN_E TIM_En, FUNC_EN_E TIM_IntEn)
{
    //����ģʽ
    PREG_TMOD = (PREG_TMOD & 0xCF) | (TIM_Mode << 4);
	
    //���ö�ʱֵ��������ģʽ����д���ؼĴ�������ģʽ2��ʹ��
    PREG_CRCH1 = PREG_TH1 = TIMERx_Cal_TH(TIM_Mode, TIM_Times);
    PREG_CRCL1 = PREG_TL1 = TIMERx_Cal_TL(TIM_Mode, TIM_Times);
	
    //������ʱ��
    PBIT_TR1 = TIM_En;
    //ʹ�ܶ�ʱ���ж�
    PBIT_ET1 = TIM_IntEn;
}

/**
* @brief  ��ʱ��1��װ��ֵ
* @param  TIM_Mode ��ʱ���Ĺ���ģʽ��ѡ�� \n
* @ref TIM_MODE_0 \n
* @ref TIM_MODE_1 \n
* @param  TIM_Times ��ʱ���Ķ�ʱʱ�䣬��λus��TIM_MODE_0���ʱʱ��Ϊ6ms��TIM_MODE_1���ʱʱ��Ϊ49ms
* @retval ��
* @par   ˵��
* -# ����TIM_MODE_0��TIM_MODE_1����ģʽ��ʹ��
*/
void plib_tim1_reload(TIM_Mode_E TIM_Mode, U16 TIM_Times)
{
    //���ö�ʱֵ
    PREG_TH1 = TIMERx_Cal_TH(TIM_Mode, TIM_Times);
    PREG_TL1 = TIMERx_Cal_TL(TIM_Mode, TIM_Times);	
}


/**
* @brief  Timer0�Ƿ�������ʱ
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_tim0_en(FUNC_EN_E ifEn)
{
    PBIT_TR0 = ifEn;
}

/**
* @brief  Timer0�ж�ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par    ˵��
* ��
*/
void plib_tim0_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_ET0 = 1;
    else
        PBIT_ET0 = 0;
}

/**
* @brief  Timer1�Ƿ�������ʱ
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_tim1_en(FUNC_EN_E ifEn)
{
    PBIT_TR1 = ifEn;
}

/**
* @brief  Timer1�ж�ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par    ˵��
* ��
*/
void plib_tim1_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_ET1 = 1;
    else
        PBIT_ET1 = 0;
}
