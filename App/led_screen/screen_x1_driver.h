#ifndef __SCREEN_X1_DRIVER_H__
#define __SCREEN_X1_DRIVER_H__

#include "led_xx.h"

/**********************************************************************
//5脚断码屏
     1                       
     A         A
    ——      ——	             
  F|    |B  F|    |B   # H1     
    ——      ——           
  E|    |C  E|    |C   * H2  
    ——      ——            
     D         D

//GPIO分配
COM1------GPIOA0
COM2------GPIOA1
COM3------GPIOA2
COM4------GPIOA3
COM5------GPIOB3

//真值表
 L/H COM1 COM2 COM3 COM4 COM5
COM1  --   A1   B1   C1   D1            
COM2  E1   --   F1   G1   A2
COM3  B2   C2   --   G2   --                              
COM4  F2   G2   H1   --   H2                                  
COM5  --   --   --   --   --   
*****************************************************************************/

#define DIGITS_NUM  (2)							 //“0”数码管数量
#define SPECIAL_DIG_INDEX   (2)					 //特殊数码段数量，如“H1”
#define VALID_BIT_MASK   (0xFFFF0000)            //全屏有效控制掩码
#define DIG1_MASK        (0xFF000000)            //十位有效掩码
#define DIG2_MASK        (0x00FF0000)            //个位有效掩码
#define RESERVE_MASK       (0xFFFFFFFF)           
#define DIGITAL_NUM_MASK  (DIG1_MASK|DIG2_MASK)

typedef struct
{
    u8 a  : 1;	//A1 A2
    u8 b  : 1;	//B1 B2
    u8 c  : 1;	//C1 C2
    u8 d  : 1;	//D1 D2
    u8 e  : 1;	//E1 E2
    u8 f  : 1;	//F1 F2
    u8 g  : 1;	//G1 G2
    u8 h  : 1;	//H1 H2
} DIGITS_T;

typedef union
{
    DIGITS_T dig[DIGITS_NUM];
    u32      hex[2];      //最多64段，如需扩展请调整数组大小
} LEDSCREEN_STATUS_U;
extern xdata LEDSCREEN_STATUS_U g_screen_status_u;




typedef enum
{
    COM_1 = 0,
    COM_2,
    COM_3,
    COM_4,
    COM_5,
	COM_NUM		
} COM_E;

typedef enum {
	MARQUEE_MASS_0 = 0,
	MARQUEE_MASS_1,
	MARQUEE_MASS_2,
	MARQUEE_MASS_3,
	MARQUEE_MASS_4,
	MARQUEE_MASS_5,
	MARQUEE_MASS_6,
	MARQUEE_MASS_7,
	
	MARQUEE_MASS_NUM,
} MARQUEE_MASS_E;

#define LED_ALLCOM_SET_NONE() 					\
{                             					\
    SET_COM_INNONE(CFG_PIN_COM1_PORT, CFG_PIN_COM1_PINNUM);     	\
    SET_COM_INNONE(CFG_PIN_COM2_PORT, CFG_PIN_COM2_PINNUM);     	\
    SET_COM_INNONE(CFG_PIN_COM3_PORT, CFG_PIN_COM3_PINNUM);     	\
    SET_COM_INNONE(CFG_PIN_COM4_PORT, CFG_PIN_COM4_PINNUM);     	\
    SET_COM_INNONE(CFG_PIN_COM5_PORT, CFG_PIN_COM5_PINNUM);     	\
}

#define LED_PERCENT_MAX (99)
#define LED_PERCENT_MIN (0)
#define LED_PERCENT_OFF (-1)
		

void LEDSCREEN_STATUS_CLEAR(u32 MASK, u32 MASK2);
void LEDSCREEN_SET_STATUS(u32 MASK, u32 MASK2);

void screen_set_smoke_bit(bit on);			//油量图标
void screen_set_charge_bit(bit on);			//闪电图标
void screen_set_display_num(s8 num); 		//显示数字
void screen_set_marquee(MARQUEE_MASS_E marquee_mass); 	//跑马灯
void screen_driver_scan_loop(void);
							  
#endif