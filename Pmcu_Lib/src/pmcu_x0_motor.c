/**
 * @file
 * @brief		MOTOR����
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.0
 * @par 		Copyright(c): All rights reserved.
*/

#include "pmcu_x0_motor.h"

/**
* @brief  MOTOR PWM���ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_motor_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_MOTOR_CTRL |= 0x10;
    else
        PREG_MOTOR_CTRL &= ~0x10;
}

/**
* @brief  MOTOR���ռ�ձ�����
* @param  duty ռ�ձ����ã�ѡ�� \n
*@ref MOTOR_DUTY_0  \n
*@ref MOTOR_DUTY_7  \n
*@ref MOTOR_DUTY_13 \n
*@ref MOTOR_DUTY_20 \n
*@ref MOTOR_DUTY_27 \n
*@ref MOTOR_DUTY_33 \n
*@ref MOTOR_DUTY_40 \n
*@ref MOTOR_DUTY_47 \n
*@ref MOTOR_DUTY_53 \n
*@ref MOTOR_DUTY_60 \n
*@ref MOTOR_DUTY_67 \n
*@ref MOTOR_DUTY_73 \n
*@ref MOTOR_DUTY_80 \n
*@ref MOTOR_DUTY_87 \n
*@ref MOTOR_DUTY_93 \n
*@ref MOTOR_DUTY_100 \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_motor_set_duty(MOTOR_DUTY_E duty)
{
    PREG_MOTOR_CTRL = (PREG_MOTOR_CTRL & 0xF0) | duty;
}
