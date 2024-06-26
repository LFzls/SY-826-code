#include "util_filter.h"

/**
 * @brief Get the output value of the filter
 *
 * @param filter Pointer to the filter structure
 * @param indata Input data
 * @param cnt_div Count divisor
 * @param loop Loop flag, if set to 1, the count will loop
 * @return u8 Return value indicating whether the output value was successfully obtained (1 for success, 0 for failure)
 */
u8 filter_get(Filter_Typedef * filter, u16 indata, u8 cnt_div, u8 loop)
{
    filter->in = indata;

    if (loop)
    {
        filter->insum = 0;
        filter->count = 0;
    }

again:

    if (filter->count < cnt_div)
    {
        filter->insum += filter->in;
        filter->count += 1;

        if (loop)
        {
            goto again;
        }
    }
    else
    {
        filter->count = 0;
        filter->out = filter->insum / cnt_div;
        filter->insum = 0;

        return 1;
    }

    return 0;
}

/**
 * @brief Scan for changed bits in the input value
 *
 * This function compares the input value with the last recorded value in the given pipeline structure.
 * If the input value is different from the last value, it increases the filter counter.
 * When the filter counter reaches the specified filter value, it calculates the changed bits and updates the last value.
 * If the input value is the same as the last value, it resets the filter counter and returns 0.
 *
 * @param input The input value to be scanned for changed bits
 * @param piple Pointer to the input scan pipeline structure
 * @param filter The filter value used to determine when to calculate changed bits
 * @return u8 The changed bits between the current and last input value (0 if no change)
 */
u8 piple_change_scan(u8 input, struct piple_state * piple, u8 filter)
{
    u8 bits;

    if (input != piple->last)
    {
        if (++(piple->filter) >= filter)
        {
            bits = (piple->last) ^ input;
            piple->last = input;
        }
    }
    else
    {
        piple->filter = 0;
        bits = 0;
    }

    return bits;
}
