#ifndef _OUTPUT_CTRL_H_
#define	_OUTPUT_CTRL_H_

#include "application.h"

#define CFG_MOS_PWM_PERIOD_MAX	((u32)CFG_MOS_PWM_PERIOD * 99 / 100)	//满占空比以99%输出，确保能触发PWM边沿采样
#define CFG_MOS_PWM_PERIOD_MIN	((u32)CFG_MOS_PWM_PERIOD * 20 / 100)	//最小占空比输出，以20%输出

#define CFG_EXTMOS_PWM_PERIOD_MAX	((u32)CFG_EXTMOS_PWM_PERIOD * 99 / 100)	//满占空比以99%输出，确保能触发PWM边沿采样
#define CFG_EXTMOS_PWM_PERIOD_MIN	((u32)CFG_EXTMOS_PWM_PERIOD * 20 / 100)	//最小占空比输出，以20%输出

#define ExtMOS_Output(ifen)       	\
{                                   \
    if(ifen == ENABLE)              \
        plib_gpio_set_value(CFG_PIN_EXTMOS_VOUT_PORT, CFG_PIN_EXTMOS_VOUT_PINNUM, PLIB_LOW);      \
    else                            \
        plib_gpio_set_value(CFG_PIN_EXTMOS_VOUT_PORT, CFG_PIN_EXTMOS_VOUT_PINNUM, PLIB_HIGH);       \
}

typedef enum {
	OUTPUT_MODE_MOS_NONE = 0,		//无输出	
	OUTPUT_MODE_INMOS_ONLY,			//仅内部MOS输出
	OUTPUT_MODE_EXMOS_ONLY,			//仅外部MOS输出
	OUTPUT_MODE_MOS_BOTH,			//双MOS同时输出
} OUTPUT_MODE_E;

struct output_data {
	u8 pwm_open_dly;		//MOS PWM导通后，延时采样ADC的时间周期，在100us定时器处理，实际延时=N*100us
	u8 pwm_open_flg;		//避开MOS PWM上升沿采样ADC的标志
	u8 pwm_ris_flg;			//PWM上升沿标志
	u16 pwm_duty;			//输出理论占空比	
    u16 v_mos_out;			//输出实时电压
    u16 v_user_set;			//输出设置的目标电压
	u8 fire_on;				//吸烟标志，1=正在输出
	u8 ouput_mode;			//输出模式，内部MOS输出；外部MOS输出；双发同时输出	
};

struct output_ctrl {
	struct output_data chn[2];		//定义最多两路MOS输出
	u8 ouput_mode;			//输出模式，内部MOS输出；外部MOS输出；双发同时输出	
};

extern idata struct output_ctrl g_out_s;

void out_fire_start(void);
void out_fire_stop(void);
void out_ctrl_cv(void);
void out_ctrl_cw(void);
void output_mos_change(void);

#endif

