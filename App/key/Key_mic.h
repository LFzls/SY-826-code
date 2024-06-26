#ifndef __KEY_MIC_H__
#define __KEY_MIC_H__

#include "application.h"

#define _PIN_KEY	(plib_gpio_get_value(CFG_PIN_KEY_PORT, CFG_PIN_KEY_PINNUM))
#define _PIN_MIC	(plib_gpio_get_value(CFG_PIN_MIC_PORT, CFG_PIN_MIC_PINNUM))

//读取按键键值
#if (CFG_PIN_KEY_VALUE_TYPE == 0)	//低有效
#define _GET_PIN_KEY() 	(!_PIN_KEY)

#elif (CFG_PIN_KEY_VALUE_TYPE == 1)	//高有效
#define _GET_PIN_KEY() 	(_PIN_KEY)

#endif

#define KEY_TICK_MAX   		(2)//防抖
#define KEY_TICK_MIN   		(0)

#define KEY_TIM_DOWN_MAX    (5000)
#define KEY_TIM_DOWN_MIN    (0)

#define KEY_TIM_UP_MAX      (3000)
#define KEY_TIM_UP_ACT      (50)	//按键弹起计时：n*10ms，两次按键间隔在此时间内，认为连续按下
#define KEY_TIM_UP_MIN      (0)

//长按时间
#define _KEY_DOWN_2S            (200)

//咪头恢复阈值
#define _MIC_RECOVER_THD         (20)

typedef enum{
    KEY_EVENT_NONE = 0,	
    KEY_EVENT_PRESS,
    KEY_EVENT_RELEASE,        	
    KEY_EVENT_PRESS_X1,    
    KEY_EVENT_PRESS_X2, 	
    KEY_EVENT_PRESS_X3,	
    KEY_EVENT_PRESS_X4,   
    KEY_EVENT_PRESS_X5, 
    KEY_EVENT_PRESS_LONG,
}KEY_EVENT_E;

struct key_det_s {
    u8 tick;			//防抖次数
    u8 cnt;				//按键次数
  u8 is_down  : 1;  //确认按下标志位
  u8 is_up    : 1;  //确认释放标志位
  u8 reserve  : 6;  //预留
	u16 tim_down;		//长按时间
	u16 tim_up;			//释放时间
  u16 tim_multi_countdown; //连续按键检测倒计时
};
extern idata struct key_det_s g_key_s;

typedef struct
{
	u8  start : 1;      	//吸气状态，1为吸气，0为释放
	u8  hardware_ot : 1;  	//硬件超时更新初值
	u8  unuse :6;
}REV_MIC_STATUS_T;
extern REV_MIC_STATUS_T g_rev_mic;    //反向mic状态

extern bit g_mic_fire_en;  //MIC触发，高有效
extern bit g_key_fire_en;  //按键触发，高有效
extern bit g_key_power_on;

void mic_scan(void);
void key_scan(void);

#endif
