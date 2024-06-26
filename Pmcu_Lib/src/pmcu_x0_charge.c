/**
 * @file
 * @brief		�������
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.1
 * @par 		Copyright(c): All rights reserved.
 * @par 		�޸ļ�¼
 * @par 		1.admin��2023-09-06������plib_chg_ifen()�ӿڣ�����plib_chg_init()IBCEn�������� 
*/

#include "pmcu_x0_charge.h"

/**
* @brief  ����ʼ������
* @param  IBCEn ��������ǰ���Ƿ��г���������\n
* @ref PLIB_ENABLE ʹ�ܣ��޳����� \n
* @ref PLIB_DISABLE ��ʹ�ܣ��г����� \n
* @param  CCCurrent ������������ѡ�� \n
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
* @param  FullCurrent ����������� \n
*@ref CHG_FULL_ISET_20 \n
*@ref CHG_FULL_ISET_10 \n
* @param  UVVoltage �������Ƿѹ������ѹ \n
*@ref CHG_UVLS_2_3V \n
*@ref CHG_UVLS_2_4V \n
*@ref CHG_UVLS_2_5V \n
*@ref CHG_UVLS_2_6V \n
* @par   ˵��
* ��
*/
void plib_chg_init(FUNC_EN_E IBCEn, CHG_ISET_E CCCurrent, CHG_FULL_E FullCurrent, VCC_UV_E UVVoltage)
{
    //��������ǰ���Ƿ��г�����
    if (IBCEn == PLIB_ENABLE)
		PREG_CHG_CTRL |= 0x04;
    else
        PREG_CHG_CTRL &= ~0x04;

    //����������
    PREG_CHG_ISET = (PREG_CHG_ISET & 0xF0) | CCCurrent;
    //�����������
    PREG_CHG_CTRL = (PREG_CHG_CTRL & 0xFD) | (FullCurrent << 1);
    //�������Ƿѹ������ѹ
    PREG_CHG_ISET = (PREG_CHG_ISET & 0x3F) | (UVVoltage << 6);
}

/**
  * @brief  ���ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* -# ����رճ��������½���USB�������������������¿������
*/
void plib_chg_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_CHG_CTRL &= ~0x01;
    else
        PREG_CHG_CTRL |= 0x01;
}

/**
* @brief  ����Ƿ�ʹ��
* @retval  ���ʹ��״̬
* - 0 δʹ��
* - ��0 ��ʹ��
* @par ˵��
* ��
*/
U8 plib_chg_ifen(void)
{
    return (!(PREG_CHG_CTRL & 0x01));
}


/**
* @brief  ���ú���������
* @param  Current ������������ѡ�� \n
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
* @par   ˵��
* -# ֧�ֳ��������޸ĳ�����
*/
void plib_chg_set_cc_current(CHG_ISET_E Current)
{
    PREG_CHG_ISET = (PREG_CHG_ISET & 0xF0) | Current;
}

/**
* @brief  ����ж�ʹ��
* @param  event ����¼���ѡ������һ�������� \n
* @ref CHG_IEN_CHGST \n
* @ref CHG_IEN_USB	\n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_chg_it_cfg(U8 event, FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_CHG_CTRL = (PREG_CHG_CTRL & 0xE7) | event;
    else
        PREG_CHG_CTRL &= ~event;
}

/**
* @brief  ����ж��Ƿ�ʹ��
* @param  event ����¼���ѡ������һ�������� \n
* @ref CHG_IEN_CHGST \n
* @ref CHG_IEN_USB	\n\n
* @retval  �¼��ж�ʹ��״̬
* - 0 δʹ��
* - ��0 ��ʹ��
* @par ˵��
* ��
*/
U8 plib_chg_it_ifen(U8 event)
{
    return (PREG_CHG_CTRL & event);
}

/**
* @brief  ������ж�ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_chg_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EX7 = 1;
    else
        PBIT_EX7 = 0;
}

/**
* @brief  ��ȡ����¼�״̬
* @param  event ����¼���ѡ�� \n
* @ref CHG_CHG_ST_IF \n
* @ref CHG_USB_IN	\n
* @ref CHG_USB_OUT	\n
* @retval  �¼�����״̬
* - 0 �¼�δ����
* - ��0 �¼��Ѵ���
* @par   ˵��
* ��
*/
U8 plib_chg_get_flg(U8 event)
{
    return (PREG_CHG_FLAG & event);
}

/**
* @brief  �������¼���־
* @param  event ����¼���ѡ�� \n
* @ref CHG_CHG_ST_IF \n
* @ref CHG_USB_IN	\n
* @ref CHG_USB_OUT	\n
* @retval ��
* @par   ˵��
* ��
*/
void plib_chg_clr_flg(U8 event)
{
    PREG_CHG_FLAG &= ~event;
}

/**
* @brief  ��ȡ��統ǰ״̬
* @param  flg ���״̬��ѡ�� \n
* @ref CHG_S_RECHARGE \n
* @ref CHG_S_USBOVP	\n
* @ref CHG_S_USBUVP	\n
* @ref CHG_S_TC \n
* @ref CHG_S_CC	\n
* @ref CHG_S_CV	\n
* @ref CHG_S_FULL \n
* @ref CHG_S_USB_IN	\n
* @retval ��統ǰ����״̬
* @par   ˵��
* ��
*/
U8 plib_chg_get_status(U8 flg)
{
    return (PREG_CHG_STATUS & flg);
}
