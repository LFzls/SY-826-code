#ifndef __MAIN_H__
#define __MAIN_H__

#include "application.h"

/**
 * @brief peripheral initialization
 *
 */
void bsy_sys_init(void);

/**
 * @brief local Basic functionality state initialization
 *
 */
void local_init(void);
/**
 * @brief local main functionality process
 *
 */
void local_process(void);

#endif
