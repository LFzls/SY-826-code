/**
 * @file
 * @brief		串口配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#ifndef __PMCU_UART_H_
#define __PMCU_UART_H_

#include "pmcu_x0_config.h"

#define UART_S1RI 							((U8)0x01)	/*!< 串口接收标志位 */
#define UART_S1TI 							((U8)0x02)	/*!< 串口发送标志位 */

//串口数据长度
#define UART_WordLength_8b                  ((U8)0x80)	/*!< 串口8bit数据模式 */
#define UART_WordLength_9b                  ((U8)0x00)	/*!< 串口9bit数据模式 */

//串口收发模式
#define UART_Mode_FullDuplex                ((U8)0x00)	/*!< 串口全双工模式，TX复用在GPIOC0，RX复用在GPIOC1 */
#define UART_Mode_HalfDuplex                ((U8)0x40)	/*!< 串口半双工模式，使用GPIOC0管脚 */

//串口接收使能
#define UART_RxEnable                		((U8)0x10)	/*!< 串口接收使能 */
#define UART_RxDisable                		((U8)0x00)	/*!< 串口接收不使能 */

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
void plib_uart_init(U8 WordLength, U32 BaudRate, U8 Mode, FUNC_EN_E RxEn, FUNC_EN_E ITEn);

/**
* @brief  UART接收使能
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* -# UART工作在半双工时，需要使用此接口切换串口的收发状态
*/
void plib_uart_rx_en(FUNC_EN_E ifEn);

/**
* @brief  UART中断使能
* @param  newstate 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* 无
*/
void plib_uart_it_en(FUNC_EN_E ifEn);

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
U8 plib_uart_get_flg(U8 Flg);

/**
* @brief  清除串口状态
* @param  Flg 串口标志位，选择： \n
* @ref UART_S1RI \n
* @ref UART_S1TI \n
* @retval 无
* @par   说明
* 无
*/
void plib_uart_clr_flg(U8 Flg);

/**
* @brief  发送单字节数据
* @param  value 要发送的字节
* @retval 无
* @par   说明
* 无
*/
void plib_uart_send_byte(U8 value);

/**
* @brief  获取单字节数据
* @param  无
* @retval 读取到的字节数据
* @par   说明
* 无
*/
U8 plib_uart_get_byte();

/**
* @brief  获取串口是否忙状态
* @param  无
* @retval  串口工作状态
* - 0 串口空闲
* - 非0 串口忙
* @par   说明
* 无
*/
U8 plib_uart_is_busy();


#endif /* end of __PMCU_UART_H_ */
