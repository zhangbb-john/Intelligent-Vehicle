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
��busclock��120.000MHz
��pllclock��240.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef __GPIO_H__
#define __GPIO_H__

extern GPIO_MemMapPtr GPIOX[5] ; //�������ָ�����鱣�� GPIOX �ĵ�ַ
extern PORT_MemMapPtr PORTX[5] ;

#define  PULLDOWN    (0x02 << PORT_PCR_PS_SHIFT)     //����
#define  PULLUP      (0x03 << PORT_PCR_PS_SHIFT)     //����
//����ܽŷ���
typedef enum GPIO_CFG
{
    //�����ֵ���ܸģ�����
    GPI         = 0,                          //����ܽ����뷽��      GPIOx_PDDRn�0��ʾ���룬1��ʾ���
    GPO         = 1,                          //����ܽ��������

    GPI_DOWN    = 0x02,                       //��������              PORTx_PCRn��ҪPE=1��PS=0
    GPI_UP      = 0x03,                       //��������              PORTx_PCRn��ҪPE=1��PS=1
    GPI_PF      = 0x10,                       //���룬����Դ�˲���,�˲���Χ��10 MHz ~ 30 MHz ����֧�ָ��ٽӿڣ�>=2MHz��  0b10000           Passive Filter Enable
    GPI_DOWN_PF = GPI_DOWN | GPI_PF ,         //��������������Դ�˲���
    GPI_UP_PF   = GPI_UP   | GPI_PF ,         //��������������Դ�˲���

    GPO_HDS     = 0x41,                        //�������������   0b100 0001    High drive strength
    GPO_SSR     = 0x05,                        //������仯��          0b101     Slow slew rate
    GPO_HDS_SSR = GPO_HDS | GPO_SSR,           //������������������仯��
} GPIO_CFG;  //���λΪ0���϶������룻GPI_UP �� GPI_UP_PF�����λΪ1������Ϊ���



typedef enum exti_cfg
{
    rising_DMA        = 0x01,     //�����ش���DMA�ж�
    falling_DMA       = 0x02,     //�½��ش���DMA�ж�
    either_down_DMA   = 0x03,     //�����ش���DMA�ж�

    //�����λ��־����������
    zero          = 0x08,     //�͵�ƽ����
    rising        = 0x09,     //�����ش���
    falling       = 0x0A,     //�½��ش���
    either        = 0x0B,     //�����ش���
    one           = 0x0C,      //�ߵ�ƽ����
      
    zero_down     = 0x08u,     //�͵�ƽ�������ڲ�����
    rising_down   = 0x09u,     //�����ش������ڲ�����
    falling_down  = 0x0Au,     //�½��ش������ڲ�����
    either_down   = 0x0Bu,     //�����ش������ڲ�����
    one_down      = 0x0Cu,     //�ߵ�ƽ�������ڲ�����

    //�����λ��־����������
    zero_up       = 0x88u,     //�͵�ƽ�������ڲ�����
    rising_up     = 0x89u,     //�����ش������ڲ�����
    falling_up    = 0x8Au,     //�½��ش������ڲ�����
    either_up     = 0x8Bu,     //�����ش������ڲ�����
    one_up        = 0x8Cu      //�ߵ�ƽ�������ڲ�����
} exti_cfg;

#define GPIOX_BASE(PTxn)    GPIOX[PTX(PTxn)]       //GPIOģ��ĵ�ַ
#define PTX(PTxn)           ((PTxn)>>5)
#define PTn(PTxn)           ((PTxn)&0x1f)
#define PORTX_BASE(PTxn)     PORTX[PTX(PTxn)]       //PORTģ��ĵ�ַ
/*********************** GPIO���ܺ��� **************************/
void GPIO_Init (GPIO_Type* port, int index, GPIO_CFG dir,int data);
void GPIO_Ctrl (GPIO_Type* port, int index, int data);
void GPIO_Reverse (GPIO_Type* port, int index);
u8 GPIO_Get(PTXn_e ptxn);
uint8 gpio_get(PTXn_e ptxn);
void EXTI_Init(GPIO_Type * port, u8 n, exti_cfg cfg);
void gpio_set(PTXn_e ptxn, uint8 data);
void gpio_turn(PTXn_e ptxn);
uint8 gpio_get(PTXn_e ptxn);
#endif
