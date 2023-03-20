/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱KV58F24智能车VD母板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2017年12月15日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4
【Target  】MKV58F1M0VLQ24
【Crystal 】 50.000Mhz
【busclock】120.000MHz
【pllclock】240.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_INC_H__
#define __LQ_INC_H__

//#define __USE_TFT18

//通用头文件
#include <stdio.h>                       //printf
#include <string.h>                      //memcpy
#include <stdlib.h>                      //malloc
#include <stdint.h>
#include "pin_mux.h"

//Cortex-M内核MCU寄存器头文件
#include "MKV58F24.h"   //寄存器映像头文件
#include "arm_math.h "
#include "stdio.h "

//数据类型及端口名称重定义    
#include "fsl_debug_console.h"
#include "fsl_clock_manager.h"
#include "fsl_gpio_driver.h"
#include "fsl_smc_hal.h"    
#include "pin_mux.h"    
#include "common.h"
#include "math.h"//-------------------------
//MCU内部模块驱动的头文件
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
* Include 用户自定义的头文件
*/
//欢迎新加入的成员
#include 	"control.h"
#include	"debug.h"
#include 	"search.h"
#include  "function.h"
#include  "fuzzy.h"

#endif 
