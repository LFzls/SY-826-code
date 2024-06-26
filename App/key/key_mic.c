#include "key_mic.h"

//��������ʱ�����ֻ�������¼���Ӧһ�Σ��˺�����Ϊ1��
#define MULTI_KEY_ONLY_HANDLE_FIRST_PRESS_DOWN  0

/* Global key status */
idata struct key_det_s g_mic_s, g_key_s;
REV_MIC_STATUS_T g_rev_mic;         //����mic״̬

bit g_mic_fire_en;  //MIC����
bit g_key_fire_en;  //��������
bit g_key_power_on;  //���ڱ����ϵ�ʱ������״̬����ȷ�����Ű����ϵ磬���ᴥ������

/**
* @brief  Scans the key input and updates the key status accordingly.
* @retval None
* @par   Explanation
* This function is placed in a 10ms timer to poll
*/
u8 key_det(struct key_det_s * pkey, u8 state)
{
    u8 key_event = KEY_EVENT_NONE;

    if(state)
    {
        if(pkey->tick < KEY_TICK_MAX) //�������ΰ��£�������������
        {
            pkey->tick++;
            pkey->tim_up = KEY_TIM_UP_MIN;
        }
        else if (pkey->tick == KEY_TICK_MAX)  //����ȷ�ϱ�����
        {
			//��������ʱ���������һ�ΰ�����Ӧ�������¼���
#if MULTI_KEY_ONLY_HANDLE_FIRST_PRESS_DOWN
            if(!pkey->cnt)
#endif
            {
                key_event = KEY_EVENT_PRESS;
            }

            pkey->tick++;
            pkey->cnt++;
            pkey->tim_multi_countdown = KEY_TIM_UP_ACT;   //�������º����õ���ʱ
            pkey->is_down = 1;
            pkey->is_up = 0;
        }
        else //key_tick > KEY_TICK_MAX -->������ʱ
        {
            if(pkey->tim_down < KEY_TIM_DOWN_MAX)
            {
                pkey->tim_down++;    //������ʱ

            }
        }
    }
    else    //����δ���»��º��ͷ�
    {
        if(pkey->tick)//�����ͷŵ���ʱ
        {
            pkey->tick = pkey->tick / 2; //key_tick�ݼ�

            if(pkey->tim_up == 0) //ֻ��0��ʱ��ִ��һ��
            {
                pkey->tim_up++;
                key_event = KEY_EVENT_RELEASE;
                pkey->tim_down = 0; //�ͷ�����
            }
        }
        else    //ȷ���ͷ�
        {
            pkey->tim_down = KEY_TIM_DOWN_MIN;    //��������
            pkey->is_down = 0;
            pkey->is_up = 1;

            if(pkey->tim_up < KEY_TIM_UP_MAX)     //���������ʱ
            {
                pkey->tim_up++;
            }

            if(pkey->cnt == 0)    //�������ڵ���5�κ�������Ӧ�����ٵȴ���������
            {
                pkey->tim_up = 1;    //tim_up ����Ϊ��С������Ϊ0�����밴���ɿ��¼���ͻ
            }
        }
    }

    if(pkey->tim_multi_countdown)
    {
        pkey->tim_multi_countdown--;
    }

    //1.����ʱ�������Ұ����Ѿ��ͷ�
    //2.�����������ڵ���5�Σ�����ִ��
    if( ((0 == pkey->tim_multi_countdown) && (pkey->is_up))   || \
            (pkey->cnt >= 5) )
    {
        switch(pkey->cnt) //������������
        {
        case 1:
            key_event = KEY_EVENT_PRESS_X1;
            AM_DBG_PRINTF("x1+++\r\n");
            break;

        case 2:
            key_event = KEY_EVENT_PRESS_X2;
            AM_DBG_PRINTF("x2\r\n");
            break;

        case 3:
            key_event = KEY_EVENT_PRESS_X3;
            AM_DBG_PRINTF("x3\r\n");
            break;

        case 4:
            key_event = KEY_EVENT_PRESS_X4;
            AM_DBG_PRINTF("x4\r\n");
            break;

        case 5:
            key_event = KEY_EVENT_PRESS_X5;
            AM_DBG_PRINTF("x5\r\n");
            break;

        default:
            break;
        }

        pkey->cnt = 0;    //�����������
    }

    //������ʱ
    switch(pkey->tim_down)
    {
    case _KEY_DOWN_2S:
        key_event = KEY_EVENT_PRESS_LONG;
        pkey->cnt = 0;    //�����������
        break;

    default:
        break;
    }

    return key_event;
}

/**
* @brief  Scans the key input and updates the key status accordingly.
* @retval None
* @par   Explanation
* This function is placed in a 10ms timer to poll
*/
void mic_scan(void)
{
#if CFG_MIC_TYPE == 0   //������ͷ���
	
    if(plib_mic_get_flg(MIC_INHALE))
    {
		plib_mic_clr_flg(MIC_INHALE);
		g_mic_fire_en = 1;	
		g_rev_mic.start	= 1;		

		//��ȡ����ʱ�ĳ�ֵ
		g_userdata_t.mic_ini = plib_mic_get_init_value();		
        AM_DBG_PRINTF("Inhale\r\n");
    }
    else if(plib_mic_get_flg(MIC_INHALE_RELEASE))
    {
        plib_mic_clr_flg(MIC_INHALE_RELEASE);
        g_mic_fire_en = 0;
		AM_DBG_PRINTF("Inhale release\r\n");
		
        //���̺�һֱ���ͷţ�������Ӳ����ʱ
        //�����ͷ�ʱ���л�Ӳ������		
        if(g_rev_mic.hardware_ot)
        {
            g_rev_mic.hardware_ot = 0;

			plib_mic_ctrl_mode(MIC_CTRL_MODE_HW);
			AM_DBG_PRINTF("TO HW Ctrl\r\n");
        }
    }
    else if(plib_mic_get_flg(MIC_INHALE_TIMEOUT))
    {
        plib_mic_clr_flg(MIC_INHALE_TIMEOUT);
        g_mic_fire_en = 0;	
        tiny_printf("Inhale timeout\r\n");
		
		//���̺�һֱ���ͷţ�������Ӳ����ʱ���л���������ƣ���������ֵ����
        if(g_rev_mic.start)
        {
			g_rev_mic.start = 0;
            g_rev_mic.hardware_ot = 1;
			
			plib_mic_ctrl_mode(MIC_CTRL_MODE_SW);
			AM_DBG_PRINTF("TO SW Ctrl\r\n");
        }
    }	
    else if(plib_mic_get_flg(MIC_BLOW_RELEASE))
    {
        plib_mic_clr_flg(MIC_BLOW_RELEASE);
		
		//�����ͷ�ʱ�����л�Ӳ�����ƣ��ָ���ֵ���´���
		plib_mic_ctrl_mode(MIC_CTRL_MODE_HW);
		AM_DBG_PRINTF("Blow release\r\n");			
	}		
    else if(plib_mic_get_flg(MIC_BLOW))
    {
        //MIC���̵��¶�·��λ����λ��MICδ�ͷţ���ͬ�������ϵ磩ʱ������һ�γ�ֵ���Աܿ��������³�ֵ��10S
		if(g_sys.flg_lvr)
        {
			//�ȴ���ͷ�ָ��Ÿ��³�ֵ
			g_sys.flg_lvr_ref = 1;
			if(g_userdata_t.mic_ini <= (plib_mic_get_cur_value() + _MIC_RECOVER_THD))
			{
				g_sys.flg_lvr = 0;
				g_sys.flg_lvr_ref = 0;
				plib_mic_reflesh_ini_value();
				AM_DBG_PRINTF("lvr rel\r\n");				
			}
			else
			{
				AM_DBG_PRINTF("wait...\r\n");
				return;
			}
        }
		else
		{
			//��������ʱ�����л���������ƣ���������ֵ����
			plib_mic_ctrl_mode(MIC_CTRL_MODE_SW);
			AM_DBG_PRINTF("BLOW\r\n");	
		}	
		
		plib_mic_clr_flg(MIC_BLOW);
    }
	else
	{
		//����״̬����ͷ�ѻָ���ֱ������
		if(g_userdata_t.mic_ini <= (plib_mic_get_cur_value() + _MIC_RECOVER_THD))
		{
			g_sys.flg_lvr = 0;
		}
	}

#elif CFG_MIC_TYPE == 1   //������ͷ���

    if(plib_mic_get_flg(MIC_BLOW))
    {
        plib_mic_clr_flg(MIC_BLOW);
		
        g_mic_fire_en = 1;
        g_rev_mic.start = 1;
		
		//��ȡ����ʱ�ĳ�ֵ
		g_userdata_t.mic_ini = plib_mic_get_init_value();		
        AM_DBG_PRINTF("Blow\r\n");
    }
    else if(plib_mic_get_flg(MIC_BLOW_RELEASE))
    {
        plib_mic_clr_flg(MIC_BLOW_RELEASE);
        g_mic_fire_en = 0;
		AM_DBG_PRINTF("Blow release\r\n");
		 
		//��������������ʱ���µ������ͷţ�������
		if(!plib_mic_get_flg(MIC_REFLESH_VALUE))
		{
			g_rev_mic.start = 0;
			g_rev_mic.hardware_ot = 0;
			
			AM_DBG_PRINTF("Blow Clear\r\n");
		}			
    }
    else if(plib_mic_get_flg(MIC_REFLESH_VALUE))
    {
        plib_mic_clr_flg(MIC_REFLESH_VALUE);

		//��������һֱ���ͷţ�����Ӳ�����̳�ʱ
        if(g_rev_mic.start)
        {
			g_rev_mic.start = 0;
            g_rev_mic.hardware_ot = 1;
			AM_DBG_PRINTF("hwot\r\n");
        }
    }
    else if(plib_mic_get_flg(MIC_INHALE_RELEASE))
    {
        plib_mic_clr_flg(MIC_INHALE_RELEASE);
		
		//�����ͷ�ʱ�����л�Ӳ�����ƣ��ָ���ֵ���´���
		plib_mic_ctrl_mode(MIC_CTRL_MODE_HW);
		AM_DBG_PRINTF("Blow release\r\n");		
	}		
    else if(plib_mic_get_flg(MIC_INHALE))
    {
        if(g_rev_mic.hardware_ot)       //�����䳬ʱ�ͷţ����³�ֵ
        {
            plib_mic_reflesh_ini_value();
            g_rev_mic.hardware_ot = 0;
			AM_DBG_PRINTF("To rel\r\n");
        }
        //MIC���̵��¶�·��λ����λ��MICδ�ͷţ���ͬ�ڴ����ϵ磩ʱ������һ�γ�ֵ���Աܿ��������³�ֵ�ĳ�ʱʱ��
		else if(g_sys.flg_lvr)
        {
			//�ȴ���ͷ�ָ��Ÿ��³�ֵ
			g_sys.flg_lvr_ref = 1;
			if((g_userdata_t.mic_ini + _MIC_RECOVER_THD) >= plib_mic_get_cur_value())
			{
				g_sys.flg_lvr = 0;
				g_sys.flg_lvr_ref = 0;
				plib_mic_reflesh_ini_value();
				AM_DBG_PRINTF("lvr rel\r\n");				
			}
			else
			{
				AM_DBG_PRINTF("wait...\r\n");
				return;
			}			
        }
        else //�����������������
        {
			//��������ʱ�����л���������ƣ���������ֵ����
			plib_mic_ctrl_mode(MIC_CTRL_MODE_SW);
			AM_DBG_PRINTF("BLOW\r\n");
        }
		
        plib_mic_clr_flg(MIC_INHALE);		
    }
	else
	{
		//����״̬����ͷ�ѻָ���ֱ������
		if((g_userdata_t.mic_ini + _MIC_RECOVER_THD) >= plib_mic_get_cur_value())
		{
			g_sys.flg_lvr = 0;
		}
	}	

#else //���߿�����ͷ���
    g_mic_fire_en = _PIN_MIC;

#endif   /* end of #if CFG_MIC_TYPE == 0 */

    switch(key_det(&g_mic_s, g_mic_fire_en))
    {
    case KEY_EVENT_PRESS:

        //���Ű����ϵ磬����������
        if(g_key_power_on)
        {
            break;
        }

        util_queue_push(EVENT_MIC_START);
        AM_DBG_PRINTF("mic_start\r\n");
        break;

    case KEY_EVENT_RELEASE:
        g_key_power_on = 0;
        util_queue_push(EVENT_MIC_STOP);
        AM_DBG_PRINTF("mic stop\r\n");
        break;

    case KEY_EVENT_PRESS_X3:
#if CFG_MIC_LOCK_CNT != 0
        util_queue_push(EVENT_LOCK_CHILD);
#endif

    default:
        break;
    }
}

/**
* @brief  Scans the key input and updates the key status accordingly.
* @retval None
* @par   Explanation
* This function is placed in a 10ms timer to poll
*/
void key_scan(void)
{
    //��ȡ��������״̬
	g_key_fire_en = _GET_PIN_KEY();
	
    switch(key_det(&g_key_s, g_key_fire_en))
    {
    case KEY_EVENT_PRESS:
        AM_DBG_PRINTF("down\r\n");
        util_queue_push(EVENT_KEY_PRESS);
        break;

    case KEY_EVENT_RELEASE:
        AM_DBG_PRINTF("up\r\n");
        util_queue_push(EVENT_KEY_RELEASE);
        g_key_power_on = 0;
        break;

    case KEY_EVENT_PRESS_X1:
        util_queue_push(EVENT_PRESS_x1);
        break;

    case KEY_EVENT_PRESS_X2:
        break;

    case KEY_EVENT_PRESS_X3:
#if CFG_KEY_LOCK_CNT != 0
        util_queue_push(EVENT_LOCK_CHILD);
#endif
        break;

    case KEY_EVENT_PRESS_X4:
        break;

    case KEY_EVENT_PRESS_X5:
        break;

    case KEY_EVENT_PRESS_LONG:
        break;

    default:
        break;
    }
}
