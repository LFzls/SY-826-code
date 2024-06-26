/**
 * @file
 * @brief		��������
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#include "pmcu_x0_uart.h"

/**
* @brief  ���ڳ�ʼ������
* @param  WordLength ��������λ��ѡ�� \n
* @ref UART_WordLength_8b \n
* @ref UART_WordLength_9b \n
* @param  BaudRate ���ڲ����ʣ���Χ��2400~115200
* @param  Mode ���ڹ���ģʽ��ѡ�� \n
* @ref UART_Mode_FullDuplex \n
* @ref UART_Mode_HalfDuplex \n
* @param  RxEn ���ڽ���ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @param  ITEn �����ж�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_uart_init(U8 WordLength, U32 BaudRate, U8 Mode, FUNC_EN_E RxEn, FUNC_EN_E ITEn)
{
    //���ô��ڹ���ģʽ
    if (RxEn == PLIB_ENABLE)
        PREG_UART_CTRL = (PREG_UART_CTRL & 0x2F) | WordLength | Mode | 0x10;
    else
        PREG_UART_CTRL = (PREG_UART_CTRL & 0x2F) | WordLength | Mode;

    //���㴮�ڲ�����
    PREG_UART_BAUD_H = (U8)((SYS_CLK / BaudRate - 1) / 256);
    PREG_UART_BAUD_L = (U8)((SYS_CLK / BaudRate - 1) % 256);

    //����1�ж���������
    if (ITEn == PLIB_ENABLE)
        PREG_IEN2 |= 0x01;
    else
        PREG_IEN2 &= ~0x01;
}

/**
* @brief  UART����ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par    ˵��
* -# UART�����ڰ�˫��ʱ����Ҫʹ�ô˽ӿ��л����ڵ��շ�״̬
*/
void plib_uart_rx_en(FUNC_EN_E ifEn)
{
    if (ifEn)
        PREG_UART_CTRL |= 0x10;
    else
        PREG_UART_CTRL &= ~0x10;
}

/**
* @brief  UART�ж�ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par    ˵��
* ��
*/
void plib_uart_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_IEN2 |= 0x01;
    else
        PREG_IEN2 &= ~0x01;
}

/**
* @brief  ��ȡ����״̬
* @param  ���ڽṹ�������ַ
* @param  Flg ���ڱ�־λ��ѡ�� \n
* @ref UART_S1RI \n
* @ref UART_S1TI \n
* @retval  ����״̬
* - 0 �޶�Ӧ״̬����
* - ��0 ��Ӧ״̬������
* @par   ˵��
* ��
*/
U8 plib_uart_get_flg(U8 Flg)
{
    return (PREG_UART_CTRL & (Flg));
}

/**
* @brief  �������״̬
* @param  Flg ���ڱ�־λ��ѡ�� \n
* @ref UART_S1RI \n
* @ref UART_S1TI \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_uart_clr_flg(U8 Flg)
{
    PREG_UART_CTRL &= ~(Flg);
}

/**
* @brief  ���͵��ֽ�����
* @param  value Ҫ���͵��ֽ�
* @retval ��
* @par   ˵��
* ��
*/
void plib_uart_send_byte(U8 value)
{
    PREG_UART_S1BUF = value;
}

/**
* @brief  ��ȡ���ֽ�����
* @param  ��
* @retval ��ȡ�����ֽ�����
* @par   ˵��
* ��
*/
U8 plib_uart_get_byte()
{
    return (PREG_UART_S1BUF);
}

/**
* @brief  ��ȡ�����Ƿ�æ״̬
* @param  ��
* @retval  ���ڹ���״̬
* - 0 ���ڿ���
* - ��0 ����æ
* @par   ˵��
* ��
*/
U8 plib_uart_is_busy()
{
    return (PREG_UART_CTRL & 0x20);
}
