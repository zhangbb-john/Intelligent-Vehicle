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

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】初始化LED所用IO口
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
//void LED_Init(void)
//{  
//  //-----端口初始化----//
//  GPIO_Init(GPIOE,29,GPO,0);
//  GPIO_Init(GPIOE,30,GPO,0);
//  GPIO_Init(GPIOE,13,GPO,0);
//}
void LED_Init(void)
{  
  //-----端口初始化----//
  GPIO_Init(GPIOC,0,GPO,0);
  GPIO_Init(GPIOA,17,GPO,0);
  GPIO_Init(GPIOE,29,GPO,0);
//  GPIO_Init(GPIOD,15,GPO,0);  
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】控制IO输出高低电平
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】
LEDn_e ledno, 编号
LEDs_e sta 状态，亮灭
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void LED_Ctrl(LEDn_e ledno, LEDs_e sta)
{
  switch(ledno) 
  {
  case LED0:
    if(sta==ON)        PTC0_OUT=0; //Turn on target LED1 
    else if(sta==OFF) PTC0_OUT=1; //Turn off target LED1 
    else if(sta==RVS) GPIO_Reverse (GPIOC, 0);//Toggle on target LED1
    break;
  case LED1:
    if(sta==ON)        PTD15_OUT=0; //Turn on target LED3 
    else if(sta==OFF) PTD15_OUT=1; //Turn off target LED3 
    else if(sta==RVS) GPIO_Reverse (GPIOD, 15);//Toggle on target LED3
    break;   
  case LED3:
    if(sta==ON)        PTA17_OUT=0; //Turn on target LED2 
    else if(sta==OFF) PTA17_OUT=1; //Turn off target LED2 
    else if(sta==RVS) GPIO_Reverse (GPIOA, 17);//Toggle on target LED2
    break;    
  case LED2:
    if(sta==ON)        PTE29_OUT=0; //Turn on target LED3 
    else if(sta==OFF) PTE29_OUT=1; //Turn off target LED3 
    else if(sta==RVS) GPIO_Reverse (GPIOE, 29);//Toggle on target LED3
    break; 
  case LEDALL:
    if(sta==ON) 
    {       
      PTD15_OUT=0;
      PTC0_OUT=0; //Turn on target LED1 
      PTA17_OUT=0; //Turn on target LED2 
      PTE29_OUT=0;//Turn on target LED3 
    }
    else if(sta==OFF)
    { 
      PTD15_OUT=1;
      PTC0_OUT=1;   //Turn off target LED1 
      PTA17_OUT=1;   //Turn off target LED2 
      PTE29_OUT=1;  //Turn off target LED3 
    }
    else if(sta==RVS)
    {       
      GPIO_Reverse (GPIOA, 17); //Toggle on target LED1
      GPIO_Reverse (GPIOE, 29); //Toggle on target LED2
      GPIO_Reverse (GPIOC, 0);  //Toggle on target LED3
      GPIO_Reverse (GPIOD, 15);
    }
    break;
  default:
    break;    
  }   
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】测试LED亮灭，流水灯
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_LED(void)
{
  u8 i=0;
  //Init output LED GPIO. //
  LED_Init();
  LED_Ctrl(LEDALL, OFF);    
  while (1)
  {          
    for(i=0;i<10;i++)
    {
      LED_Ctrl(LED1, RVS); 
      time_delay_ms(50*i);
      LED_Ctrl(LED1, OFF); 
      LED_Ctrl(LED2, RVS); 
      time_delay_ms(50*i);
      LED_Ctrl(LED2, OFF); 
      LED_Ctrl(LED3, RVS); 
      time_delay_ms(50*i);
      LED_Ctrl(LED3, OFF); 
      LED_Ctrl(LED0, RVS); 
      time_delay_ms(50*i);
      LED_Ctrl(LEDALL, OFF); 
      time_delay_ms(500);
    }
    LED_Ctrl(LEDALL, OFF); 
    time_delay_ms(500);
    LED_Ctrl(LEDALL, ON); 
    time_delay_ms(500);
  }
}

