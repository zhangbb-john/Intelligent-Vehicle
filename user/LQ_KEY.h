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
#ifndef __LQ_KEY_H__
#define __LQ_KEY_H__

#include "include.h"
#define BT_SHOW    PTB20
#define BT_LEFT   PTB21
#define BT_UP      PTB22
//#define BT_DOWN    PTC9
//#define BT_YES     PTC5
//#define BT_LEFT    PTC10

#define SW1      PTC6
#define SW2      PTC7
#define SW3      PTC8
#define SW4      PTC9


#define SW1_IN   gpio_get(SW1)
#define SW2_IN   gpio_get(SW2)
#define SW3_IN   gpio_get(SW3)
#define SW4_IN   gpio_get(SW4)

#define BT_SHOW_IN   (gpio_get(BT_SHOW)||(!gpio_get(SW1)))
#define BT_LEFT_IN   (gpio_get(BT_LEFT)||(!gpio_get(SW1)))
#define BT_UP_IN     (gpio_get(BT_UP)||(!gpio_get(SW1)))
#define BT_DOWN_IN   (gpio_get(BT_SHOW)||(gpio_get(SW1)))
#define BT_YES_IN    (gpio_get(BT_LEFT)||(gpio_get(SW1)))
#define BT_RIGHT_IN  (gpio_get(BT_UP)||(gpio_get(SW1)))

/*******************************************************************************
* Definitions
******************************************************************************/
//定义模块号
typedef enum
{
    KEY0=0,
    KEY1=1,
    KEY2=2,   
} KEYn_e;
typedef enum
{
    LOW=0,  //DOWN
    HIGH=1, //UP  
    FAIL=0xff,
}KEYs_;//e;

extern void TestLED(void);
extern void KEY_SW_Init(void);
extern u8 KEY_Read(KEYn_e keyno);
extern void  Test_GPIO_KEY(void);
extern void  Test_GPIO_EXINT(void);
void water_lights(); 
void led_flash();
#endif 
