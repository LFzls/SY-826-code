#include "screen_x1_driver.h"

xdata LEDSCREEN_STATUS_U g_screen_status_u;

code u8 g_num_code[] =
{
    0x3f,   //0
    0x06,   //1
    0x5b,   //2
    0x4f,   //3
    0x66,   //4
    0x6d,   //5
    0x7d,   //6
    0x07,   //7
    0x7f,   //8
    0x6f,   //9
    0x77,   //A
    0x7c,   //B
    0x39,   //C
    0x5e,   //D
    0x79,   //E
    0x71    //F
};


void LEDSCREEN_STATUS_CLEAR(u32 MASK, u32 MASK2)
{
    g_screen_status_u.hex[0] &= ~MASK;
    g_screen_status_u.hex[1] &= ~MASK2;
}


void LEDSCREEN_SET_STATUS(u32 MASK, u32 MASK2)
{
    g_screen_status_u.hex[0] = MASK;
    g_screen_status_u.hex[1] = MASK2;
}

/**
* @brief  Set the output according to the value of each segment of the digital tube
* @param  com Control the pins of the Nixie tube, choose one from the following: \n
* @ref COM_1    \n
* @ref COM_2    \n
* @ref COM_3    \n
* @ref COM_4    \n
* @ref COM_5    \n
* @param  bitstate Controls the output level of the pin of the Nixie tube
* @retval None
* @par   Explanation
* None
*/
static void com_set_mode_by_state(COM_E com, bit bitstate)
{
    switch (com)
    {
    case COM_1:
        if(bitstate)
        {
            SET_COM_OUTVALUE(CFG_PIN_COM1_PORT, CFG_PIN_COM1_PINNUM, PLIB_HIGH);
        }

        break;

    case COM_2:
        if(bitstate)
        {
            SET_COM_OUTVALUE(CFG_PIN_COM2_PORT, CFG_PIN_COM2_PINNUM, PLIB_HIGH);
        }

        break;

    case COM_3:
        if(bitstate)
        {
            SET_COM_OUTVALUE(CFG_PIN_COM3_PORT, CFG_PIN_COM3_PINNUM, PLIB_HIGH);
        }

        break;

    case COM_4:
        if(bitstate)
        {
            SET_COM_OUTVALUE(CFG_PIN_COM4_PORT, CFG_PIN_COM4_PINNUM, PLIB_HIGH);
        }

        break;

    case COM_5:
        if(bitstate)
        {
            SET_COM_OUTVALUE(CFG_PIN_COM5_PORT, CFG_PIN_COM5_PINNUM, PLIB_HIGH);
        }

        break;

    default:
        break;
    }
}

/**
* @brief  Control of the Nixie tube H1
* @param  on Controls the output level of the pin
* @retval None
* @par   Explanation
* None
*/
void screen_set_smoke_bit(bit on)
{
    g_screen_status_u.dig[0].h = on;
}

/**
* @brief  Control of the Nixie tube H2
* @param  on Controls the output level of the pin
* @retval None
* @par   Explanation
* None
*/
void screen_set_charge_bit(bit on)
{
    g_screen_status_u.dig[1].h = on;
}

/**
* @brief  Set the value to be displayed by the digital tube
* @param  num The numeric value to display
* @retval None
* @par   Explanation
* None
*/
void screen_set_display_num(s8 num)
{
    xdata u16 temp_num = 0;

    if( num < LED_PERCENT_MIN )
    {
        g_screen_status_u.hex[0] &= ~(DIGITAL_NUM_MASK);
        return;
    }

    if( num > LED_PERCENT_MAX)
    {
        num = LED_PERCENT_MAX;
    }

    g_screen_status_u.hex[0] &= ~(DIGITAL_NUM_MASK);

    //ones place
    temp_num |= g_num_code[num % 10];
    //tens place
    temp_num |= (((u16)(g_num_code[num / 10 % 10] )) << 8);

    //hundreds place
    if(num / 100)
    {
        //赋值对应的段即可
    }
    else
    {
        //赋值对应的段即可
    }

    g_screen_status_u.hex[0] |= (((u32)temp_num ) << 16);
}

/**
* @brief  Marquee
* @param  None
* @retval None
* @par   Explanation
* NONE
*/
void screen_set_marquee(MARQUEE_MASS_E marquee_mass)
{
    //A1-->A2-->B2-->C2-->D2-->D1-->E1-->F1-->A1
    switch (marquee_mass)
    {
    case MARQUEE_MASS_0:
        g_screen_status_u.dig[0].a = 1;
        g_screen_status_u.dig[1].a = 0;
        g_screen_status_u.dig[1].b = 0;
        g_screen_status_u.dig[1].c = 0;
        g_screen_status_u.dig[1].d = 0;
        g_screen_status_u.dig[0].d = 0;
        g_screen_status_u.dig[0].e = 0;
        g_screen_status_u.dig[0].f = 0;
        break;

    case MARQUEE_MASS_1:
        g_screen_status_u.dig[0].a = 0;
        g_screen_status_u.dig[1].a = 1;
        g_screen_status_u.dig[1].b = 0;
        g_screen_status_u.dig[1].c = 0;
        g_screen_status_u.dig[1].d = 0;
        g_screen_status_u.dig[0].d = 0;
        g_screen_status_u.dig[0].e = 0;
        g_screen_status_u.dig[0].f = 0;
        break;

    case MARQUEE_MASS_2:
        g_screen_status_u.dig[0].a = 0;
        g_screen_status_u.dig[1].a = 0;
        g_screen_status_u.dig[1].b = 1;
        g_screen_status_u.dig[1].c = 0;
        g_screen_status_u.dig[1].d = 0;
        g_screen_status_u.dig[0].d = 0;
        g_screen_status_u.dig[0].e = 0;
        g_screen_status_u.dig[0].f = 0;
        break;

    case MARQUEE_MASS_3:
        g_screen_status_u.dig[0].a = 0;
        g_screen_status_u.dig[1].a = 0;
        g_screen_status_u.dig[1].b = 0;
        g_screen_status_u.dig[1].c = 1;
        g_screen_status_u.dig[1].d = 0;
        g_screen_status_u.dig[0].d = 0;
        g_screen_status_u.dig[0].e = 0;
        g_screen_status_u.dig[0].f = 0;
        break;

    case MARQUEE_MASS_4:
        g_screen_status_u.dig[0].a = 0;
        g_screen_status_u.dig[1].a = 0;
        g_screen_status_u.dig[1].b = 0;
        g_screen_status_u.dig[1].c = 0;
        g_screen_status_u.dig[1].d = 1;
        g_screen_status_u.dig[0].d = 0;
        g_screen_status_u.dig[0].e = 0;
        g_screen_status_u.dig[0].f = 0;
        break;

    case MARQUEE_MASS_5:
        g_screen_status_u.dig[0].a = 0;
        g_screen_status_u.dig[1].a = 0;
        g_screen_status_u.dig[1].b = 0;
        g_screen_status_u.dig[1].c = 0;
        g_screen_status_u.dig[1].d = 0;
        g_screen_status_u.dig[0].d = 1;
        g_screen_status_u.dig[0].e = 0;
        g_screen_status_u.dig[0].f = 0;
        break;

    case MARQUEE_MASS_6:
        g_screen_status_u.dig[0].a = 0;
        g_screen_status_u.dig[1].a = 0;
        g_screen_status_u.dig[1].b = 0;
        g_screen_status_u.dig[1].c = 0;
        g_screen_status_u.dig[1].d = 0;
        g_screen_status_u.dig[0].d = 0;
        g_screen_status_u.dig[0].e = 1;
        g_screen_status_u.dig[0].f = 0;
        break;

    case MARQUEE_MASS_7:
        g_screen_status_u.dig[0].a = 0;
        g_screen_status_u.dig[1].a = 0;
        g_screen_status_u.dig[1].b = 0;
        g_screen_status_u.dig[1].c = 0;
        g_screen_status_u.dig[1].d = 0;
        g_screen_status_u.dig[0].d = 0;
        g_screen_status_u.dig[0].e = 0;
        g_screen_status_u.dig[0].f = 1;
        break;

    default:
        g_screen_status_u.dig[0].a = 0;
        g_screen_status_u.dig[1].a = 0;
        g_screen_status_u.dig[1].b = 0;
        g_screen_status_u.dig[1].c = 0;
        g_screen_status_u.dig[1].d = 0;
        g_screen_status_u.dig[0].d = 0;
        g_screen_status_u.dig[0].e = 0;
        g_screen_status_u.dig[0].f = 0;
        break;
    }
}

/**
* @brief  The Nixie tube displays polling refresh
* @param  None
* @retval None
* @par   Explanation
* -# Place in a 1ms timer for refresh
*/
void screen_driver_scan_loop(void)
{
    static xdata COM_E scan_com = COM_1;
    static xdata u8 cnt = 0;

    LED_ALLCOM_SET_NONE();

    switch(scan_com)
    {
    case COM_1:
        SET_COM_OUTVALUE(CFG_PIN_COM1_PORT, CFG_PIN_COM1_PINNUM, PLIB_LOW);

        switch(cnt)
        {
        case 0:
            com_set_mode_by_state(COM_2, g_screen_status_u.dig[0].a);
            break;  //A1

        case 1:
            com_set_mode_by_state(COM_3, g_screen_status_u.dig[0].b);
            break;  //B1

        case 2:
            com_set_mode_by_state(COM_4, g_screen_status_u.dig[0].c);
            break;  //C1

        case 3:
            com_set_mode_by_state(COM_5, g_screen_status_u.dig[0].d);
            break;  //D1

        default:
            break;
        }

        break;

    case COM_2:
        SET_COM_OUTVALUE(CFG_PIN_COM2_PORT, CFG_PIN_COM2_PINNUM, PLIB_LOW);

        switch(cnt)
        {
        case 0:
            com_set_mode_by_state(COM_1, g_screen_status_u.dig[0].e);
            break;  //E1

        case 1:
            com_set_mode_by_state(COM_3, g_screen_status_u.dig[0].f);
            break;  //F1

        case 2:
            com_set_mode_by_state(COM_4, g_screen_status_u.dig[0].g);
            break;  //G1

        case 3:
            com_set_mode_by_state(COM_5, g_screen_status_u.dig[1].a);
            break;  //A2

        default:
            break;
        }

        break;

    case COM_3:
        SET_COM_OUTVALUE(CFG_PIN_COM3_PORT, CFG_PIN_COM3_PINNUM, PLIB_LOW);

        switch(cnt)
        {
        case 0:
            com_set_mode_by_state(COM_1, g_screen_status_u.dig[1].b);
            break;   //B2

        case 1:
            com_set_mode_by_state(COM_2, g_screen_status_u.dig[1].c);
            break;   //C2

        case 2:
            com_set_mode_by_state(COM_4, g_screen_status_u.dig[1].d);
            break;   //D2

        case 3:
            com_set_mode_by_state(COM_5, g_screen_status_u.dig[1].e);
            break;   //E2

        default:
            break;
        }

        break;

    case COM_4:
        SET_COM_OUTVALUE(CFG_PIN_COM4_PORT, CFG_PIN_COM4_PINNUM, PLIB_LOW);

        switch(cnt)
        {
        case 0:
            com_set_mode_by_state(COM_1, g_screen_status_u.dig[1].f);
            break;   //F2

        case 1:
            com_set_mode_by_state(COM_2, g_screen_status_u.dig[1].g);
            break;   //G2

        case 2:
            com_set_mode_by_state(COM_3, g_screen_status_u.dig[0].h);
            break;   //H1

        case 3:
            com_set_mode_by_state(COM_5, g_screen_status_u.dig[1].h);
            break;   //H2

        default:
            break;
        }

        break;

    default:
        break;
    }

    if( ++cnt == 4 )
    {
        cnt = 0;

        if( ++scan_com == COM_NUM )
        {
            scan_com = COM_1;
        }
    }
}
