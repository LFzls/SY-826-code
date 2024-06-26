/**
 * @file
 * @brief       GPIO middleware interface functions
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/


#define __BSP_GPIO_C__

#include "bsp_gpio.h"

void pmcu_gpio_init(void)
{
    U8 Led_Mask;

    /********************¿ª¹ØMIC***************************/
#if CFG_MIC_TYPE == 2
    plib_gpio_init(CFG_PIN_MIC_PORT, CFG_PIN_MIC_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_IN_FLOATING, GPIO_PUPDMode_PD, GPIO_Driver_Weak);
    plib_gpio_it_cfg(CFG_PIN_MIC_PORT, CFG_PIN_MIC_PINNUM, PLIB_ENABLE);
#endif /* end of #if CFG_KEY_EN */

    /********************KEY***************************/
#if CFG_KEY_EN
#if CFG_PIN_KEY_VALUE_TYPE==0
    plib_gpio_init(CFG_PIN_KEY_PORT, CFG_PIN_KEY_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_IN_FLOATING, GPIO_PUPDMode_PU, GPIO_Driver_Weak);
#elif   CFG_PIN_KEY_VALUE_TYPE==1
    plib_gpio_init(CFG_PIN_KEY_PORT, CFG_PIN_KEY_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_IN_FLOATING, GPIO_PUPDMode_PD, GPIO_Driver_Weak);
#endif /* end of CFG_PIN_KEY_VALUE_TYPE==0 */

#if CFG_PIN_IT_EN
    plib_gpio_it_cfg(CFG_PIN_KEY_PORT, CFG_PIN_KEY_PINNUM, PLIB_ENABLE);
#endif /* end of #if CFG_PIN_IT_EN */
#endif /* end of #if CFG_KEY_EN */

    /********************EXTMOS***************************/
#if CFG_VOUT_CNH_MAX == 2 || CFG_VOUT_CNH_MAX == 3
    //EXTMOS output en
    plib_gpio_init(CFG_PIN_EXTMOS_VOUT_PORT, CFG_PIN_EXTMOS_VOUT_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_Out_PP, GPIO_PUPDMode_None, GPIO_Driver_Strength);
    plib_gpio_set_value(CFG_PIN_EXTMOS_VOUT_PORT, CFG_PIN_EXTMOS_VOUT_PINNUM, PLIB_HIGH);

#if CFG_PIN_EXTMOS_RL_DET_GPIO
    //EXTMOS rload detect en
    plib_gpio_init(CFG_PIN_EXTMOS_RL_PORT, CFG_PIN_EXTMOS_RL_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_Out_PP, GPIO_PUPDMode_None, GPIO_Driver_Strength);
    plib_gpio_set_value(CFG_PIN_EXTMOS_RL_PORT, CFG_PIN_EXTMOS_RL_PINNUM, PLIB_HIGH);
#endif /* end of #if CFG_PIN_EXTMOS_RL_DET_GPIO */

    //EXTMOS ADC
    plib_gpio_init(CFG_PIN_EXTMOS_ADC_PORT, CFG_PIN_EXTMOS_ADC_PINNUM, GPIO_PinMux_ADC, GPIO_IOMode_IN_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Weak);
#endif /* end of #if CFG_VOUT_CNH_MAX==2 */

    /********************LED***************************/
#if CFG_UI_LED_EN

#if CFG_UI_LED0_EN
    Led_Mask |= GPIO_LED_0;
    plib_gpio_init(CFG_PIN_LED0_PORT, CFG_PIN_LED0_PINNUM, GPIO_PinMux_LED, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Weak);
#endif /* end of #if CFG_UI_LED0_EN */

#if CFG_UI_LED1_EN
    Led_Mask |= GPIO_LED_1;
    plib_gpio_init(CFG_PIN_LED1_PORT, CFG_PIN_LED1_PINNUM, GPIO_PinMux_LED, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Weak);
#endif /* end of #if CFG_UI_LED1_EN */

#if CFG_UI_LED2_EN
    Led_Mask |= GPIO_LED_2;
    plib_gpio_init(CFG_PIN_LED2_PORT, CFG_PIN_LED2_PINNUM, GPIO_PinMux_LED, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Weak);
#endif /* end of #if CFG_UI_LED2_EN */

    //LED driver current
    plib_gpio_set_led_curr(CFG_UI_LED_CURR);
    //Enable LED driver output
    plib_gpio_led_output_en(Led_Mask, PLIB_ENABLE);

#if CFG_UI_LED3_EN
    plib_gpio_init(CFG_PIN_LED3_PORT, CFG_PIN_LED3_PINNUM, GPIO_PinMux_PWM1_0, GPIO_IOMode_Out_PP, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_LED4_EN */

#if CFG_UI_LED4_EN
    plib_gpio_init(CFG_PIN_LED4_PORT, CFG_PIN_LED4_PINNUM, GPIO_PinMux_PWM1_1, GPIO_IOMode_Out_PP, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_LED4_EN */

#if CFG_UI_LED5_EN
    plib_gpio_init(CFG_PIN_LED5_PORT, CFG_PIN_LED5_PINNUM, GPIO_PinMux_PWM1_2, GPIO_IOMode_Out_PP, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_LED4_EN */

#endif /* end of #if CFG_UI_LED_EN */

    /********************SCREEN***************************/
#if CFG_UI_SCREEN_EN

#if CFG_UI_COM1_EN
    plib_gpio_init(CFG_PIN_COM1_PORT, CFG_PIN_COM1_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_COM1_EN */
#if CFG_UI_COM2_EN
    plib_gpio_init(CFG_PIN_COM2_PORT, CFG_PIN_COM2_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_COM2_EN */
#if CFG_UI_COM3_EN
    plib_gpio_init(CFG_PIN_COM3_PORT, CFG_PIN_COM3_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_COM3_EN */
#if CFG_UI_COM4_EN
    plib_gpio_init(CFG_PIN_COM4_PORT, CFG_PIN_COM4_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_COM4_EN */
#if CFG_UI_COM5_EN
    plib_gpio_init(CFG_PIN_COM5_PORT, CFG_PIN_COM5_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_COM5_EN */
#if CFG_UI_COM6_EN
    plib_gpio_init(CFG_PIN_COM6_PORT, CFG_PIN_COM6_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_COM6_EN */
#if CFG_UI_COM7_EN
    plib_gpio_init(CFG_PIN_COM7_PORT, CFG_PIN_COM7_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_COM7_EN */
#if CFG_UI_COM8_EN
    plib_gpio_init(CFG_PIN_COM8_PORT, CFG_PIN_COM8_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_COM8_EN */
#if CFG_UI_COM9_EN
    plib_gpio_init(CFG_PIN_COM9_PORT, CFG_PIN_COM9_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_COM9_EN */

#endif /* end of #if CFG_UI_SCREEN_EN */

    /********************»Ã²ÊµÆ***************************/
#if CFG_UI_MAGIC_LED_EN

#if CFG_UI_MAGIC_LED_PWR_EN
    plib_gpio_init(CFG_PIN_MAGIC_LED_PWR_PORT, CFG_PIN_MAGIC_LED_PWR_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_Out_PP, GPIO_PUPDMode_None, GPIO_Driver_Strength);
    plib_gpio_set_value(CFG_PIN_MAGIC_LED_PWR_PORT, CFG_PIN_MAGIC_LED_PWR_PINNUM, PLIB_LOW);
#endif /* end of #if CFG_UI_MAGIC_LED_PWR_EN */

#if CFG_UI_MAGIC_LED0_EN
    plib_gpio_init(1 << CFG_PIN_MAGIC_LED0_PORT, 1 << CFG_PIN_MAGIC_LED0_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_Out_PP, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UI_MAGIC_LED0_EN */

#endif /* end of #if CFG_UI_MAGIC_LED_EN */

}

#if CFG_IT_GPIO_EN
/**
  * @brief  GPIO interrupt handler
  * @param  None
  * @retval None
  */
void pmcu_gpio_irq_handler() interrupt 9
{
}
#endif
