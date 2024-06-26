/**
 * @file
 * @brief		延时函数配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#include "pmcu_x0_delay.h"

/**
* @brief 延时xms函数
* @param ms 延时nms
* @retval 无
* @par   说明
* -# ms延时函数，且填入数值为延时多少ms，最大输入65535
*/
void delay_ms(U16 ms)
{
    U16 i, j;

    for (i = 0; i < ms; i ++) {
        for (j = 0; j < 1400; j ++);
    }
}

/**
* @brief 延时x10us函数
* @param us 延时(n *10) us
* @retval 无
* @par   说明
* -# us延时函数，且填入数值为延时多少个10us，最大输入65535
*/
void delay10us(U16 us)
{
    U8 cnt;

    do {
        cnt = 35;

        while (--cnt);
    } while (--us);
}
