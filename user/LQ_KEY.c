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

void KEY_SW_Init(void)
{
	//key
  GPIO_Init(GPIOB,20,GPI,1);
  GPIO_Init(GPIOB,21,GPI,1);
  GPIO_Init(GPIOB,22,GPI,1); //��ʼ״̬�ߵ�ƽ
  
  
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
����  �ߡ�CHIUSIR
������˵�������԰�����OLED��ʾ
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_GPIO_KEY(void)
{ 
  while (1)
  {  
    //���԰���      
    if(KEY_Read(KEY0)==0)
      LCD_P6x8Str(13,3,(uint8_t*)"KEY0 Pressed!   ");
    else LCD_P6x8Str(13,3,(uint8_t*)"KEY0 NO Pressed!");
    if(KEY_Read(KEY1)==0)
      LCD_P6x8Str(13,5,(uint8_t*)"KEY1 Pressed!   ");
    else LCD_P6x8Str(13,5,(uint8_t*)"KEY1 NO Pressed!");
    if(KEY_Read(KEY2)==0)
      LCD_P6x8Str(13,7,(uint8_t*)"KEY2 Pressed!   ");
    else LCD_P6x8Str(13,7,(uint8_t*)"KEY2 NO Pressed!");
    
    //LED��˸
    LED_Ctrl(LED1, RVS);     
    
    //��ʱ
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
      /* �û���������ж��ڳ��� */
      LED_Ctrl(LED0, RVS); 
  }
  n=21;
  if((PORTB_ISFR & (1<<n)))
  {
      PORTB_ISFR |= (1<<n);
      /* �û���������ж��ڳ��� */
      LED_Ctrl(LED1, RVS); 
  }
  n=22;
  if((PORTB_ISFR & (1<<n)))
  {
      PORTB_ISFR |= (1<<n);
      /* �û���������ж��ڳ��� */
      LED_Ctrl(LED2, RVS); 
  }
}

void Test_GPIO_EXINT(void)
{  
  EXTI_Init(GPIOB,22,rising_down);   //K2
  EXTI_Init(GPIOB,21,falling_up);    //K1�ж�  
  EXTI_Init(GPIOB,20,falling_up);    //K0�ж� 
  for(;;)
  {  
    //systick�ж���ʱ
    time_delay_ms(5);
  }
}
 /*
    �������� :����led��ʼ��
    ע�����İ����������ɱ��LED���˿ڷֱ��� PTA19,PTE6,PTC18,�͵�ƽ����
      �˿ڶ����� led.h
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