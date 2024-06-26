/**
 * @file
 * @brief		MIC配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.1
 * @par 		Copyright(c): All rights reserved.
 * @par 		修改记录
 * @par 		1.admin，2023-08-21，修正库封装方式，减少代码空间
*/

#include "pmcu_x0_delay.h"
#include "pmcu_x0_mic.h"

/**
* @brief  使能咪头工作
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* -# 修改MIC参数时，需要先关闭MIC使能
* -# MIC使能后，需要延时300ms，等待MIC工作稳定
*/
void plib_mic_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_MIC_CTRL0 |= 0x01;
    else
		PREG_MIC_CTRL0 &= ~0x01;
    delay10us(15);
}

/**
* @brief  MIC初始化函数
* @param  Event MIC事件，配置中断使能，选择以下参数： \n
* @ref MIC_ALL_ON \n
* @ref MIC_ABNORMAL \n
* @ref MIC_SAMPLE \n
* @ref MIC_BLOW \n
* @ref MIC_INHALE_TIMEOUT \n
* @ref MIC_INHALE_RELEASE \n
* @ref MIC_INHALE \n
* @ref MIC_REFLESH_VALUE \n
* @ref MIC_BLOW_RELEASE \n
* @ref MIC_ALL_OFF	    \n
* @param  Mic_Curr 咪头充电电流，选择： \n
* @ref MIC_CURR_160NA \n
* @ref MIC_CURR_320NA \n
* @param  Sample_Time 咪头采样时间，选择： \n
* @ref MIC_SAMPLE_TIME_45MS \n
* @ref MIC_SAMPLE_TIME_35MS \n
* @ref MIC_SAMPLE_TIME_23MS \n
* @ref MIC_SAMPLE_TIME_57MS \n
* @param  Timeout 咪头吸气超时时间，选择： \n
* @ref MIC_TIMEOUT_2_5 \n
* @ref MIC_TIMEOUT_5 \n
* @ref MIC_TIMEOUT_10 \n
* @ref MIC_TIMEOUT_20 \n
* @retval 无
* @par    说明
* -# 修改MIC参数时，需要先关闭MIC使能
* -# 若使能睡眠唤醒的MIC事件唤醒，MIC_IntEn的中断使能，同时作为睡眠唤醒事件
* -# 吹气MIC_BLOW和吹气释放MIC_BLOW_RELEASE共享一个中断使能控制
*/
void plib_mic_init(U8 Event, U8 Mic_Curr, U8 Sample_Time, MIC_TIMEOUT_E Timeout)
{
    //配置MIC充电电流
    PREG_SENSOR_CTRL = (PREG_SENSOR_CTRL & 0xF7) | Mic_Curr;
	
    //配置MIC采样时间
    PREG_MIC_TRIG1 = (PREG_MIC_TRIG1 & 0x9F) | Sample_Time;
	
    //配置MIC超时时间
    PREG_MIC_CTRL1 = (PREG_MIC_CTRL1 & 0xFC) | Timeout;
	
    //配置MIC中断
    PREG_MIC_CTRL0 = (PREG_MIC_CTRL0 & 0x01) | (Event & 0xFE);

	delay10us(15);	
}

/**
* @brief  MIC初始化函数
* @param  Trig1 MIC第一阈值，配置范围0~31，吸烟比例为：配置值/1024
* @param  Trig2 MIC第二阈值，配置范围0~255，吸烟比例为：配置值/1024
* @retval 无
* @par    说明
* 无
*/
void plib_mic_set_trig(U8 Trig1, U8 Trig2)
{
    //配置吸烟第一阈值
    if (Trig1 > 31)
        Trig1 = 31;
    PREG_MIC_TRIG1 = (PREG_MIC_TRIG1 & 0xE0) | Trig1;
	
    //配置吸烟第二阈值
    if (Trig2 > 255)
        Trig2 = 255;
   PREG_MIC_TRIG2 = Trig2;
   
	delay10us(15);	
}

/**
* @brief  MIC中断配置
* @param  Event MIC事件，配置中断使能，选择以下参数： \n
* @ref MIC_ALL_ON \n
* @ref MIC_ABNORMAL \n
* @ref MIC_SAMPLE \n
* @ref MIC_BLOW \n
* @ref MIC_INHALE_TIMEOUT \n
* @ref MIC_INHALE_RELEASE \n
* @ref MIC_INHALE \n
* @ref MIC_REFLESH_VALUE \n
* @ref MIC_BLOW_RELEASE \n
* @ref MIC_ALL_OFF	    \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* -# 若使能睡眠唤醒的MIC事件唤醒，MIC_IntEn的中断使能，同时作为睡眠唤醒事件
* -# 吹气MIC_BLOW和吹气释放MIC_BLOW_RELEASE共享一个中断使能控制
*/
void plib_mic_it_cfg(U8 Event, FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE) 
        PREG_MIC_CTRL0 = (PREG_MIC_CTRL0 & 0x01) | (Event & 0xFE);
    else 
        PREG_MIC_CTRL0 &= ~(Event & 0xFE);
   
	delay10us(15);
}

/**
* @brief  MIC中断是否使能
* @param  Event MIC事件，配置中断使能，选择以下参数： \n
* @ref MIC_ALL_ON \n
* @ref MIC_ABNORMAL \n
* @ref MIC_SAMPLE \n
* @ref MIC_BLOW \n
* @ref MIC_INHALE_TIMEOUT \n
* @ref MIC_INHALE_RELEASE \n
* @ref MIC_INHALE \n
* @ref MIC_REFLESH_VALUE \n
* @ref MIC_BLOW_RELEASE \n
* @ref MIC_ALL_OFF	    \n
* @retval  事件中断使能状态
* - 0 未使能
* - 非0 已使能
* @par 说明
* 无
*/
U8 plib_mic_it_ifen(U8 Event)
{
    return (PREG_MIC_CTRL0 & Event);
}


/**
* @brief  MIC总中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_mic_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EX0 = 1;
    else
        PBIT_EX0 = 0;
}

/**
* @brief  设置咪头第一阈值
* @param  TrigValue MIC第一阈值，配置范围0~31，吸烟比例为：配置值/1024
* @retval 无
* @par    说明
* -# 该接口仅在MIC使能300ms后，调用生效
*/
void plib_mic_set_trig1(U8 TrigValue)
{
    //配置吸烟第一阈值
    if (TrigValue > 31)
        TrigValue = 31;

    PREG_MIC_TRIG1 = (PREG_MIC_TRIG1 & 0xE0) | TrigValue;
    delay10us(15);
}

/**
* @brief  获取咪头第一阈值
* @param  无
* @retval 当前设置的MIC第一阈值
* @par   说明
* 无
*/
U8 plib_mic_get_trig1(void)
{
    return (PREG_MIC_TRIG1 & 0x1F);
}

/**
* @brief  设置咪头第二阈值
* @param  TrigValue MIC第二阈值，配置范围0~255，吸烟比例为：配置值/1024
* @retval 无
* @par    说明
* -# 该接口仅在MIC使能300ms后，调用生效
*/
void plib_mic_set_trig2(U8 TrigValue)
{
    if (TrigValue > 255)
        TrigValue = 255;
    PREG_MIC_TRIG2 = TrigValue;
    delay10us(15);
}

/**
* @brief  获取咪头第二阈值
* @param  无
* @retval 当前设置的MIC第二阈值
* @par   说明
* 无
*/
U8 plib_mic_get_trig2(void)
{
    return (PREG_MIC_TRIG2);
}

/**
* @brief  获取咪头初值
* @param  无
* @retval 当前咪头的初值
* @par   说明
* 无
*/
U16 plib_mic_get_init_value(void)
{
    return ((PREG_MIC_INI1 << 8) | PREG_MIC_INI0);
}

/**
* @brief  获取咪头实时计数值
* @param  无
* @retval 当前咪头的实时计数值
* @par   说明
* 无
*/
U16 plib_mic_get_cur_value(void)
{
    return ((PREG_MIC_VAL1 << 8) | PREG_MIC_VAL0);
}

/**
* @brief  获取MIC事件状态
* @param  Event MIC事件，选择以下参数： \n
* @ref MIC_ALL_ON \n
* @ref MIC_ABNORMAL \n
* @ref MIC_SAMPLE \n
* @ref MIC_BLOW \n
* @ref MIC_INHALE_TIMEOUT \n
* @ref MIC_INHALE_RELEASE \n
* @ref MIC_INHALE \n
* @ref MIC_REFLESH_VALUE \n
* @ref MIC_BLOW_RELEASE \n
* @ref MIC_ALL_OFF	    \n
* @retval  事件触发状态
* - 0 未触发该事件
* - 非0 已触发该事件
* @par   说明
* 无
*/
U8 plib_mic_get_flg(U8 Event)
{
    return (PREG_MIC_FLAG & Event);
}

/**
* @brief  清除MIC事件状态
* @param  Event MIC事件，选择以下参数： \n
* @ref MIC_ALL_ON \n
* @ref MIC_ABNORMAL \n
* @ref MIC_SAMPLE \n
* @ref MIC_BLOW \n
* @ref MIC_INHALE_TIMEOUT \n
* @ref MIC_INHALE_RELEASE \n
* @ref MIC_INHALE \n
* @ref MIC_REFLESH_VALUE \n
* @ref MIC_BLOW_RELEASE \n
* @ref MIC_ALL_OFF	    \n
* @retval 无
* @par   说明
* 无
*/
void plib_mic_clr_flg(U8 Event)
{
    PREG_MIC_FLAG &= ~Event;
}

/**
* @brief  软件主动更新吸烟初值
* @param  无
* @retval 无
* @par    说明
* -# 该节口可用于任意时刻，主动更新一次咪头吸烟初值
*/
void plib_mic_reflesh_ini_value()
{
	//使能MCU模式
    PREG_MIC_CTRL1 = (PREG_MIC_CTRL1 & 0xFB) | 0x04;
	delay10us(15);
	
	//使能MCU主动更新初值
    PREG_MIC_CTRL1 = (PREG_MIC_CTRL1 & 0xF7) | 0x08;
	delay10us(15);
	
	//关闭MCU模式
    PREG_MIC_CTRL1 = PREG_MIC_CTRL1 & 0xF3;	
	delay10us(15);
}

/**
* @brief  MIC控制模式
* @param  mode MIC控制模式，选择以下参数： \n
* @ref MIC_CTRL_MODE_HW \n
* @ref MIC_CTRL_MODE_SW \n
* @retval 无
* @par    说明
* -# 该节口用于设置MIC控制模式，切换到软件模式后，咪头自动更新初值使能将失效
*/
void plib_mic_ctrl_mode(U8 mode)
{
	if(mode == MIC_CTRL_MODE_SW)
	{
		PREG_MIC_CTRL1 = (PREG_MIC_CTRL1 & 0xFB) | 0x04;
	}
	else
	{
		PREG_MIC_CTRL1 = PREG_MIC_CTRL1 & 0xF3;
	}
	delay10us(15);	
}

