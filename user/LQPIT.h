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
#ifndef _PIT_H_
#define _PIT_H_


#define PIT_Flag_Clear(PITn)   PIT_TFLG(PITn)|=PIT_TFLG_TIF_MASK      //���жϱ�־

extern u32 Value;

//ģ�鶨��
typedef enum PITn
{
    PIT0,
    PIT1,
    PIT2,
    PIT3
} PITn;

/*********************** PIT���ܺ��� **************************/
void PIT_Init(PITn, u32 cnt);                                            //��ʼ��PITn�������ö�ʱʱ��(��λΪbusʱ������)
void PIT0_Interrupt();
void PIT1_Interrupt();
void PIT2_Interrupt();
void PIT3_Interrupt();
void Test_PIT(void);

#endif  