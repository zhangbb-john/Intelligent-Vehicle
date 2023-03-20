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
【busclock】137.500MHz
【pllclock】275.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"	
                                                        
//功  能: 关闭看门狗模块   
void Kick_Dog(void)
{
    //给看门狗模块解锁，以便写寄存器
    Feed_Dog();
    //关闭看门狗
    WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;
}
                                                   
//功  能: 看门狗解锁     
void Feed_Dog(void)
{
    //注意： 不要单步调试此程序!!! ，否则可能会引起CPU复位
    //关总中断
    DisableInterrupts;		
    //写解锁寄存器
    WDOG_UNLOCK = 0xC520;	
    //完成解锁
    WDOG_UNLOCK = 0xD928;	
    //开总中断
    EnableInterrupts;		
}
