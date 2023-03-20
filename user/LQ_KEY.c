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

void KEY_SW_Init(void)
{
	//key
  GPIO_Init(GPIOB,20,GPI,1);
  GPIO_Init(GPIOB,21,GPI,1);
  GPIO_Init(GPIOB,22,GPI,1); //初始状态高电平
  
  
//  GPIO_Init(GPIOC,5,GPI_UP,1);
//  GPIO_Init(GPIOC,6,GPI_UP,1);
//  GPIO_Init(GPIOC,7,GPI_UP,1);   
//  GPIO_Init(GPIOC,8,GPI_UP,1);   
//  GPIO_Init(GPIOC,9,GPI_UP,1);   
//  GPIO_Init(GPIOC,10,GPI_UP,1);

													 
  //SW
//  GPIO_Init(GPIOA,26,GPI_UP,1);
//  GPIO_Init(GPIOA,27,GPI_UP,1);
//  GPIO_Init(GPIOA,28,GPI_UP,1);
//  GPIO_Init(GPIOA,29,GPI_UP,1);

  GPIO_Init(GPIOC,6,GPI_UP,1);
  GPIO_Init(GPIOC,7,GPI_UP,1);
  GPIO_Init(GPIOC,8,GPI_UP,1);
  GPIO_Init(GPIOC,9,GPI_UP,1);
  time_delay_ms(5000);
}

u8 KEY_Read(KEYn_e keyno)
{
  switch(keyno) 
  {
  case KEY0:
    return GPIO_Get(PTB20);
    break;
    
  case KEY1:
    return GPIO_Get(PTB21);
    break;
    
  case KEY2:
    return GPIO_Get(PTB22);
    break;
  default:
    return 0XFF;    
  }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】测试按键及OLED显示
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_GPIO_KEY(void)
{ 
  while (1)
  {  
    //测试按键      
    if(KEY_Read(KEY0)==0)
      LCD_P6x8Str(13,3,(uint8_t*)"KEY0 Pressed!   ");
    else LCD_P6x8Str(13,3,(uint8_t*)"KEY0 NO Pressed!");
    if(KEY_Read(KEY1)==0)
      LCD_P6x8Str(13,5,(uint8_t*)"KEY1 Pressed!   ");
    else LCD_P6x8Str(13,5,(uint8_t*)"KEY1 NO Pressed!");
    if(KEY_Read(KEY2)==0)
      LCD_P6x8Str(13,7,(uint8_t*)"KEY2 Pressed!   ");
    else LCD_P6x8Str(13,7,(uint8_t*)"KEY2 NO Pressed!");
    
    //LED闪烁
    LED_Ctrl(LED1, RVS);     
    
    //延时
    time_delay_ms(50);
  }
}

void PORTB_IRQHandler(void)
{
  int n;
  n=20;
  if((PORTB_ISFR & (1<<n)))
  {
      PORTB_ISFR |= (1<<n);
      /* 用户自行添加中断内程序 */
      LED_Ctrl(LED0, RVS); 
  }
  n=21;
  if((PORTB_ISFR & (1<<n)))
  {
      PORTB_ISFR |= (1<<n);
      /* 用户自行添加中断内程序 */
      LED_Ctrl(LED1, RVS); 
  }
  n=22;
  if((PORTB_ISFR & (1<<n)))
  {
      PORTB_ISFR |= (1<<n);
      /* 用户自行添加中断内程序 */
      LED_Ctrl(LED2, RVS); 
  }
}

void Test_GPIO_EXINT(void)
{  
  EXTI_Init(GPIOB,22,rising_down);   //K2
  EXTI_Init(GPIOB,21,falling_up);    //K1中断  
  EXTI_Init(GPIOB,20,falling_up);    //K0中断 
  for(;;)
  {  
    //systick中断延时
    time_delay_ms(5);
  }
}
 /*
    函数作用 :板载led初始化
    注：核心板上有三个可编程LED，端口分别是 PTA19,PTE6,PTC18,低电平点亮
      端口定义在 led.h
 */ 

void water_lights()
{
  LED_GREEN_ON;
  LED_RED_OFF;
  LED_BLUE_OFF;
  time_delay_ms(150);
  LED_GREEN_OFF;
  LED_RED_ON;
  LED_BLUE_OFF;
  time_delay_ms(150);
  LED_GREEN_OFF;
  LED_RED_OFF;
  LED_BLUE_ON;
  time_delay_ms(150);
}
void led_flash()
{
  LED_GREEN_ON;
  LED_RED_ON;
  LED_BLUE_ON;
  time_delay_ms(500);
  LED_GREEN_OFF;
  LED_RED_OFF;
  LED_BLUE_OFF;
  time_delay_ms(500);
}