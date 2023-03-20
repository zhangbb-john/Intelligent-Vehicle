/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�MK66FX1M0VLQ18���İ�
����    д��CHIUSIR
����    ע��
������汾��V1.0
�������¡�2016��08��20��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
���������䡿chiusir@163.com
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef __LPTMR_H__
#define __LPTMR_H__

/**
 *  @brief LPTMR�����������ܽ�ѡ��
 */
typedef enum
{
    //ֻ��1��2�ܽţ���û��0��3�ܽ�
    LPT0_ALT1 = 1,      // PTA19
    LPT0_ALT2 = 2       // PTC5
} LPT0_ALTn;

/**
 *  @brief LPTMR�������������ʽ
 */
typedef enum LPT_CFG
{
    LPT_Rising  = 0,    //�����ش���
    LPT_Falling = 1     //�½��ش���
} LPT_CFG;

#define LPTMR_Flag_Clear()  (LPTMR0_CSR |= LPTMR_CSR_TCF_MASK)         //���LPT�Ƚϱ�־λ


/*          ������ʱ         */
extern void     LPTMR_delay_ms(uint16 ms);      //��ʱ(ms)
extern void     LPTMR_delay_us(uint16 us);      //��ʱ(us)

/*       ���ڶ�ʱ           */
extern void     LPTMR_timing_ms(uint16 ms);     //��ʱ(ms)
extern void     LPTMR_timing_us(uint16 ms);     //��ʱ(us)

/*        ���ڼ�ʱ           */
extern void     LPTMR_time_start_ms(void);      //��ʼ��ʱ(ms)
extern uint32   LPTMR_time_get_ms(void);        //��ȡ��ʱʱ�� 

extern void     LPTMR_time_start_us(void);      //��ʼ��ʱ(ns)
extern uint32   LPTMR_time_get_us(void);        //��ȡ��ʱʱ�� 

extern void     LPTMR_time_close();             //�رռ�ʱ��


/*       �����������        */
extern void     LPTMR_Pulse_Init  (LPT0_ALTn, uint16 count, LPT_CFG);   //��������ʼ������
extern uint16   LPTMR_Pulse_Get   (void);                               //��ȡ����ֵ
extern void     LPTMR_Pulse_Clean (void);                               //��ռ���ֵ


/*      �жϸ�λ����ģ��    */
extern void LPTMR_test_handler(void);                                       //�жϸ�λ�����������ο������û�����ʵ�֣�
extern void LPTMR_Interrupt(void);
extern void Test_LPTMR_Counter(void);
extern void Test_LPTMR_delay(void);

#endif 
