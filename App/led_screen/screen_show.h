#ifndef __SCREEN_SHOW_H__
#define __SCREEN_SHOW_H__

#include "led_xx.h"

#if CFG_UI_SCREEN_EN

#define LED_Show_LVR() \
{                                             \
    LEDSCREEN_SET_STATUS(0xbfbf0000,RESERVE_MASK); \
    screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_LVR, CFG_UI_SCREEN_ONTIME_LVR, CFG_UI_SCREEN_CNT_LVR, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_LVR);  \
    g_led_show_type = LED_SHOW_TYPE_RL_SHORT;   \
}

#define LED_Show_Por() \
{                                             \
    LEDSCREEN_SET_STATUS(0xffff0000,RESERVE_MASK); \
    screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_POR, CFG_UI_SCREEN_ONTIME_POR, CFG_UI_SCREEN_CNT_POR, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_POR);  \
    g_led_show_type = LED_SHOW_TYPE_POR;   \
}

#define LED_Show_USB_IN_1st() \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \	
	screen_set_display_num(get_battery_level());   \
	screen_set_charge_bit(1);     \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_USB_IN, CFG_UI_SCREEN_ONTIME_USB_IN, CFG_UI_SCREEN_CNT_USB_IN, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_USB_IN);  \
	g_led_show_type=LED_SHOW_TYPE_USB_IN_FIRST;     \
}

#define LED_Show_USB_CHARGING() \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \	
	screen_set_display_num(get_battery_level());   \
	screen_set_charge_bit(1);     \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_USB_CHARGING, CFG_UI_SCREEN_ONTIME_USB_CHARGING, CFG_UI_SCREEN_CNT_USB_CHARGING, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_USB_CHARGING);  \
	g_led_show_type=LED_SHOW_TYPE_USB_CHARGING;     \
}

#define LED_SHow_USB_FULL_1st() \
{                                             \
    LEDSCREEN_SET_STATUS(0x713e0000,RESERVE_MASK); \
    screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_USB_FULL, CFG_UI_SCREEN_ONTIME_USB_FULL, CFG_UI_SCREEN_CNT_USB_FULL, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_USB_FULL);  \
    g_led_show_type = LED_SHOW_TYPE_USB_FULL_FIRST;   \
}

#define LED_Show_USB_Remove() \
{                                             \
    LEDSCREEN_SET_STATUS(0xffff0000,RESERVE_MASK); \
    screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_USB_OUT, CFG_UI_SCREEN_ONTIME_USB_OUT, CFG_UI_SCREEN_CNT_USB_OUT, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_USB_OUT);  \
    g_led_show_type = LED_SHOW_TYPE_USB_REMOVE;   \
}

#define LED_Show_FireStart() \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \	
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_FIRE_START, CFG_UI_SCREEN_ONTIME_FIRE_START, CFG_UI_SCREEN_CNT_FIRE_START, DIGITAL_NUM_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_FIRE_START);  \
	g_led_show_type=LED_SHOW_TYPE_FIRE_START;     \
}

#define LED_Show_FireStop()	 \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \	
	screen_set_display_num(get_battery_level());   \
	screen_set_smoke_bit(1);     \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_FIRE_STOP, CFG_UI_SCREEN_ONTIME_FIRE_STOP, CFG_UI_SCREEN_CNT_FIRE_STOP, DIGITAL_NUM_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_FIRE_STOP);  \
	g_led_show_type=LED_SHOW_TYPE_FIRE_STOP;     \
}

#define LED_Show_OT() \
{                                         \
    LEDSCREEN_SET_STATUS(0xffff0000,RESERVE_MASK); \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_FIRE_TIMEOUT, CFG_UI_SCREEN_ONTIME_FIRE_TIMEOUT, CFG_UI_SCREEN_CNT_FIRE_TIMEOUT, DIGITAL_NUM_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_FIRE_TIMEOUT);  \
	g_led_show_type=LED_SHOW_TYPE_FIRE_OT;     \
}

#define LED_Show_RL_IN() \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \	
	screen_set_charge_bit(1);     \
	screen_set_smoke_bit(1);     \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_RL_IN, CFG_UI_SCREEN_ONTIME_RL_IN, CFG_UI_SCREEN_CNT_RL_IN, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_RL_IN);  \
	g_led_show_type=LED_SHOW_TYPE_HEATER_IN;     \
}

#define LED_Show_RL_OUT() \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \	
	screen_set_charge_bit(1);     \
	screen_set_smoke_bit(1);     \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_RL_OUT, CFG_UI_SCREEN_ONTIME_RL_OUT, CFG_UI_SCREEN_CNT_RL_OUT, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_RL_OUT);  \
	g_led_show_type=LED_SHOW_TYPE_HEATER_REMOVE;     \
}

#define LED_Show_RLSHORT()	 \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \	
	screen_set_charge_bit(1);     \
	screen_set_smoke_bit(1);     \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_RL_SHORT, CFG_UI_SCREEN_ONTIME_RL_SHORT, CFG_UI_SCREEN_CNT_RL_SHORT, VALID_BIT_MASK, RESERVE_MASK,CFG_UI_SCREEN_END_STATE_RL_SHORT);  \
	g_led_show_type=LED_SHOW_TYPE_RL_SHORT;     \
}

#define LED_Show_RLLOW()	 \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \	
	screen_set_charge_bit(1);     \
	screen_set_smoke_bit(1);     \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_RL_LOW, CFG_UI_SCREEN_ONTIME_RL_LOW, CFG_UI_SCREEN_CNT_RL_LOW, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_RL_LOW);  \
	g_led_show_type=LED_SHOW_TYPE_RL_LOW;     \
}

#define LED_Show_RLOPEN()	 \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \	
	screen_set_charge_bit(1);     \
	screen_set_smoke_bit(1);     \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_RL_OPEN, CFG_UI_SCREEN_ONTIME_RL_OPEN, CFG_UI_SCREEN_CNT_RL_OPEN, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_RL_OPEN);  \
	g_led_show_type=LED_SHOW_TYPE_RL_OPEN;     \
}

#define LED_Show_RLDRY()		 \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \
	screen_set_charge_bit(1);     \
	screen_set_smoke_bit(1);     \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_RL_DRY, CFG_UI_SCREEN_ONTIME_RL_DRY, CFG_UI_SCREEN_CNT_RL_DRY, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_RL_DRY);  \
	g_led_show_type=LED_SHOW_TYPE_RL_DRY;     \
}

#define LED_Show_Lock_Child() \
{                                         \
    LEDSCREEN_SET_STATUS(0xffff0000,RESERVE_MASK); \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_CHILD_LOCK, CFG_UI_SCREEN_ONTIME_CHILD_LOCK, CFG_UI_SCREEN_CNT_CHILD_LOCK, VALID_BIT_MASK, RESERVE_MASK,CFG_UI_SCREEN_END_STATE_CHILD_LOCK);  \
	g_led_show_type=LED_SHOW_TYPE_CHILD_LOCK_ON;     \
}

#define LED_Show_UnLock_Child() \
{                                         \
    LEDSCREEN_SET_STATUS(0xffff0000,RESERVE_MASK); \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_CHILD_UNLOCK, CFG_UI_SCREEN_ONTIME_CHILD_UNLOCK, CFG_UI_SCREEN_CNT_CHILD_UNLOCK, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_CHILD_UNLOCK);  \
	g_led_show_type=LED_SHOW_TYPE_CHILD_LOCK_OFF;     \
}

#define LED_Show_BatLow() \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \	
	screen_set_display_num(get_battery_level());   \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_BAT_LOW, CFG_UI_SCREEN_ONTIME_BAT_LOW, CFG_UI_SCREEN_CNT_BAT_LOW, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_BAT_LOW);  \
	g_led_show_type=LED_SHOW_TYPE_BATLOW;     \
}

#define LED_Show_Lock_Sys()	  \
{                                         \
    LEDSCREEN_SET_STATUS(0xffff0000,RESERVE_MASK); \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_SYS_LOCK, CFG_UI_SCREEN_ONTIME_SYS_LOCK, CFG_UI_SCREEN_CNT_SYS_LOCK, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_SYS_LOCK);  \
	g_led_show_type=LED_SHOW_TYPE_LOCK_SYS;     \
}

#define LED_Show_UnLock_Sys()	  \
{                                         \
    LEDSCREEN_SET_STATUS(0xffff0000,RESERVE_MASK); \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_SYS_UNLOCK, CFG_UI_SCREEN_ONTIME_SYS_UNLOCK, CFG_UI_SCREEN_CNT_SYS_UNLOCK, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_SYS_UNLOCK);  \
	g_led_show_type=LED_SHOW_TYPE_UNLOCK_SYS;     \
}

#define LED_Show_ChipOTP()	  \
{                                         \
	LEDSCREEN_STATUS_CLEAR(VALID_BIT_MASK,RESERVE_MASK); \	
	screen_set_charge_bit(1);     \
	screen_set_smoke_bit(1);     \
	screen_set_ctrl_info(CFG_UI_SCREEN_TYPE_CHIP_OTP, CFG_UI_SCREEN_ONTIME_CHIP_OTP, CFG_UI_SCREEN_CNT_CHIP_OTP, VALID_BIT_MASK,RESERVE_MASK, CFG_UI_SCREEN_END_STATE_CHIP_OTP);  \
	g_led_show_type=LED_SHOW_TYPE_CHIP_OTP;     \
}

#endif /* end of CFG_UI_LED_EN */

#endif
