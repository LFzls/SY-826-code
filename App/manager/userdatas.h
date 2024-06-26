#ifndef __USERDATAS_H__
#define __USERDATAS_H__

#include "application.h"

#define RST_POR_RAM		0x55AA5AA5	// Power-on reset
#define RST_LVR_RAM		0x00000000	// Low voltage (short circuit) reset

typedef enum
{
  RST_TYPE_NORMAL = 0,
  RST_TYPE_LVR,
}RST_TYPE_E;

typedef struct  
{
  //复位状态区分， 请不要改动此变量
    u32 rst_status; 
  
  //油量保存参数
    u32 time;      	// Total oil volume
    u32 work_time; 	// Amount of oil used
  
  //电量保存参数
    u8 show_level;					// 显示百分比
    u8 real_level;    			// 真实百分比	
   
  //模式保存参数
    u8  output_mode;        //单双发输出模式
  
  //如果有需要掉电保存的参数，请在以下位置添加，但请注意空间占用大小
	u16 mic_ini;        	//咪头初值
	
}USER_DATA_T;

extern xdata USER_DATA_T g_userdata_t;

void reset_src_set(void);
void reset_src_clear(void);
u8 reset_src_get(void);
void smoke_info_init(void);
u8 get_oil_percentage(void);
void oil_value_update(void);

#endif

