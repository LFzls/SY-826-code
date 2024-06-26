#ifndef __LED_SCREEN_COMMON_H__
#define __LED_SCREEN_COMMON_H__

#include "bsp_gpio.h"
#include "led_xx.h"

enum {
    LED_SHOW_TYPE_OFF = 0,             // LED all off
    LED_SHOW_TYPE_NONE,                // LED stays unchanged
    LED_SHOW_TYPE_LVR,                 // Low voltage (short circuit) reset	
    LED_SHOW_TYPE_POR,                 // Power on
    LED_SHOW_TYPE_BATLOW,              // Low battery before smoking
    LED_SHOW_TYPE_BATLOW_FIRE,         // Low battery while smoking
    LED_SHOW_TYPE_FIRE_START,          // Smoking ignition
    LED_SHOW_TYPE_FIRE_STOP,           // Smoking ended
    LED_SHOW_TYPE_FIRE_OT,             // Smoking timeout
    LED_SHOW_TYPE_RL_OPEN,             // Open circuit alarm
    LED_SHOW_TYPE_RL_LOW,              // Low resistance alarm??
    LED_SHOW_TYPE_RL_SHORT,            // Short circuit alarm??
    LED_SHOW_TYPE_RL_DRY,              // DRY circuit alarm??	
    LED_SHOW_TYPE_RL_OPEN_FIRE,        // Open circuit while smoking
    LED_SHOW_TYPE_RL_SHORT_FIRE,       // Short circuit while smoking
    LED_SHOW_TYPE_HEATER_IN,           // Heater connected
    LED_SHOW_TYPE_HEATER_REMOVE,       // Heater removed 
    LED_SHOW_TYPE_CHILD_LOCK_ON,       // Child lock activated
    LED_SHOW_TYPE_CHILD_LOCK_OFF,      // Child lock deactivated

    LED_SHOW_TYPE_USB_IN_FIRST,        // USB first connected
    LED_SHOW_TYPE_USB_CHARGING,        // USB charging in progress
    LED_SHOW_TYPE_USB_FULL_FIRST,      // USB first fully charged
    LED_SHOW_TYPE_USB_FULL_HOLD,       // USB fully charged and maintained
    LED_SHOW_TYPE_USB_REMOVE,          // USB removed
    LED_SHOW_TYPE_USB_RECHAG,          // USB recharged
	LED_SHOW_TYPE_LOCK_SYS,			   // Lock system
	LED_SHOW_TYPE_UNLOCK_SYS,		   // Unlock system
	
	LED_SHOW_TYPE_CHIP_OTP,		       // Chip OTP
	
    LED_SHOW_TYPE_FIRE_STOP_BREATHOFF, // LED ignition stops breathing
    LED_SHOW_TYPE_POW_OFF,             // Power off
    LED_SHOW_TYPE_POW_ON,              // Power on

    LED_SHOW_TYPE_HEALTH_FLASH,        // Health reminder
    LED_SHOW_TYPE_VOL_SELECT,          // Gear reminder

    LED_SHOW_TYPE_FIRE_NOOIL,          // Dry-burn protection
};

extern idata u8 g_led_show_type;

#endif
