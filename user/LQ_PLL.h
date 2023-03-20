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
#ifndef __LQ_KV58P144SYSVG_H__
#define __LQ_KV58P144SYSVG_H__
#include "include.h"

extern uint32 core_clk_M;//单位MHZ
extern uint32 bus_clk_M;//单位MHZ

//PLL参数
typedef enum clk_option
{
    PLLUNULL ,   
    PLL150   ,  
    PLL180   ,
    PLL200   ,   
    PLL235   ,
    PLL250   ,
    PLL262_5 ,
    PLL275 ,
    PLL287_5 ,
    PLL293_75,
} clk_option;

/*********************** PLL功能函数 **************************/
void PLL_Init(clk_option);     //锁相环初始化

void disable_unused_pins(void);
void enable_unused_pins(void);

/* Function to initialize OSC0 base on board configuration. */
void BOARD_InitOsc0(void);

#endif /* __BOARD_H__ */

