/**
 * @file
 * @brief		延时函数配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#ifndef __PMCU_DELAY_H_
#define __PMCU_DELAY_H_

#include "pmcu_x0_config.h"

/**
* @brief 延时xms函数
* @param ms 延时nms
* @retval 无
* @par   说明
* -# ms延时函数，且填入数值为延时多少ms，最大输入65535
*/
void delay_ms(U16 ms);

/**
* @brief 延时x10us函数
* @param us 延时(n *10) us
* @retval 无
* @par   说明
* -# us延时函数，且填入数值为延时多少个10us，最大输入65535
*/
void delay10us(U16 us);

#endif /* end of __PMCU_DELAY_H_ */
