    #include "battery.h"
//fndskj
/* Global battery parameters */
idata struct battery_state g_battery;

#define SUB_LEVEL_PER               (10)
#define BAT_VOLT_LEVEL_MAX          (11)

code u16 bat_volt_map[BAT_VOLT_LEVEL_MAX] =
{
    3300,     //0
    3610,     //10
    3700,     //20
    3773,     //30
    3822,     //40
    3866,     //50
    3910,     //60
    3957,     //70
    4000,     //80
    4050,     //90
    4200,     //100
};

#define BAT_SUB_LEVEL_LSB(INDEX)  ( (bat_volt_map[INDEX+1] - bat_volt_map[INDEX])  / SUB_LEVEL_PER)
#define TABLES_LEN (sizeof(bat_volt_map) / sizeof(bat_volt_map[0]))
/*
 * Perform voltage sampling in a loop.
 */
void battery_get_volt(void)
{
    g_battery.advalue = pmcu_adc_sample_1ch_mul(ADC_CHN1_VBAT, 4);
    g_battery.volt.now = plib_adc_get_volt_div2(g_battery.advalue);
    g_battery.volt.idle = g_battery.volt.now;
}

void batlow_force_zero(void)
{
    g_userdata_t.real_level = g_userdata_t.show_level = 0;
}

void batfull_force_hundred(void)
{
    g_userdata_t.real_level = g_userdata_t.show_level = 100;
}

/*
 * Get the BAT init value
 */
void battery_get_volt_init(void)
{
    u8 temp_level;

    battery_get_volt();
    temp_level = battery_get_init_level();
    g_userdata_t.real_level = g_userdata_t.show_level = temp_level / CFG_BAT_STEP * CFG_BAT_STEP; //��ȡ��һ���ϵ��Ӧ�İٷֱȵ���
    g_battery.init_level = g_userdata_t.show_level;
}

/**
 * @brief update battery fire time
 *
 */
void battery_fire_time_update(void)
{
    if (util_timepass_check(&g_sys.time.timer_fire_update, CFG_BAT_FIRE_UPDATA_TIME))   // xms timer
    {
        g_battery.fire_time++;
    }
}

/*
 * Get the bat level
 */
u8 battery_get_init_level()
{
    u8 sub_level, temp_level;
    u8 i;
    u16 cal_use_volt, vol_diff;
    sub_level = temp_level = 0;

    //���ʱ����ȥ���̧���ĵ�ѹ
    if(USB_IS_IN_CHARGING)
    {
        cal_use_volt  = g_battery.volt.idle - CFG_BAT_DIFF_CHG;
    }
    else    //������ŵ�ʱ�����Ϸŵ����͵�ƫ��
    {
        cal_use_volt  = g_battery.volt.idle;
    }

    //���ҵ�ѹ�����ĸ�����
    for(i = 0; i < TABLES_LEN; i++)
    {
        if(cal_use_volt <= bat_volt_map[i])
        {
            break;
        }
    }

    if(cal_use_volt <= bat_volt_map[0] ) //С����͵���ѹ
    {
        temp_level = 0;
    }
    else if(cal_use_volt > bat_volt_map[TABLES_LEN - 1] ) //������ߵ���ѹ
    {
        temp_level = 100;
    }
    else
    {
        i -= 1;
        vol_diff = (cal_use_volt >= bat_volt_map[i])  ? (cal_use_volt - bat_volt_map[i])  : 0;
        sub_level =  vol_diff /  BAT_SUB_LEVEL_LSB(i);
        temp_level = i * SUB_LEVEL_PER + sub_level;

    }

    //AM_DBG_PRINTF("%d, %d, %d\r\n", (u16)i, (u16)sub_level, (u16)temp_level);

    return temp_level;
}

#define   BAT_LEVEL_BEFORE_FULL   (100 - CFG_BAT_STEP)
#define BAT_REAL_LEVEL_MAX  (100)
#define BAT_REAL_LEVEL_MIN  (1)
/*
 * Correct the bat level
 */
u8 get_battery_level()
{
    u8 temp_level, Percent_Dvol = 0, BatPercent_Revise = 0;

    //��ȡ��ǰ��ѹ��Ӧ�ĵ����ٷֱ�
    temp_level = battery_get_init_level();

    //���״̬���������� CFG_BAT_IDLE_UPDATA_TIME
    if(USB_IS_IN_CHARGING)
    {
        if(_ChgBit.hw_full || _ChgBit.sf_full)  //Ӳ���������������
        {
            //�Ѿ����䣬����û��ʾ100%���ӿ���µ�100%
            if(++g_battery.chg_time >= CFG_CHG_PRE100_UPDATA_TIME)
            {
                g_battery.chg_time = 0;

                if(g_userdata_t.show_level < 100)
                {
                    if(g_userdata_t.real_level < BAT_REAL_LEVEL_MAX)
                    {
                        g_userdata_t.real_level++;    //ֻ��1%���ϼ�
                    }

                    util_queue_push(EVENT_USB_CHRGING); //���µ���
                }
            }
        }
        else
        {
            //ʵ���ѹ�İٷֱȣ�������ĵİٷֱ�
            if(temp_level > g_userdata_t.real_level)
            {
                if(++g_battery.chg_time >= CFG_CHG_NOT_PRE100_UPDATA_TIME)
                {
                    g_battery.chg_time = 0;

                    //����絽99%����Ҫ�ȴ�оƬ�������źŲ�ָʾ���䣬��ʾ100%
                    if(g_userdata_t.show_level < 99)
                    {
                        if(g_userdata_t.real_level < BAT_REAL_LEVEL_MAX)
                        {
                            g_userdata_t.real_level++;    //ֻ��1%���ϼ�
                        }

                        util_queue_push(EVENT_USB_CHRGING);     //�������µ���
                    }
                }
            }
            else
            {
                g_battery.chg_time = 0;
            }
        }

        //ʵ�ʵ����ٷֱȲ�����������ʾ�İٷֱȣ�������ʾ
        if(g_userdata_t.real_level > g_userdata_t.show_level)
        {
            if(g_userdata_t.show_level + CFG_BAT_STEP <= g_userdata_t.real_level)
            {
                g_userdata_t.show_level += CFG_BAT_STEP;
            }

            //δ���䣬������ʾ100%
            if(g_userdata_t.real_level > BAT_LEVEL_BEFORE_FULL && (!_ChgBit.hw_full || !_ChgBit.sf_full))
            {
                g_userdata_t.show_level = BAT_LEVEL_BEFORE_FULL;
            }
        }
    }
    else    //�ǳ��״̬
    {
        if (g_userdata_t.show_level > 0)   //��ǰ��ʾ�İٷֱȴ���0
        {

            BatPercent_Revise = (g_battery.fire_time >= CFG_BAT_SUBB_PRE_1_TIME) ?  1 : 0;


            if(BatPercent_Revise)
            {
#if 0

                if (g_userdata_t.real_level > 1)
                {
                    if (g_userdata_t.real_level <= BatPercent_Revise)
                    {
                        g_userdata_t.real_level = 1;
                    }
                    else
                    {
                        //����Ҫ�󣺵��������ڵ�ѹ���ޣ������������ʾ��û��1%��ǿ����Сֻ�ܵ�1%�����磩
                        if(g_battery.volt.idle > CFG_BAT_UV_IDLE_THD && g_userdata_t.real_level <= 1)
                        {
                            g_userdata_t.real_level = 1;
                        }
                        else
                        {
                            g_userdata_t.real_level -= BatPercent_Revise;
                        }
                    }
                }

#else

                //����Ҫ�󣺵��������ڵ�ѹ���ޣ������������ʾ��û��1%��ǿ����Сֻ�ܵ�1%�����磩
                if (g_userdata_t.real_level - BatPercent_Revise >=  BAT_REAL_LEVEL_MIN)
                {
                    g_userdata_t.real_level -= BatPercent_Revise;
                }
                else
                {
                    g_userdata_t.real_level = BAT_REAL_LEVEL_MIN;
                }

#endif

                if(g_battery.fire_time >= CFG_BAT_SUBB_PRE_1_TIME)
                {
                    g_battery.fire_time -= CFG_BAT_SUBB_PRE_1_TIME;
                }

                //���ݵ����ٷֱȲ��������ض�Ӧ�ٷֱ�
                if(g_userdata_t.real_level < g_userdata_t.show_level)
                {
                    if(g_userdata_t.real_level < g_userdata_t.show_level - CFG_BAT_STEP)
                    {
                        g_userdata_t.show_level -= CFG_BAT_STEP;
                    }
                    else if ( (g_userdata_t.show_level - CFG_BAT_STEP <= BAT_REAL_LEVEL_MIN)  &&  \
                              (g_userdata_t.real_level == BAT_REAL_LEVEL_MIN) )
                    {
                        g_userdata_t.show_level -= CFG_BAT_STEP;
                    }

                    if(g_battery.volt.idle > CFG_BAT_UV_IDLE_THD && g_userdata_t.show_level <= CFG_BAT_STEP)
                    {
                        g_userdata_t.show_level = CFG_BAT_STEP;
                    }
                }
            }
        }
    }

    AM_DBG_PRINTF(">>V: %d, %d, %d, %d\r\n", (u16)g_battery.volt.idle, (u16)temp_level, (u16)g_userdata_t.real_level, (u16)g_userdata_t.show_level);
    return g_userdata_t.show_level;
}
