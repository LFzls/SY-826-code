#ifndef __USER_CONFIG_H__
#define __USER_CONFIG_H__

// <<< Use Configuration Wizard in Context Menu >>>

//	<s> 配置功能版本号
	#define UI_SW_VERSION "PMCU V6.30"

// <h> 系统配置
	// <o> 欠压复位门限
		// <i>默认: 2
		// <0=> 2.3V
		// <1=> 2.4V
		// <2=> 2.5V
		// <3=> 2.6V
		#define CFG_SYS_UVLS           	0
	// <e> 欠压复位提示
		#define CFG_SYS_UVLS_EN 		1		
	// </e>		
	// <e> 休眠长时间进入
		#define CFG_LONG_SLEEP_EN 			1
		// <o> 长时间无动作，进入休眠时间(ms)
			#define CFG_LONG_SLEEP_TIME 	3000 	
		// <h> 睡眠唤醒源配置
			// <i>默认: 0x00
			// <q.7> WK_SRC_TIMER：定时唤醒(需配置定时时间)
			// <q.4> WK_SRC_MIC：MIC事件唤醒(需配置MIC事件中断)
			// <q.3> WK_SRC_CHG_FULL：充电满充唤醒
			// <q.2> WK_SRC_USB：USB插拔唤醒
			// <q.1> WK_SRC_PLUG：负载插拔唤醒
			// <q.0> WK_SRC_GPIO：GPIO边沿唤醒(需配置GPIO边沿中断)
			#define CFG_WK_SRC		        0x15
		// </h>	
		// <o> 定时唤醒时间配置
			// <i> 默认: 0
			// <0-127>		
			#define CFG_WK_SRC_TIME 			0 			
	// </e>
	// <e> 看门狗功能开启
		#define CFG_WDT_EN 			1
		// <o> 看门狗溢出时间(ms)
			// <i> 默认: 0
			// <1-1500>	
			#define CFG_WDT_TIME 	100 			
	// </e>	
	// <e> 系统锁机
		#define CFG_SYS_LOCK_EN 			0
		// <o> 锁机方式
			// <i>默认: 0
			// <0=> 不锁机
			// <1=> 初次上电锁机
			#define CFG_SYS_LOCK_MODE		1
		// <o> 解锁方式
			// <i>默认: 0
			// <0=> 不锁机
			// <1=> USB接入
			// <2=> 按键5次
			// <3=> 连续吸烟3次
			#define CFG_SYS_UNLOCK_MODE		1
	// </e>
	// <e> 吸烟超时保护(软件定时)
		#define CFG_SMOKE_TIMEOUT_EN 		1
		// <o> 吸烟超时保护时间（ms）
			// <i> 默认: 0
			#define CFG_SMOKE_TIMEOUT_TIME 	8000 
	// </e>	
	// <h> 系统中断配置(不使用的关闭，省代码空间)
		// <e> MIC事件中断
			#define CFG_IT_MIC_EN		0
		// </e>	
		// <e> ADC采样完成中断
			#define CFG_IT_ADC_EN		0
		// </e>		
		// <e> 充电中断
			#define CFG_IT_CHG_EN		0
		// </e>			
		// <e> GPIO边沿中断
			#define CFG_IT_GPIO_EN		0
		// </e>			
		// <e> PWM边沿中断
			#define CFG_IT_PWM_EN		1
		// </e>			
		// <e> MOS异常中断
			#define CFG_IT_MOS_ABN_EN	0
		// </e>		
		// <e> UART中断
			#define CFG_IT_UART_EN	0
		// </e>				
	// </h>			
// </h>

// <h> MIC配置
	// <e> MIC 功能使能
		#define CFG_MIC_EN							2
		// <o> MIC类型
			// <i>默认: 0
			// <0=> 正向空咪
			// <1=> 反向空咪
			// <2=> 三线开关咪
			#define CFG_MIC_TYPE					0		
		// <o> 三线开关咪检测使用的GPIO组
			// <i>默认: 1
			// <0x01=> GPIOA组
			// <0x02=> GPIOB组
			// <0x04=> GPIOC组
			#define CFG_PIN_MIC_PORT			0x02
		// <o> 三线开关咪检测使用的GPIO号
			// <i>默认: 1
			// <0x01=> PIN0
			// <0x02=> PIN1
			// <0x04=> PIN2
			// <0x08=> PIN3
			#define CFG_PIN_MIC_PINNUM			0x01				
		// <e> MIC允许触发吸烟
			#define CFG_MIC_FIRE_EN					1
		// </e>		
		// <e> MIC反吹检测使能
			#define CFG_MIC_BLOW_EN					0			
		// </e>			
		// <h> MIC模块参数
			// <o> 设置咪头工作电流(电容)
				// <i>默认: 160nA
				// <0x00=> 160nA
				// <0x08=> 320nA
				#define CFG_MIC_MIC_CURR        	0x08
			// <o> 设置MIC采样时间
				// <i>默认: 45ms
				// <0x00=> 45ms
				// <0x20=> 35ms
				// <0x40=> 23ms
				// <0x60=> 57ms
				#define CFG_MIC_SAMPLE_TIME        	 0x00
			// <o> 设置MIC吸烟超时时间（硬件定时）
				// <i>默认: 20s
				// <0=> 2.5s
				// <1=> 5s
				// <2=> 10s
				// <3=> 20s
				#define CFG_MIC_INHALE_TIMEOUT		  3
			// <h> 配置MIC中断使能（同时作为睡眠唤醒源）
				// <i>默认: 吸气，吹气
				// <q.5> MIC_BLOW：咪头吹气和吹气释放
				// <q.4> MIC_INHALE_TIMEOUT：咪头吸气超时
				// <q.3> MIC_INHALE_RELEASE：咪头吸气释放
				// <q.2> MIC_INHALE：咪头吸气
				// <q.1> MIC_REFLESH_VALUE：咪头初值更新
				#define CFG_MIC_IT		        	0x2C
			// </h>
			// <o> MIC吸烟触发阈值1
				// <i> 默认: 8
				// <0-31>
				#define CFG_MIC_TRIG1_THD             8
			// <o> MIC吸烟触发阈值2
				// <i> 默认: 31
				// <0-255>
				#define CFG_MIC_TRIG2_THD             31
		// </h>		
		// <h> MIC连续触发
			// <o> 咪头预热触发模式（未实现预热）
				// <i>默认: 2
				// <0x00=> 关闭
				// <0x02=> 2次					
				// <0x03=> 3次
				#define CFG_MIC_PREFIRE_CNT		0
			// <o> 咪头换挡触发模式（未实现换挡）
				// <i>默认: 3
				// <0x00=> 关闭
				// <0x03=> 3次
				#define CFG_MIC_MODE_SW_CNT		0
			// <o> 咪头童锁触发模式
				// <i>默认: 5
				// <0x00=> 关闭
				// <0x03=> 3次
				// <0x05=> 5次
				#define CFG_MIC_LOCK_CNT		0x00	
		// </h>
	// </e>		
// </h>

// <h> 按键配置
	// <e> 按键功能启用
		#define CFG_KEY_EN						1
		// <o> 按键检测使用的GPIO组
			// <i>默认: 1
			// <0x01=> GPIOA组
			// <0x02=> GPIOB组
			// <0x04=> GPIOC组
			#define CFG_PIN_KEY_PORT			0x02
		// <o> 按键检测使用的GPIO号
			// <i>默认: 1
			// <0x01=> PIN0
			// <0x02=> PIN1
			// <0x04=> PIN2
			// <0x08=> PIN3
			#define CFG_PIN_KEY_PINNUM			0x01
		// <o> 按键输入有效电平
			// <i>默认: 0
			// <0=> 低电平有效
			// <1=> 高电平有效
			#define CFG_PIN_KEY_VALUE_TYPE		0			
		// <e> 按键GPIO输入边沿中断使能（可作为睡眠唤醒源）
			#define CFG_PIN_IT_EN				1	
		// </e>			
		// <e> 按键允许触发吸烟
			#define CFG_KEY_FIRE_EN				1
		// </e>
		// <o> 预热触发模式（未实现预热）
			// <i>默认: 2
			// <0x00=> 关闭
			// <0x02=> 2次
			#define CFG_KEY_PREFIRE_CNT			0
		// <o> 换挡触发模式（未实现换挡）
			// <i>默认: 3
			// <0x00=> 关闭
			// <0x03=> 3次
			#define CFG_KEY_MODE_SW_CNT			0
		// <o> 童锁触发模式
			// <i>默认: 5
			// <0x00=> 关闭
			// <0x03=> 3次
			// <0x05=> 5次
			#define CFG_KEY_LOCK_CNT			0x00			
	// </e>
// </h>

// <h> 定时器配置
	// <e> 设置TIME0使能
		// <i>默认: 使能
		#define CFG_TIM0_EN          1          
		// <o> 定时器0设置中断时间（us）
			// <i> 默认：1000us
			// <i> 最大设置49000us（49ms）
			// <1-49000>
			#define CFG_TIM0_CNT           	200  
	// </e>
	// <e> 设置TIME1使能
		// <i>默认: 使能
		#define CFG_TIM1_EN          1 
			#define CFG_TIM1_MODE         	2 
		// <o> 定时器1设置中断时间（us）
			// <i> 默认：1000us
			// <i> 最大设置49000us（49ms）
			// <1-49000>
			#define CFG_TIM1_CNT           	100  
	// </e>
// </h>

// <h> 功率输出配置
	// <o> 功率输出路数
		// <i> 默认：单路
		// <1=> 单发，仅内部MOS
		// <2=> 单发，仅外部MOS
		// <3=> 双发，内外MOS两路
		#define CFG_VOUT_CNH_MAX           			1 
	// <h> 内部MOS配置
		// <h> 内部MOS异常保护配置					
			// <o> 内部MOS过流保护阀值
				// <i>默认: 7A
				// <0=> 4A
				// <1=> 5A
				// <2=> 6A
				// <3=> 7A
				#define CFG_MOS_OCP_THD				3
			// <e> 内部MOS输出过流保护使能
				#define CFG_MOS_OCP_EN				1     
			// </e>
			// <e> 内部MOS输出过温保护使能
				#define CFG_MOS_OTP_EN				1    
			// </e>
		// </h>
		// <e> 外扩MOS增强输出（MOS_EXT控制，与内部MOS并联）
			// <i> 默认:失能
			#define CFG_MOSEXT_EN				0		
			// <o> 设置内/外MOS功率管上升/下降斜率1
				// <i>默认: 最快
				// <0=> 最快
				// <1=> 较快
				// <2=> 较慢
				// <3=> 最慢
				#define CFG_MOS_GRADE_SPEED1            0 
			// <o> 设置内/外MOS功率管上升/下降斜率2
				// <i>默认: 最快
				// <0=> 斜率1*1
				// <1=> 斜率1*2
				#define CFG_MOS_GRADE_SPEED2    		0 
		// </e>
		// <h> 内部MOS输出参数配置
			// <o> 内部MOS PWM输出周期
				// <i> 默认：61(1000Hz)
				// <i> 输出频率=1000000/输出周期，最大设置20000（50Hz），最小设置20（50000Hz）
				// <20-20000>
				#define CFG_MOS_PWM_PERIOD      		20000
			// <o> 内部MOS输出模式
				// <i>默认: 恒压输出
				// <0=> 恒压
				// <1=> 恒压有效值（均方根）
				// <2=> 恒压换挡（未实现）				
				// <3=> 恒功率
				// <4=> 恒电阻（恒温）（未实现）
				#define CFG_MOS_OUT_MODE				3
			// <o> 内部MOS输出目标（mV/mW/mΩ）
				#define CFG_MOS_OUTPUT_TARGET           10000
			// <o> 输出目标补偿（仅正补偿）
				#define CFG_MOS_OUTPUT_TARGET_FIX    	0				
			// <o> 内部MOS开启后，ADC采样延时（避开MOS开通瞬间不稳定阶段，LSB=100us）
				// <i> 根据实际测试微调
				#define CFG_MOS_OPEN_DELAY          30
		// </h>	
	// </h>			
	// <h> 外部MOS配置（双路输出时配置）
		// <h> 外部MOS负载检测的GPIO配置（三选一）
      // <e> 外部无测阻电路
				#define CFG_PIN_EXTMOS_RL_DET_NONE				0    
			// </e>
			// <e> 使用MOTOR管脚驱动（GPIO不够用）
				#define CFG_PIN_EXTMOS_RL_DET_MOTOR				1    
			// </e>
			// <e> 使用GPIO管脚驱动
				#define CFG_PIN_EXTMOS_RL_DET_GPIO				0    		
				// <o> 使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_EXTMOS_RL_PORT				0x02
				// <o> 使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_EXTMOS_RL_PINNUM			0x01
			// </e>				
		// </h>		
		// <h> 外部MOS输出控制的GPIO配置	
			// <o> 使用的GPIO组
				// <i>默认: 1
				// <0x01=> GPIOA组
				// <0x02=> GPIOB组
				// <0x04=> GPIOC组
				#define CFG_PIN_EXTMOS_VOUT_PORT			0x02
			// <o> 使用的GPIO号
				// <i>默认: 1
				// <0x01=> PIN0
				// <0x02=> PIN1
				// <0x04=> PIN2
				// <0x08=> PIN3
				#define CFG_PIN_EXTMOS_VOUT_PINNUM			0x02
		// </h>	
		// <h> VOUT电压ADC采集的GPIO配置	
			// <o> 使用的GPIO组
				// <i>默认: 1
				// <0x02=> GPIOB组
				#define CFG_PIN_EXTMOS_ADC_PORT				0x02
			// <o> 使用的GPIO号
				// <i>默认: 1
				// <0x01=> PIN0
				// <0x02=> PIN1
				// <0x04=> PIN2
				#define CFG_PIN_EXTMOS_ADC_PINNUM			0x01
				
				#if (CFG_PIN_EXTMOS_ADC_PINNUM==0x01)
				#define CFG_EXTMOS_ADC_CHN			ADC_CHN3_GPIOB0
				#elif (CFG_PIN_EXTMOS_ADC_PINNUM==0x02) 
				#define CFG_EXTMOS_ADC_CHN			ADC_CHN4_GPIOB1
				#else
				#define CFG_EXTMOS_ADC_CHN			ADC_CHN5_GPIOB2
				#endif
		// </h>				
		// <h> 外部MOS输出参数配置
			// <o> 外部MOS PWM输出周期
				// <i> 输出频率=1/输出周期
				// <20-200>
				#define CFG_EXTMOS_PWM_PERIOD      		200
			// <o> 外部MOS输出模式
				// <i>默认: 恒压输出
				// <0=> 恒压
				// <1=> 恒压有效值（均方根）
				#define CFG_EXTMOS_OUT_MODE				0
			// <o> 外部MOS输出目标
				#define CFG_EXTMOS_OUTPUT_TARGET        3400	
			// <o> 输出目标补偿（仅正补偿）
				#define CFG_EXTMOS_OUTPUT_TARGET_FIX    0					
			// <o> 外部MOS开启后，ADC采样延时（避开MOS开通瞬间不稳定阶段，LSB=100us）
				// <i> 根据实际测试微调
				#define CFG_EXTMOS_OPEN_DELAY          	30
		// </h>	
	// </h>		
// </h>	

// <h> 充电配置       
	// <o> 设置恒流充电电流ISET(mA)
		// <i>默认: 5
		// <0=> 250
		// <1=> 300
		// <2=> 350
		// <3=> 400
		// <4=> 450
		// <5=> 500
		// <6=> 550
		// <7=> 600
		// <8=> 650
		// <9=> 700
		// <10=> 750
		#define CFG_CHG_ISET           	5 
	// <o> 设置满充截止电流
		// <i>默认: 0
		// <0=> 20%ISET
		// <1=> 10%ISET
		#define CFG_CHG_FULL_ISET       0	
	// <e> 充电中吸烟使能
		// <i> 吸烟时，停充；吸烟释放，重新充电
		#define CFG_CHG_SMOKE_EN		0 
	// </e>  	
	// <e> 大电流(>600mA)充电，主动降电流使能
		#define CFG_CHG_SUB_CUR_EN		0 
		// <o> VBAT降流门限（mV）
			#define   CFG_CHG_SUB_CUR_VBAT_THD		3900				
		// <o> 设置降电流档位ISET(mA)
			// <i>默认: 5
			// <0=> 250
			// <1=> 300
			// <2=> 350
			// <3=> 400
			// <4=> 450
			// <5=> 500
			// <6=> 550
			// <7=> 600
			// <8=> 650
			#define CFG_CHG_SUB_CUR_ISET     		6 	
		// <o> 降流检测时间（LSB=10ms）
			#define CFG_CHG_SUB_CUR_TIMER 			100			
	// </e> 	
	// <e> 充电结束(满充或USB拔出)，更新一次MIC初值，避免充电影响初值
		#define CFG_CHG_REFLESH_MIC_VALUE_EN		1 	
	// </e> 	
	// <e> 满充由软件控制
		#define CFG_CHG_FULL_BY_SOFT_EN		0 
		// <o> 满充电压门限（mV）
			#define CFG_CHG_FULL_VBAT_THD		4100	
		// <o> 复充电压门限（mV）
			#define CFG_CHG_RECHG_VBAT_THD		4000			
		// <o> 满充检测时间（LSB=10ms）
			#define CFG_CHG_FULL_TIMER 			60000				
	// </e> 	
// </h>

// <h> 负载检测配置
	// <e> 负载插拔检测功能使能（仅内部MOS支持）
		// <i> 默认:失能
		#define CFG_RLOAD_PLUG_EN				0
	// </e>
	// <e> 负载短路/低阻保护使能
		// <i> 默认:失能
		#define CFG_RLOAD_SHORT_PRO_EN				1	
		// <o> 短路判断发热丝阻值（mΩ）
		#define CFG_RL_VALUE_SHORT				600 	 		
	// </e>	
	// <e> 负载开路保护使能
		// <i> 默认:失能
		#define CFG_RLOAD_OPEN_PRO_EN				0	
		// <o> 空载判断发热丝阻值（mΩ）
		#define CFG_RL_VALUE_OPEN				3000  		
		// <e> 功率输出时，检测负载开路
			// <i> 默认:失能
			#define CFG_VOUT_DET_RL_EN				0
			// <o> 检测周期（ms）
			// <i> 不建议太小，否则会影响输出稳定性
			#define CFG_VOUT_DET_RL_TIME           	100		
		// </e>			
	// </e>		
// </h>

// <h> 电机功能配置
	// <e> 电机驱动功能使能
		// <i> 默认:失能
		#define CFG_MOTOR_EN					0	
		// <o> 电机默认输出占空比
			// <i>默认: 0
			// <0=> 0%
			// <1=> 7%
			// <2=> 13%
			// <3=> 20%
			// <4=> 27%
			// <5=> 33%
			// <6=> 40%
			// <7=> 47%
			// <8=> 53%
			// <9=> 60%
			// <10=> 67%
			// <11=> 73%
			// <12=> 80%
			// <13=> 87%
			// <14=> 93%
			// <15=> 100%
			#define CFG_MOTOR_DUTY 				0			
	// </e>	
// </h>

// <h> 灯效显示配置
	// <e> LED功能（与断码屏功能二选一）
		#define CFG_UI_LED_EN				1	
		// <o> LED驱动电流（仅RA1/RA2/RA3做恒流源时有效）
			// <i>默认: 0
			// <0x00=> 4mA
			// <0x08=> 8mA
			// <0x10=> 21mA
			// <0x18=> 29mA
			#define CFG_UI_LED_CURR       	0x00		
		// <h> LED管脚配置
			// <e> LED0      
				#define CFG_UI_LED0_EN					1	
				// <o> LED0使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					#define CFG_PIN_LED0_PORT			0x01
				// <o> LED0使用的GPIO号
					// <i>默认: 1
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_LED0_PINNUM			0x02
			// </e>	
			// <e> LED1      
				#define CFG_UI_LED1_EN					1	
				// <o> LED1使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					#define CFG_PIN_LED1_PORT			0x01
				// <o> LED1使用的GPIO号
					// <i>默认: 1
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_LED1_PINNUM			0x04
			// </e>	
			// <e> LED2      
				#define CFG_UI_LED2_EN					1	
				// <o> LED2使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					#define CFG_PIN_LED2_PORT			0x01
				// <o> LED2使用的GPIO号
					// <i>默认: 1
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_LED2_PINNUM			0x08
			// </e>	
			// <e> LED3      
				#define CFG_UI_LED3_EN					0	
				// <o> LED3使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_LED3_PORT			0x02
				// <o> LED3使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_LED3_PINNUM			0x01
			// </e>		
			// <e> LED4      
				#define CFG_UI_LED4_EN					0	
				// <o> LED4使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_LED4_PORT			0x02
				// <o> LED4使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_LED4_PINNUM			0x02
			// </e>		
			// <e> LED5      
				#define CFG_UI_LED5_EN					0	
				// <o> LED5使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_LED5_PORT			0x02
				// <o> LED5使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_LED5_PINNUM			0x04
			// </e>							
		// </h>			
		// <e> PWM0控制LED使能（控制LED0/LED1/LED2）
			#define CFG_PWM0_CTRL_EN    		1		
			// <o> PWM0的时钟分频
				// <i>默认: 7分频系数128（125K）
				// <0=> 分频系数1（16M）
				// <1=> 分频系数2（8M）
				// <2=> 分频系数4（4M）
				// <3=> 分频系数8（2M）
				// <4=> 分频系数16（1M）
				// <5=> 分频系数32（500K）
				// <6=> 分频系数64（250K）
				// <7=> 分频系数128（125K）
				#define CFG_PWM0_FCLK_SET           7 
			// <o> PWM0输出周期
				// <i> 默认：61
				// <i> 输出频率=分频时钟/输出周期
				// <0-255>
				#define CFG_PWM0_PERIOD      		255
			// <e> PWM0极性反转使能
				#define CFG_PWM0_NEGATE_EN    		0
			// </e>								
		// </e>			
		// <e> PWM1控制LED使能（控制LED3/LED4/LED5）
			#define CFG_PWM1_CTRL_EN    		0		
			// <o> PWM1的时钟分频
				// <i>默认: 7分频系数128（125K）
				// <0=> 分频系数1（16M）
				// <1=> 分频系数2（8M）
				// <2=> 分频系数4（4M）
				// <3=> 分频系数8（2M）
				// <4=> 分频系数16（1M）
				// <5=> 分频系数32（500K）
				// <6=> 分频系数64（250K）
				// <7=> 分频系数128（125K）
				#define CFG_PWM1_FCLK_SET           7 
			// <o> PWM1输出周期
				// <i> 默认：61
				// <i> 输出频率=分频时钟/输出周期
				// <0-255>
				#define CFG_PWM1_PERIOD      		255
			// <e> PWM1极性反转使能(共阳LED使用)
				#define CFG_PWM1_NEGATE_EN    		1
			// </e>								
		// </e>			
		// <h> 灯效配置		
			// <e> 上电闪灯（POR）
				#define CFG_UI_LED_POR			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮
					#define CFG_UI_LED_COLOR_POR    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_POR		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_POR		25
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_POR		1
			// </e>
			// <e> 低电复位闪灯（LVR）
				#define CFG_UI_LED_LVR			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_LVR    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_LVR		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_LVR		25
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_LVR		1
			// </e>		
			// <e> USB接入（USB_IN）
				#define CFG_UI_LED_USB_IN			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_USB_IN    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_USB_IN		1
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_USB_IN		50
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_USB_IN			0
			// </e>		
			// <e> USB充电中（USB_CHARGING）
				#define CFG_UI_LED_USB_CHARGING			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_USB_CHARGING    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_USB_CHARGING		6
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_USB_CHARGING	100
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_USB_CHARGING		1
			// </e>				
			// <e> USB满充（USB_FULL）
				#define CFG_UI_LED_USB_FULL			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_USB_FULL    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_USB_FULL		2
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_USB_FULL	50
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_USB_FULL		0
			// </e>			
			// <e> USB拔出（USB_OUT）
				#define CFG_UI_LED_USB_OUT			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_USB_OUT    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_USB_OUT		2
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_USB_OUT		0
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_USB_OUT		0
			// </e>			
			// <e> 开始放电（FIRE_START）
				#define CFG_UI_LED_FIRE_START			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_FIRE_START    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_FIRE_START		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_FIRE_START		100
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_FIRE_START			1
			// </e>			
			// <e> 结束放电（FIRE_STOP）
				#define CFG_UI_LED_FIRE_STOP			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_FIRE_STOP    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_FIRE_STOP		4
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_FIRE_STOP	100
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_FIRE_STOP		1
			// </e>	
			// <e> 吸烟超时（FIRE_TIMEOUT）
				#define CFG_UI_LED_FIRE_TIMEOUT			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_FIRE_TIMEOUT    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_FIRE_TIMEOUT		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_FIRE_TIMEOUT	25
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_FIRE_TIMEOUT		2
			// </e>					
			// <e> 负载接入（RL_IN）
				#define CFG_UI_LED_RL_IN			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_RL_IN    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_RL_IN		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_RL_IN	25
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_RL_IN		1
			// </e>	
			// <e> 负载拔出（RL_OUT）
				#define CFG_UI_LED_RL_OUT			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_RL_OUT    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_RL_OUT		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_RL_OUT	25
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_RL_OUT		1
			// </e>			
			// <e> 负载短路（RL_SHORT）
				#define CFG_UI_LED_RL_SHORT			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_RL_SHORT    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_RL_SHORT		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_RL_SHORT	30
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_RL_SHORT		2
			// </e>			
			// <e> 负载开路（RL_OPEN）
				#define CFG_UI_LED_RL_OPEN			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_RL_OPEN    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_RL_OPEN		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_RL_OPEN	30
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_RL_OPEN		4
			// </e>			
			// <e> 负载干烧（RL_DRY）
				#define CFG_UI_LED_RL_DRY			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_RL_DRY    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_RL_DRY		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_RL_DRY	30
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_RL_DRY		5
			// </e>			
			// <e> 触发童锁（CHILD_LOCK）
				#define CFG_UI_LED_CHILD_LOCK			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_CHILD_LOCK    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_CHILD_LOCK		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_CHILD_LOCK	50
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_CHILD_LOCK		2
			// </e>			
			// <e> 童锁解锁（CHILD_UNLOCK）
				#define CFG_UI_LED_CHILD_UNLOCK			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_CHILD_UNLOCK    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_CHILD_UNLOCK		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_CHILD_UNLOCK	50
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_CHILD_UNLOCK		2
			// </e>		
			// <e> 电池低压（BAT_LOW）
				#define CFG_UI_LED_BAT_LOW			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_BAT_LOW    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_BAT_LOW		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_BAT_LOW	25
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_BAT_LOW		10
			// </e>			
			// <e> 系统锁机（SYS_LOCK）
				#define CFG_UI_LED_SYS_LOCK			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_SYS_LOCK    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_SYS_LOCK		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_SYS_LOCK	50
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_SYS_LOCK		3
			// </e>			
			// <e> 系统解锁（SYS_UNLOCK）
				#define CFG_UI_LED_SYS_UNLOCK			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_SYS_UNLOCK    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_SYS_UNLOCK		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_SYS_UNLOCK	50
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_SYS_UNLOCK		3
			// </e>		
			// <e> 芯片过温（CHIP_OTP）
				#define CFG_UI_LED_CHIP_OTP			1
				//	<h>颜色
					// <o0.0> LED0 亮
					// <o0.1> LED1 亮
					// <o0.2> LED2 亮
					// <o0.3> LED3 亮
					// <o0.4> LED4 亮		
					// <o0.5> LED5 亮					
					#define CFG_UI_LED_COLOR_CHIP_OTP    0x07
				// </h>
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 常亮
					// <2=>  2 - 熄灭
					// <3=>  3 - 渐亮
					// <4=>  4 - 渐灭
					// <5=>  5 - 闪烁
					// <6=>  6 - 呼吸
					// <7=>  7 - 常亮后熄灭
					#define   CFG_UI_LED_TYPE_CHIP_OTP		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_LED_ONTIME_CHIP_OTP	25
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_LED_CNT_CHIP_OTP		5
			// </e>			
		// </h>	
	// </e>

	// <e> 断码屏功能（与LED功能二选一）
		#define CFG_UI_SCREEN_EN				0		
		// <h> 驱动管脚配置（根据实际断码屏按顺序使能管脚）
			// <e> COM1      
				#define CFG_UI_COM1_EN					1	
				// <o> COM1使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_COM1_PORT			0x02
				// <o> COM1使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_COM1_PINNUM			0x08
			// </e>	
			// <e> COM2      
				#define CFG_UI_COM2_EN					1	
				// <o> COM2使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_COM2_PORT			0x02
				// <o> COM2使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_COM2_PINNUM			0x04
			// </e>	
			// <e> COM3      
				#define CFG_UI_COM3_EN					1	
				// <o> COM3使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_COM3_PORT			0x01
				// <o> COM3使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_COM3_PINNUM			0x08
			// </e>	
			// <e> COM4      
				#define CFG_UI_COM4_EN					1	
				// <o> COM4使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_COM4_PORT			0x01
				// <o> COM4使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_COM4_PINNUM			0x04
			// </e>	
			// <e> COM5      
				#define CFG_UI_COM5_EN					1	
				// <o> COM5使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_COM5_PORT			0x01
				// <o> COM5使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_COM5_PINNUM			0x02
			// </e>	
			// <e> COM6      
				#define CFG_UI_COM6_EN					0	
				// <o> COM6使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_COM6_PORT			0x02
				// <o> COM6使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_COM6_PINNUM			0x02
			// </e>	
			// <e> COM7      
				#define CFG_UI_COM7_EN					0	
				// <o> COM7使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_COM7_PORT			0x02
				// <o> COM7使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_COM7_PINNUM			0x04
			// </e>	
			// <e> COM8      
				#define CFG_UI_COM8_EN					0	
				// <o> COM8使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_COM8_PORT			0x02
				// <o> COM8使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_COM8_PINNUM			0x08
			// </e>	
			// <e> COM9      
				#define CFG_UI_COM9_EN					0	
				// <o> COM9使用的GPIO组
					// <i>默认: 1
					// <0x01=> GPIOA组
					// <0x02=> GPIOB组
					// <0x04=> GPIOC组
					#define CFG_PIN_COM9_PORT			0x04
				// <o> COM9使用的GPIO号
					// <i>默认: 1
					// <0x01=> PIN0
					// <0x02=> PIN1
					// <0x04=> PIN2
					// <0x08=> PIN3
					#define CFG_PIN_COM9_PINNUM			0x02
			// </e>			
		// </h>	
    
    // <e> 使用屏幕呼吸灯效
        #define CFG_UI_SCREEN_SOFT_PWM_BREATH_EN  0
    // </e>
    
		// <h> 灯效配置		
			// <e> 上电闪灯（POR）
				#define CFG_UI_SCREEN_POR			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_POR		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_POR		25
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_POR		1
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_POR		0				
			// </e>
			// <e> 低电复位闪灯（LVR）
				#define CFG_UI_SCREEN_LVR			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_LVR		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_LVR		25
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_LVR		2
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_LVR		0				
			// </e>		
			// <e> USB接入（USB_IN）
				#define CFG_UI_SCREEN_USB_IN			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_USB_IN		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_USB_IN		50
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_USB_IN			2
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_USB_IN		2				
			// </e>		
			// <e> USB充电中（USB_CHARGING）
				#define CFG_UI_SCREEN_USB_CHARGING			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_USB_CHARGING		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_USB_CHARGING	50
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_USB_CHARGING		2
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_USB_CHARGING		2					
			// </e>				
			// <e> USB满充（USB_FULL）
				#define CFG_UI_SCREEN_USB_FULL			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_USB_FULL		1
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_USB_FULL	0
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_USB_FULL		0
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_USB_FULL		0	
			// </e>			
			// <e> USB拔出（USB_OUT）
				#define CFG_UI_SCREEN_USB_OUT			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_USB_OUT		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_USB_OUT	25
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_USB_OUT		1
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_USB_OUT		0	
			// </e>			
			// <e> 开始放电（FIRE_START）
			#define CFG_UI_SCREEN_FIRE_START			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁				
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_FIRE_START		5
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_FIRE_START	10
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_FIRE_START		1
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_FIRE_START		2
			// </e>			
			// <e> 结束放电（FIRE_STOP）
			#define CFG_UI_SCREEN_FIRE_STOP			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_FIRE_STOP		4
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_FIRE_STOP	300
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_FIRE_STOP		1
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_FIRE_STOP		0
			// </e>	
			// <e> 吸烟超时（FIRE_TIMEOUT）
			#define CFG_UI_SCREEN_FIRE_TIMEOUT			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_FIRE_TIMEOUT		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_FIRE_TIMEOUT	40
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_FIRE_TIMEOUT		5
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_FIRE_TIMEOUT		0
			// </e>					
			// <e> 负载接入（RL_IN）
			#define CFG_UI_SCREEN_RL_IN			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_RL_IN		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_RL_IN	20
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_RL_IN		1
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_RL_IN		0
			// </e>	
			// <e> 负载拔出（RL_OUT）
			#define CFG_UI_SCREEN_RL_OUT			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_RL_OUT		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_RL_OUT	20
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_RL_OUT		1
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_RL_OUT		0
			// </e>			
			// <e> 负载短路（RL_SHORT）
			#define CFG_UI_SCREEN_RL_SHORT			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_RL_SHORT		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_RL_SHORT	20
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_RL_SHORT		10
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_RL_SHORT		0
			// </e>	
			// <e> 负载开路（RL_OPEN）
			#define CFG_UI_SCREEN_RL_OPEN			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_RL_OPEN		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_RL_OPEN	20
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_RL_OPEN		5
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_RL_OPEN		0
			// </e>			
			// <e> 负载干烧（RL_DRY）
			#define CFG_UI_SCREEN_RL_DRY			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_RL_DRY		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_RL_DRY	20
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_RL_DRY		5
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_RL_DRY		0
			// </e>			
			// <e> 触发童锁（CHILD_LOCK）
			#define CFG_UI_SCREEN_CHILD_LOCK			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_CHILD_LOCK		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_CHILD_LOCK	50
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_CHILD_LOCK		2
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_CHILD_LOCK		0
			// </e>			
			// <e> 童锁解锁（CHILD_UNLOCK）
			#define CFG_UI_SCREEN_CHILD_UNLOCK			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_CHILD_UNLOCK		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_CHILD_UNLOCK	50
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_CHILD_UNLOCK		2
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_CHILD_UNLOCK		0
			// </e>		
			// <e> 电池低压（BAT_LOW）
				#define CFG_UI_SCREEN_BAT_LOW			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_BAT_LOW		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_BAT_LOW	20
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_BAT_LOW		20
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_BAT_LOW		0
			// </e>			
			// <e> 系统锁机（SYS_LOCK）
				#define CFG_UI_SCREEN_SYS_LOCK			0
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_SYS_LOCK		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_SYS_LOCK	20
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_SYS_LOCK		20
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_SYS_LOCK		0
			// </e>			
			// <e> 系统解锁（SYS_UNLOCK）
				#define CFG_UI_SCREEN_SYS_UNLOCK			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_SYS_UNLOCK		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_SYS_UNLOCK	20
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_SYS_UNLOCK		20
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_SYS_UNLOCK		0
			// </e>		
			// <e> 芯片过温（CHIP_OTP）
				#define CFG_UI_SCREEN_CHIP_OTP			1
				// <o> 输出模式选择
					// <0=>  0 - 无定义
					// <1=>  1 - 熄灭
					// <2=>  2 - 常亮
					// <3=>  3 - 闪烁
					// <4=>  4 - 维持当前状态
					// <5=>  5 - 跑马灯
					#define   CFG_UI_SCREEN_TYPE_CHIP_OTP		3
				// <o> 亮/灭灯时长（LSB=10ms）
					#define   CFG_UI_SCREEN_ONTIME_CHIP_OTP	50
				// <o> 闪灯或者呼吸次数
					#define   CFG_UI_SCREEN_CNT_CHIP_OTP		5
				// <o> 亮灯后状态
					// <0=>  0 - 闪完后熄灭
					// <1=>  1 - 闪后常亮
					// <2=>  2 - 一直闪
					#define   CFG_UI_SCREEN_END_STATE_CHIP_OTP		0
			// </e>			
		// </h>	
	// </e>
	// <e> 幻彩灯控制驱动
		#define CFG_UI_MAGIC_LED_EN							0			
		// <e> 电源控制管脚（睡眠关闭电源）      
			#define CFG_UI_MAGIC_LED_PWR_EN					0	
			// <o> 使用的GPIO组
				// <i>默认: GPIOA组
				// <0x01=> GPIOA组
				// <0x02=> GPIOB组
				// <0x04=> GPIOC组
				#define CFG_PIN_MAGIC_LED_PWR_PORT			0x01
			// <o> 使用用的GPIO号
				// <i>默认: PIN0
				// <0x01=> PIN0
				// <0x02=> PIN1
				// <0x04=> PIN2
				// <0x08=> PIN3
				#define CFG_PIN_MAGIC_LED_PWR_PINNUM		0x01
		// </e>		
		// <e> 控制管脚1      
			#define CFG_UI_MAGIC_LED0_EN					0	
			// <o> 使用的GPIO组
				// <i>默认: GPIOA组
				// <0=> GPIOA组
				// <1=> GPIOB组
				// <2=> GPIOC组
				#define CFG_PIN_MAGIC_LED0_PORT			0
			// <o> 使用用的GPIO号
				// <i>默认: PIN0
				// <0=> PIN0
				// <1=> PIN1
				// <2=> PIN2
				// <3=> PIN3
				#define CFG_PIN_MAGIC_LED0_PINNUM		1
		// </e>		
		// <e> 测试示例（3个灯）      
			#define CFG_UI_MAGIC_LED_TEST_EN			0	
		// </e>			
	// </e>
// </h>

// <h> 电池电量档位
	// <e> 吸烟低压保护使能
		// <i> 默认:使能
		#define CFG_BAT_UV_FIRE_EN				1	
		// <o> 吸烟前欠压门限（mV）
		#define   CFG_BAT_UV_IDLE_THD		3300
		// <o> 吸烟中欠压门限（mV）
		#define   CFG_BAT_UV_FIRING_THD		2550		
	// </e>
		// <o> 电量增加/减小的步进（%）
		#define CFG_BAT_STEP						1	
	// <e> 空闲/充电时，电池电量更新使能
		// <i> 默认:失能
		#define CFG_BAT_UPDATE_IDLE_EN				1		
		// <o> 充电时，电压抬升偏差（mV）
		#define   CFG_BAT_DIFF_CHG					30	
		// <o> 更新周期（ms）
		#define CFG_BAT_IDLE_UPDATA_TIME 			100			
		// <o> 充电时，未充满电量更新周期（LSB=100ms）
		#define CFG_CHG_NOT_PRE100_UPDATA_TIME 		200	
		// <o> 充电时，已充满电量更新周期（LSB=100ms）
		#define CFG_CHG_PRE100_UPDATA_TIME 			40		
	// </e>	
	// <e> 吸烟时，电池电量更新使能
		// <i> 默认:失能
		#define CFG_BAT_UPDATE_FIRE_EN				1		
		// <o> 放电时，电压拉低偏差（mV）
		#define   CFG_BAT_DIFF_DISCHG				30			
		// <o> 更新周期（ms）
		#define CFG_BAT_FIRE_UPDATA_TIME 				100	
		// <o> 电量减少1%，累计时间（LSB=100ms）
		#define CFG_BAT_SUBB_PRE_1_TIME 			80		
		// <o> 停止输出后，延时更新电池电量（LSB=10ms）
			#define CFG_OUTPUT_STOP_UPDATE_BATTERY_TIME 100			
	// </e>		
// </h>

// <h> 掉电保存参数（非完全掉电）
	// <e> 油量计算
		// <i> 默认:失能
		#define CFG_OIL_CAL_EN						    1			
			// <o> 总油量（s）
			// <0-10000>
			#define CFG_OIL_MAX 						2200
			// <o> 油量更新周期（ms）
			#define CFG_OIL_UPDATA_TIME 				100			
	// </e>
// </h>

// <h> 串口功能
	// <e> 硬件UART功能使能
		// <i> 默认:失能
		#define CFG_UART_HW_EN						    1
			// <o> 串口波特率
				#define CFG_UART_BAUDRATE 				115200
			// <o> 串口发送缓冲区大小（Bytes）
				#define CFG_UART_TX_BUF_LENGTH 			32				
			// <o> 设置串口半双工/全双工收发
				// <i>默认: 全双工
				// <0=> 全双工
				// <1=> 半双工
				#define CFG_UART_MODE					0
			// <e> 串口接收使能（不使用接收功能，可关闭）
				// <i>默认: 失能
					#define CFG_UART_RX_EN				1
				// <o> 串口接收缓冲区大小（Bytes）
					#define CFG_UART_RX_BUF_LENGTH 		10	
				// <o> 串口接收数据超时（ms）
					#define CFG_UART_RX_TIMEOUT 		3		
			// </e>
			// <e> 串口带电升级使能(需要开启RC1的GPIO唤醒功能)
				// <i>默认: 失能
					#define CFG_UART_BOOTING_EN			1
				// <o> 串口升级指令0
					#define CFG_UART_BOOTING_CMD0 		0x55
				// <o> 串口升级指令1
					#define CFG_UART_BOOTING_CMD1 		0x50
				// <o> 串口升级指令2
					#define CFG_UART_BOOTING_CMD2 		0x44					
				// <o> 串口升级指令3
					#define CFG_UART_BOOTING_CMD3 		0x41
				// <o> 串口升级指令4
					#define CFG_UART_BOOTING_CMD4 		0x54
				// <o> 串口升级指令5
					#define CFG_UART_BOOTING_CMD5 		0x45					
			// </e>			
			// <o> 串口收发方式
				// <i>默认: 串口中断发送
				// <0=> 串口轮询发送
				// <1=> 串口中断发送
				#define CFG_UART_CONFIG_SEND_METHORD	0	
		// <e> Debug功能使能（量产建议关闭）
			// <i> 默认:失能
			#define CFG_DEBUG_ON               			1
      
      // <e> 测试模式（只打印充放电信息，其他打印不生效）
      #define CFG_DEBUG_FACTORY_MODE          0
      //  </e>
      #if CFG_DEBUG_ON
        #if CFG_DEBUG_FACTORY_MODE
          #define   AM_FACTORY_PRINTF    tiny_printf
          #define   AM_DBG_PRINTF    /##/
        #else    
          #define   AM_FACTORY_PRINTF    /##/
          #define   AM_DBG_PRINTF    tiny_printf
        #endif
      #else
        #define   AM_FACTORY_PRINTF    /##/
        #define   AM_DBG_PRINTF    /##/
      #endif

		// </e>
    
    
	// </e>
// </h>

  // <h>  配置低功耗时未使用的io（需要勾选未使用的IO,配置为输入下拉）
      // <h>  GPIOA组 未使用的IO
				// <q.3> PIN3
				// <q.2> PIN2
				// <q.1> PIN1
        // <q.0> PIN0
				#define CFG_GPIOA_UNUSE_PIN		        	0x0
      // </h>
      
      // <h>  GPIOB组 未使用的IO
				// <q.3> PIN3
				// <q.2> PIN2
				// <q.1> PIN1
        // <q.0> PIN0
				#define CFG_GPIOB_UNUSE_PIN		        	0x0
      // </h>
      
      // <h>  GPIOC组 未使用的IO
				// <q.1> PIN1
        // <q.0> PIN0
				#define CFG_GPIOC_UNUSE_PIN		        	0x0
      // </h>
			
  // </h>

// <<< end of configuration section >>>

#endif /* end of __USER_CONFIG_H__ */
