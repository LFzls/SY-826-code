/**
 * @file
 * @brief		��ʱ��������
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#include "pmcu_x0_delay.h"

/**
* @brief ��ʱxms����
* @param ms ��ʱnms
* @retval ��
* @par   ˵��
* -# ms��ʱ��������������ֵΪ��ʱ����ms���������65535
*/
void delay_ms(U16 ms)
{
    U16 i, j;

    for (i = 0; i < ms; i ++) {
        for (j = 0; j < 1400; j ++);
    }
}

/**
* @brief ��ʱx10us����
* @param us ��ʱ(n *10) us
* @retval ��
* @par   ˵��
* -# us��ʱ��������������ֵΪ��ʱ���ٸ�10us���������65535
*/
void delay10us(U16 us)
{
    U8 cnt;

    do {
        cnt = 35;

        while (--cnt);
    } while (--us);
}
