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
#ifndef __LQ_KV58P144SYSVG_H__
#define __LQ_KV58P144SYSVG_H__
#include "include.h"

extern uint32 core_clk_M;//��λMHZ
extern uint32 bus_clk_M;//��λMHZ

//PLL����
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

/*********************** PLL���ܺ��� **************************/
void PLL_Init(clk_option);     //���໷��ʼ��

void disable_unused_pins(void);
void enable_unused_pins(void);

/* Function to initialize OSC0 base on board configuration. */
void BOARD_InitOsc0(void);

#endif /* __BOARD_H__ */

