#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "application.h"

typedef enum {
    EVENT_NONE  = 0,

    EVENT_KEY_PRESS,   // Single key press
	EVENT_PRESS_x1,
	EVENT_PRESS_x2,
    EVENT_PRESS_x3,
	EVENT_PRESS_x4,
    EVENT_PRESS_x5,
    EVENT_KEY_RELEASE, // Key release

    EVENT_MIC_START,
    EVENT_MIC_STOP,
    EVENT_MIC_BLOW_START, // Blow action

	EVENT_PREFIRE_START,// Preheat
	EVENT_LOCK_CHILD,	// Lock child
	EVENT_LOCK_SYS,		// Lock Sys
	EVENT_POWER_ON_OFF,	// Power on off
	EVENT_MODE_SW,		// Shift gears	
    EVENT_BAT_LOW,      // Low battery voltage
    EVENT_HEATER_OPEN,  // Heater open
    EVENT_HEATER_SHORT, // Heater short
    EVENT_HEATER_INPUT, // Load connection
    EVENT_HEATER_REMOVE,// Load disconnection
    EVENT_HEATER_DRY,	// Dry burn protection

    EVENT_FIREPRE_STOP, // Preheating completed
    EVENT_FIRE_STOP,    // Heating completed
    EVENT_OUTPUT_OCP,   // Output overcurrent
    EVENT_OUTPUT_OVP,   // Output overvoltage
    EVENT_FIRE_OTP,     // Smoking timeout
    EVENT_CHIP_OTP,     // Chip overheat protection
	
    EVENT_USB_FULL,
    EVENT_USB_RECHRG,
    EVENT_USB_INPUT,
    EVENT_USB_CHRGING,	
    EVENT_USB_REMOVE,
	EVENT_USB_OVP,
	EVENT_USB_UVP,	
    EVENT_USB_FULLED,

    EVENT_MAX,
};

typedef enum {
    SYSTEM_IDLE = 0,        // Standby
    SYSTEM_POWEROFF,    // Power off
    SYSTEM_FIRE_START,
    SYSTEM_FIRE_START_ERR,
    SYSTEM_FIRE_RUNNING,
    SYSTEM_FIRE_STOP_ERR,
    SYSTEM_FIRE_STOP,
} SYSTEM_STATE;

typedef enum {
    FIRE_STOP = 0,        // Stop heating
    FIRE_STEP_FIREPRE,    // Preheating stage
    FIRE_STEP_HIGH,        // Power enhancement stage. If the preheating temperature is not reached within 15s, it needs to enter the power enhancement stage
    FIRE_STEP_HIGH_FIREING,
    FIRE_STEP_HIGH_DELAY,
    FIRE_STEP_GOTO_NORMAL,    // Actions before entering constant temperature heating mode
    FIRE_STEP_NORMAL,    // Constant temperature stage
    FIRE_STEP_DEC,        // Temperature reduction handling after constant temperature stage
} FIREING_STEP;

struct system_timer {
    u16 systick;
    u8  timer_1ms;
    u16 timer_10ms;
    u16 timesleep;    	// Sleep countdown
    u16 firing;    		// Total smoking time
	u16 bat_dly;	//Get bat volt
    u16 bat_volt_update;//update bat volt
	u16 dry_det;		//detect dry	
    u16 timer_1S;
    u16 timer_disp;	
    u16 timer_oil_update;	
    u16 timer_fire_update;		
};

struct system_info {
    u8 event;        // System message event
    SYSTEM_STATE status_sys;    // System running status
    struct system_timer time;        // System time definitions
    u8 lock_child;    	// Lock Child flag
    u8 lock_sys;    	// Lock Sys flag
	u8 flg_lvr;			//LVR reset
	u8 flg_lvr_ref;		//LVR reset, than refresh mic init value
};

extern idata struct system_info g_sys;

void manager_process(void);

#endif
