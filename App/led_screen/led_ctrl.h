#ifndef __LED_CTRL_H__
#define __LED_CTRL_H__

#include "led_xx.h"

#define LED_NUM_MAX 	6   
#define LED0_MASK       (0x01)	//PWM0_0
#define LED1_MASK       (0x02)	//PWM0_1
#define LED2_MASK       (0x04)	//PWM0_2
#define LED_GROUP0_ALL_MASK    (LED0_MASK|LED1_MASK|LED2_MASK)

#define LED3_MASK       (0x08)	//PWM1_0
#define LED4_MASK       (0x10)	//PWM1_1
#define LED5_MASK       (0x20)	//PWM1_2
#define LED_GROUP1_ALL_MASK    (LED3_MASK|LED4_MASK|LED5_MASK)

typedef enum{
    LED_MODE_UNDEFINE = 0,
    LED_MODE_ON,        	//Always on	
    LED_MODE_OFF,       	//Always off
    LED_MODE_BREATH_ON, 	//Gradually brighten	
    LED_MODE_BREATH_OFF,	//Gradually dim	
    LED_MODE_FLASH,     	//Blink
    LED_MODE_BREATH,    	//Breathing
	LED_MODE_ON_OFF,		//Always on and than off	
}LED_MODE_E;

typedef enum{    
    LED_COLOR_NOTHING=0,
    LED_COLOR_RED,      	//Red
    LED_COLOR_GREEN,    	//Green
    LED_COLOR_BLUE,     	//Blue	
    LED_COLOR_YELLOW,   	//Yellow, R+G
    LED_COLOR_PURPLE,   	//Purple, R+B
    LED_COLOR_CYAN,     	//Cyan, G+B
    LED_COLOR_WHITE,    	//White, R+G+B
}LED_COLOR_TYPE;

struct led_ctrl {
    u8 mode;				//Light up mode
    u8 cnt;					//Number of light on
	u8 run;					//The length of time it has been light on
	u8 onoff;				//The length of time to flash 、breath on/off
	u8 led_mask;			//LED combination
	u8 is_on;         //当前是否是亮屏，用于辅助闪烁状态	
};
extern xdata struct led_ctrl g_led_s;

#define led_cal_duty_breath_up()	(g_led_s.run * CFG_PWM0_PERIOD / g_led_s.onoff)
#define led_cal_duty_breath_dn()	(CFG_PWM0_PERIOD - led_cal_duty_breath_up())
#define led_all_off(color_msk)		led_set_bright(color_msk, 0)
#define led_all_on(color_msk)		led_set_bright(color_msk, CFG_PWM0_PERIOD)

void led_set_ctrl_info(LED_MODE_E mode, u8 Period_Onff,u8 Loop_Times,u8 ch_Mark);
void led_set_bright(u8 color_msk, u8 duty);
void led_ctrl_handler(void);

#endif
