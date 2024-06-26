/**
 * @file
 * @brief		串口配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#include "pmcu_x0_uart.h"

/**
* @brief  串口初始化函数
* @param  WordLength 串口数据位宽，选择： \n
* @ref UART_WordLength_8b \n
* @ref UART_WordLength_9b \n
* @param  BaudRate 串口波特率，范围：2400~115200
* @param  Mode 串口工作模式，选择： \n
* @ref UART_Mode_FullDuplex \n
* @ref UART_Mode_HalfDuplex \n
* @param  RxEn 串口接收使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @param  ITEn 串口中断使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_uart_init(U8 WordLength, U32 BaudRate, U8 Mode, FUNC_EN_E RxEn, FUNC_EN_E ITEn)
{
    //设置串口工作模式
    if (RxEn == PLIB_ENABLE)
        PREG_UART_CTRL = (PREG_UART_CTRL & 0x2F) | WordLength | Mode | 0x10;
    else
        PREG_UART_CTRL = (PREG_UART_CTRL & 0x2F) | WordLength | Mode;

    //计算串口波特率
    PREG_UART_BAUD_H = (U8)((SYS_CLK / BaudRate - 1) / 256);
    PREG_UART_BAUD_L = (U8)((SYS_CLK / BaudRate - 1) % 256);

    //串口1中断允许配置
    if (ITEn == PLIB_ENABLE)
        PREG_IEN2 |= 0x01;
    else
        PREG_IEN2 &= ~0x01;
}

/**
* @brief  UART接收使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* -# UART工作在半双工时，需要使用此接口切换串口的收发状态
*/
void plib_uart_rx_en(FUNC_EN_E ifEn)
{
    if (ifEn)
        PREG_UART_CTRL |= 0x10;
    else
        PREG_UART_CTRL &= ~0x10;
}

/**
* @brief  UART中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* 无
*/
void plib_uart_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_IEN2 |= 0x01;
    else
        PREG_IEN2 &= ~0x01;
}

/**
* @brief  获取串口状态
* @param  串口结构体变量地址
* @param  Flg 串口标志位，选择： \n
* @ref UART_S1RI \n
* @ref UART_S1TI \n
* @retval  串口状态
* - 0 无对应状态产生
* - 非0 对应状态发生了
* @par   说明
* 无
*/
U8 plib_uart_get_flg(U8 Flg)
{
    return (PREG_UART_CTRL & (Flg));
}

/**
* @brief  清除串口状态
* @param  Flg 串口标志位，选择： \n
* @ref UART_S1RI \n
* @ref UART_S1TI \n
* @retval 无
* @par   说明
* 无
*/
void plib_uart_clr_flg(U8 Flg)
{
    PREG_UART_CTRL &= ~(Flg);
}

/**
* @brief  发送单字节数据
* @param  value 要发送的字节
* @retval 无
* @par   说明
* 无
*/
void plib_uart_send_byte(U8 value)
{
    PREG_UART_S1BUF = value;
}

/**
* @brief  获取单字节数据
* @param  无
* @retval 读取到的字节数据
* @par   说明
* 无
*/
U8 plib_uart_get_byte()
{
    return (PREG_UART_S1BUF);
}

/**
* @brief  获取串口是否忙状态
* @param  无
* @retval  串口工作状态
* - 0 串口空闲
* - 非0 串口忙
* @par   说明
* 无
*/
U8 plib_uart_is_busy()
{
    return (PREG_UART_CTRL & 0x20);
}
