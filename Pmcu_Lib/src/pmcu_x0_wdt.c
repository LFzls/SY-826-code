/**
 * @file
 * @brief		���Ź�����
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#include "pmcu_x0_wdt.h"

/**
* @brief  ���Ź����ʱ������
* @param  Tim_ms ���Ź����ʱ�䣬��λms�����ֵ����1500
* @retval ��
* @par   ˵��
* ��
*/
void plib_wdt_set_time(U16 Tim_ms)
{
    if (Tim_ms > 1500)
        Tim_ms = 1500;

    if (Tim_ms >= 98) {
        PREG_WDT_TIME = ((32764 - (SYS_CLK / 1000 * Tim_ms / 48 / 16)) / 256) | 0x80;
    } else {
        PREG_WDT_TIME = (32764 - (SYS_CLK / 1000 * Tim_ms / 48)) / 256;
    }
}

/**
* @brief  ���Ź�����
* @param  ��
* @retval ��
* @par   ˵��
* ��
*/
void plib_wdt_open(void)
{
    PBIT_WDTEN = 1;
}

/**
* @brief  ���Ź��Ƿ���
* @param  ��
* @retval  ���Ź�״̬
* - 0 ���Ź�δ����
* - ��0 ���Ź��ѿ���
* @par   ˵��
* ��
*/
U8 plib_wdt_if_open(void)
{
    return PBIT_WDTEN;
}

/**
* @brief  ���Ź��ر�
* @param  ��
* @retval ��
* @par   ˵��
* ��
*/
void plib_wdt_close(void)
{
    PBIT_WDTEN = 0;
    PBIT_WDTEN = 1;
}

/**
* @brief  ���Ź�ι��
* @param  ��
* @retval ��
* @par   ˵��
* ��
*/
void plib_wdt_reflesh(void)
{
    PBIT_WDTEN = 1;
}
