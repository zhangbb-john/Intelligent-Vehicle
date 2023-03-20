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
��busclock��137.500MHz
��pllclock��275.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵������ʼ��LED����IO��
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
//void LED_Init(void)
//{  
//  //-----�˿ڳ�ʼ��----//
//  GPIO_Init(GPIOE,29,GPO,0);
//  GPIO_Init(GPIOE,30,GPO,0);
//  GPIO_Init(GPIOE,13,GPO,0);
//}
void LED_Init(void)
{  
  //-----�˿ڳ�ʼ��----//
  GPIO_Init(GPIOC,0,GPO,0);
  GPIO_Init(GPIOA,17,GPO,0);
  GPIO_Init(GPIOE,29,GPO,0);
//  GPIO_Init(GPIOD,15,GPO,0);  
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵��������IO����ߵ͵�ƽ
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ��
LEDn_e ledno, ���
LEDs_e sta ״̬������
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
����  �ߡ�CHIUSIR
������˵��������LED������ˮ��
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ����
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

