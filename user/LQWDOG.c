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
                                                        
//��  ��: �رտ��Ź�ģ��   
void Kick_Dog(void)
{
    //�����Ź�ģ��������Ա�д�Ĵ���
    Feed_Dog();
    //�رտ��Ź�
    WDOG_STCTRLH &= ~WDOG_STCTRLH_WDOGEN_MASK;
}
                                                   
//��  ��: ���Ź�����     
void Feed_Dog(void)
{
    //ע�⣺ ��Ҫ�������Դ˳���!!! ��������ܻ�����CPU��λ
    //�����ж�
    DisableInterrupts;		
    //д�����Ĵ���
    WDOG_UNLOCK = 0xC520;	
    //��ɽ���
    WDOG_UNLOCK = 0xD928;	
    //�����ж�
    EnableInterrupts;		
}
