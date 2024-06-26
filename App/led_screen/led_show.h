#ifndef __LED_SHOW_H__
#define __LED_SHOW_H__

#include "led_xx.h"

#if CFG_UI_LED_EN

#define LED_Show_LVR()			{led_set_ctrl_info(CFG_UI_LED_TYPE_LVR, CFG_UI_LED_ONTIME_LVR, CFG_UI_LED_CNT_LVR, CFG_UI_LED_COLOR_LVR); g_led_show_type=LED_SHOW_TYPE_LVR;}
#define LED_Show_Por()			{led_set_ctrl_info(CFG_UI_LED_TYPE_POR, CFG_UI_LED_ONTIME_POR, CFG_UI_LED_CNT_POR, CFG_UI_LED_COLOR_POR); g_led_show_type=LED_SHOW_TYPE_POR;}

#define LED_Show_USB_IN_1st()	{led_set_ctrl_info(CFG_UI_LED_TYPE_USB_IN, CFG_UI_LED_ONTIME_USB_IN, CFG_UI_LED_CNT_USB_IN, CFG_UI_LED_COLOR_USB_IN); g_led_show_type=LED_SHOW_TYPE_USB_IN_FIRST;}
#define LED_Show_USB_CHARGING()	{led_set_ctrl_info(CFG_UI_LED_TYPE_USB_CHARGING, CFG_UI_LED_ONTIME_USB_CHARGING, CFG_UI_LED_CNT_USB_CHARGING, CFG_UI_LED_COLOR_USB_CHARGING); g_led_show_type=LED_SHOW_TYPE_USB_CHARGING;}
#define LED_SHow_USB_FULL_1st()	{led_set_ctrl_info(CFG_UI_LED_TYPE_USB_FULL, CFG_UI_LED_ONTIME_USB_FULL, CFG_UI_LED_CNT_USB_FULL, CFG_UI_LED_COLOR_USB_FULL); g_led_show_type=LED_SHOW_TYPE_USB_FULL_FIRST;}
#define LED_Show_USB_Remove()	{led_set_ctrl_info(CFG_UI_LED_TYPE_USB_OUT, CFG_UI_LED_ONTIME_USB_OUT, CFG_UI_LED_CNT_USB_OUT, CFG_UI_LED_COLOR_USB_OUT); g_led_show_type=LED_SHOW_TYPE_USB_REMOVE;}

#define LED_Show_FireStart()	{led_set_ctrl_info(CFG_UI_LED_TYPE_FIRE_START, CFG_UI_LED_ONTIME_FIRE_START, CFG_UI_LED_CNT_FIRE_START, CFG_UI_LED_COLOR_FIRE_START); g_led_show_type=LED_SHOW_TYPE_FIRE_START;}
#define LED_Show_FireStop()		{led_set_ctrl_info(CFG_UI_LED_TYPE_FIRE_STOP, CFG_UI_LED_ONTIME_FIRE_STOP, CFG_UI_LED_CNT_FIRE_STOP, CFG_UI_LED_COLOR_FIRE_STOP); g_led_show_type=LED_SHOW_TYPE_FIRE_STOP;}
#define LED_Show_OT()			{led_set_ctrl_info(CFG_UI_LED_TYPE_FIRE_TIMEOUT, CFG_UI_LED_ONTIME_FIRE_TIMEOUT, CFG_UI_LED_CNT_FIRE_TIMEOUT, CFG_UI_LED_COLOR_FIRE_TIMEOUT); g_led_show_type=LED_SHOW_TYPE_FIRE_OT;}

#define LED_Show_RL_IN()		{led_set_ctrl_info(CFG_UI_LED_TYPE_RL_IN, CFG_UI_LED_ONTIME_RL_IN, CFG_UI_LED_CNT_RL_IN, CFG_UI_LED_COLOR_RL_IN); g_led_show_type=LED_SHOW_TYPE_HEATER_IN;}
#define LED_Show_RL_OUT()		{led_set_ctrl_info(CFG_UI_LED_TYPE_RL_OUT, CFG_UI_LED_ONTIME_RL_OUT, CFG_UI_LED_CNT_RL_OUT, CFG_UI_LED_COLOR_RL_OUT); g_led_show_type=LED_SHOW_TYPE_HEATER_REMOVE;}
#define LED_Show_RLSHORT()		{led_set_ctrl_info(CFG_UI_LED_TYPE_RL_SHORT, CFG_UI_LED_ONTIME_RL_SHORT, CFG_UI_LED_CNT_RL_SHORT, CFG_UI_LED_COLOR_RL_SHORT); g_led_show_type=LED_SHOW_TYPE_RL_SHORT;}
#define LED_Show_RLOPEN()		{led_set_ctrl_info(CFG_UI_LED_TYPE_RL_OPEN, CFG_UI_LED_ONTIME_RL_OPEN, CFG_UI_LED_CNT_RL_OPEN, CFG_UI_LED_COLOR_RL_OPEN); g_led_show_type=LED_SHOW_TYPE_RL_OPEN;}
#define LED_Show_RLDRY()		{led_set_ctrl_info(CFG_UI_LED_TYPE_RL_DRY, CFG_UI_LED_ONTIME_RL_DRY, CFG_UI_LED_CNT_RL_DRY, CFG_UI_LED_COLOR_RL_DRY); g_led_show_type=LED_SHOW_TYPE_RL_DRY;}

#define LED_Show_Lock_Child()	{led_set_ctrl_info(CFG_UI_LED_TYPE_CHILD_LOCK, CFG_UI_LED_ONTIME_CHILD_LOCK, CFG_UI_LED_CNT_CHILD_LOCK, CFG_UI_LED_COLOR_CHILD_LOCK); g_led_show_type=LED_SHOW_TYPE_CHILD_LOCK_ON;}
#define LED_Show_UnLock_Child()	{led_set_ctrl_info(CFG_UI_LED_TYPE_CHILD_UNLOCK, CFG_UI_LED_ONTIME_CHILD_UNLOCK, CFG_UI_LED_CNT_CHILD_UNLOCK, CFG_UI_LED_COLOR_CHILD_UNLOCK); g_led_show_type=LED_SHOW_TYPE_CHILD_LOCK_OFF;}

#define LED_Show_BatLow()		{led_set_ctrl_info(CFG_UI_LED_TYPE_BAT_LOW, CFG_UI_LED_ONTIME_BAT_LOW, CFG_UI_LED_CNT_BAT_LOW, CFG_UI_LED_COLOR_BAT_LOW); g_led_show_type=LED_SHOW_TYPE_BATLOW;}

#define LED_Show_Lock_Sys()	    {led_set_ctrl_info(CFG_UI_LED_TYPE_SYS_LOCK, CFG_UI_LED_ONTIME_SYS_LOCK, CFG_UI_LED_CNT_SYS_LOCK, CFG_UI_LED_COLOR_SYS_LOCK); g_led_show_type=LED_SHOW_TYPE_LOCK_SYS;}
#define LED_Show_UnLock_Sys()	{led_set_ctrl_info(CFG_UI_LED_TYPE_SYS_UNLOCK, CFG_UI_LED_ONTIME_SYS_UNLOCK, CFG_UI_LED_CNT_SYS_UNLOCK, CFG_UI_LED_COLOR_SYS_UNLOCK); g_led_show_type=LED_SHOW_TYPE_UNLOCK_SYS;}

#define LED_Show_ChipOTP()		{led_set_ctrl_info(CFG_UI_LED_TYPE_CHIP_OTP, CFG_UI_LED_ONTIME_CHIP_OTP, CFG_UI_LED_CNT_CHIP_OTP, CFG_UI_LED_COLOR_CHIP_OTP); g_led_show_type=LED_SHOW_TYPE_CHIP_OTP;}

#endif /* end of CFG_UI_LED_EN */

#endif
