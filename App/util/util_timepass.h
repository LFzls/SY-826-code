#ifndef __UTIL_TIMEPASS_H__
#define __UTIL_TIMEPASS_H__

#include "user_typedef.h"
#include "bsp_timer.h"

#define TIMEPASS_MAX	0xFFFF

#define util_timepass_init(softtimer)	softtimer=g_sys_tick
u16 util_time_passing(u16 softtimer);
u8 util_timepass_check(u16* softtimer, u16 cnt);

#endif


