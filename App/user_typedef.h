#ifndef TYPE_DEF_H
#define TYPE_DEF_H
/* the mcu's core */
#define __C51	0
#define __ARM	1
#define __x64	2
/* the mcu's endian mode */
#define LITTLE_ENDIAN	0
#define BIG_ENDIAN		1

#ifdef __CC_ARM
#define DEVICE_CORE	  __ARM
#define __ENDIAN_MODE	LITTLE_ENDIAN
#else
#define DEVICE_CORE	  __C51
#define __ENDIAN_MODE	BIG_ENDIAN
#endif

#ifndef DISABLE
#define DISABLE 	0
#endif
#ifndef ENABLE
#define ENABLE		1
#endif
#if  DEVICE_CORE == __C51
typedef bit					BIT;
typedef unsigned char		u8;
typedef unsigned int		u16;
typedef unsigned int		uint16;
typedef unsigned long		u32;
typedef signed char			s8;
typedef short int 			s16;
typedef long				s32;
#elif  DEVICE_CORE == __ARM
//typedef bool				BIT;
#include "stdbool.h"
typedef unsigned	char 	u8;
typedef unsigned short int 	u16;
typedef unsigned short int 	uint16;
typedef unsigned	int 	u32;
//typedef unsigned	__INT64 	u64;
typedef signed char			s8;
typedef signed short int	s16;
typedef signed	int 		s32;
#endif

typedef float				f32;
typedef double				f64;



#if __ENDIAN_MODE==BIG_ENDIAN
#define _GET_U16_HI(arg)      		(*(((u8 *)&arg) + 0))
#define _GET_U16_LOW(arg)      		(*(((u8 *)&arg) + 1))
#define _GET_U32_3BYTE(arg)      	(*(((u8 *)&arg) + 0))
#define _GET_U32_2BYTE(arg)      	(*(((u8 *)&arg) + 1))
#define _GET_U32_1BYTE(arg)      	(*(((u8 *)&arg) + 2))
#define _GET_U32_0BYTE(arg)      	(*(((u8 *)&arg) + 3))

#elif __ENDIAN_MODE==LITTLE_ENDIAN
#define _GET_U16_HI(arg)       		(*(((u8 *)&arg) + 1))
#define _GET_U16_LOW(arg)      		(*(((u8 *)&arg) + 0))
#define _GET_U32_3BYTE(arg)    		(*(((u8 *)&arg) + 3))
#define _GET_U32_2BYTE(arg)    		(*(((u8 *)&arg) + 2))
#define _GET_U32_1BYTE(arg)    		(*(((u8 *)&arg) + 1))
#define _GET_U32_0BYTE(arg)    		(*(((u8 *)&arg) + 0))
#endif

#define bLobyte(arg)	_GET_U16_LOW(arg)
#define bHibyte(arg)	_GET_U16_HI(arg)
/* ----------------------------------------------------------
	Read byte data from u16/u32 (code)
-----------------------------------------------------------*/
#define _GET_U16_HI_CONST(value)	(value>>8)
#define _GET_U16_LOW_CONST(value)	(value&0xFF)
#define _GET_U32_3BYTE_CONST(value) ((value&0xFF000000)>>24)
#define _GET_U32_2BYTE_CONST(value) ((value&0x00FF0000)>>16)
#define _GET_U32_1BYTE_CONST(value) ((value&0x0000FF00)>>8)
#define _GET_U32_0BYTE_CONST(value) (value&0xFF)

//========		volatile type    ========
typedef volatile u8  	_vu8;
typedef volatile u16 	_vu16;
typedef volatile u32  	_vu32;
#define _M8(adr)  (*((_vu8  *) (adr)))
#define _M16(adr) (*((_vu16 *) (adr)))
#define _M32(adr) (*((_vu32 *) (adr)))

/* ----------------------------------------------------------
	Read or Write u8/u16/u32 From or Into buff (u8 * pstr)[same endian]
	NOTE: different endian refernece "ulti_endian.h" / "ulti_endian.c"
-----------------------------------------------------------*/
#define _SET_U8(psrt,value)   	(_M8(psrt))=(value)
#define _GET_U8(psrt)          	(_M8(psrt))
#define _SET_U16(psrt,value)  	(_M16(psrt))=(value)
#define _GET_U16(psrt)         	(_M16(psrt))
#define _SET_U32(psrt,value)  	(_M32(psrt))=(value)
#define _GET_U32(psrt)         	(_M32(psrt))

#define _GET_ADDR_STRUCT(base,index)	(index-base)

//============== Usually usage: Literal constant value =====================//
#if 0
#ifndef TRUE
#define TRUE  		(1)
#endif
#ifndef FALSE
#define FALSE  		(0)
#endif

//Enable or Disable
#ifndef ENABLE
#define ENABLE		(0x1)
#endif

#ifndef DISABLE
#define DISABLE		(0x0)
#endif
#endif

#ifndef OK
#define	OK			(0x0)
#endif

#ifndef FAIL
#define	FAIL		(0x1)
#endif

#ifndef HIGH
#define HIGH      	(1)
#endif

#ifndef LOW
#define LOW       	(0)
#endif

#ifndef UNKNOWN
#define UNKNOWN    	(0xFF)
#endif

#ifndef NULL
#define NULL    	((void *)0)
#endif

#ifndef ON
#define ON			(1)
#endif

#ifndef OFF
#define OFF		 	(0)
#endif

#ifndef GPIO_HIGH
#define GPIO_HIGH  	(1)
#endif

#ifndef GPIO_LOW
#define GPIO_LOW    (0)
#endif

#ifndef  GARBAGE
// Windows 0xCC, Apple  0xA3,  ARM 0xA5
#define    GARBAGE	(0xA5)
#endif

typedef struct {
    unsigned bit0: 1;
    unsigned bit1: 1;
    unsigned bit2: 1;
    unsigned bit3: 1;
    unsigned bit4: 1;
    unsigned bit5: 1;
    unsigned bit6: 1;
    unsigned bit7: 1;
} BYTE_BITS;
typedef union {
    u8 BYTE_BIT;
    BYTE_BITS  bits;
} BYTE_TYPE;

typedef struct {
    unsigned bit00: 1;
    unsigned bit01: 1;
    unsigned bit02: 1;
    unsigned bit03: 1;
    unsigned bit04: 1;
    unsigned bit05: 1;
    unsigned bit06: 1;
    unsigned bit07: 1;
    unsigned bit08: 1;
    unsigned bit09: 1;
    unsigned bit10: 1;
    unsigned bit11: 1;
    unsigned bit12: 1;
    unsigned bit13: 1;
    unsigned bit14: 1;
    unsigned bit15: 1;
    unsigned bit16: 1;
    unsigned bit17: 1;
    unsigned bit18: 1;
    unsigned bit19: 1;
    unsigned bit20: 1;
    unsigned bit21: 1;
    unsigned bit22: 1;
    unsigned bit23: 1;
    unsigned bit24: 1;
    unsigned bit25: 1;
    unsigned bit26: 1;
    unsigned bit27: 1;
    unsigned bit28: 1;
    unsigned bit29: 1;
    unsigned bit30: 1;
    unsigned bit31: 1;
} WORD_BITS;
typedef union {
    u32 WORD_BIT;
    WORD_BITS bits;
} WORD_TYPE;

typedef struct {
    u8	a;
    u8	b;
    u16	c;
} MTRX2_U112_ST;

#if  DEVICE_CORE == __C51
#define IRQ_DISABLE_ALL		EAL=0;		//Global interrupt close
#define IRQ_ENABLE_ALL		EAL=1;		//Global interrupt open
#define code				code		//use code as code in C51
#define ALIGN_4							//Align is not availble in C51
#elif DEVICE_CORE == __ARM
#define IRQ_DISABLE_ALL		__disable_irq();
#define IRQ_ENABLE_ALL		__enable_irq();
#define xdata							//no ram type in MDK
#define idata
#define bdata
#define ALIGN_4				__align(4)	/*set address bit0=0 & bit1=0*/
#endif

#if 0
/* Bit Mask Definitions */
#ifndef BIT0
#define BIT0    0x00000001
#define BIT1    0x00000002
#define BIT2    0x00000004
#define BIT3    0x00000008
#define BIT4    0x00000010
#define BIT5    0x00000020
#define BIT6    0x00000040
#define BIT7    0x00000080
#define BIT8    0x00000100
#define BIT9    0x00000200
#define BIT10   0x00000400
#define BIT11   0x00000800
#define BIT12   0x00001000
#define BIT13   0x00002000
#define BIT14   0x00004000
#define BIT15   0x00008000
#define BIT16   0x00010000
#define BIT17   0x00020000
#define BIT18   0x00040000
#define BIT19   0x00080000
#define BIT20   0x00100000
#define BIT21   0x00200000
#define BIT22   0x00400000
#define BIT23   0x00800000
#define BIT24   0x01000000
#define BIT25   0x02000000
#define BIT26   0x04000000
#define BIT27   0x08000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000
#endif
#endif

#define _GET_OFFSET_STRUCT(structtype, indexname)	((u32)&(((structtype*)0)->indexname))



#endif

