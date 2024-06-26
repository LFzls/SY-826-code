/**
 * @file
 * @brief		GPIO配置
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.2
 * @par 		Copyright(c): All rights reserved.
 * @par 		修改记录
 * @par 		1.admin，2023-08-21，修正plib_gpio_init()接口，GPIOC0/GPIOC1内部弱上/下拉配置相反问题   
 * @par 		2.admin，2023-09-07，增加接口plib_gpio_mode()  
*/
#include "pmcu_x0_gpio.h"

/**
* @brief  GPIO输出使能
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_output_en(U8 Gpiox, U8 Pinx, FUNC_EN_E ifEn)// reentrant
{
    switch (Gpiox) {
        case GPIO_GroupA: {
                if (ifEn == PLIB_ENABLE)
                    PREG_GPIO_CFG3 |= (Pinx << 4);
                else
                    PREG_GPIO_CFG3 &= ~(Pinx << 4);

                break;
            }

        case GPIO_GroupB: {
                if (ifEn == PLIB_ENABLE)
                    PREG_GPIO_CFG3 |= (Pinx << 0);
                else
                    PREG_GPIO_CFG3 &= ~(Pinx << 0);

                break;
            }

        case GPIO_GroupC: {
                if (ifEn == PLIB_ENABLE)
                    PREG_GPIO_CFG5 |= ((Pinx & 0x03) << 0);
                else
                    PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 0);

                break;
            }

        default:
            break;
    }
}

/**
* @brief  GPIO输入使能
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_input_en(U8 Gpiox, U8 Pinx, FUNC_EN_E ifEn)// reentrant
{
    switch (Gpiox) {
        case GPIO_GroupA: {
                if (ifEn == PLIB_ENABLE)
                    PREG_GPIO_CFG4 |= (Pinx << 4);
                else
                    PREG_GPIO_CFG4 &= ~(Pinx << 4);

                break;
            }

        case GPIO_GroupB: {
                if (ifEn == PLIB_ENABLE)
                    PREG_GPIO_CFG4 |= (Pinx << 0);
                else
                    PREG_GPIO_CFG4 &= ~(Pinx << 0);

                break;
            }

        case GPIO_GroupC: {
                if (ifEn == PLIB_ENABLE)
                    PREG_GPIO_CFG6 |= ((Pinx & 0x03) << 0);
                else
                    PREG_GPIO_CFG6 &= ~((Pinx & 0x03) << 0);

                break;
            }

        default:
            break;
    }
}

/**
* @brief  GPIO输出模式配置函数
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  IOMode GPIO输入输出模式，选择： \n
* @ref GPIO_IOMode_FLOATING    \n
* @ref GPIO_IOMode_IN_FLOATING   \n
* @ref GPIO_IOMode_Out_PP    \n
* @ref GPIO_IOMode_Out_OD    \n
* @retval 无
* @par   说明
* 无
* @par 修改记录
* -# admin，2023-09-07，新增
*/
void plib_gpio_mode(U8 Gpiox, U8 Pinx, GPIO_IOMode_E IOMode) 
{
    switch (Gpiox) {
        case GPIO_GroupA: {
                //输入输出配置
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
						PREG_GPIO_CFG3 &= ~(Pinx << 4); 	//关闭输出使能						
                        PREG_GPIO_CFG4 |= (Pinx << 4); 		//高阻输入
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG4 &= ~(Pinx << 4);		//关闭输入使能
                        PREG_GPIO_CFG0 &= ~(Pinx << 4); 	//OD模式
                        PREG_GPIO_CFG3 |= (Pinx << 4); 		//输出使能
                        break;

                    case GPIO_IOMode_Out_PP:
						PREG_GPIO_CFG4 &= ~(Pinx << 4);		//关闭输入使能
                        PREG_GPIO_CFG0 |= (Pinx << 4); 		//PP模式
                        PREG_GPIO_CFG3 |= (Pinx << 4); 		//输出使能
                        break;

                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG4 &= ~(Pinx << 4);		//关闭输入使能
                        PREG_GPIO_CFG3 &= ~(Pinx << 4); 	//关闭输出使能
                        break;

                    default:
                        break;
                }

                break;
            }

        case GPIO_GroupB: {
                //输入输出配置
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
                        PREG_GPIO_CFG3 &= ~(Pinx << 0); 	//关闭输出使能						
                        PREG_GPIO_CFG4 |= (Pinx << 0); 	//高阻输入
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG4 &= ~(Pinx << 0);		//关闭输入使能
                        PREG_GPIO_CFG0 &= ~(Pinx << 0); 	//OD模式
                        PREG_GPIO_CFG3 |= (Pinx << 0); 	//输出使能
                        break;

                    case GPIO_IOMode_Out_PP:
						PREG_GPIO_CFG4 &= ~(Pinx << 0);		//关闭输入使能
                        PREG_GPIO_CFG0 |= (Pinx << 0);	//PP模式
                        PREG_GPIO_CFG3 |= (Pinx << 0); 	//输出使能
                        break;

                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG4 &= ~(Pinx << 0);		//关闭输入使能
                        PREG_GPIO_CFG3 &= ~(Pinx << 0); 	//关闭输出使能
                        break;
						
                    default:
                        break;
                }

                break;
            }

        case GPIO_GroupC: {
                //输入输出配置
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
                        PREG_GPIO_CFG5 &= ~(Pinx & 0x03); 		//关闭输出使能						
                        PREG_GPIO_CFG6 |= (Pinx & 0x03);	 		//高阻输入
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//关闭输入使能
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 6);	//OD模式
                        PREG_GPIO_CFG5 |= (Pinx & 0x03); 			//输出使能
                        break;

                    case GPIO_IOMode_Out_PP:
						PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//关闭输入使能
                        PREG_GPIO_CFG5 |= ((Pinx & 0x03) << 6);	//PP模式
                        PREG_GPIO_CFG5 |= (Pinx & 0x03); 			//输出使能
                        break;
						
                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//关闭输入使能
                        PREG_GPIO_CFG5 &= ~(Pinx & 0x03); 		//关闭输出使能
                        break;
						
                    default:
                        break;
                }

                break;
            }

        default:
            break;
    }
}

/**
* @brief  GPIO初始化函数
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  PinmuxMode GPIO复用模式，选择： \n
* @ref GPIO_PinMux_IO \n
* @ref GPIO_PinMux_PWM0_0 \n
* @ref GPIO_PinMux_PWM0_1 \n
* @ref GPIO_PinMux_PWM0_2 \n
* @ref GPIO_PinMux_PWM1_0 \n
* @ref GPIO_PinMux_PWM1_1 \n
* @ref GPIO_PinMux_PWM1_2 \n
* @ref GPIO_PinMux_ADC    \n
* @ref GPIO_PinMux_UART   \n
* @ref GPIO_PinMux_LED    \n
* @param  IOMode GPIO输入输出模式，选择： \n
* @ref GPIO_IOMode_FLOATING    \n
* @ref GPIO_IOMode_IN_FLOATING   \n
* @ref GPIO_IOMode_Out_PP    \n
* @ref GPIO_IOMode_Out_OD    \n
* @param  PUPDMode GPIO内部上下拉模式，选择： \n
* @ref GPIO_PUPDMode_None \n
* @ref GPIO_PUPDMode_PD \n
* @ref GPIO_PUPDMode_PU \n
* @param  PPDriver PP输出时，GPIO驱动能力，选择： \n
* @ref GPIO_Driver_Weak \n
* @ref GPIO_Driver_Strength \n
* @retval 无
* @par   说明
* 无
* @par 修改记录
* -# admin，2023-08-21，修正GPIOC0/GPIOC1内部弱上/下拉配置相反问题
*/
void plib_gpio_init(U8 Gpiox, U8 Pinx, GPIO_PINMUX_E PinmuxMode, GPIO_IOMode_E IOMode, GPIO_PDPUMode_E PUPDMode, GPIO_DRIVER_E PPDriver) 
{
    //若GPIOA1/GPIOA2/GPIOA3复用为LED，自动适配对应配置
    if ((Gpiox == GPIO_GroupA) && (PinmuxMode == GPIO_PinMux_LED)) {
        if (Pinx & GPIO_Pin_1)
            PinmuxMode = GPIO_PinMux_PWM0_0;

        if (Pinx & GPIO_Pin_2)
            PinmuxMode = GPIO_PinMux_PWM0_1;

        if (Pinx & GPIO_Pin_3)
            PinmuxMode = GPIO_PinMux_PWM0_2;

        PUPDMode = GPIO_PUPDMode_None;
        IOMode = GPIO_IOMode_FLOATING;
    }

    switch (Gpiox) {
        case GPIO_GroupA: {
                //复用模式配置
                if (Pinx & GPIO_Pin_0)
                    PREG_GPIO_PINMUX0 = (PREG_GPIO_PINMUX0 & 0x0F) | (PinmuxMode << 4);

                if (Pinx & GPIO_Pin_1)
                    PREG_GPIO_PINMUX0 = (PREG_GPIO_PINMUX0 & 0xF0) | (PinmuxMode << 0);

                if (Pinx & GPIO_Pin_2)
                    PREG_GPIO_PINMUX1 = (PREG_GPIO_PINMUX1 & 0x0F) | (PinmuxMode << 4);

                if (Pinx & GPIO_Pin_3)
                    PREG_GPIO_PINMUX1 = (PREG_GPIO_PINMUX1 & 0xF0) | (PinmuxMode << 0);

                //内部上下拉配置
                switch (PUPDMode) {
                    case GPIO_PUPDMode_None:
                        PREG_GPIO_CFG1 &= ~(Pinx << 4);		//关闭上拉
                        PREG_GPIO_CFG2 &= ~(Pinx << 4); 	//关闭下拉
                        break;

                    case GPIO_PUPDMode_PD:
                        PREG_GPIO_CFG1 &= ~(Pinx << 4);		//关闭上拉
                        PREG_GPIO_CFG2 |= (Pinx << 4); 		//开启下拉
                        break;

                    case GPIO_PUPDMode_PU:
                        PREG_GPIO_CFG2 &= ~(Pinx << 4); 	//关闭下拉
                        PREG_GPIO_CFG1 |= (Pinx << 4); 		//开启上拉
                        break;

                    default:
                        break;
                }

                //输入输出配置
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
						PREG_GPIO_CFG3 &= ~(Pinx << 4); 	//关闭输出使能						
                        PREG_GPIO_CFG4 |= (Pinx << 4); 		//高阻输入
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG4 &= ~(Pinx << 4);		//关闭输入使能
                        PREG_GPIO_CFG0 &= ~(Pinx << 4); 	//OD模式
                        PREG_GPIO_CFG3 |= (Pinx << 4); 		//输出使能
                        break;

                    case GPIO_IOMode_Out_PP:						
						PREG_GPIO_CFG4 &= ~(Pinx << 4);		//关闭输入使能
                        PREG_GPIO_CFG0 |= (Pinx << 4); 		//PP模式
                        PREG_GPIO_CFG3 |= (Pinx << 4); 		//输出使能
                        break;

                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG4 &= ~(Pinx << 4);		//关闭输入使能
                        PREG_GPIO_CFG3 &= ~(Pinx << 4); 	//关闭输出使能
                        break;

                    default:
                        break;
                }

				//驱动能力配置
				if (GPIO_Driver_Strength == PPDriver)
					PREG_GPIO_DRV1 |= Pinx;
				else
					PREG_GPIO_DRV1 &= ~Pinx;
						
                break;
            }

        case GPIO_GroupB: {
                //复用模式配置
                if (Pinx & GPIO_Pin_0)
                    PREG_GPIO_PINMUX2 = (PREG_GPIO_PINMUX2 & 0x0F) | (PinmuxMode << 4);

                if (Pinx & GPIO_Pin_1)
                    PREG_GPIO_PINMUX2 = (PREG_GPIO_PINMUX2 & 0xF0) | (PinmuxMode << 0);

                if (Pinx & GPIO_Pin_2)
                    PREG_GPIO_PINMUX3 = (PREG_GPIO_PINMUX3 & 0x0F) | (PinmuxMode << 4);

                if (Pinx & GPIO_Pin_3)
                    PREG_GPIO_PINMUX3 = (PREG_GPIO_PINMUX3 & 0xF0) | (PinmuxMode << 0);

                //内部上下拉配置
                switch (PUPDMode) {
                    case GPIO_PUPDMode_None:
                        PREG_GPIO_CFG1 &= ~(Pinx << 0);	//关闭上拉
                        PREG_GPIO_CFG2 &= ~(Pinx << 0); 	//关闭下拉
                        break;

                    case GPIO_PUPDMode_PD:
                        PREG_GPIO_CFG1 &= ~(Pinx << 0);	//关闭上拉
                        PREG_GPIO_CFG2 |= (Pinx << 0); 	//开启下拉
                        break;

                    case GPIO_PUPDMode_PU:
                        PREG_GPIO_CFG2 &= ~(Pinx << 0); 	//关闭下拉
                        PREG_GPIO_CFG1 |= (Pinx << 0); 	//开启上拉
                        break;

                    default:
                        break;
                }

                //输入输出配置
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
                        PREG_GPIO_CFG3 &= ~(Pinx << 0); 	//关闭输出使能						
                        PREG_GPIO_CFG4 |= (Pinx << 0); 	//高阻输入
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG4 &= ~(Pinx << 0);		//关闭输入使能
                        PREG_GPIO_CFG0 &= ~(Pinx << 0); 	//OD模式
                        PREG_GPIO_CFG3 |= (Pinx << 0); 	//输出使能
                        break;

                    case GPIO_IOMode_Out_PP:
						PREG_GPIO_CFG4 &= ~(Pinx << 0);		//关闭输入使能
                        PREG_GPIO_CFG0 |= (Pinx << 0);	//PP模式
                        PREG_GPIO_CFG3 |= (Pinx << 0); 	//输出使能
                        break;

                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG4 &= ~(Pinx << 0);		//关闭输入使能
                        PREG_GPIO_CFG3 &= ~(Pinx << 0); 	//关闭输出使能
                        break;
						
                    default:
                        break;
                }

				//驱动能力配置
				if (GPIO_Driver_Strength == PPDriver)
					PREG_GPIO_DRV2 |= Pinx;
				else
					PREG_GPIO_DRV2 &= ~Pinx;
				
                break;
            }

        case GPIO_GroupC: {
                //复用模式配置
                if (Pinx & GPIO_Pin_0)
                    PREG_GPIO_PINMUX4 = (PREG_GPIO_PINMUX4 & 0x0F) | (PinmuxMode << 4);

                if (Pinx & GPIO_Pin_1)
                    PREG_GPIO_PINMUX4 = (PREG_GPIO_PINMUX4 & 0xF0) | (PinmuxMode << 0);

                //内部上下拉配置
                switch (PUPDMode) {
                    case GPIO_PUPDMode_None:
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 4); 	//关闭上拉
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 2); 	//关闭下拉
                        break;

                    case GPIO_PUPDMode_PD:
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 4); 	//关闭上拉
                        PREG_GPIO_CFG5 |= ((Pinx & 0x03) << 2); 	//开启下拉
                        break;

                    case GPIO_PUPDMode_PU:
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 2); 	//关闭下拉
                        PREG_GPIO_CFG5 |= ((Pinx & 0x03) << 4); 	//开启上拉
                        break;

                    default:
                        break;
                }

                //输入输出配置
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
                        PREG_GPIO_CFG5 &= ~(Pinx & 0x03); 		//关闭输出使能						
                        PREG_GPIO_CFG6 |= (Pinx & 0x03);	 		//高阻输入
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//关闭输入使能
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 6);	//OD模式
                        PREG_GPIO_CFG5 |= (Pinx & 0x03); 			//输出使能
                        break;

                    case GPIO_IOMode_Out_PP:
						PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//关闭输入使能
                        PREG_GPIO_CFG5 |= ((Pinx & 0x03) << 6);	//PP模式
                        PREG_GPIO_CFG5 |= (Pinx & 0x03); 			//输出使能
                        break;
						
                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//关闭输入使能
                        PREG_GPIO_CFG5 &= ~(Pinx & 0x03); 		//关闭输出使能
                        break;
						
                    default:
                        break;
                }

				//驱动能力配置
				if (GPIO_Driver_Strength == PPDriver)
					PREG_GPIO_DRV3 |= (Pinx  & 0x03);
				else
					PREG_GPIO_DRV3 &= ~(Pinx  & 0x03);
						
                break;
            }

        default:
            break;
    }
}

/**
* @brief  GPIO输出高电平
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  level 输出电平 \n
* @ref PLIB_HIGH 高电平 \n
* @ref PLIB_LOW 低电平 \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_set_value(U8 GPIOx, U8 Pinx, IO_LEVEL_E level)// reentrant
{
    switch (GPIOx) {
        case GPIO_GroupA: {
                if (PLIB_HIGH == level)
                    PREG_P0 |= Pinx;
                else
                    PREG_P0 &= ~Pinx;

                break;
            }

        case GPIO_GroupB: {
                if (PLIB_HIGH == level)
                    PREG_P1 |= Pinx;
                else
                    PREG_P1 &= ~Pinx;

                break;
            }

        case GPIO_GroupC: {
                if (PLIB_HIGH == level)
                    PREG_P2 |= Pinx;
                else
                    PREG_P2 &= ~Pinx;

                break;
            }

        default:
            break;
    }
}

/**
  * @brief  GPIO获取输入电平
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @retval  事件触发状态
* - PLIB_LOW 低电平
* - PLIB_HIGH 高电平
* @par   说明
* 无
*/
U8 plib_gpio_get_value(U8 GPIOx, U8 Pinx)// reentrant
{
    U8 level;

    switch (GPIOx) {
        case GPIO_GroupA: {
                if (Pinx == GPIO_Pin_All) {
                    level = PREG_P0 & 0x0F;
                    break;
                }

                if ((PREG_P0 & Pinx) != (U8)PLIB_LOW)
                    level = (U8)PLIB_HIGH;
                else
                    level = (U8)PLIB_LOW;

                break;
            }

        case GPIO_GroupB: {
                if (Pinx == GPIO_Pin_All) {
                    level = PREG_P1 & 0x0F;
                    break;
                }

                if ((PREG_P1 & Pinx) != (U8)PLIB_LOW)
                    level = (U8)PLIB_HIGH;
                else
                    level = (U8)PLIB_LOW;

                break;
            }

        case GPIO_GroupC: {
                if (Pinx == GPIO_Pin_All) {
                    level = PREG_P2 & 0x03;
                    break;
                }

                if ((PREG_P2 & Pinx) != (U8)PLIB_LOW)
                    level = (U8)PLIB_HIGH;
                else
                    level = (U8)PLIB_LOW;

                break;
            }

        default:
            break;
    }

    return level;
}

/**
* @brief  GPIO 输入中断
* @param  Gpiox GPIO组号，选择： \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO引脚号，选择： \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par    说明
* -# 若使能睡眠唤醒的GPIO事件唤醒，该中断使能配置，同时作为睡眠唤醒事件
*/
void plib_gpio_it_cfg(U8 Gpiox, U8 Pinx, FUNC_EN_E ifEn)
{
    switch (Gpiox) {
        case GPIO_GroupA: {
                if (ifEn == PLIB_ENABLE)
                    PREG_AFIO_IE0 |= (Pinx << 4);
                else
                    PREG_AFIO_IE0 &= ~(Pinx << 4);

                break;
            }

        case GPIO_GroupB: {
                if (ifEn == PLIB_ENABLE)
                    PREG_AFIO_IE0 |= (Pinx << 0);
                else
                    PREG_AFIO_IE0 &= ~(Pinx << 0);

                break;
            }

        case GPIO_GroupC: {
                if (ifEn == PLIB_ENABLE)
                    PREG_AFIO_IE1 |= ((Pinx & 0x03) << 0);
                else
                    PREG_AFIO_IE1 &= ~((Pinx & 0x03) << 0);

                break;
            }

        default:
            break;
    }
}

/**
* @brief  GPIO 总中断使能
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EX2 = 1;
    else
        PBIT_EX2 = 0;
}

/**
* @brief  GPIOA1/GPIOA2/GPIOA3 用作LED时的，驱动电流配置
* @param  LEDCurr LED驱动电流档位，选择： \n
* @ref GPIO_LED_4MA \n
* @ref GPIO_LED_8MA \n
* @ref GPIO_LED_21MA \n
* @ref GPIO_LED_29MA \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_set_led_curr(U8 LEDCurr)
{
    PREG_LED_CTRL = (PREG_LED_CTRL & 0xE7) | LEDCurr;
}

/**
* @brief  LED输出使能
* @param  LED_Numbe LED号 \n
* @ref GPIO_LED_0 \n
* @ref GPIO_LED_1 \n
* @ref GPIO_LED_2 \n
* @ref GPIO_LED_All \n
* @param  ifEn 是否使能 \n
* @ref PLIB_ENABLE 使能 \n
* @ref PLIB_DISABLE 不使能 \n
* @retval 无
* @par   说明
* 无
*/
void plib_gpio_led_output_en(U8 LED_Number, FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_LED_CTRL |= LED_Number;
    else
        PREG_LED_CTRL &= ~LED_Number;
}
