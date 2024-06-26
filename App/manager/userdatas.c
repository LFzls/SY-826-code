#include "userdatas.h"

//#define DEBUG_OIL_LESS

/* USER DATA saved in the 32 bytes of XDATA（0xE0~0xFF） */
xdata USER_DATA_T g_userdata_t _at_ 0xE0;

/**
 * @brief Set the reset source
 */
void reset_src_set(void)
{
    //输出前，将rst_status设置为特定值
    g_userdata_t.rst_status = RST_POR_RAM;
}

/**
 * @brief Clear the reset source
 */
void reset_src_clear(void)
{
    //停止输出后，将rst_status清零
    g_userdata_t.rst_status = RST_LVR_RAM;
}

/**
 * @brief Get the reset reason after power on
 * @return 0xAA if reset reason is found, otherwise 0x00
 */
u8 reset_src_get(void)
{
	AM_DBG_PRINTF("rst=%08lx\r\n", (u32)g_userdata_t.rst_status);
	
    //在初始化的时候检查rst_status，如果rst_status等于RST_POR_RAM，则认为是输出中短路导致的lvr复位
    if (g_userdata_t.rst_status == RST_POR_RAM)
    {
        return RST_TYPE_LVR;
    }
    else
    {
        return RST_TYPE_NORMAL;
    }
}

/**
 * @brief Init userdatas tobe zero
 *
 */
void smoke_info_init(void)
{
    g_userdata_t.time = (u32)CFG_OIL_MAX * 1000 / CFG_OIL_UPDATA_TIME;
    g_userdata_t.work_time = 0;
    //AM_DBG_PRINTF("Max:%ld, Work:%ld\r\n", (u32)g_userdata_t.time, (u32)g_userdata_t.work_time);
}

/**
 * @brief update oil
 *
 */
void oil_value_update(void)
{
    if (util_timepass_check(&g_sys.time.timer_oil_update, CFG_OIL_UPDATA_TIME))   // xms timer
    {
        if (g_userdata_t.work_time < g_userdata_t.time)
        {
            g_userdata_t.work_time++;
        }
        else
        {
            g_userdata_t.work_time = g_userdata_t.time;
        }

//        AM_DBG_PRINTF("Oil:%ld, Smoke:%ld\r\n", (u32)g_userdata_t.time, (u32)g_userdata_t.work_time);
    }
}

/**
 * @brief get oil percentage
 *
 */
u8 get_oil_percentage(void)
{
#if defined(DEBUG_OIL_LESS)
    return 0;
#endif

    if(g_userdata_t.work_time >= g_userdata_t.time )
    {
        return 0;
    }

    return (u32)(g_userdata_t.time - g_userdata_t.work_time) * 100 / g_userdata_t.time;

}


