#include "charger_usb.h"

#define FALLING_CURRENT_STEP  (5) //降电流分档
#define S_FULL_VOLTAGE_CNT_PER  (CFG_CHG_FULL_TIMER/FALLING_CURRENT_STEP)

/* Global usb struct */
idata CHG_T g_chg_s;

/**
 * @brief Detect usb access
 */
static void usb_in_det(void)
{
    if(plib_chg_get_status(CHG_S_USB_IN))   //USB 插入
    {
        _ChgBit.in = 1;
    }
    else
    {
        _ChgBit.in = 0;
    }
}

/**
 * @brief Detect usb chg full
 */
static void usb_full_det(void)
{
    if(!_ChgBit.in)   //未插入，不检测满
    {
        return;
    }

    if(!plib_chg_ifen())    //充电禁止，不检测满
    {
        return;
    }

    if(plib_chg_get_status(CHG_S_FULL))
    {
        _ChgBit.hw_full = 1;
    }
    else
    {
        _ChgBit.hw_full = 0;
    }
}

/**
 * @brief USB charging control function.
 *        Controls the charging process based on the current USB state.
 */
void usb_charger_process(void)
{
    static u16 s_full_voltage_cnt;
    static u16 s_sub_curr_voltage_cnt;
    s8  falling_step, charg_iset, iset_max;
    //USB接入和满充检测
    usb_in_det();
    usb_full_det();

    switch (g_chg_s.chg_state)
    {
    case USB_STATE_USB_IDLE:
        if(_ChgBit.in)
        {
            _ChgBit.hw_full = 0;
            _ChgBit.sf_full = 0;

            plib_chg_en(PLIB_DISABLE);

            //吸烟中，不跳转到充电状态
            if(SYSTEM_FIRE_RUNNING == g_sys.status_sys)
            {
                break;
            }

            //USB接入解除锁机
#if CFG_SYS_UNLOCK_MODE==1
            util_queue_push(EVENT_LOCK_SYS);
#endif

            //防抖，解决USB过/欠压接入，先检测到USB接入，后检测到USB 过/欠压的问题
            if(++g_chg_s.in_cnt >= USB_IN_CNT_MAX)
            {
                g_chg_s.in_cnt = 0;

#if CFG_CHG_SUB_CUR_EN
                plib_chg_set_cc_current(CFG_CHG_ISET);
#endif

//              //方案要求：电池电压低于4.05V时，接入USB才开启充电
//                if(g_battery.volt.idle >= CFG_CHG_RECHG_VBAT_THD)
//                {
//                  AM_DBG_PRINTF("Bat>4050\r\n");
//                  //util_queue_push(EVENT_USB_FULL);
//                  //g_chg_s.chg_state = USB_STATE_USB_FULL;
//                    //关闭充电，等待下次接入USB重新开启
//                    plib_chg_en(PLIB_DISABLE);
//                  break;
//                }

                util_queue_push(EVENT_USB_CHRGING);
                g_chg_s.chg_state = USB_STATE_USB_CHRGING;
                plib_chg_en(PLIB_ENABLE);
            }
        }

        break;

    case USB_STATE_USB_CHRGING:
        if(_ChgBit.in)
        {
            if(_ChgBit.hw_full) //硬件满充
            {
                if(g_userdata_t.real_level >= 99)
                {
                    s_full_voltage_cnt = 0;
                    batfull_force_hundred();
                    util_queue_push(EVENT_USB_FULL);
                    g_chg_s.chg_state = USB_STATE_USB_FULL;
                }
            }

#if CFG_CHG_SUB_CUR_EN

            if(g_battery.volt.idle >= CFG_CHG_SUB_CUR_VBAT_THD)
            {
                if(++s_sub_curr_voltage_cnt >= CFG_CHG_SUB_CUR_TIMER)
                {
                    s_sub_curr_voltage_cnt = 0;
                    plib_chg_set_cc_current(CFG_CHG_SUB_CUR_ISET);
                }
            }

#endif

#if CFG_CHG_FULL_BY_SOFT_EN

            if(g_battery.volt.idle >= CFG_CHG_FULL_VBAT_THD)
            {
                s_full_voltage_cnt++;

                //AM_DBG_PRINTF("full cnt:%d\r\n", (u16)s_full_voltage_cnt);
                if(s_full_voltage_cnt >= CFG_CHG_FULL_TIMER)
                {
                    _ChgBit.sf_full = 1;

                    if(g_userdata_t.real_level >= 99)
                    {
                        s_full_voltage_cnt = 0;
                        batfull_force_hundred();
                        util_queue_push(EVENT_USB_FULL);
                        g_chg_s.chg_state = USB_STATE_USB_FULL;

                        plib_chg_en(PLIB_DISABLE);
                    }

                    //方案要求：满充后，常亮灯，软件判断满充，关闭充电，等待下次接入USB重新开启

                }

                falling_step = s_full_voltage_cnt / S_FULL_VOLTAGE_CNT_PER;

                if( 0 == (s_full_voltage_cnt % S_FULL_VOLTAGE_CNT_PER) )
                {
                    iset_max = (CFG_CHG_ISET > CHG_ISET_500MA) ? CHG_ISET_500MA : CFG_CHG_ISET;
                    charg_iset = iset_max - falling_step;

                    if( charg_iset < 0)
                    {
                        charg_iset = 0;
                    }

                    plib_chg_set_cc_current(charg_iset);
                }

            }

#endif
        }
        else
        {
            g_chg_s.chg_state = USB_STATE_USB_IDLE;
            util_queue_push(EVENT_USB_REMOVE);
        }

        break;

    case USB_STATE_USB_FULL:
        if(_ChgBit.in)
        {
#if CFG_CHG_FULL_BY_SOFT_EN

            //软件控制充电时，满充后，电压掉到复充电压时，继续充电，但不显示充电灯
            if(g_battery.volt.idle < CFG_CHG_RECHG_VBAT_THD)
            {
                util_queue_push(EVENT_USB_FULL);        //保持满充灯效
                g_chg_s.chg_state = USB_STATE_USB_RECHG;      //进入复充
                plib_chg_set_cc_current(CHG_ISET_400MA);
                plib_chg_en(PLIB_ENABLE);
//              util_queue_push(EVENT_USB_CHRGING);
//              g_chg_s.chg_state = USB_STATE_USB_CHRGING;
            }
            else if(g_battery.volt.idle >= CFG_CHG_RECHG_VBAT_THD)
            {
                //util_queue_push(EVENT_USB_FULL);
                //g_chg_s.chg_state = USB_STATE_USB_FULL;
                //方案要求：满充后，常亮灯，软件判断满充，关闭充电，等待下次接入USB重新开启
                plib_chg_en(PLIB_DISABLE);
            }

#endif
        }
        else
        {
            g_chg_s.chg_state = USB_STATE_USB_IDLE;
            util_queue_push(EVENT_USB_REMOVE);
        }

        break;

    case USB_STATE_USB_RECHG:
        if(_ChgBit.in)
        {
#if CFG_CHG_FULL_BY_SOFT_EN

            if(g_battery.volt.idle >= CFG_CHG_FULL_VBAT_THD)
            {
                s_full_voltage_cnt++;

                //AM_DBG_PRINTF("re full cnt:%d\r\n", (u16)s_full_voltage_cnt);
                if(s_full_voltage_cnt >= CFG_CHG_FULL_TIMER)
                {
                    s_full_voltage_cnt = 0;
                    util_queue_push(EVENT_USB_FULL);
                    g_chg_s.chg_state = USB_STATE_USB_FULL;

                    //方案要求：满充后，关闭充电
                    plib_chg_en(PLIB_DISABLE);
                }
            }

#endif

            if(_ChgBit.hw_full)
            {
                s_full_voltage_cnt = 0;
                util_queue_push(EVENT_USB_FULL);
                g_chg_s.chg_state = USB_STATE_USB_FULL;
            }
        }
        else
        {
            g_chg_s.chg_state = USB_STATE_USB_IDLE;
            util_queue_push(EVENT_USB_REMOVE);
        }

        break;

    default:
        g_chg_s.chg_state = USB_STATE_USB_IDLE;
        break;
    }
}
