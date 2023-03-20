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

#ifndef __UART_H__
#define __UART_H__

extern uint32 core_clk_M;//��λMHZ
extern uint32 bus_clk_M;//��λMHZ

//����ģ���
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

/**********************************  UART(���Ÿ���)��ȷ��20171218***************************/
//      ģ��ͨ��    �˿�          ��ѡ��Χ                          ����
#define UART0_RX    PTA15       //PTA1��PTA15��PTB16��PTD6 PTE21 PTB0 PTC6      PTA1��Ҫ�ã���J-LINK��ͻ��
#define UART0_TX    PTA14       //PTA2��PTA14��PTB17��PTD7 PTE20 PTB1 PTC7     PTA2��Ҫ�ã���J-LINK��ͻ��

#define UART1_RX    PTC3        //PTC3��PTE1
#define UART1_TX    PTC4        //PTC4��PTE0

#define UART2_RX    PTD2        //PTD2 PTE17
#define UART2_TX    PTD3        //PTD3 PTE16

#define UART3_RX    PTC16       //PTB10��PTC16��PTE5
#define UART3_TX    PTC17       //PTB11��PTC17��PTE4

#define UART4_RX    PTE25       //PTC14��PTE25
#define UART4_TX    PTE24       //PTC15��PTE24

#define UART5_RX    PTE9        //PTD8 ��PTE9 
#define UART5_TX    PTE8        //PTD9 ��PTE8 
/**********************************  UART(���Ÿ���) ***************************************/



/*********************** UART���ܺ��� **************************/
//��ʼ��
extern void UART_Init      (UARTn_e, uint32 baud);             //��ʼ��uartxģ��

//������ش���
extern  char UART_Get_Char (UARTn_e uratn);                //�ȴ�����1���ֽ�
extern  char UART_Query_Char (UARTn_e, char *ch);                //��ѯ����1���ַ�
extern  char UART_Query_Str  (UARTn_e, char *str, uint32 max_len); //��ѯ�����ַ���
extern  char UART_Query    (UARTn_e);                          //��ѯ�Ƿ���յ�һ���ֽ�
//������ش���
extern void UART_Put_Char   (UARTn_e, char ch);                 //����1���ֽ�
extern void UART_Put_Buff   (UARTn_e , s8 *buff, uint32 len);//����len���ֽ�buff
extern void UART_Put_Str    (UARTn_e , const uint8 *str);       //�����ַ���

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
