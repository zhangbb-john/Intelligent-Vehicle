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

#ifndef __UART_H__
#define __UART_H__

extern uint32 core_clk_M;//单位MHZ
extern uint32 bus_clk_M;//单位MHZ

//定义模块号
typedef enum
{
    UART_0,
    UART_1,
    UART_2,
    UART_3,
    UART_4,
    UART_5,
    UART_MAX,
} UARTn_e;

extern UART_MemMapPtr UARTN[UART_MAX];

/**********************************  UART(引脚复用)已确认20171218***************************/
//      模块通道    端口          可选范围                          建议
#define UART0_RX    PTA15       //PTA1、PTA15、PTB16、PTD6 PTE21 PTB0 PTC6      PTA1不要用（与J-LINK冲突）
#define UART0_TX    PTA14       //PTA2、PTA14、PTB17、PTD7 PTE20 PTB1 PTC7     PTA2不要用（与J-LINK冲突）

#define UART1_RX    PTC3        //PTC3、PTE1
#define UART1_TX    PTC4        //PTC4、PTE0

#define UART2_RX    PTD2        //PTD2 PTE17
#define UART2_TX    PTD3        //PTD3 PTE16

#define UART3_RX    PTC16       //PTB10、PTC16、PTE5
#define UART3_TX    PTC17       //PTB11、PTC17、PTE4

#define UART4_RX    PTE25       //PTC14、PTE25
#define UART4_TX    PTE24       //PTC15、PTE24

#define UART5_RX    PTE9        //PTD8 、PTE9 
#define UART5_TX    PTE8        //PTD9 、PTE8 
/**********************************  UART(引脚复用) ***************************************/



/*********************** UART功能函数 **************************/
//初始化
extern void UART_Init      (UARTn_e, uint32 baud);             //初始化uartx模块

//接收相关代码
extern  char UART_Get_Char (UARTn_e uratn);                //等待接受1个字节
extern  char UART_Query_Char (UARTn_e, char *ch);                //查询接收1个字符
extern  char UART_Query_Str  (UARTn_e, char *str, uint32 max_len); //查询接收字符串
extern  char UART_Query    (UARTn_e);                          //查询是否接收到一个字节
//发送相关代码
extern void UART_Put_Char   (UARTn_e, char ch);                 //发送1个字节
extern void UART_Put_Buff   (UARTn_e , s8 *buff, uint32 len);//发送len个字节buff
extern void UART_Put_Str    (UARTn_e , const uint8 *str);       //发送字符串

void UART_Irq_En(UARTn_e uratn);
void UART_Irq_Dis(UARTn_e uratn);
extern void UART0_IRQHandler(void);
extern void UART1_IRQHandler(void);
extern void UART2_IRQHandler(void);
extern void UART3_IRQHandler(void);
extern void UART4_IRQHandler(void);
/********************************************************************/
void Test_UART(void);
#endif 
