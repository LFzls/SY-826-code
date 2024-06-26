#ifndef ___UTIL_PRINTF_H__
#define ___UTIL_PRINTF_H__

#include "user_typedef.h"
#include "bsp_uart.h"
#include "pmcu_x0_include.h"

#define ADDRESS_TX_BUFF		(g_txbuffs)
extern u8 tiny_printf(char* fmt, ...);
#define print_data_out()	pmcu_uart_tx(ADDRESS_TX_BUFF,uLen);while(g_uart1.txbussy)

#endif
