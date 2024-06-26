/**
 * @file
 * @brief		GPIO����
 * @author		admin
 * @date		2023.07.27
 * @version	    v1.2
 * @par 		Copyright(c): All rights reserved.
 * @par 		�޸ļ�¼
 * @par 		1.admin��2023-08-21������plib_gpio_init()�ӿڣ�GPIOC0/GPIOC1�ڲ�����/���������෴����   
 * @par 		2.admin��2023-09-07�����ӽӿ�plib_gpio_mode()  
*/
#include "pmcu_x0_gpio.h"

/**
* @brief  GPIO���ʹ��
* @param  Gpiox GPIO��ţ�ѡ�� \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO���źţ�ѡ�� \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
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
* @brief  GPIO����ʹ��
* @param  Gpiox GPIO��ţ�ѡ�� \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO���źţ�ѡ�� \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
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
* @brief  GPIO���ģʽ���ú���
* @param  Gpiox GPIO��ţ�ѡ�� \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO���źţ�ѡ�� \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  IOMode GPIO�������ģʽ��ѡ�� \n
* @ref GPIO_IOMode_FLOATING    \n
* @ref GPIO_IOMode_IN_FLOATING   \n
* @ref GPIO_IOMode_Out_PP    \n
* @ref GPIO_IOMode_Out_OD    \n
* @retval ��
* @par   ˵��
* ��
* @par �޸ļ�¼
* -# admin��2023-09-07������
*/
void plib_gpio_mode(U8 Gpiox, U8 Pinx, GPIO_IOMode_E IOMode) 
{
    switch (Gpiox) {
        case GPIO_GroupA: {
                //�����������
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
						PREG_GPIO_CFG3 &= ~(Pinx << 4); 	//�ر����ʹ��						
                        PREG_GPIO_CFG4 |= (Pinx << 4); 		//��������
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG4 &= ~(Pinx << 4);		//�ر�����ʹ��
                        PREG_GPIO_CFG0 &= ~(Pinx << 4); 	//ODģʽ
                        PREG_GPIO_CFG3 |= (Pinx << 4); 		//���ʹ��
                        break;

                    case GPIO_IOMode_Out_PP:
						PREG_GPIO_CFG4 &= ~(Pinx << 4);		//�ر�����ʹ��
                        PREG_GPIO_CFG0 |= (Pinx << 4); 		//PPģʽ
                        PREG_GPIO_CFG3 |= (Pinx << 4); 		//���ʹ��
                        break;

                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG4 &= ~(Pinx << 4);		//�ر�����ʹ��
                        PREG_GPIO_CFG3 &= ~(Pinx << 4); 	//�ر����ʹ��
                        break;

                    default:
                        break;
                }

                break;
            }

        case GPIO_GroupB: {
                //�����������
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
                        PREG_GPIO_CFG3 &= ~(Pinx << 0); 	//�ر����ʹ��						
                        PREG_GPIO_CFG4 |= (Pinx << 0); 	//��������
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG4 &= ~(Pinx << 0);		//�ر�����ʹ��
                        PREG_GPIO_CFG0 &= ~(Pinx << 0); 	//ODģʽ
                        PREG_GPIO_CFG3 |= (Pinx << 0); 	//���ʹ��
                        break;

                    case GPIO_IOMode_Out_PP:
						PREG_GPIO_CFG4 &= ~(Pinx << 0);		//�ر�����ʹ��
                        PREG_GPIO_CFG0 |= (Pinx << 0);	//PPģʽ
                        PREG_GPIO_CFG3 |= (Pinx << 0); 	//���ʹ��
                        break;

                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG4 &= ~(Pinx << 0);		//�ر�����ʹ��
                        PREG_GPIO_CFG3 &= ~(Pinx << 0); 	//�ر����ʹ��
                        break;
						
                    default:
                        break;
                }

                break;
            }

        case GPIO_GroupC: {
                //�����������
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
                        PREG_GPIO_CFG5 &= ~(Pinx & 0x03); 		//�ر����ʹ��						
                        PREG_GPIO_CFG6 |= (Pinx & 0x03);	 		//��������
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//�ر�����ʹ��
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 6);	//ODģʽ
                        PREG_GPIO_CFG5 |= (Pinx & 0x03); 			//���ʹ��
                        break;

                    case GPIO_IOMode_Out_PP:
						PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//�ر�����ʹ��
                        PREG_GPIO_CFG5 |= ((Pinx & 0x03) << 6);	//PPģʽ
                        PREG_GPIO_CFG5 |= (Pinx & 0x03); 			//���ʹ��
                        break;
						
                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//�ر�����ʹ��
                        PREG_GPIO_CFG5 &= ~(Pinx & 0x03); 		//�ر����ʹ��
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
* @brief  GPIO��ʼ������
* @param  Gpiox GPIO��ţ�ѡ�� \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO���źţ�ѡ�� \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  PinmuxMode GPIO����ģʽ��ѡ�� \n
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
* @param  IOMode GPIO�������ģʽ��ѡ�� \n
* @ref GPIO_IOMode_FLOATING    \n
* @ref GPIO_IOMode_IN_FLOATING   \n
* @ref GPIO_IOMode_Out_PP    \n
* @ref GPIO_IOMode_Out_OD    \n
* @param  PUPDMode GPIO�ڲ�������ģʽ��ѡ�� \n
* @ref GPIO_PUPDMode_None \n
* @ref GPIO_PUPDMode_PD \n
* @ref GPIO_PUPDMode_PU \n
* @param  PPDriver PP���ʱ��GPIO����������ѡ�� \n
* @ref GPIO_Driver_Weak \n
* @ref GPIO_Driver_Strength \n
* @retval ��
* @par   ˵��
* ��
* @par �޸ļ�¼
* -# admin��2023-08-21������GPIOC0/GPIOC1�ڲ�����/���������෴����
*/
void plib_gpio_init(U8 Gpiox, U8 Pinx, GPIO_PINMUX_E PinmuxMode, GPIO_IOMode_E IOMode, GPIO_PDPUMode_E PUPDMode, GPIO_DRIVER_E PPDriver) 
{
    //��GPIOA1/GPIOA2/GPIOA3����ΪLED���Զ������Ӧ����
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
                //����ģʽ����
                if (Pinx & GPIO_Pin_0)
                    PREG_GPIO_PINMUX0 = (PREG_GPIO_PINMUX0 & 0x0F) | (PinmuxMode << 4);

                if (Pinx & GPIO_Pin_1)
                    PREG_GPIO_PINMUX0 = (PREG_GPIO_PINMUX0 & 0xF0) | (PinmuxMode << 0);

                if (Pinx & GPIO_Pin_2)
                    PREG_GPIO_PINMUX1 = (PREG_GPIO_PINMUX1 & 0x0F) | (PinmuxMode << 4);

                if (Pinx & GPIO_Pin_3)
                    PREG_GPIO_PINMUX1 = (PREG_GPIO_PINMUX1 & 0xF0) | (PinmuxMode << 0);

                //�ڲ�����������
                switch (PUPDMode) {
                    case GPIO_PUPDMode_None:
                        PREG_GPIO_CFG1 &= ~(Pinx << 4);		//�ر�����
                        PREG_GPIO_CFG2 &= ~(Pinx << 4); 	//�ر�����
                        break;

                    case GPIO_PUPDMode_PD:
                        PREG_GPIO_CFG1 &= ~(Pinx << 4);		//�ر�����
                        PREG_GPIO_CFG2 |= (Pinx << 4); 		//��������
                        break;

                    case GPIO_PUPDMode_PU:
                        PREG_GPIO_CFG2 &= ~(Pinx << 4); 	//�ر�����
                        PREG_GPIO_CFG1 |= (Pinx << 4); 		//��������
                        break;

                    default:
                        break;
                }

                //�����������
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
						PREG_GPIO_CFG3 &= ~(Pinx << 4); 	//�ر����ʹ��						
                        PREG_GPIO_CFG4 |= (Pinx << 4); 		//��������
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG4 &= ~(Pinx << 4);		//�ر�����ʹ��
                        PREG_GPIO_CFG0 &= ~(Pinx << 4); 	//ODģʽ
                        PREG_GPIO_CFG3 |= (Pinx << 4); 		//���ʹ��
                        break;

                    case GPIO_IOMode_Out_PP:						
						PREG_GPIO_CFG4 &= ~(Pinx << 4);		//�ر�����ʹ��
                        PREG_GPIO_CFG0 |= (Pinx << 4); 		//PPģʽ
                        PREG_GPIO_CFG3 |= (Pinx << 4); 		//���ʹ��
                        break;

                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG4 &= ~(Pinx << 4);		//�ر�����ʹ��
                        PREG_GPIO_CFG3 &= ~(Pinx << 4); 	//�ر����ʹ��
                        break;

                    default:
                        break;
                }

				//������������
				if (GPIO_Driver_Strength == PPDriver)
					PREG_GPIO_DRV1 |= Pinx;
				else
					PREG_GPIO_DRV1 &= ~Pinx;
						
                break;
            }

        case GPIO_GroupB: {
                //����ģʽ����
                if (Pinx & GPIO_Pin_0)
                    PREG_GPIO_PINMUX2 = (PREG_GPIO_PINMUX2 & 0x0F) | (PinmuxMode << 4);

                if (Pinx & GPIO_Pin_1)
                    PREG_GPIO_PINMUX2 = (PREG_GPIO_PINMUX2 & 0xF0) | (PinmuxMode << 0);

                if (Pinx & GPIO_Pin_2)
                    PREG_GPIO_PINMUX3 = (PREG_GPIO_PINMUX3 & 0x0F) | (PinmuxMode << 4);

                if (Pinx & GPIO_Pin_3)
                    PREG_GPIO_PINMUX3 = (PREG_GPIO_PINMUX3 & 0xF0) | (PinmuxMode << 0);

                //�ڲ�����������
                switch (PUPDMode) {
                    case GPIO_PUPDMode_None:
                        PREG_GPIO_CFG1 &= ~(Pinx << 0);	//�ر�����
                        PREG_GPIO_CFG2 &= ~(Pinx << 0); 	//�ر�����
                        break;

                    case GPIO_PUPDMode_PD:
                        PREG_GPIO_CFG1 &= ~(Pinx << 0);	//�ر�����
                        PREG_GPIO_CFG2 |= (Pinx << 0); 	//��������
                        break;

                    case GPIO_PUPDMode_PU:
                        PREG_GPIO_CFG2 &= ~(Pinx << 0); 	//�ر�����
                        PREG_GPIO_CFG1 |= (Pinx << 0); 	//��������
                        break;

                    default:
                        break;
                }

                //�����������
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
                        PREG_GPIO_CFG3 &= ~(Pinx << 0); 	//�ر����ʹ��						
                        PREG_GPIO_CFG4 |= (Pinx << 0); 	//��������
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG4 &= ~(Pinx << 0);		//�ر�����ʹ��
                        PREG_GPIO_CFG0 &= ~(Pinx << 0); 	//ODģʽ
                        PREG_GPIO_CFG3 |= (Pinx << 0); 	//���ʹ��
                        break;

                    case GPIO_IOMode_Out_PP:
						PREG_GPIO_CFG4 &= ~(Pinx << 0);		//�ر�����ʹ��
                        PREG_GPIO_CFG0 |= (Pinx << 0);	//PPģʽ
                        PREG_GPIO_CFG3 |= (Pinx << 0); 	//���ʹ��
                        break;

                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG4 &= ~(Pinx << 0);		//�ر�����ʹ��
                        PREG_GPIO_CFG3 &= ~(Pinx << 0); 	//�ر����ʹ��
                        break;
						
                    default:
                        break;
                }

				//������������
				if (GPIO_Driver_Strength == PPDriver)
					PREG_GPIO_DRV2 |= Pinx;
				else
					PREG_GPIO_DRV2 &= ~Pinx;
				
                break;
            }

        case GPIO_GroupC: {
                //����ģʽ����
                if (Pinx & GPIO_Pin_0)
                    PREG_GPIO_PINMUX4 = (PREG_GPIO_PINMUX4 & 0x0F) | (PinmuxMode << 4);

                if (Pinx & GPIO_Pin_1)
                    PREG_GPIO_PINMUX4 = (PREG_GPIO_PINMUX4 & 0xF0) | (PinmuxMode << 0);

                //�ڲ�����������
                switch (PUPDMode) {
                    case GPIO_PUPDMode_None:
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 4); 	//�ر�����
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 2); 	//�ر�����
                        break;

                    case GPIO_PUPDMode_PD:
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 4); 	//�ر�����
                        PREG_GPIO_CFG5 |= ((Pinx & 0x03) << 2); 	//��������
                        break;

                    case GPIO_PUPDMode_PU:
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 2); 	//�ر�����
                        PREG_GPIO_CFG5 |= ((Pinx & 0x03) << 4); 	//��������
                        break;

                    default:
                        break;
                }

                //�����������
                switch (IOMode) {
                    case GPIO_IOMode_IN_FLOATING:
                        PREG_GPIO_CFG5 &= ~(Pinx & 0x03); 		//�ر����ʹ��						
                        PREG_GPIO_CFG6 |= (Pinx & 0x03);	 		//��������
                        break;

                    case GPIO_IOMode_Out_OD:
						PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//�ر�����ʹ��
                        PREG_GPIO_CFG5 &= ~((Pinx & 0x03) << 6);	//ODģʽ
                        PREG_GPIO_CFG5 |= (Pinx & 0x03); 			//���ʹ��
                        break;

                    case GPIO_IOMode_Out_PP:
						PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//�ر�����ʹ��
                        PREG_GPIO_CFG5 |= ((Pinx & 0x03) << 6);	//PPģʽ
                        PREG_GPIO_CFG5 |= (Pinx & 0x03); 			//���ʹ��
                        break;
						
                    case GPIO_IOMode_FLOATING:
                        PREG_GPIO_CFG6 &= ~(Pinx & 0x03);		//�ر�����ʹ��
                        PREG_GPIO_CFG5 &= ~(Pinx & 0x03); 		//�ر����ʹ��
                        break;
						
                    default:
                        break;
                }

				//������������
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
* @brief  GPIO����ߵ�ƽ
* @param  Gpiox GPIO��ţ�ѡ�� \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO���źţ�ѡ�� \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  level �����ƽ \n
* @ref PLIB_HIGH �ߵ�ƽ \n
* @ref PLIB_LOW �͵�ƽ \n
* @retval ��
* @par   ˵��
* ��
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
  * @brief  GPIO��ȡ�����ƽ
* @param  Gpiox GPIO��ţ�ѡ�� \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO���źţ�ѡ�� \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @retval  �¼�����״̬
* - PLIB_LOW �͵�ƽ
* - PLIB_HIGH �ߵ�ƽ
* @par   ˵��
* ��
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
* @brief  GPIO �����ж�
* @param  Gpiox GPIO��ţ�ѡ�� \n
* @ref GPIO_GroupA \n
* @ref GPIO_GroupB \n
* @ref GPIO_GroupC \n
* @param  Pinx GPIO���źţ�ѡ�� \n
* @ref GPIO_Pin_0 \n
* @ref GPIO_Pin_1 \n
* @ref GPIO_Pin_2 \n
* @ref GPIO_Pin_3 \n
* @ref GPIO_Pin_All \n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par    ˵��
* -# ��ʹ��˯�߻��ѵ�GPIO�¼����ѣ����ж�ʹ�����ã�ͬʱ��Ϊ˯�߻����¼�
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
* @brief  GPIO ���ж�ʹ��
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_gpio_it_en(FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PBIT_EX2 = 1;
    else
        PBIT_EX2 = 0;
}

/**
* @brief  GPIOA1/GPIOA2/GPIOA3 ����LEDʱ�ģ�������������
* @param  LEDCurr LED����������λ��ѡ�� \n
* @ref GPIO_LED_4MA \n
* @ref GPIO_LED_8MA \n
* @ref GPIO_LED_21MA \n
* @ref GPIO_LED_29MA \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_gpio_set_led_curr(U8 LEDCurr)
{
    PREG_LED_CTRL = (PREG_LED_CTRL & 0xE7) | LEDCurr;
}

/**
* @brief  LED���ʹ��
* @param  LED_Numbe LED�� \n
* @ref GPIO_LED_0 \n
* @ref GPIO_LED_1 \n
* @ref GPIO_LED_2 \n
* @ref GPIO_LED_All \n
* @param  ifEn �Ƿ�ʹ�� \n
* @ref PLIB_ENABLE ʹ�� \n
* @ref PLIB_DISABLE ��ʹ�� \n
* @retval ��
* @par   ˵��
* ��
*/
void plib_gpio_led_output_en(U8 LED_Number, FUNC_EN_E ifEn)
{
    if (ifEn == PLIB_ENABLE)
        PREG_LED_CTRL |= LED_Number;
    else
        PREG_LED_CTRL &= ~LED_Number;
}
