#ifndef __UTIL_QUEUE_H__
#define __UTIL_QUEUE_H__

#include "user_typedef.h"

#define UTIL_FIFO_SIZE 			8

struct util_queue {
    u8 fifo[UTIL_FIFO_SIZE];
    u8 out;
    u8 in;
};
extern struct util_queue xdata g_event_queue;

void util_queue_push(u8 a);
u8 util_queue_pull(struct util_queue* queue);

#endif
