/**
 * @file
 * @brief		˯�߻�������
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/
#include "pmcu_x0_wakeup.h"

/**
  * @brief  ϵͳ����˯��ģʽ
  * @param  ��
  * @retval ��
  * @par   ˵��
		   ��
  */
void plib_wk_sleep(void)
{
    PREG_WK_CTRL |= 0x80;

    while (!(PREG_WK_CTRL & 0x80));			//�ȴ�ϵͳ�������˯��

    PREG_PCON |= 0x80; 			//ϵͳ����˯��
}

/**
* @brief  ����Դ����
* @param  Src ����Դʹ�ܣ�ѡ������һ�������� \n
* @ref WK_SRC_GPIO \n
* @ref WK_SRC_PLUG \n
* @ref WK_SRC_USB \n
* @ref WK_SRC_CHG_FULL \n
* @ref WK_SRC_MIC \n
* @ref WK_SRC_TIMER \n
* @param  Timer_cfg ʹ�ܶ�ʱ����ʱ�����ö�ʱʱ�����������ֵΪ127��ʱ��=����ֵ*7.76ms����ʹ��ʱ����Ϊ0
* @retval ��
* @par   ˵��
* -# ��ʹ��WK_SRC_TIMER����Դ����Ҫ����Timer_cfg����ʱ��
* -# ��ʹ��WK_SRC_MIC����Դ����Ҫ����plib_mic_it_cfg()���þ����MIC�����¼�
* -# ��ʹ��WK_SRC_GPIO����Դ����Ҫ����plib_gpio_it_cfg()���þ����ĸ�IO���ѣ�����Ҫ����plib_gpio_init()����IOΪ����ģʽ
*/
void plib_wk_init(U8 Src, U8 Timer_cfg)
{
    //��ʱ˯�߻���
    if (Src & WK_SRC_TIMER)
        PREG_WK_TIMER_CFG = 0x80 | (Timer_cfg & 0x7F);
    else
        PREG_WK_TIMER_CFG = 0x01;

    //һ������Դ����
    PREG_WK_CTRL = (PREG_WK_CTRL & 0xE0) | (Src & 0x7F);
}
