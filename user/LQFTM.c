/*******************************************************************************
��ƽ    ̨������KV58F24���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��2��2��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4�����ϰ汾840 1400 1790
��Target  ��MKV58F1M0VLQ24
��Crystal �� 50.000Mhz
��busclock��137.500MHz
��pllclock��275.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

FTM_MemMapPtr FTMN[3] = {FTM0_BASE_PTR, FTM1_BASE_PTR, FTM2_BASE_PTR}; //��������ָ�����鱣�� FTMn_e �ĵ�ַ


//-------------------------------------------------------------------------*
//������: FTM_PWM_init
//��  ��: FTM��PWM����
//��  ��: ftmn:ģ����FTM0,FTM1��FTM2
//        ch  :ͨ���� ��Ӧ���Ųο�ftm.h�ļ�
//        mod :������  ��Χ��0~65535��
//        cv  :�ߵ�ƽ��� ��Χ��0~mod��
//��  ��: ��
//��  ��: FTM_PWM_init(FTM0,FTM_CH6,65535,32768); ����ռ�ձ���50%
//-------------------------------------------------------------------------*
void FTM_PWM_Init(FTM_Type * ftmn, FTM_CHn_e ch, u16 mod, u16 cv)
{
  /******************* ����ʱ�� �� ����IO��*******************/
    switch((u32)ftmn)
    {
    case FTM0_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;       //ʹ��FTM0ʱ��
        switch(ch)
        {
        case FTM_CH0:
            if(FTM0_CH0 == PTC1)
            {
                PORT_PCR_REG(PORTC,1)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH0 == PTA3)
            {
                PORT_PCR_REG(PORTA,3)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH0 == PTE24)
            {
                PORT_PCR_REG(PORTE,24)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH0 == PTD0)
            {
                PORT_PCR_REG(PORTD,0)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH1:
            if(FTM0_CH1 == PTC2)
            {
                PORT_PCR_REG(PORTC,2)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH1 == PTA4)
            {
                PORT_PCR_REG(PORTA,4)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH1 == PTE25)
            {
                PORT_PCR_REG(PORTE,25)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH1 == PTD1)
            {
                PORT_PCR_REG(PORTD,1)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH2:
            if(FTM0_CH2 == PTC3)
            {
                PORT_PCR_REG(PORTC,3)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH2 == PTA5)
            {
                PORT_PCR_REG(PORTA,5)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH2 == PTE29)
            {
                PORT_PCR_REG(PORTE,29)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH2 == PTD2)
            {
                PORT_PCR_REG(PORTD,2)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH3:
            if(FTM0_CH3 == PTC4)
            {
                PORT_PCR_REG(PORTC,4)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH3 == PTA6)
            {
                PORT_PCR_REG(PORTA,6)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH3 == PTE30)
            {
                PORT_PCR_REG(PORTE,30)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH3 == PTD3)
            {
                PORT_PCR_REG(PORTD,3)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH4:
            if(FTM0_CH4 == PTD4)
            {
                PORT_PCR_REG(PORTD,4)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH4 == PTA7)
            {
                PORT_PCR_REG(PORTA,7)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH4 == PTE26)
            {
                PORT_PCR_REG(PORTE,26)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH4 == PTD4)
            {
                PORT_PCR_REG(PORTD,4)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH5:
            if(FTM0_CH5 == PTD5)
            {
                PORT_PCR_REG(PORTD,5)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH5 == PTA0)
            {
                PORT_PCR_REG(PORTA,0)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH5 == PTD5)
            {
                PORT_PCR_REG(PORTD,5)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH6:
            if(FTM0_CH6 == PTD6)
            {
                PORT_PCR_REG(PORTD,6)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH6 == PTA1)
            {
                PORT_PCR_REG(PORTA,1)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH6 == PTD6)
            {
                PORT_PCR_REG(PORTD,6)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH7:
            if(FTM0_CH7 == PTD7)
            {
                PORT_PCR_REG(PORTD,7)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH7 == PTA2)
            {
                PORT_PCR_REG(PORTA,2)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH7 == PTD7)
            {
                PORT_PCR_REG(PORTD,7)=PORT_PCR_MUX(4);
            }
            break;
        default:
            return;
        }
        break;

    case FTM1_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;       //ʹ��FTM1ʱ��
        switch(ch)
        {
        case FTM_CH0:
            if(FTM1_CH0 == PTA8)
            {
                PORT_PCR_REG(PORTA,8)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH0 == PTA12)
            {
               PORT_PCR_REG(PORTA,12)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH0 == PTB0)
            {
                PORT_PCR_REG(PORTB,0)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH0 == PTE20)
            {
               PORT_PCR_REG(PORTE,20)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH0 == PTA2)
            {
               PORT_PCR_REG(PORTA,2)=PORT_PCR_MUX(6);
            }
            else if(FTM1_CH0 == PTD6)
            {
               PORT_PCR_REG(PORTD,6)=PORT_PCR_MUX(5);
            }
            break;


        case FTM_CH1:
            if(FTM1_CH1 == PTA9)
            {
                PORT_PCR_REG(PORTA,9)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH1 == PTA13)
            {
                PORT_PCR_REG(PORTA,13)=PORT_PCR_MUX(3);
            }
              else if(FTM1_CH1 == PTB1)
            {
                PORT_PCR_REG(PORTB,1)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH1 == PTE21)
            {
               PORT_PCR_REG(PORTE,21)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH1 == PTA1)
            {
               PORT_PCR_REG(PORTA,1)=PORT_PCR_MUX(6);
            }
            else if(FTM1_CH1 == PTD7)
            {
               PORT_PCR_REG(PORTD,7)=PORT_PCR_MUX(5);
            }
            break;

        default:
            return;
        }
        break;

    case FTM2_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;                           //ʹ��FTM2ʱ��
        switch(ch)
        {
        case FTM_CH0:
            if(FTM2_CH0 == PTA10)
            {
                PORT_PCR_REG(PORTA,10)=PORT_PCR_MUX(3);
            }
            else if(FTM2_CH0 == PTB18)
            {
                PORT_PCR_REG(PORTB,18)=PORT_PCR_MUX(3);
            }
            else if(FTM2_CH0 == PTE22)
            {
                PORT_PCR_REG(PORTE,22)=PORT_PCR_MUX(3);
            }
            break;

        case FTM_CH1:
            if(FTM2_CH1 == PTA11)
            {
                PORT_PCR_REG(PORTA,11)=PORT_PCR_MUX(3);
            }
            else if(FTM2_CH1 == PTB19)
            {
                PORT_PCR_REG(PORTB,19)=PORT_PCR_MUX(3);
            }
            else if(FTM2_CH1 == PTE23)
            {
                PORT_PCR_REG(PORTE,23)=PORT_PCR_MUX(3);
            }
            break;

        default:
            return;
        }
        break;

   case FTM3_BASE:
        SIM_SCGC3 |= SIM_SOPT8_FTM3OCH1SRC_MASK;

         switch(ch)
        {
        case FTM_CH0:
            if(FTM3_CH0 == PTE5)
            {
                PORT_PCR_REG(PORTE,5)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH0 == PTD0)
            {
                PORT_PCR_REG(PORTD,0)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH1:
            if(FTM3_CH1 == PTE6)
            {
                PORT_PCR_REG(PORTE,6)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH1 == PTD1)
            {
                PORT_PCR_REG(PORTD,1)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH2:
            if(FTM3_CH2 == PTE7)
            {
                PORT_PCR_REG(PORTE,7)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH2 == PTD2)
            {
                PORT_PCR_REG(PORTD,2)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH3:
            if(FTM3_CH3 == PTE8)
            {
                PORT_PCR_REG(PORTE,8)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH3 == PTD3)
            {
                PORT_PCR_REG(PORTD,3)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH4:
            if(FTM3_CH4 == PTE9)
            {
                PORT_PCR_REG(PORTE,9)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH4 == PTD1)
            {
                PORT_PCR_REG(PORTC,8)=PORT_PCR_MUX(4);
            }
            else if(FTM3_CH5 == PTC8)
            {
                PORT_PCR_REG(PORTC,8)=PORT_PCR_MUX(3);
            }
            break;
        case FTM_CH5:
            if(FTM3_CH5 == PTE10)
            {
                PORT_PCR_REG(PORTE,10)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH5 == PTC9)
            {
                PORT_PCR_REG(PORTC,9)=PORT_PCR_MUX(3);
            }
            break;
        case FTM_CH6:
            if(FTM3_CH6 == PTE11)
            {
                PORT_PCR_REG(PORTE,11)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH6 == PTC10)
            {
                PORT_PCR_REG(PORTC,10)=PORT_PCR_MUX(3);
            }
            break;
        case FTM_CH7:
            if(FTM3_CH7 == PTE12)
            {
                PORT_PCR_REG(PORTE,12)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH7 == PTC11)
            {
                PORT_PCR_REG(PORTC,11)=PORT_PCR_MUX(3);
            }
            break;
       default:  return;

      }

       default:  break;
    }

               
    /******************** ѡ�����ģʽΪ ���ض���PWM *******************/
    //ͨ��״̬���ƣ�����ģʽ��ѡ�� ���ػ��ƽ
    FTM_CnSC_REG(ftmn, ch) &= ~FTM_CnSC_ELSA_MASK;
    FTM_CnSC_REG(ftmn, ch)  = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;

    /******************** ����ʱ�Ӻͷ�Ƶ ********************/
    FTM_SC_REG(ftmn)    = ( 0
                                  | FTM_SC_PS(4)      //��Ƶ2^FTM_SC_PS,Ƶ��Ϊ 275M/2/16
                                  | FTM_SC_CLKS(1)    //ʱ��ѡ��busʱ��
                          );                          //PMWƵ��=XϵͳƵ��/2/(2^FTM1_SC_PS)/FTM1_MOD
    FTM_MOD_REG(ftmn)   = mod;                        //ģ��, EPWM������Ϊ ��MOD - CNTIN + 0x0001
    FTM_CNTIN_REG(ftmn) = 0;                          //��������ʼ��ֵ�����������ȣ�(CnV - CNTIN).
    FTM_CnV_REG(ftmn, ch) = cv;
    FTM_CNT_REG(ftmn)   = 0;                          //��������ֻ�е�16λ���ã�д�κ�ֵ���˼Ĵ������������ CNTIN ��ֵ��

  //   FTM_PWMLOAD_REG(ftmn) = 0xFFff;
  //  FTM_COMBINE_REG(ftmn) =  FTM_COMBINE_COMBINE3_MASK ;
  //   FTM_MODE_REG(ftmn) &=~ FTM_MODE_WPDIS_MASK ; // д��������
}


void ServoFTM_PWM_Init(FTM_Type * ftmn, FTM_CHn_e ch, u16 mod, u16 cv)
{
  /******************* ����ʱ�� �� ����IO��*******************/
    switch((u32)ftmn)
    {
    case FTM0_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;       //ʹ��FTM0ʱ��
        switch(ch)
        {
        case FTM_CH0:
            if(FTM0_CH0 == PTC1)
            {
                PORT_PCR_REG(PORTC,1)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH0 == PTA3)
            {
                PORT_PCR_REG(PORTA,3)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH0 == PTE24)
            {
                PORT_PCR_REG(PORTE,24)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH0 == PTD0)
            {
                PORT_PCR_REG(PORTD,0)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH1:
            if(FTM0_CH1 == PTC2)
            {
                PORT_PCR_REG(PORTC,2)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH1 == PTA4)
            {
                PORT_PCR_REG(PORTA,4)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH1 == PTE25)
            {
                PORT_PCR_REG(PORTE,25)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH1 == PTD1)
            {
                PORT_PCR_REG(PORTD,1)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH2:
            if(FTM0_CH2 == PTC3)
            {
                PORT_PCR_REG(PORTC,3)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH2 == PTA5)
            {
                PORT_PCR_REG(PORTA,5)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH2 == PTE29)
            {
                PORT_PCR_REG(PORTE,29)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH2 == PTD2)
            {
                PORT_PCR_REG(PORTD,2)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH3:
            if(FTM0_CH3 == PTC4)
            {
                PORT_PCR_REG(PORTC,4)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH3 == PTA6)
            {
                PORT_PCR_REG(PORTA,6)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH3 == PTE30)
            {
                PORT_PCR_REG(PORTE,30)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH3 == PTD3)
            {
                PORT_PCR_REG(PORTD,3)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH4:
            if(FTM0_CH4 == PTD4)
            {
                PORT_PCR_REG(PORTD,4)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH4 == PTA7)
            {
                PORT_PCR_REG(PORTA,7)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH4 == PTE26)
            {
                PORT_PCR_REG(PORTE,26)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH4 == PTD4)
            {
                PORT_PCR_REG(PORTD,4)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH5:
            if(FTM0_CH5 == PTD5)
            {
                PORT_PCR_REG(PORTD,5)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH5 == PTA0)
            {
                PORT_PCR_REG(PORTA,0)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH5 == PTD5)
            {
                PORT_PCR_REG(PORTD,5)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH6:
            if(FTM0_CH6 == PTD6)
            {
                PORT_PCR_REG(PORTD,6)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH6 == PTA1)
            {
                PORT_PCR_REG(PORTA,1)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH6 == PTD6)
            {
                PORT_PCR_REG(PORTD,6)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH7:
            if(FTM0_CH7 == PTD7)
            {
                PORT_PCR_REG(PORTD,7)=PORT_PCR_MUX(4);
            }
            else if(FTM0_CH7 == PTA2)
            {
                PORT_PCR_REG(PORTA,2)=PORT_PCR_MUX(3);
            }
            else if(FTM0_CH7 == PTD7)
            {
                PORT_PCR_REG(PORTD,7)=PORT_PCR_MUX(4);
            }
            break;
        default:
            return;
        }
        break;

    case FTM1_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;       //ʹ��FTM1ʱ��
        switch(ch)
        {
        case FTM_CH0:
            if(FTM1_CH0 == PTA8)
            {
                PORT_PCR_REG(PORTA,8)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH0 == PTA12)
            {
               PORT_PCR_REG(PORTA,12)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH0 == PTB0)
            {
                PORT_PCR_REG(PORTB,0)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH0 == PTE20)
            {
               PORT_PCR_REG(PORTE,20)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH0 == PTA2)
            {
               PORT_PCR_REG(PORTA,2)=PORT_PCR_MUX(6);
            }
            else if(FTM1_CH0 == PTD6)
            {
               PORT_PCR_REG(PORTD,6)=PORT_PCR_MUX(5);
            }
            break;


        case FTM_CH1:
            if(FTM1_CH1 == PTA9)
            {
                PORT_PCR_REG(PORTA,9)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH1 == PTA13)
            {
                PORT_PCR_REG(PORTA,13)=PORT_PCR_MUX(3);
            }
              else if(FTM1_CH1 == PTB1)
            {
                PORT_PCR_REG(PORTB,1)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH1 == PTE21)
            {
               PORT_PCR_REG(PORTE,21)=PORT_PCR_MUX(3);
            }
            else if(FTM1_CH1 == PTA1)
            {
               PORT_PCR_REG(PORTA,1)=PORT_PCR_MUX(6);
            }
            else if(FTM1_CH1 == PTD7)
            {
               PORT_PCR_REG(PORTD,7)=PORT_PCR_MUX(5);
            }
            break;

        default:
            return;
        }
        break;

    case FTM2_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;                           //ʹ��FTM2ʱ��
        switch(ch)
        {
        case FTM_CH0:
            if(FTM2_CH0 == PTA10)
            {
                PORT_PCR_REG(PORTA,10)=PORT_PCR_MUX(3);
            }
            else if(FTM2_CH0 == PTB18)
            {
                PORT_PCR_REG(PORTB,18)=PORT_PCR_MUX(3);
            }
            else if(FTM2_CH0 == PTE22)
            {
                PORT_PCR_REG(PORTE,22)=PORT_PCR_MUX(3);
            }
            break;

        case FTM_CH1:
            if(FTM2_CH1 == PTA11)
            {
                PORT_PCR_REG(PORTA,11)=PORT_PCR_MUX(3);
            }
            else if(FTM2_CH1 == PTB19)
            {
                PORT_PCR_REG(PORTB,19)=PORT_PCR_MUX(3);
            }
            else if(FTM2_CH1 == PTE23)
            {
                PORT_PCR_REG(PORTE,23)=PORT_PCR_MUX(3);
            }
            break;

        default:
            return;
        }
        break;

   case FTM3_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM3_MASK;

         switch(ch)
        {
        case FTM_CH0:
            if(FTM3_CH0 == PTE5)
            {
                PORT_PCR_REG(PORTE,5)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH0 == PTD0)
            {
                PORT_PCR_REG(PORTD,0)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH1:
            if(FTM3_CH1 == PTE6)
            {
                PORT_PCR_REG(PORTE,6)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH1 == PTD1)
            {
                PORT_PCR_REG(PORTD,1)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH2:
            if(FTM3_CH2 == PTE7)
            {
                PORT_PCR_REG(PORTE,7)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH2 == PTD2)
            {
                PORT_PCR_REG(PORTD,2)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH3:
            if(FTM3_CH3 == PTE8)
            {
                PORT_PCR_REG(PORTE,8)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH3 == PTD3)
            {
                PORT_PCR_REG(PORTD,3)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH4:
            if(FTM3_CH4 == PTE9)
            {
                PORT_PCR_REG(PORTE,9)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH4 == PTD1)
            {
                PORT_PCR_REG(PORTC,8)=PORT_PCR_MUX(4);
            }
            else if(FTM3_CH5 == PTC8)
            {
                PORT_PCR_REG(PORTC,8)=PORT_PCR_MUX(3);
            }
            break;
        case FTM_CH5:
            if(FTM3_CH5 == PTE10)
            {
                PORT_PCR_REG(PORTE,10)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH5 == PTC9)
            {
                PORT_PCR_REG(PORTC,9)=PORT_PCR_MUX(3);
            }
            break;
        case FTM_CH6:
            if(FTM3_CH6 == PTE11)
            {
                PORT_PCR_REG(PORTE,11)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH6 == PTC10)
            {
                PORT_PCR_REG(PORTC,10)=PORT_PCR_MUX(3);
            }
            break;
        case FTM_CH7:
            if(FTM3_CH7 == PTE12)
            {
                PORT_PCR_REG(PORTE,12)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH7 == PTC11)
            {
                PORT_PCR_REG(PORTC,11)=PORT_PCR_MUX(3);
            }
            break;
       default:  return;
      }

       default:  break;
    }
    /******************** ѡ�����ģʽΪ ���ض���PWM *******************/
    //ͨ��״̬���ƣ�����ģʽ��ѡ�� ���ػ��ƽ
    FTM_CnSC_REG(ftmn, ch) &= ~FTM_CnSC_ELSA_MASK;
    FTM_CnSC_REG(ftmn, ch)  = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;

    /******************** ����ʱ�Ӻͷ�Ƶ ********************/
    FTM_SC_REG(ftmn)    = ( 0
                                  | FTM_SC_PS(7)      //��Ƶ2^FTM_SC_PS,Ƶ��Ϊ 275M/2/2^7
                                  | FTM_SC_CLKS(1)    //ʱ��ѡ��busʱ��
                          );                          //PMWƵ��=XϵͳƵ��/2/(2^FTM1_SC_PS)/FTM1_MOD
    FTM_MOD_REG(ftmn)   = mod;                        //ģ��, EPWM������Ϊ ��MOD - CNTIN + 0x0001
    FTM_CNTIN_REG(ftmn) = 0;                          //��������ʼ��ֵ�����������ȣ�(CnV - CNTIN).
    FTM_CnV_REG(ftmn, ch) = cv;
    FTM_CNT_REG(ftmn)   = 0;                          //��������ֻ�е�16λ���ã�д�κ�ֵ���˼Ĵ������������ CNTIN ��ֵ��

  //   FTM_PWMLOAD_REG(ftmn) = 0xFFff;
  //  FTM_COMBINE_REG(ftmn) =  FTM_COMBINE_COMBINE3_MASK ;
  //   FTM_MODE_REG(ftmn) &=~ FTM_MODE_WPDIS_MASK ; // д��������
}




//-------------------------------------------------------------------------*
//������: FTM_PWM_Duty
//��  ��: �ı�PWM��ռ�ձ�
//��  ��: ftmn:ģ����FTM0,FTM1��FTM2
//        ch  :ͨ���� ��Ӧ���Ųο�ftm.h�ļ�
//        duty:�ߵ�ƽ���  ��Χ��0~mod��mod�ڳ�ʼ����ʱ���趨
//��  ��: ��
//��  ��: FTM_PWM_Duty(FTM0, FTM_CH6,duty);duty�趨��0~mod֮����κ���
//-------------------------------------------------------------------------*
void FTM_PWM_Duty(FTM_Type * ftmn, FTM_CHn_e ch, u16 duty)
{

    FTM_CnV_REG(ftmn, ch) = duty;

}



//////////////////////////////// ����Ϊ�������� //////////////////////////////////////////



//-------------------------------------------------------------------------*
//������: FTM_AB_Init
//��  ��: ��ʼ��FTM���������빦��
//��  ��: ftmn:ģ����FTM1��FTM2
//��  ��: ��
//��  ��:  FTM_AB_Init(FTM2);
//-------------------------------------------------------------------------*
void FTM_AB_Init(FTM_Type * ftmn)
{


    /******************* ����ʱ�� �� ����IO��*******************/
    switch((u32)ftmn)
    {

    case FTM1_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;       //ʹ��FTM1ʱ��
        if(FTM1_QDPHA == PTA8)                  //�ܽŸ���
        {

             PORTA_PCR8= PORT_PCR_MUX(6);
        }
        else if(FTM1_QDPHA == PTA12)
        {

             PORTA_PCR12= PORT_PCR_MUX(7);
        }
        else if(FTM1_QDPHA == PTB0)
        {
          
          PORTB_PCR0= PORT_PCR_MUX(6);
        }
        else if(FTM1_QDPHA == PTE20)
        {
          
          PORTE_PCR20= PORT_PCR_MUX(5);
        }
        
        if(FTM1_QDPHB == PTA9)
        {
          
          PORTA_PCR9= PORT_PCR_MUX(6);
        }
        else if(FTM1_QDPHB == PTA13)
        {
          
          PORTA_PCR13= PORT_PCR_MUX(7);
        }
        else if(FTM1_QDPHB == PTB1)
        {
          
          PORTB_PCR1= PORT_PCR_MUX(6);
        }
        else if(FTM1_QDPHB == PTE21)
        {
          
          PORTE_PCR21= PORT_PCR_MUX(5);
        }
        break;
        
        
    case FTM2_BASE:
      //    SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;                           //ʹ��FTM2ʱ��
      SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;
      if(FTM2_QDPHA == PTA10)                  //�ܽŸ���
      {
        
        PORTA_PCR10= PORT_PCR_MUX(6);
      }
      else if(FTM2_QDPHA == PTB18)
      {
        
        PORTB_PCR18= PORT_PCR_MUX(6);
      }
      else if(FTM2_QDPHA == PTE22)
      {
        
        PORTE_PCR22= PORT_PCR_MUX(5);
      }
      else if(FTM2_QDPHA == PTA1)
      {
        
        PORTA_PCR1= PORT_PCR_MUX(5);
      }
      
      if(FTM2_QDPHB == PTA11)                  //�ܽŸ���
      {
        
        PORTA_PCR11= PORT_PCR_MUX(6);
      }
      else if(FTM2_QDPHB == PTB19)
      {
        
        PORTB_PCR19= PORT_PCR_MUX(6);
      }
      else if(FTM2_QDPHB == PTE23)
      {
        
        PORTE_PCR23= PORT_PCR_MUX(5);
      }
      else if(FTM2_QDPHB == PTA2)
      {
        
        PORTA_PCR2= PORT_PCR_MUX(5);
      }
      break;
      
    case FTM3_BASE:
      
      SIM_SCGC3 |= SIM_SCGC6_FTM3_MASK;
      
      if(FTM3_CH0 == PTE5)
      {
        PORT_PCR_REG(PORTE,5)=PORT_PCR_MUX(6);
      }
      else if(FTM3_CH0 == PTD0)
      {
        PORT_PCR_REG(PORTD,0)=PORT_PCR_MUX(4);
      }
      
      if(FTM3_CH1 == PTE6)
      {
        PORT_PCR_REG(PORTE,6)=PORT_PCR_MUX(6);
      }
      else if(FTM3_CH1 == PTD1)
      {
        PORT_PCR_REG(PORTD,1)=PORT_PCR_MUX(4);
      }     
      
      if(FTM3_CH2 == PTE7)
      {
        PORT_PCR_REG(PORTE,7)=PORT_PCR_MUX(6);
      }
      else if(FTM3_CH2 == PTD2)
      {
        PORT_PCR_REG(PORTD,2)=PORT_PCR_MUX(4);
      }     
      
      if(FTM3_CH3 == PTE8)
      {
        PORT_PCR_REG(PORTE,8)=PORT_PCR_MUX(6);
      }
      else if(FTM3_CH3 == PTD3)
      {
        PORT_PCR_REG(PORTD,3)=PORT_PCR_MUX(4);
      }
      
      if(FTM3_CH4 == PTE9)
      {
        PORT_PCR_REG(PORTE,9)=PORT_PCR_MUX(6);
      }
      else if(FTM3_CH4 == PTD1)
      {
        PORT_PCR_REG(PORTC,8)=PORT_PCR_MUX(4);
      }
      
      if(FTM3_CH5 == PTE10)
      {
        PORT_PCR_REG(PORTE,10)=PORT_PCR_MUX(6);
      }
      else if(FTM3_CH5 == PTC9)
      {
        PORT_PCR_REG(PORTC,9)=PORT_PCR_MUX(4);
      }
      
      if(FTM3_CH6 == PTE11)
      {
        PORT_PCR_REG(PORTE,11)=PORT_PCR_MUX(6);
      }
      else if(FTM3_CH6 == PTC10)
      {
        PORT_PCR_REG(PORTC,10)=PORT_PCR_MUX(4);
      }
      
      if(FTM3_CH7 == PTE12)
      {
        PORT_PCR_REG(PORTE,12)=PORT_PCR_MUX(6);
      }
      else if(FTM3_CH7 == PTC11)
      {
        PORT_PCR_REG(PORTC,11)=PORT_PCR_MUX(4);
      }
      break;      
        
    }

    FTM_MODE_REG(ftmn)  |=    (0
                                     | FTM_MODE_WPDIS_MASK  //д������ֹ
                                     //| FTM_MODE_FTMEN_MASK   //ʹ�� FTM
                                    );
    FTM_QDCTRL_REG(ftmn) |=   (0
                                    | FTM_QDCTRL_QUADMODE_MASK
                                     );
    FTM_CNTIN_REG(ftmn)   = 0;
    FTM_MOD_REG(ftmn)     = FTM_MOD_MOD_MASK;
    FTM_QDCTRL_REG(ftmn) |=   (0
                                    | FTM_QDCTRL_QUADEN_MASK
                                     );
    FTM_MODE_REG(ftmn)  |= FTM_QDCTRL_QUADEN_MASK;;
    FTM_CNT_REG(ftmn)     = 0;                    //��������ֻ�е�16λ���ã�д�κ�ֵ���˼Ĵ������������ CNTIN ��ֵ��

}


//-------------------------------------------------------------------------*
//������: FTM_AB_get
//��  ��: ��ȡFTM���������������
//��  ��: ftmn:ģ����FTM1��FTM2
//��  ��: val
//��  ��: speed=FTM_AB_get(FTM2);
//-------------------------------------------------------------------------*
int16 FTM_AB_Get(FTM_Type * ftmn)
{
    int16 val;

    val = FTM_CNT_REG(ftmn);

    FTM_CNT_REG(ftmn) = 0;//����ֵ����

    return val;
}



//-------------------------------------------------------------------------*
//������: FTM_Input_init
//��  ��: FTM�����벶׽����
//��  ��: ftmn:ģ����FTM0,FTM1��FTM2
//        ch  :ͨ���� ��Ӧ���Ųο�ftm.h�ļ�
//        cfg :������ʽ  :
//                        FTM_Rising,               //�����ز�׽
//                        FTM_Falling,              //�½��ز�׽
//                        FTM_Rising_or_Falling     //�����ز�׽
//��  ��: ��
//��  ��: FTM_Input_init(FTM0,FTM_CH6,FTM_Rising);
//-------------------------------------------------------------------------*
void FTM_Input_init(FTM_Type * ftmn, FTM_CHn_e ch, FTM_Input_cfg cfg)
{

    /******************* ����ʱ�� �� ����IO��*******************/
    switch((u32)ftmn)
    {
    case FTM0_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;       //ʹ��FTM0ʱ��
        switch(ch)
        {
        case FTM_CH0:
            if(FTM0_CH0 == PTC1)
            {
                PORTC_PCR1= PORT_PCR_MUX(4);
            }
            else if(FTM0_CH0 == PTA3)
            {
                PORTA_PCR3= PORT_PCR_MUX(3);
            }
            else
            {
               ;
            }
            break;

        case FTM_CH1:
            if(FTM0_CH1 == PTC2)
            {
                PORTC_PCR2= PORT_PCR_MUX(4);
            }
            else if(FTM0_CH1 == PTA4)
            {
                PORTA_PCR4= PORT_PCR_MUX(3);
            }
            else
            {
                ;                      //���ùܽ�����
            }
            break;

        case FTM_CH2:
            if(FTM0_CH2 == PTC3)
            {
                PORTC_PCR3= PORT_PCR_MUX(4);
            }
            else if(FTM0_CH2 == PTA5)
            {
                PORTA_PCR5= PORT_PCR_MUX(3);
            }
            else
            {
                ;                      //���ùܽ�����
            }
            break;

        case FTM_CH3:
            if(FTM0_CH3 == PTC4)
            {
                PORTC_PCR4= PORT_PCR_MUX(4);
            }
            else if(FTM0_CH3 == PTA6)
            {
                PORTA_PCR6= PORT_PCR_MUX(3);
            }
            else
            {
                ;                      //���ùܽ�����
            }
            break;

        case FTM_CH4:
            if(FTM0_CH4 == PTD4)
            {
                PORTD_PCR4= PORT_PCR_MUX(4);
            }
            else if(FTM0_CH4 == PTA7)
            {
                PORTA_PCR7= PORT_PCR_MUX(3);
            }
            else
            {
               ;                      //���ùܽ�����
            }
            break;

        case FTM_CH5:
            if(FTM0_CH5 == PTD5)
            {
                PORTD_PCR5= PORT_PCR_MUX(4);
            }
            else if(FTM0_CH5 == PTA0)
            {
                PORTA_PCR0= PORT_PCR_MUX(3);
            }
            else
            {
                ;                      //���ùܽ�����
            }
            break;

        case FTM_CH6:
            if(FTM0_CH6 == PTD6)
            {
                PORTD_PCR6= PORT_PCR_MUX(4);
            }
            else if(FTM0_CH6 == PTA1)
            {
                PORTA_PCR1= PORT_PCR_MUX(3);
            }
            else
            {
               ;                      //���ùܽ�����
            }
            break;

        case FTM_CH7:
            if(FTM0_CH7 == PTD7)
            {
                PORTD_PCR7= PORT_PCR_MUX(4);
            }
            else if(FTM0_CH7 == PTA2)
            {
                PORTA_PCR2= PORT_PCR_MUX(3);
            }
            else
            {
               ;                      //���ùܽ�����
            }
            break;
        default:
            return;
        }
        break;

    case FTM1_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;       //ʹ��FTM1ʱ��
        switch(ch)
        {
        case FTM_CH0:
            if(FTM1_CH0 == PTA8)
            {
                PORTA_PCR8= PORT_PCR_MUX(3);
            }
            else if(FTM1_CH0 == PTA12)
            {
               PORTA_PCR12= PORT_PCR_MUX(3);
            }
            else if(FTM1_CH0 == PTB0)
            {
               PORTB_PCR0= PORT_PCR_MUX(3);
            }
            break;


        case FTM_CH1:
            if(FTM1_CH1 == PTA9 )
            {
                PORTA_PCR9= PORT_PCR_MUX(3);
            }
            else if  (FTM1_CH1 == PTA13)
            {
                PORTA_PCR13= PORT_PCR_MUX(3);
            }
            else if(FTM1_CH1 == PTB1)
            {
                PORTB_PCR1= PORT_PCR_MUX(3);
            }
            break;

        default:
            return;
        }
        break;

    case FTM2_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;                           //ʹ��FTM2ʱ��
        switch(ch)
        {
        case FTM_CH0:
            if(FTM2_CH0 == PTA10)
            {
                PORTA_PCR10= PORT_PCR_MUX(3);
            }
            else if (FTM2_CH0 == PTB18)
            {
               PORTB_PCR18= PORT_PCR_MUX(3);
            }
            break;

        case FTM_CH1:
            if(FTM2_CH1 == PTA11)
            {
                PORTA_PCR11= PORT_PCR_MUX(3);
            }
            else if(FTM2_CH1 == PTB19)
            {
               PORTB_PCR19= PORT_PCR_MUX(3);
            }
            break;

        default:
            return;
        }
        break;
        case FTM3_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM3_MASK;

         switch(ch)
        {
        case FTM_CH0:
            if(FTM3_CH0 == PTE5)
            {
                PORT_PCR_REG(PORTE,5)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH0 == PTD0)
            {
                PORT_PCR_REG(PORTD,0)=PORT_PCR_MUX(4);
            }
            break;

        case FTM_CH1:
            if(FTM3_CH1 == PTE6)
            {
                PORT_PCR_REG(PORTE,6)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH1 == PTD1)
            {
                PORT_PCR_REG(PORTD,1)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH2:
            if(FTM3_CH2 == PTE7)
            {
                PORT_PCR_REG(PORTE,7)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH2 == PTD2)
            {
                PORT_PCR_REG(PORTD,2)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH3:
            if(FTM3_CH3 == PTE8)
            {
                PORT_PCR_REG(PORTE,8)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH3 == PTD3)
            {
                PORT_PCR_REG(PORTD,3)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH4:
            if(FTM3_CH4 == PTE9)
            {
                PORT_PCR_REG(PORTE,9)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH4 == PTD1)
            {
                PORT_PCR_REG(PORTC,8)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH5:
            if(FTM3_CH5 == PTE10)
            {
                PORT_PCR_REG(PORTE,10)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH5 == PTC9)
            {
                PORT_PCR_REG(PORTC,9)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH6:
            if(FTM3_CH6 == PTE11)
            {
                PORT_PCR_REG(PORTE,11)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH6 == PTC10)
            {
                PORT_PCR_REG(PORTC,10)=PORT_PCR_MUX(4);
            }
            break;
        case FTM_CH7:
            if(FTM3_CH7 == PTE12)
            {
                PORT_PCR_REG(PORTE,12)=PORT_PCR_MUX(6);
            }
            else if(FTM3_CH7 == PTC11)
            {
                PORT_PCR_REG(PORTC,11)=PORT_PCR_MUX(4);
            }
            break;
       default:  return;

      }

       default:  break;
    }

    /******************* ����Ϊ���벶׽���� *******************/
    switch(cfg)
    {
        //���벶׽ģʽ�£�DECAPEN = 0 �� DECAPEN = 0 ��CPWMS = 0�� MSnB:MSnA = 0

        // ELSnB:ELSnA         1          10          11
        // ����             ������      �½���      ������

    case FTM_Rising:    //�����ش���
        FTM_CnSC_REG(ftmn, ch) |=  ( FTM_CnSC_ELSA_MASK  | FTM_CnSC_CHIE_MASK );                   //��1
        FTM_CnSC_REG(ftmn, ch) &= ~( FTM_CnSC_ELSB_MASK  | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK); //��0
        break;

    case FTM_Falling:   //�½��ش���
        FTM_CnSC_REG(ftmn, ch) |= (FTM_CnSC_ELSB_MASK  | FTM_CnSC_CHIE_MASK );                    //��1
        FTM_CnSC_REG(ftmn, ch) &= ~( FTM_CnSC_ELSA_MASK | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK); //��0
        break;

    case FTM_Rising_or_Falling: //�����ء��½��ض�����
        FTM_CnSC_REG(ftmn, ch) |=  ( FTM_CnSC_ELSB_MASK | FTM_CnSC_ELSA_MASK  | FTM_CnSC_CHIE_MASK ); //��1
        FTM_CnSC_REG(ftmn, ch) &= ~( FTM_CnSC_MSB_MASK  | FTM_CnSC_MSA_MASK); //��0
        break;
    }

    FTM_SC_REG(ftmn) = FTM_SC_CLKS(0x1);       //ѡ�� bus ʱ��

    FTM_MODE_REG(ftmn)    |= FTM_MODE_WPDIS_MASK; //��ֹд����
    FTM_COMBINE_REG(ftmn) = 0;
    FTM_MODE_REG(ftmn)    &= ~FTM_MODE_FTMEN_MASK;    //ʹ��FTM
    FTM_CNTIN_REG(ftmn)   = 0;

    FTM_STATUS_REG(ftmn)  = 0x00;               //���жϱ�־λ

    //�������벶׽�ж�
    //enable_irq(62 + ftmn);
}


//-------------------------------------------------------------------------*
//������: FTM_interrupt
//��  ��: FTM���жϹ���
//��  ��: ��
//��  ��: ��
//-------------------------------------------------------------------------*
void FTM0_interrupt(void)
{
    uint8 s = FTM0_STATUS;             //��ȡ��׽�ͱȽ�״̬
    uint8 CHn;

    FTM0_STATUS = 0x00;             //���жϱ�־λ

    CHn = 0;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_DIS(FTM0, CHn);     //��ֹ���벶׽�ж�
        /*     �û�����       */

        /*********************/
        //FTM_IRQ_EN(FTM0, CHn); //�������벶׽�ж�

    }

    /* ������� n=1 ��ģ�棬����ģ������� */
    CHn = 1;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_EN(FTM0, CHn); //�������벶׽�ж�
        /*     �û�����       */


        /*********************/
        //�����������￪�����벶׽�ж�
        //FTM_IRQ_EN(FTM0, CHn); //�������벶׽�ж�
    }
}

void FTM1_interrupt(void)
{
    uint8 s = FTM1_STATUS;             //��ȡ��׽�ͱȽ�״̬
    uint8 CHn;

    FTM1_STATUS = 0x00;             //���жϱ�־λ

    CHn = 0;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_DIS(FTM1, CHn);     //��ֹ���벶׽�ж�
        /*     �û�����       */

        /*********************/
        //FTM_IRQ_EN(FTM1, CHn); //�������벶׽�ж�

    }

    /* ������� n=1 ��ģ�棬����ģ������� */
    CHn = 1;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_EN(FTM1, CHn); //�������벶׽�ж�
        /*     �û�����       */


        /*********************/
        //�����������￪�����벶׽�ж�
        //FTM_IRQ_EN(FTM1, CHn); //�������벶׽�ж�
    }
}


void FTM2_interrupt(void)
{
    uint8 s = FTM2_STATUS;             //��ȡ��׽�ͱȽ�״̬
    uint8 CHn;

    FTM2_STATUS = 0x00;             //���жϱ�־λ

    CHn = 0;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_DIS(FTM2, CHn);     //��ֹ���벶׽�ж�
        /*     �û�����       */

        /*********************/
        //FTM_IRQ_EN(FTM2, CHn); //�������벶׽�ж�

    }

    /* ������� n=1 ��ģ�棬����ģ������� */
    CHn = 1;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_EN(FTM2, CHn); //�������벶׽�ж�
        /*     �û�����       */


        /*********************/
        //�����������￪�����벶׽�ж�
        //FTM_IRQ_EN(FTM2, CHn); //�������벶׽�ж�
    }
}

void FTM3_interrupt(void)
{
    uint8 s = FTM3_STATUS;             //��ȡ��׽�ͱȽ�״̬
    uint8 CHn;

    FTM3_STATUS = 0x00;             //���жϱ�־λ

    CHn = 0;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_DIS(FTM2, CHn);     //��ֹ���벶׽�ж�
        /*     �û�����       */

        /*********************/
        //FTM_IRQ_EN(FTM2, CHn); //�������벶׽�ж�

    }

    /* ������� n=1 ��ģ�棬����ģ������� */
    CHn = 1;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_EN(FTM2, CHn); //�������벶׽�ж�
        /*     �û�����       */


        /*********************/
        //�����������￪�����벶׽�ж�
        //FTM_IRQ_EN(FTM2, CHn); //�������벶׽�ж�
    }
}

//��ʼ������ͨ��PWM
void Motor_Init(void)
{
   //���Ƶ�ʣ�275M/2/(2^4)/1000=8.5kHZ,  /8
   FTM_PWM_Init(FTM0,FTM_CH0,850,  500);//Mot0-PTC1
   FTM_PWM_Init(FTM0,FTM_CH1,850,  0);//Mot1-PTC2 
   FTM_PWM_Init(FTM0,FTM_CH2,850,  500);//Mot2-PTC3
   FTM_PWM_Init(FTM0,FTM_CH3,850,  0);//Mot3-PTC4 
}

void Servo_Init(void)
{
   //���Ƶ�ʣ�275M/2/(2^7)/21484.375=50HZ,FTM3Ӳ������
   //���Ƶ�ʣ�275M/2/(2^7)/20000=54HZ,FTM3Ӳ������
   ServoFTM_PWM_Init(FTM3,FTM_CH7,20000,Servo_Middle);//Mot11-PTC11    ���������ߴ��ұ�С
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵�����������PWMռ�ձȿ���
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ��
u16 Motno, Mot0--3
u32 duty,  0--500--1000,ͨ����·PWM���ư��ŵ������ѹ������ѹ������ֱ���������ת

�û�Ҳ�����Լ��޸ı���ϵ�����Է����Լ�ʹ�ã�Ĭ��Ϊ15
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/ 
void Motor_Duty(u16 Motno, u32 duty)
{    
//	duty = duty * 80/10;
  duty = duty * 85/100;
  //��һ��Ϊ0--500--1000
  //if(duty<1001)
  {   
    switch(Motno) 
    {
    case Mot0:      
      FTM_CnV_REG(FTM0, FTM_CH0) = duty;   //�����
      break;      
    case Mot1:
      FTM_CnV_REG(FTM0, FTM_CH1) = duty;   //�����
      break;      
    case Mot2:
      FTM_CnV_REG(FTM0, FTM_CH2) = duty;   //�����    
      break;      
    case Mot3:
      FTM_CnV_REG(FTM0, FTM_CH3) = duty;  //�����
      break;             
    default:
      break; 
    }  
  }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������˵�������ռ�ձȿ���
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ��u32 duty ,500--2500us
CT_PWM_Duty(CT4_CH0, duty*12/5);6000/0.5ms  18000/1.5ms  30000/2.5ms
�û�Ҳ�����Լ��޸ı���ϵ�����Է����Լ�ʹ�ã�Ĭ��Ϊ2.4
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Servo_Duty(u32 duty)
{      
  //��һ��Ϊ2500--12500
  //if((duty>2500)&&(duty<12500))
  { 
    FTM_CnV_REG(FTM3, FTM_CH7) = duty;  //�������PTC11
    //FTM_CnV_REG(FTM3, FTM_CH6) = duty;  //�������PTC10
  }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������ֵ��
������汾��V1.0
�������¡�2017��10��27�� 
����������
������ֵ����
������ֵ��
//ͨ��ĸ�尴���Ͷ���ӿڣ����Զ��ת�򼰶���궨����ʾ��OLED
��ʵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

void Test_Servo(void)
{
  char txt[16];
  uint16_t servopwm=Servo_Middle;   
#ifdef __USE_TFT18
  
#else    
  KEY_SW_Init();          //����������ڳ�ʼ��
  LCD_CLS();           //LCD����    
  Servo_Init();        //���Ƶ������
  LCD_P8x16Str(13,0,(uint8_t*)"LQ Servo PWM");
#endif    
  
  while (1)
  {    
    
//    if(!KEY_Read(KEY0))  
//    {
      //if(servopwm>Servo_Left-9) 
	  time_delay_ms(500);
      servopwm-=100;
	  if(servopwm > 12500) servopwm = 12500;
	  else if(servopwm < 2500) servopwm = 2500;
      Servo_Duty(servopwm);//ˢ��servopwmƵ��
//    }
//    else if(!KEY_Read(KEY2))  
//    {
      //if(servopwm<Servo_Right-9) 
//        servopwm+=10;
//      Servo_Duty(servopwm);//ˢ��servopwmƵ��
//    }
//    else if(!KEY_Read(KEY1))  
//    {
//      servopwm=Servo_Middle;
//      Servo_Duty(servopwm);//ˢ��servopwmƵ��
//    }    
    
    sprintf(txt,"PWM: %05d",servopwm);
#ifdef __USE_TFT18    
    TFTSPI_P8X16Str(2,3,(uint8_t*)txt,u16WHITE,u16BLACK);		//�ַ�����ʾ   
#else    
    LCD_P8x16Str(2,3,(uint8_t*)txt);
#endif
    
    UART_Put_Str(UART_4,(uint8*)txt); //PTE24 ����� 
    
    //LED��˸
    LED_Ctrl(LED1, RVS);    
    time_delay_ms(50);
  }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������ֵ��
������汾��V1.0
�������¡�2017��10��27�� 
����������
������ֵ����
������ֵ��
//ͨ��ĸ�尴���͵���ӿڣ����Ե��������ת״̬���궨����ʾ��OLED
��ʵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_Motor(void)
{    
  char txt[16];
  uint16_t motorpwm=500;   
  
  KEY_SW_Init();          //����������ڳ�ʼ��
#ifdef __USE_TFT18
  TFTSPI_CLS(u16BLUE);//��ɫ��Ļ	
  TFTSPI_P8X16Str(13,0,(uint8_t*)"LQ Motor PWM",u16WHITE,u16BLACK);		//�ַ�����ʾ   
#else    
  LCD_CLS();           //LCD����    
  LCD_P8x16Str(13,0,(uint8_t*)"LQ Motor PWM");
#endif
  Motor_Init();        //���Ƶ������
  motorpwm = 0;
  while (1)
  {        
	  motorpwm += 100;
	  if(motorpwm >= 1000) motorpwm = 0;
	  time_delay_ms(100);
	  Motor_Duty(Mot1,motorpwm);//ˢ��servopwmƵ��
//	  
//    if(!KEY_Read(KEY0))  
//    {
//      //if(motorpwm>99) 
//        motorpwm-=10;
//      Motor_Duty(Mot1,motorpwm);//ˢ��servopwmƵ��
//    }
//    else if(!KEY_Read(KEY2))  
//    {
//      //if(motorpwm<12000) 
//        motorpwm+=10;
//      Motor_Duty(Mot1,motorpwm);//ˢ��servopwmƵ��
//    }
//    else if(!KEY_Read(KEY1))  
//    {
//      motorpwm=500;
//      Motor_Duty(Mot1,motorpwm);//ˢ��servopwmƵ��
//    }    
    
    sprintf(txt,"PWM: %05d",motorpwm);
#ifdef __USE_TFT18    
    TFTSPI_P8X16Str(2,3,(uint8_t*)txt,u16WHITE,u16BLACK);		//�ַ�����ʾ  
#else    
    LCD_P8x16Str(2,3,(uint8_t*)txt);
#endif
    
    UART_Put_Str(UART_4,(uint8*)txt); //PTE24 ����� 
    
    //LED��˸
    LED_Ctrl(LED1, RVS);    
    time_delay_ms(50);
  }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�CHIUSIR
������ֵ��
������汾��V1.0
�������¡�2017��10��27�� 
����������
������ֵ����
������ֵ��
��ʵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_AB_Pulse_Cnt(void)
{
  s16 counterVal;
  uint16_t motorpwm=50;  
  char txt[16]; 
  Motor_Init();        //���Ƶ������
  Motor_Duty(Mot2,50);//ˢ��servopwmƵ��
  FTM_AB_Init(FTM1);           //��������ʼ��
  FTM_AB_Init(FTM2);           //��������ʼ��    
#ifdef __USE_TFT18
  TFTSPI_CLS(u16BLUE);//��ɫ��Ļ	
  TFTSPI_P8X16Str(13,0,(uint8_t*)txt,u16WHITE,u16BLACK);		//�ַ�����ʾ    
#else    
  LCD_CLS();           //LCD����  
 // LCD_P8x16Str(13,0,(uint8_t*)"LQ Encoder CNT");
#endif
  
  
  while (1)
  {    if(!KEY_Read(KEY0))  
    {
      //if(motorpwm>99) 
        motorpwm-=10;
      Motor_Duty(Mot2,motorpwm);//ˢ��servopwmƵ��
    }
    else if(!KEY_Read(KEY2))  
    {
      //if(motorpwm<12000) 
        motorpwm+=10;
      Motor_Duty(Mot2,motorpwm);//ˢ��servopwmƵ��
    }
    else if(!KEY_Read(KEY1))  
    {
      motorpwm=50;
      Motor_Duty(Mot2,motorpwm);//ˢ��servopwmƵ��
    }    
    
    
    
    counterVal =FTM_AB_Get(FTM1);     //��ȡ���������ٶȣ�������ʾ����;     
    
    sprintf(txt,"QAB1: %05d \n",counterVal);
    
#ifdef __USE_TFT18
    TFTSPI_P8X16Str(2,3,(uint8_t*)txt,u16WHITE,u16BLACK);		//�ַ�����ʾ  
#else    
    LCD_P8x16Str(2,3,(uint8_t*)txt);
#endif     
    UART_Put_Str(UART_4,(uint8*)txt); //PTE24 ����� 
    
    time_delay_ms(200);
    counterVal =FTM_AB_Get(FTM2);     //��ȡ���������ٶȣ�������ʾ����;   
    //sprintf(txt,"QAB2: %05d \n",counterVal);
    sprintf(txt,"PWM: %05d \n",motorpwm);
#ifdef __USE_TFT18
    TFTSPI_P8X16Str(2,5,(uint8_t*)txt,u16WHITE,u16BLACK);		//�ַ�����ʾ  
#else    
    LCD_P8x16Str(2,5,(uint8_t*)txt);
#endif 
    UART_Put_Str(UART_4,(uint8*)txt); //PTE24 ����� 
    //LED��˸
    LED_Ctrl(LED1, RVS);    
    time_delay_ms(200);         
  }
}
