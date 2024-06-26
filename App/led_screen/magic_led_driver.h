#ifndef __MAGIC_LED_DRIVER_H__
#define __MAGIC_LED_DRIVER_H__

#include "led_xx.h"

extern void magic_led_send_one_bit(u8 bit_value);
extern void magic_led_reset_led();
extern void magic_led_send_24bits(u32 grb_value);
extern void magic_led_test();

#endif