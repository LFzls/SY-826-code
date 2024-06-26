#ifndef __UTIL_FILTER_H__
#define __UTIL_FILTER_H__

#include "user_typedef.h"

#define FILTER_COUNT	16
typedef struct {
    u8	count;
    u16 in;
    u32 insum;
    u16 out;
} Filter_Typedef;

#define filter_clear(filter)		\
{								\
	filter.count=0;				\
	filter.insum=0;				\
}
enum {
    INPUT_NO_CHANGE,
    INPUT_RAISING,
    INPUT_FALLING,
};

struct piple_state {
    u8 last;
    u8 filter;
    u8 tate;
};


u8 piple_change_scan(u8 input, struct piple_state* piple, u8 filter);
u8 filter_get(Filter_Typedef* filter, u16 indata, u8 cnt_div, u8 loop);

#endif


