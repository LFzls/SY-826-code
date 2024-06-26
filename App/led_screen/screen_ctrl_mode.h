#ifndef __SCREEN_CTRL_MODE_H__
#define __SCREEN_CTRL_MODE_H__

#include "battery.h"
#include "screen_xx.h"
typedef enum
{
    SCREEN_MODE_UNDEFINE = 0,
    SCREEN_MODE_OFF,        	//Always off
    SCREEN_MODE_ON,         	//Always on
    SCREEN_MODE_FLASH,      	//Blink
    SCREEN_MODE_HOLD,			//Holding Status
	SCREEN_MODE_MARQUEE,		//Marquee	
  SCREEN_MODE_BREATH,

} SCREEN_MODE_E;

typedef struct
{
    u8 mode;         //模式
    u8 cnt;          //需要控制的次数
    u16 run;          //计数器，计算已运行的时间
    u16 period;       //单次控制的周期
    u8 is_on;         //当前是否是亮屏，用于辅助闪烁状态	
    u8 onoff_after_flash;  //闪烁最终状态
    u8 delay;
    u32 ctrl_mask;      //控制掩码
    u32 ctrl_bak;       //控制前的备份
    u32 ctrl_mask2;      //控制掩码
    u32 ctrl_bak2;       //控制前的备份
} SCREEN_CTRL_T;


typedef struct
{
  u8 period ;        //周期
  u8 duty   ;        //占空比  
  u8 run   ;         //当前值 
}SCR_PWM_T;


#define SCR_PWM_PERIOD  (16)
#define SCR_PWM_MUTY_MAX  (SCR_PWM_PERIOD - 1)

#define SCR_CAL_DUTY_BREATH_UP()	((u32)screen_ctrl_t.run * SCR_PWM_MUTY_MAX / screen_ctrl_t.period)
#define SCR_CAL_DUTY_BREATH_DN()	(SCR_PWM_MUTY_MAX - SCR_CAL_DUTY_BREATH_UP())


extern SCREEN_CTRL_T xdata screen_ctrl_t;

void screen_set_ctrl_info(SCREEN_MODE_E mode, u16 Period_Onff, u8 Loop_Times, u32 ch_Mark, u32 ch_Mark2, u8 flash_on);
void screen_set_bright(u32 mask, u32 mask2);
void screen_ctrl_handler(void);
void screen_soft_pwm_process(void);
#endif




