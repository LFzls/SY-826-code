#include "mic_calibration.h"


#define ENTRY_FILTER_TIME   (10)
#define ENTRY_FILTER_CNT    (50)

#define TRIG_REDUNDANCY     (5)

#define CALITRATION_INFO_HEAD (0X55AA)


#define MTP_SIZE_826    (0x4000)
#define SECTOR_SIZE_826 (128)

#define MTP_SIZE_821    (0x1000)
#define SECTOR_SIZE_821 (64)

#define CHIP_MTP_SIZE     MTP_SIZE_826
#define CHIP_SECTOR_SIZE  SECTOR_SIZE_826

#define PARAMS_SAVE_ADDR  (CHIP_MTP_SIZE - CHIP_SECTOR_SIZE)
#define PARAMS_SIZE       CHIP_SECTOR_SIZE


typedef struct
{
    u16 head;
    u8  first_trig;   //unuse
    u8  second_trig;
} CALITRATION_INFO_T;

static idata  CALITRATION_INFO_T s_cali_info;

extern void WriteMtp(u16 addr, u8 dat);
extern u8 ReadMtp(u16 addr);


void mtp_write_full_word(u16 addr, u32 dat)   //这里需要注意地址必须是按全字对齐的，否则会有问题
{
    WriteMtp(addr, dat);
    dat >>= 8;
    WriteMtp(addr + 1, dat);
    dat >>= 8;
    WriteMtp(addr + 2, dat);
    dat >>= 8;
    WriteMtp(addr + 3, dat);
}

void mtp_read_buff(u16 addr, u8 * buffer, u16 len)
{
#if 0
    u16 i;

    if(addr + len > CHIP_MTP_SIZE)
    {
        len = CHIP_MTP_SIZE - addr;
    }

    for(i = 0; i < len; i++)
    {
        buffer[i] = ReadMtp(addr);
        addr++;
    }

#else
    buffer[3] = ReadMtp(addr);
    buffer[2] = ReadMtp(addr + 1);
    buffer[1] = ReadMtp(addr + 2);
    buffer[0] = ReadMtp(addr + 3);

#endif
}

void calitration_info_struct_init(CALITRATION_INFO_T * ptr)
{
    ptr->head = CALITRATION_INFO_HEAD;
    ptr->first_trig = 8;      //default value
    ptr->second_trig = 31;    //default value
}

u8  calibration_mode_entry(void)
{
    u8 entry_cnt = 0;

    plib_gpio_init(CFG_PIN_CALIBRATION_PORT, CFG_PIN_CALIBRATION_PINNUM, GPIO_PinMux_IO, GPIO_IOMode_IN_FLOATING, GPIO_PUPDMode_PD, GPIO_Driver_Strength);
    delay_ms(2);

    while(ENTRY_CALIBRATION_MODE)
    {
        if(++entry_cnt > ENTRY_FILTER_CNT)
        {
            entry_cnt = ENTRY_FILTER_CNT;
        }

        delay_ms(10);
        /* Feed wdt*/
        pmcu_wdt_feed();

    }

    if(entry_cnt >= ENTRY_FILTER_CNT)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

#define FIRST_TRIG_VALUE  (8)
#define SECOND_TRIG_MAX   (250)

// 如果未保存过，返回-1
s8 get_lastest_calibration_info(void)
{
    u8 index;
    CALITRATION_INFO_T tmp;

    for(index = 0; index < PARAMS_SIZE / sizeof(CALITRATION_INFO_T); index++)
    {
        //tmp = (CALITRATION_INFO_T *)(PARAMS_SAVE_ADDR+sizeof(CALITRATION_INFO_T) * index);
        mtp_read_buff((PARAMS_SAVE_ADDR + sizeof(CALITRATION_INFO_T) * index), (u8 *)&tmp, 4);
        tiny_printf("%d, %d\r\n", (u16)index, (u16)tmp.second_trig);

        if(tmp.head != CALITRATION_INFO_HEAD)
        {
            break;
        }
    }



    return index - 1;

}


void read_calibration_info(void)
{
    CALITRATION_INFO_T tmp ;
    s8 index = 0;
    index = get_lastest_calibration_info();

    if(index < 0)
    {
        tiny_printf("never save\r\n");
        return;
    }

    mtp_read_buff((PARAMS_SAVE_ADDR + sizeof(CALITRATION_INFO_T) * index), (u8 *)&tmp, 4);
    //ptr = (CALITRATION_INFO_T *)(PARAMS_SAVE_ADDR+ sizeof(CALITRATION_INFO_T) * index);
    tiny_printf("%d\r\n", (u16)index);
    tiny_printf("cali1: %d\r\n", (u16)tmp.first_trig);
    tiny_printf("cali2: %d\r\n", (u16)tmp.second_trig);


}

void do_calibration_save(CALITRATION_INFO_T * ptr)
{
    u16 target_addr = 0;
    s8 target_index = get_lastest_calibration_info() + 1;
    target_addr = PARAMS_SAVE_ADDR + target_index * sizeof(CALITRATION_INFO_T);
    mtp_write_full_word(target_addr, *(u32 *)ptr);
    tiny_printf("save: %d,0 %d\r\n", (u16)target_index, (u16)ptr->second_trig);
}

void start_calibration(void)
{
    u16 init = 0, cur = 0;
    u32 delta = 0;
    u16 trig_target = 0;
    u16 sum = 0, cnt = 0;

    init = plib_mic_get_init_value();

    while(1)
    {
        cur = plib_mic_get_cur_value();

        tiny_printf("%d, %d\r\n", init, cur);

        if(init > cur)
        {
            delta = init - cur;
        }
        else
        {
            delta = cur - init;
        }

        trig_target = (delta << 10) / init;     //计算变化率

        if(trig_target < FIRST_TRIG_VALUE)
        {
            sum = 0;
            cnt = 0;
            delay_ms(20);
            continue ;     //如果计算出来的第二阈值比第一阈值小，忽略此次校准
        }

        if(trig_target >= SECOND_TRIG_MAX)
        {
            trig_target -= 50;
        }

        tiny_printf("trig %d\r\n", trig_target);
        sum += trig_target;

        if(++cnt == 100)
        {
            s_cali_info.second_trig = sum / cnt;
            do_calibration_save(&s_cali_info);
            break;
        }

        delay_ms(20);
    }



}





void mtp_write_text(void)
{
    u8 i = 0;
    mtp_write_full_word(PARAMS_SAVE_ADDR, 0x55aa5a5a);

    for(i = 0; i < 4; i++)
    {
        tiny_printf("%02x ", ReadMtp(PARAMS_SAVE_ADDR + i) );
    }

    tiny_printf("\r\n");
}


void calibration_text(void)
{
    //mtp_write_text();
    read_calibration_info();
    calitration_info_struct_init(&s_cali_info);
    delay_ms(200);
    start_calibration();

    while (1)
    {

        delay_ms(100);
        pmcu_wdt_feed();
    }
}


