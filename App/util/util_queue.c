#include "util_queue.h"

/* Global QueueEvent Parameters */
struct util_queue xdata g_event_queue;

/*
 * Purpose:    Pushes data to a FIFO (First-In, First-Out) queue function with overwrite when full
 *
 * Parameters:
 *     a - Data to be pushed to the FIFO
 *
 * Return Value:
 *     0: Successful push operation, but FIFO is full and the oldest data is removed
 *     1: Successful push operation and FIFO is in a normal state
 */
void util_queue_push(u8 a)
{
    g_event_queue.fifo[g_event_queue.in++] = a;

    if (g_event_queue.in >= UTIL_FIFO_SIZE)
    {
        g_event_queue.in = 0;
    }
}


/*
 * Purpose:    Pulls data from a FIFO (First-In, First-Out) queue function. Outputs the data in the order it was pushed.
 *
 * Parameters:
 *     queue - Pointer to the queue structure
 *
 * Return Value:
 *     key - The data that was pulled from the queue
 *
 * Remarks:
 *     If the FIFO is full, the pull operation may fail because the oldest data gets overwritten. However, for an event queue,
 *     it is typically not necessary to handle such exceptions since the FIFO being full is not considered in normal scenarios.
 */
u8 util_queue_pull(struct util_queue * queue)
{
    s16 outdata;

    if (queue->out == queue->in)
    {
        return (0x00);
    }

    outdata = queue->fifo[queue->out++];

    if (queue->out >= UTIL_FIFO_SIZE)
    {
        queue->out = 0;
    }

    return outdata;
}

