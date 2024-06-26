
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "util_printf.h"

/*************************************************************
* Custom print function. Print data to the buffer.
* Currently supports:
*   %d : Print integers. Supports u32 length.
*   %03d : Limit the total length. If the actual length exceeds the specified length, use the actual length.
*   %.3d : Specify decimal places.

* Function Name:         u8 Printf_Buff(u8 *buff, u8 leng, char *fmt, ...)
* Function Description:  Format the data to be printed to the buff array and send it out from the serial port.
* Input Parameters:
                           fmt : Formatted parameters.
                           ... : Variable parameter list.
* Return Parameter:      Data length.
* Return Type:           u8
* Notes:
*************************************************************/
u8 tiny_printf(char * fmt, ...)
{
    u8 uLen = 0;

#if CFG_DEBUG_ON
    va_list arg_ptr;
    u8 xdata * usb_tx_buff = ADDRESS_TX_BUFF;

    if(strlen(fmt) >= CFG_UART_TX_BUF_LENGTH)
    {
        return 0;
    }

    va_start(arg_ptr, fmt);
    uLen = (u8)vsprintf((char *)(usb_tx_buff), fmt, arg_ptr);
    va_end(arg_ptr);
    print_data_out();

#endif /* end of DEBUG_ON */

    return (uLen);
}

