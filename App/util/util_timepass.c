#include "util_timepass.h"

/*
*   Check the duration of a software timer.
*   Parameters:
*       softtimer: The software timer counter variable.
*   Returns:
*       The elapsed time since the previous timestamp or timer value.
*/
u16 util_time_passing(u16 softtimer)
{
    u16 time;

    if (softtimer <= g_sys_tick)
    {
        time = (g_sys_tick - softtimer);
    }
    else
    {
        time = g_sys_tick;
        time += (TIMEPASS_MAX - softtimer);
    }

    return (time);
}

/*
*   Periodically check a software timer and reinitialize if the time has elapsed.
*   Parameters:
*       softtimer: The software timer counter variable.
*       cnt: The duration of the timer.
*   Returns:
*       1 if the timer has elapsed and is reinitialized, 0 otherwise.
*/
u8 util_timepass_check(u16 * softtimer, u16 cnt)
{
    if (util_time_passing(*softtimer) >= cnt)
    {
        *softtimer = g_sys_tick;
        return 1;
    }
    else
    {
        return 0;
    }
}
