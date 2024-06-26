/**
 * @file
 * @brief       Middleware interface functions for UART (Serial Communication) control.
 * @author      admin
 * @date        2023.07.27
 * @version     v1.0
 * @par         Copyright(c): All rights reserved.
*/

#ifndef __BSP_UART_H__
#define __BSP_UART_H__

#include "pmcu_x0_include.h"

typedef struct {
    U8 txcount;         // Current number of bytes sent
    U8 txleng;          // Total number of bytes to send
    U8* pTxbuff;        // Pointer to the send buffer
    U8 txbussy;         // Sending busy flag

    U8 rxcount;         // Current number of received bytes
    U8 rxleng;          // Length of the current data frame
    U8 rxOk;            // Data frame received flag
    U8 rxtimeout;       // Receive byte timeout counter
    U8* pRxbuff;        // Pointer to the receive buffer
} UART_TYPE;

extern xdata UART_TYPE g_uart1;
extern xdata U8 g_txbuffs[CFG_UART_TX_BUF_LENGTH];   // Allocate send buffer
extern xdata U8 g_rxbuffs[CFG_UART_RX_BUF_LENGTH]; // Allocate receive buffer

extern void pmcu_uart_buf_init(void);
extern void pmcu_uart_init(void);
extern void pmcu_uart_rx_timeout(void);
extern U8 pmcu_uart_tx(U8 xdata* buff, U8 leng);
extern void pmcu_uart_booting();

#endif /* end of __BSP_UART_H__ */
