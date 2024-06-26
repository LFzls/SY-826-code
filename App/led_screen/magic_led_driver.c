#include "magic_led_driver.h"

SBIT(MAGIC_LED0_CTRL, 0x80 | (CFG_PIN_MAGIC_LED0_PORT << 4),  CFG_PIN_MAGIC_LED0_PINNUM);

/**
* @brief  Send one bit
* @param  Bit Value
* @retval None
* @par   Explanation
* None
*/
void magic_led_send_one_bit(u8 bit_value)
{
    if (bit_value != 1)
    {
        MAGIC_LED0_CTRL = 1;
        _nop_();
        MAGIC_LED0_CTRL = 0;
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
    }
    else
    {
        MAGIC_LED0_CTRL = 1;
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        _nop_();
        MAGIC_LED0_CTRL = 0;
    }
}

/**
* @brief  Reset led
* @param  None
* @retval None
* @par   Explanation
* None
*/
void magic_led_reset_led()
{
    MAGIC_LED0_CTRL = 1;
    MAGIC_LED0_CTRL = 0;
    delay10us(9);
}

/**
* @brief  Send 24 bit datas
* @param  RGB Value
* @retval None
* @par   Explanation
* G7 G6 G5 G4 G3 G2 G1 G0
* R7 R6 R5 R4 R3 R2 R1 R0
* B7 B6 B5 B4 B3 B2 B1 B0
*/
void magic_led_send_24bits(u32 grb_value)
{
    u8 i;

    for(i = 0; i < 24; i++)
    {
        if(grb_value & 0x800000)
        {
            magic_led_send_one_bit(1);
        }
        else
        {
            magic_led_send_one_bit(0);
        }

        grb_value = grb_value << 1;
    }
}

/**
* @brief  Magic led test
* @param  RGB Value
* @retval None
* @par   Explanation
* Put in 1ms timer
*/
void magic_led_test()
{
    static u16 cont;

    cont++;

    if(cont == 10)
    {
        magic_led_send_24bits(0xc0f0c0);
        magic_led_send_24bits(0x00);
        magic_led_send_24bits(0x00);
        magic_led_reset_led();
    }
    else if(cont == 200)
    {
        magic_led_send_24bits(0x00);
        magic_led_send_24bits(0xc0f0c0);
        magic_led_send_24bits(0x00);
        magic_led_reset_led();
    }
    else if(cont == 400)
    {
        magic_led_send_24bits(0x00);
        magic_led_send_24bits(0x00);
        magic_led_send_24bits(0xc0f0c0);
        magic_led_reset_led();
    }
    else if(cont == 600)
    {
        cont = 0;
    }
}
