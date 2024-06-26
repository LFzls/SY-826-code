/**
 * @file
 * @brief       UART middleware interface function
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#include "bsp_uart.h"

xdata UART_TYPE g_uart1;                      //uart1
xdata U8 g_txbuffs[CFG_UART_TX_BUF_LENGTH];   // Allocate send buffer
xdata U8 g_rxbuffs[CFG_UART_RX_BUF_LENGTH];   // Allocate receive buffer

/**
* @brief  UART receive and send BUF initialization
* @retval None
* @par   Note
* None
*/
void pmcu_uart_buf_init(void)
{
    g_uart1.pRxbuff = g_rxbuffs;
    g_uart1.pTxbuff = g_txbuffs;
}

/**
* @brief  UART initialization function
* @retval None
* @par   Note
* None
*/
void pmcu_uart_init(void)
{
#if (CFG_UART_MODE == 0)
    {
#if CFG_DEBUG_ON
        //GPIOC0-->TX
        plib_gpio_init(GPIO_GroupC, GPIO_Pin_0, GPIO_PinMux_UART, GPIO_IOMode_Out_PP, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_DEBUG_ON */

#if CFG_UART_RX_EN
        //GPIOC1-->RX
        plib_gpio_init(GPIO_GroupC, GPIO_Pin_1, GPIO_PinMux_UART, GPIO_IOMode_IN_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
#endif /* end of #if CFG_UART_RX_EN */

#if CFG_UART_BOOTING_EN  //WakeUp
        plib_gpio_it_cfg(GPIO_GroupC, GPIO_Pin_1, PLIB_ENABLE);
#endif  /* end of #if CFG_UART_BOOTING_EN */

        //UART initialization
        plib_uart_init(UART_WordLength_8b, CFG_UART_BAUDRATE, UART_Mode_FullDuplex, CFG_UART_RX_EN, PLIB_DISABLE);
    }
#else
    {
        //GPIOC0-->TX/RX
        plib_gpio_init(GPIO_GroupC, GPIO_Pin_0, GPIO_PinMux_UART, GPIO_IOMode_IN_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
        //UART initialization
        plib_uart_init(UART_WordLength_8b, CFG_UART_BAUDRATE, UART_Mode_HalfDuplex, CFG_UART_RX_EN, PLIB_DISABLE);
    }
#endif

#if (CFG_UART_CONFIG_SEND_METHORD == 1)
    plib_uart_it_en(PLIB_ENABLE);
#endif
}

/**
* @brief  In half-duplex mode, the TX pin is used as RX
* @retval None
* @par   Note
* None
*/
void pmcu_uart_half_rx(void)
{
    plib_gpio_init(GPIO_GroupC, GPIO_Pin_0, GPIO_PinMux_UART, GPIO_IOMode_IN_FLOATING, GPIO_PUPDMode_None, GPIO_Driver_Strength);
    plib_uart_rx_en(PLIB_ENABLE);
}

/**
* @brief  In half-duplex mode, the Tx pin is used as Tx
* @retval None
* @par   Note
* None
*/
void pmcu_uart_half_tx(void)
{
    plib_gpio_init(GPIO_GroupC, GPIO_Pin_0, GPIO_PinMux_UART, GPIO_IOMode_Out_PP, GPIO_PUPDMode_None, GPIO_Driver_Strength);
    plib_uart_rx_en(PLIB_DISABLE);
}


/**
* @brief  The receive function executed in the interrupt receive function
* @retval None
* @par   Note
* None
*/
void pmcu_uart_irq_rx(U8 rxdata)
{
    g_uart1.rxtimeout = CFG_UART_RX_TIMEOUT; //receive timeout

    if (g_uart1.rxcount > CFG_UART_RX_BUF_LENGTH)
    {
        g_uart1.rxcount = 0;    //Perform array out-of-bounds processing
    }

    *(g_uart1.pRxbuff + g_uart1.rxcount++) = rxdata; //Data is pushed into the cache
}

/**
* @brief  The send function executed in the interrupt send function
* @retval None
* @par   Note
* None
*/
void pmcu_uart_irq_tx(void)
{
    if ((++g_uart1.txcount) >= (g_uart1.txleng))   //Sending completed
    {
        g_uart1.txbussy = 0;        //Clear the sending busy, can receive the next send

#if CFG_UART_MODE==1
        pmcu_uart_half_rx();
#endif

    }
    else
    {
        plib_uart_send_byte(*(g_uart1.pTxbuff + g_uart1.txcount));
    }
}

/**
* @brief  UART receive timeout function
* @retval None
* @par   Note
* None
*/
void pmcu_uart_rx_timeout(void)
{
    if (g_uart1.rxtimeout)
    {
        g_uart1.rxtimeout -= 1;

        if (g_uart1.rxtimeout == 0)
        {
            g_uart1.rxcount = 0;
            g_uart1.rxOk = 1;
        }
    }
}

/**
* @brief  UART's send function
* @param  buff The cache to be sent
* @param  buff The byte length to be sent
* @retval Send status
* - 0 Currently cannot send, only valid in interrupt send mode
* - Non-0 Currently can send, query send mode returns 1 indicates that the send has been completed, interrupt send mode returns 1 indicates that the send has started
* @par   Note
* None
*/
U8 pmcu_uart_tx(U8 xdata * buff, U8 leng)
{
    //Half-duplex mode, switch to send status
#if CFG_UART_MODE==1
    pmcu_uart_half_tx();
#endif

#if (CFG_UART_CONFIG_SEND_METHORD == 0)

    while (leng)
    {
        plib_uart_send_byte(*buff);

        while (plib_uart_get_flg(UART_S1TI) == 0);

        plib_uart_clr_flg(UART_S1TI);
        buff++;
        leng--;
    }

#elif (CFG_UART_CONFIG_SEND_METHORD == 1)

    if (g_uart1.txbussy)
    {
        return 0;
    }

    g_uart1.txcount = 0;
    g_uart1.txleng = leng;          //Send length
    g_uart1.txbussy = 1;                //Send busy flag
    g_uart1.pTxbuff = buff;         //Send cache
    plib_uart_send_byte(*(g_uart1.pTxbuff));            //Send the first byte, guide the interrupt to send step by step
#endif

    //Half-duplex mode, send end switch status
#if CFG_UART_MODE==1
    pmcu_uart_half_rx();
#endif
    return 1;
}

/**
* @brief  UART interrupt function. Interrupt send/interrupt receive
* @param  None
* @retval None
* @par   Note
* None
*/
void pmcu_uart_irq_handler() interrupt 16
{
    if (plib_uart_get_flg(UART_S1RI))
    {
        plib_uart_clr_flg(UART_S1RI);
        pmcu_uart_irq_rx(plib_uart_get_byte());
    }

    if (plib_uart_get_flg(UART_S1TI))
    {
        plib_uart_clr_flg(UART_S1TI);
        pmcu_uart_irq_tx();
    }
}

/**
* @brief  UART Booting
* @param  None
* @retval None
* @par   Note
* None
*/
void pmcu_uart_booting()
{
    if (plib_uart_get_flg(UART_S1RI))
    {
        plib_uart_clr_flg(UART_S1RI);
        pmcu_uart_irq_rx(plib_uart_get_byte());
    }

    pmcu_uart_rx_timeout();     //Receive timeout

    if(g_uart1.rxOk)            //Receive finish
    {
        g_uart1.rxOk = 0;

		//接到一个正确的字节时，先将中断关闭，避免定时器中断影响数据接收
        if(g_rxbuffs[0] == CFG_UART_BOOTING_CMD0)
        {		
			plib_sys_it_en(PLIB_DISABLE);
		}
		
        if(g_rxbuffs[0] == CFG_UART_BOOTING_CMD0 &&
                g_rxbuffs[1] == CFG_UART_BOOTING_CMD1 &&
                g_rxbuffs[2] == CFG_UART_BOOTING_CMD2 &&
                g_rxbuffs[3] == CFG_UART_BOOTING_CMD3 &&
                g_rxbuffs[4] == CFG_UART_BOOTING_CMD4 &&
                g_rxbuffs[5] == CFG_UART_BOOTING_CMD5)
        {
            //Reset system to update
            plib_sys_reset();
        }
    }
}
