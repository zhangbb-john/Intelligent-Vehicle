/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������KV58F24���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2017��12��15��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4
��Target  ��MKV58F1M0VLQ24
��Crystal �� 50.000Mhz
��busclock��120.000MHz
��pllclock��240.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_INC_H__
#define __LQ_INC_H__

//#define __USE_TFT18

//ͨ��ͷ�ļ�
#include <stdio.h>                       //printf
#include <string.h>                      //memcpy
#include <stdlib.h>                      //malloc
#include <stdint.h>
#include "pin_mux.h"

//Cortex-M�ں�MCU�Ĵ���ͷ�ļ�
#include "MKV58F24.h"   //�Ĵ���ӳ��ͷ�ļ�
#include "arm_math.h "
#include "stdio.h "

//�������ͼ��˿������ض���    
#include "fsl_debug_console.h"
#include "fsl_clock_manager.h"
#include "fsl_gpio_driver.h"
#include "fsl_smc_hal.h"    
#include "pin_mux.h"    
#include "common.h"
#include "math.h"//-------------------------
//MCU�ڲ�ģ��������ͷ�ļ�
#include "LQ_PLL.h"
#include "LQWDOG.h"
#include "LQGPIO_Cfg.h"
#include "LQGPIO.h"
#include "LQ_LED.h"
#include "LQ_KEY.h"
#include "LQMT9V034.h"
#include "LQ_SGP18T.h"   
#include "LQ12864.h"
#include "LQUART.h"
#include "LQADC.h" 
#include "LQPIT.h"
#include "LQDMA.h"
#include "LQFTM.h"    
#include "LPTMR.h"   
//#include "fsl_adc16.h"
/*
* Include �û��Զ����ͷ�ļ�
*/
//��ӭ�¼���ĳ�Ա
#include 	"control.h"
#include	"debug.h"
#include 	"search.h"
#include  "function.h"
#include  "fuzzy.h"

#endif 
