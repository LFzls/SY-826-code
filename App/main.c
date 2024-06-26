#include "main.h"

/**
 * @brief main function
 *
 */
void main()
{
    /* Disable JTAG AM_DBG_PRINTF port */
    plib_sys_jtag_sel(JTAG_SEL_DISABLE);

    /* Disable the watchdog first, and then enable the watchdog in the application */
    plib_wdt_close();

    /* Delay 250ms to ensure normal start-up */
    delay_ms(250);

    /* Enable system clock*/
    plib_sys_clk_en();

    /* MIC init */
    pmcu_mic_init();

    /* peripheral initialization */
    bsy_sys_init();

    /* local main state init */
    local_init();

    /* local main function process */
    local_process();
}
