/**
 * @file
 * @brief		ϵͳ����
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#include "pmcu_x0_sys.h"

/**
* @brief  ϵͳʱ��ʹ��
* @param  ��
* @retval ��
* @par   ˵��
* -# оƬ����������ʹ��ϵͳʱ��
*/
void plib_sys_clk_en(void)
{
	//оƬʱ������Ϊ0x00
	PREG_CLK_SEL = PREG_CLK_SEL & 0xFC | 0x00;	
}

/**
* @brief  ϵͳ��λ
* @param  ��
* @retval ��
* @par   ˵��
* -# ���ú�ϵͳ��λ
*/
void plib_sys_reset(void)
{
    PREG_CLK_SEL |= 0x04;
}

/**
* @brief  ϵͳ���ж�ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* -# ʹ�ܺ�����ģ����жϲ��ܴ���
*/
void plib_sys_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EAL = 1;
    else
        PBIT_EAL = 0;
}

/**
* @brief  JTAG���Խӿ�ѡ��
* @param  sel JTAG���Ժ��ܣ�ѡ�� \n
* @ref JTAG_SEL_DISABLE \n
* @ref JTAG_SEL_GPIOA	\n
* @ref JTAG_SEL_GPIOB	\n
* @retval ��
* @par   ˵��
* -# ʹ�ܺ�����ģ����жϲ��ܴ���
*/
void plib_sys_jtag_sel(JTAG_SEL_E sel)
{
    PREG_SYS_CTRL = (PREG_SYS_CTRL & 0xFC) | sel;
}
