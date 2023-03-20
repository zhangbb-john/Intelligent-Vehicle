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

GPIO_MemMapPtr GPIOX[5] = {GPIOA_BASE_PTR, GPIOB_BASE_PTR, GPIOC_BASE_PTR, GPIOD_BASE_PTR, GPIOE_BASE_PTR}; //�������ָ�����鱣�� GPIOX �ĵ�ַ
PORT_MemMapPtr PORTX[5] = {PORTA_BASE_PTR, PORTB_BASE_PTR, PORTC_BASE_PTR, PORTD_BASE_PTR, PORTE_BASE_PTR};
//-------------------------------------------------------------------------*
//������: gpio_init                                                        *
//��  ��: ��ʼ��gpio                                                       *
//��  ��: port:�˿���                                                      *
//        index:ָ���˿�����                                               *
//        dir:���ŷ���,0=����,1=���                                       *
//        data:��ʼ״̬,0=�͵�ƽ,1=�ߵ�ƽ                                  *
//��  ��: ��                                                              *
//��  ��: gpio_init (PORTA, 17, 1,0);  PTA17���ų�ʼ��Ϊ�͵�ƽ             *
//-------------------------------------------------------------------------*
void GPIO_Init (GPIO_Type* port, int index, GPIO_CFG dir,int data)
{

     SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK
                 | SIM_SCGC5_PORTB_MASK
                 | SIM_SCGC5_PORTC_MASK
                 | SIM_SCGC5_PORTD_MASK
                 | SIM_SCGC5_PORTE_MASK );

     PORT_MemMapPtr p;
     switch((u32)port)
     {
     case 0x400FF000u:
         p = PORTA;
         break;
     case 0x400FF040u:
         p = PORTB;
         break;
     case 0x400FF080u:
         p = PORTC;
         break;
     case 0x400FF0C0u:
         p = PORTD;
         break;
     case 0x400FF100u:
         p = PORTE;
         break;
     default:
         break;
     }
     PORT_PCR_REG(p,index)=PORT_PCR_MUX(1);

     if(dir == 1)//output
     {
    	 GPIO_PDDR_REG(port) |= (1<<index);
    	 if(data == 1)//output
			  GPIO_PDOR_REG(port) |= (1<<index);
		 else
			  GPIO_PDOR_REG(port) &= ~(1<<index);
	 }
	 
	 else
		 GPIO_PDDR_REG(port) &= ~(1<<index);
	 
	 if(dir == GPI_UP)
	 {
		 PORT_PCR_REG(p,index) |= PULLUP;            //������������������
	 }
	 else if(dir == GPI_DOWN)
	 {
		 PORT_PCR_REG(p,index) |= PULLDOWN;            //������������������
	 }

}


//-------------------------------------------------------------------------*
//������: gpio_ctrl                                                        *
//��  ��: ��������״̬                                                     *
//��  ��: port:�˿���                                                      *
//        index:ָ���˿�����                                               *
//        data: ״̬,0=�͵�ƽ,1=�ߵ�ƽ                                     *
//��  ��: ��                                                               *
//��  ��: gpio_ctrl (PORTA, 17,0);  PTA17���ų�����Ϊ�͵�ƽ                 *
//-------------------------------------------------------------------------*
void GPIO_Ctrl (GPIO_Type* port, int index, int data)
{
    if(data == 1)//output
         GPIO_PDOR_REG(port) |= (1<<index);
    else
         GPIO_PDOR_REG(port) &= ~(1<<index);
}

//-----------------------------------------------------------------------*
//������: gpio_reverse                                                   *
//��  ��: �ı�����״̬                                                   *
//��  ��: port:�˿���;                                                   *
//        index:ָ���˿�����                                             *
//��  ��: ��                                                             *
//��  ��: gpio_reverse (PORTA, 17);  PTA17���������ƽ��ת                *
//-----------------------------------------------------------------------*
void GPIO_Reverse (GPIO_Type* port, int index)
{
    GPIO_PDOR_REG(port) ^= (1<<index);
}
//-----------------------------------------------------------------------*
//������: u8 GPIO_Get(PTXn_e ptxn)                                       *
//��  ��: ��ȡ����״̬                                                   *
//��  ��: ptxn�˿������ţ�����PTA17                                      *
//��  ��: ��0,��1                                                        *
//��  ��: x=GPIO_Get(PTA17);  ��ȡPTA17���ŵ�ƽ�ߵ�                      *
//-----------------------------------------------------------------------*
u8 GPIO_Get(PTXn_e ptxn)
{
    return ((GPIO_PDIR_REG(GPIOX_BASE(ptxn)) >> PTn(ptxn )) & 0x01);        // ��ȡ GPIO PDIR ptxn ״̬������ȡ�ܽ������ƽ
}

/*!
 *  @brief      �����������ݷ���
 *  @param      PTxn    �˿�
 *  @param      cfg     ���ŷ���,0=����,1=���
 *  @since      v5.0
 *  Sample usage:       gpio_ddr (PTA8, GPI);    //���� PTA8 �ܽ�Ϊ����
 */
void    gpio_ddr   (PTXn_e ptxn, GPIO_CFG cfg)
{
    //�˿ڷ���������뻹�����
    if(  cfg == GPI )
    {
        //���ö˿ڷ���Ϊ����
        GPIO_PDDR_REG(GPIOX_BASE(ptxn)) &= ~(1 << PTn(ptxn));           // GPIO PDDR �ܽź� ��0������Ӧ�ܽ�����Ϊ�˿ڷ�������
    }
    else
    {
        //���ö˿ڷ���Ϊ���
        GPIO_PDDR_REG(GPIOX_BASE(ptxn)) |= (1 << PTn(ptxn));            // GPIO PDDR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿ڷ������
    }
}

/*!
 *  @brief      ��������״̬
 *  @param      PTxn    �˿�
 *  @param      data    �����ʼ״̬,0=�͵�ƽ,1=�ߵ�ƽ ����������Ч��
 *  @since      v5.0
 *  @warning    ��ر�֤���ݷ���Ϊ�����DEBUGģʽ�£��ж��Խ��м�⣩
 *  Sample usage:       gpio_set (PTA8, 1);    // PTA8 �ܽ� ��� 1
 */
void gpio_set (PTXn_e ptxn, uint8 data)
{
    //�˿��������
    if(data == 0)
    {
        GPIO_PDOR_REG(GPIOX_BASE(ptxn)) &= ~(1 << PTn(ptxn));   // GPIO PDOR �ܽź� ��0������Ӧ�ܽ�����Ϊ�˿�����͵�ƽ
    }
    else
    {
        GPIO_PDOR_REG(GPIOX_BASE(ptxn))  |= (1 << PTn(ptxn));   // GPIO PDOR �ܽź� ��1������Ӧ�ܽ�����Ϊ�˿�����ߵ�ƽ
    }
}


/*!
 *  @brief      ��ת����״̬
 *  @param      PTxn    �˿�
 *  @since      v5.0
 *  @warning    ��ر�֤���ݷ���Ϊ�����DEBUGģʽ�£��ж��Խ��м�⣩
 *  Sample usage:       gpio_turn (PTA8);    // PTA8 �ܽ� ��� ��ת
 */
void gpio_turn (PTXn_e ptxn)
{
    GPIO_PTOR_REG( GPIOX_BASE(ptxn))  =  1 << (PTn(ptxn ));                 // GPIO PTOR ptxn ��1��������0 ������Ӧ�ܽ�����Ϊ�˿������ת������λ����
                                                                            // �˴������� BIT_SET ���������1 ����Ϊ���뱣֤����λ ���䣬����λֱ����0����
}

/*!
 *  @brief      ��ȡ��������״̬
 *  @param      PTxn    �˿�
 *  @return     �ܽŵ�״̬��1Ϊ�ߵ�ƽ��0Ϊ�͵�ƽ
 *  @since      v5.0
 *  @warning    ��ر�֤���ݷ���Ϊ���루DEBUGģʽ�£��ж��Խ��м�⣩
 *  Sample usage:       uint8 pta8_data = gpio_get (PTA8);    // ��ȡ PTA8 �ܽ� �����ƽ
 */
uint8 gpio_get(PTXn_e ptxn)
{
    return ((GPIO_PDIR_REG(GPIOX_BASE(ptxn)) >> PTn(ptxn )) & 0x01);        // ��ȡ GPIO PDIR ptxn ״̬������ȡ�ܽ������ƽ
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**************************************************************************************************************************
                                                    gpio�ⲿ�жϺ���
**************************************************************************************************************************/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------*
//������: Exti_init
//��  ��: �ⲿGPIO�жϳ�ʼ��
//��  ��: portx:�˿�����PTA,PTB,PTC,PTD,PTE��
//          n  :ָ���˿����źţ�0~31��
//     exti_cfg:�жϴ�����ʽ  �磺 rising_down //�����ش������ڲ�����
//��  ��: ��
//��  ��: exti_init(PTC, 16, rising_down);
//-----------------------------------------------------------------------*
void EXTI_Init(GPIO_Type * port, u8 n, exti_cfg cfg)
{
   // SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK << portx);    //����PORTx�˿�
    IRQn_Type IRQ;
    PORT_MemMapPtr p;
     switch((u32)port)
     {
     case 0x400FF000u:
         p = PORTA_BASE_PTR;
         IRQ=PORTA_IRQn;
         break;
     case 0x400FF040u:
         p = PORTB_BASE_PTR;
         IRQ=PORTB_IRQn;
         break;
     case 0x400FF080u:
         p = PORTC_BASE_PTR;
         IRQ=PORTC_IRQn;
         break;
     case 0x400FF0C0u:
         p = PORTD_BASE_PTR;
         IRQ=PORTD_IRQn;
         break;
     case 0x400FF100u:
         p = PORTE_BASE_PTR;
         IRQ=PORTE_IRQn;
         break;
     default:
         break;
     }

    PORT_PCR_REG(p, n) = PORT_PCR_MUX(1) |PORT_PCR_IRQC(cfg) ; // ����GPIO , ȷ������ģʽ ,������������������
    NVIC_EnableIRQ(IRQ);                         //ʹ��PORT�жϣ�PORTA��ISR�жϺ�Ϊ87
}


