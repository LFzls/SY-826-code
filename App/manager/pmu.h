#ifndef __PMU_H__
#define __PMU_H__

#include "application.h"

void pm_sleep_enter(void);
void pm_sleep_exit(void);
void pm_sleep_process(u16 timesleep);

#endif
