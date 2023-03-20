/*******************************************************************************
【平    台】龙邱KV58F24智能车VD母板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2018年2月2日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4及以上版本840 1400 1790
【Target  】MKV58F1M0VLQ24
【Crystal 】 50.000Mhz
【busclock】137.500MHz
【pllclock】275.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"

FTM_MemMapPtr FTMN[3] = {FTM0_BASE_PTR, FTM1_BASE_PTR, FTM2_BASE_PTR}; //定义三个指针数组保存 FTMn_e 的地址


//-------------------------------------------------------------------------*
//函数名: FTM_PWM_init
//功  能: FTM的PWM功能
//参  数: ftmn:模块名FTM0,FTM1，FTM2
//        ch  :通道号 对应引脚参考ftm.h文件
//        mod :脉冲宽度  范围（0~65535）
//        cv  :高电平宽度 范围（0~mod）
//返  回: 无
//简  例: FTM_PWM_init(FTM0,FTM_CH6,65535,32768); 这样占空比是50%
//-------------------------------------------------------------------------*
void FTM_PWM_Init(FTM_Type * ftmn, FTM_CHn_e ch, u16 mod, u16 cv)
{
  /******************* 开启时钟 和 复用IO口*******************/
    switch((u32)ftmn)
    {
    case FTM0_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;       //使能FTM0时钟
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
        SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;       //使能FTM1时钟
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
        SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;                           //使能FTM2时钟
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

               
    /******************** 选择输出模式为 边沿对齐PWM *******************/
    //通道状态控制，根据模式来选择 边沿或电平
    FTM_CnSC_REG(ftmn, ch) &= ~FTM_CnSC_ELSA_MASK;
    FTM_CnSC_REG(ftmn, ch)  = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;

    /******************** 配置时钟和分频 ********************/
    FTM_SC_REG(ftmn)    = ( 0
                                  | FTM_SC_PS(4)      //分频2^FTM_SC_PS,频率为 275M/2/16
                                  | FTM_SC_CLKS(1)    //时钟选择，bus时钟
                          );                          //PMW频率=X系统频率/2/(2^FTM1_SC_PS)/FTM1_MOD
    FTM_MOD_REG(ftmn)   = mod;                        //模数, EPWM的周期为 ：MOD - CNTIN + 0x0001
    FTM_CNTIN_REG(ftmn) = 0;                          //计数器初始化值。设置脉冲宽度：(CnV - CNTIN).
    FTM_CnV_REG(ftmn, ch) = cv;
    FTM_CNT_REG(ftmn)   = 0;                          //计数器。只有低16位可用（写任何值到此寄存器，都会加载 CNTIN 的值）

  //   FTM_PWMLOAD_REG(ftmn) = 0xFFff;
  //  FTM_COMBINE_REG(ftmn) =  FTM_COMBINE_COMBINE3_MASK ;
  //   FTM_MODE_REG(ftmn) &=~ FTM_MODE_WPDIS_MASK ; // 写保护开启
}


void ServoFTM_PWM_Init(FTM_Type * ftmn, FTM_CHn_e ch, u16 mod, u16 cv)
{
  /******************* 开启时钟 和 复用IO口*******************/
    switch((u32)ftmn)
    {
    case FTM0_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;       //使能FTM0时钟
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
        SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;       //使能FTM1时钟
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
        SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;                           //使能FTM2时钟
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
    /******************** 选择输出模式为 边沿对齐PWM *******************/
    //通道状态控制，根据模式来选择 边沿或电平
    FTM_CnSC_REG(ftmn, ch) &= ~FTM_CnSC_ELSA_MASK;
    FTM_CnSC_REG(ftmn, ch)  = FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;

    /******************** 配置时钟和分频 ********************/
    FTM_SC_REG(ftmn)    = ( 0
                                  | FTM_SC_PS(7)      //分频2^FTM_SC_PS,频率为 275M/2/2^7
                                  | FTM_SC_CLKS(1)    //时钟选择，bus时钟
                          );                          //PMW频率=X系统频率/2/(2^FTM1_SC_PS)/FTM1_MOD
    FTM_MOD_REG(ftmn)   = mod;                        //模数, EPWM的周期为 ：MOD - CNTIN + 0x0001
    FTM_CNTIN_REG(ftmn) = 0;                          //计数器初始化值。设置脉冲宽度：(CnV - CNTIN).
    FTM_CnV_REG(ftmn, ch) = cv;
    FTM_CNT_REG(ftmn)   = 0;                          //计数器。只有低16位可用（写任何值到此寄存器，都会加载 CNTIN 的值）

  //   FTM_PWMLOAD_REG(ftmn) = 0xFFff;
  //  FTM_COMBINE_REG(ftmn) =  FTM_COMBINE_COMBINE3_MASK ;
  //   FTM_MODE_REG(ftmn) &=~ FTM_MODE_WPDIS_MASK ; // 写保护开启
}




//-------------------------------------------------------------------------*
//函数名: FTM_PWM_Duty
//功  能: 改变PWM的占空比
//参  数: ftmn:模块名FTM0,FTM1，FTM2
//        ch  :通道号 对应引脚参考ftm.h文件
//        duty:高电平宽度  范围（0~mod）mod在初始化的时候设定
//返  回: 无
//简  例: FTM_PWM_Duty(FTM0, FTM_CH6,duty);duty设定在0~mod之间的任何数
//-------------------------------------------------------------------------*
void FTM_PWM_Duty(FTM_Type * ftmn, FTM_CHn_e ch, u16 duty)
{

    FTM_CnV_REG(ftmn, ch) = duty;

}



//////////////////////////////// 以下为正交解码 //////////////////////////////////////////



//-------------------------------------------------------------------------*
//函数名: FTM_AB_Init
//功  能: 初始化FTM的正交解码功能
//参  数: ftmn:模块名FTM1，FTM2
//返  回: 无
//简  例:  FTM_AB_Init(FTM2);
//-------------------------------------------------------------------------*
void FTM_AB_Init(FTM_Type * ftmn)
{


    /******************* 开启时钟 和 复用IO口*******************/
    switch((u32)ftmn)
    {

    case FTM1_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;       //使能FTM1时钟
        if(FTM1_QDPHA == PTA8)                  //管脚复用
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
      //    SIM_SCGC3 |= SIM_SCGC3_FTM2_MASK;                           //使能FTM2时钟
      SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;
      if(FTM2_QDPHA == PTA10)                  //管脚复用
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
      
      if(FTM2_QDPHB == PTA11)                  //管脚复用
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
                                     | FTM_MODE_WPDIS_MASK  //写保护禁止
                                     //| FTM_MODE_FTMEN_MASK   //使能 FTM
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
    FTM_CNT_REG(ftmn)     = 0;                    //计数器。只有低16位可用（写任何值到此寄存器，都会加载 CNTIN 的值）

}


//-------------------------------------------------------------------------*
//函数名: FTM_AB_get
//功  能: 获取FTM正交解码的脉冲数
//参  数: ftmn:模块名FTM1，FTM2
//返  回: val
//简  例: speed=FTM_AB_get(FTM2);
//-------------------------------------------------------------------------*
int16 FTM_AB_Get(FTM_Type * ftmn)
{
    int16 val;

    val = FTM_CNT_REG(ftmn);

    FTM_CNT_REG(ftmn) = 0;//计数值清零

    return val;
}



//-------------------------------------------------------------------------*
//函数名: FTM_Input_init
//功  能: FTM的输入捕捉功能
//参  数: ftmn:模块名FTM0,FTM1，FTM2
//        ch  :通道号 对应引脚参考ftm.h文件
//        cfg :触发方式  :
//                        FTM_Rising,               //上升沿捕捉
//                        FTM_Falling,              //下降沿捕捉
//                        FTM_Rising_or_Falling     //跳变沿捕捉
//返  回: 无
//简  例: FTM_Input_init(FTM0,FTM_CH6,FTM_Rising);
//-------------------------------------------------------------------------*
void FTM_Input_init(FTM_Type * ftmn, FTM_CHn_e ch, FTM_Input_cfg cfg)
{

    /******************* 开启时钟 和 复用IO口*******************/
    switch((u32)ftmn)
    {
    case FTM0_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;       //使能FTM0时钟
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
                ;                      //设置管脚有误？
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
                ;                      //设置管脚有误？
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
                ;                      //设置管脚有误？
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
               ;                      //设置管脚有误？
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
                ;                      //设置管脚有误？
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
               ;                      //设置管脚有误？
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
               ;                      //设置管脚有误？
            }
            break;
        default:
            return;
        }
        break;

    case FTM1_BASE:
        SIM_SCGC6 |= SIM_SCGC6_FTM1_MASK;       //使能FTM1时钟
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
        SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;                           //使能FTM2时钟
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

    /******************* 设置为输入捕捉功能 *******************/
    switch(cfg)
    {
        //输入捕捉模式下：DECAPEN = 0 ， DECAPEN = 0 ，CPWMS = 0， MSnB:MSnA = 0

        // ELSnB:ELSnA         1          10          11
        // 配置             上升沿      下降沿      跳变沿

    case FTM_Rising:    //上升沿触发
        FTM_CnSC_REG(ftmn, ch) |=  ( FTM_CnSC_ELSA_MASK  | FTM_CnSC_CHIE_MASK );                   //置1
        FTM_CnSC_REG(ftmn, ch) &= ~( FTM_CnSC_ELSB_MASK  | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK); //清0
        break;

    case FTM_Falling:   //下降沿触发
        FTM_CnSC_REG(ftmn, ch) |= (FTM_CnSC_ELSB_MASK  | FTM_CnSC_CHIE_MASK );                    //置1
        FTM_CnSC_REG(ftmn, ch) &= ~( FTM_CnSC_ELSA_MASK | FTM_CnSC_MSB_MASK | FTM_CnSC_MSA_MASK); //清0
        break;

    case FTM_Rising_or_Falling: //上升沿、下降沿都触发
        FTM_CnSC_REG(ftmn, ch) |=  ( FTM_CnSC_ELSB_MASK | FTM_CnSC_ELSA_MASK  | FTM_CnSC_CHIE_MASK ); //置1
        FTM_CnSC_REG(ftmn, ch) &= ~( FTM_CnSC_MSB_MASK  | FTM_CnSC_MSA_MASK); //清0
        break;
    }

    FTM_SC_REG(ftmn) = FTM_SC_CLKS(0x1);       //选择 bus 时钟

    FTM_MODE_REG(ftmn)    |= FTM_MODE_WPDIS_MASK; //禁止写保护
    FTM_COMBINE_REG(ftmn) = 0;
    FTM_MODE_REG(ftmn)    &= ~FTM_MODE_FTMEN_MASK;    //使能FTM
    FTM_CNTIN_REG(ftmn)   = 0;

    FTM_STATUS_REG(ftmn)  = 0x00;               //清中断标志位

    //开启输入捕捉中断
    //enable_irq(62 + ftmn);
}


//-------------------------------------------------------------------------*
//函数名: FTM_interrupt
//功  能: FTM的中断功能
//返  回: 无
//简  例: 无
//-------------------------------------------------------------------------*
void FTM0_interrupt(void)
{
    uint8 s = FTM0_STATUS;             //读取捕捉和比较状态
    uint8 CHn;

    FTM0_STATUS = 0x00;             //清中断标志位

    CHn = 0;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_DIS(FTM0, CHn);     //禁止输入捕捉中断
        /*     用户任务       */

        /*********************/
        //FTM_IRQ_EN(FTM0, CHn); //开启输入捕捉中断

    }

    /* 这里添加 n=1 的模版，根据模版来添加 */
    CHn = 1;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_EN(FTM0, CHn); //开启输入捕捉中断
        /*     用户任务       */


        /*********************/
        //不建议在这里开启输入捕捉中断
        //FTM_IRQ_EN(FTM0, CHn); //开启输入捕捉中断
    }
}

void FTM1_interrupt(void)
{
    uint8 s = FTM1_STATUS;             //读取捕捉和比较状态
    uint8 CHn;

    FTM1_STATUS = 0x00;             //清中断标志位

    CHn = 0;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_DIS(FTM1, CHn);     //禁止输入捕捉中断
        /*     用户任务       */

        /*********************/
        //FTM_IRQ_EN(FTM1, CHn); //开启输入捕捉中断

    }

    /* 这里添加 n=1 的模版，根据模版来添加 */
    CHn = 1;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_EN(FTM1, CHn); //开启输入捕捉中断
        /*     用户任务       */


        /*********************/
        //不建议在这里开启输入捕捉中断
        //FTM_IRQ_EN(FTM1, CHn); //开启输入捕捉中断
    }
}


void FTM2_interrupt(void)
{
    uint8 s = FTM2_STATUS;             //读取捕捉和比较状态
    uint8 CHn;

    FTM2_STATUS = 0x00;             //清中断标志位

    CHn = 0;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_DIS(FTM2, CHn);     //禁止输入捕捉中断
        /*     用户任务       */

        /*********************/
        //FTM_IRQ_EN(FTM2, CHn); //开启输入捕捉中断

    }

    /* 这里添加 n=1 的模版，根据模版来添加 */
    CHn = 1;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_EN(FTM2, CHn); //开启输入捕捉中断
        /*     用户任务       */


        /*********************/
        //不建议在这里开启输入捕捉中断
        //FTM_IRQ_EN(FTM2, CHn); //开启输入捕捉中断
    }
}

void FTM3_interrupt(void)
{
    uint8 s = FTM3_STATUS;             //读取捕捉和比较状态
    uint8 CHn;

    FTM3_STATUS = 0x00;             //清中断标志位

    CHn = 0;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_DIS(FTM2, CHn);     //禁止输入捕捉中断
        /*     用户任务       */

        /*********************/
        //FTM_IRQ_EN(FTM2, CHn); //开启输入捕捉中断

    }

    /* 这里添加 n=1 的模版，根据模版来添加 */
    CHn = 1;
    if( s & (1 << CHn) )
    {
        //FTM_IRQ_EN(FTM2, CHn); //开启输入捕捉中断
        /*     用户任务       */


        /*********************/
        //不建议在这里开启输入捕捉中断
        //FTM_IRQ_EN(FTM2, CHn); //开启输入捕捉中断
    }
}

//初始化各个通道PWM
void Motor_Init(void)
{
   //电机频率：275M/2/(2^4)/1000=8.5kHZ,  /8
   FTM_PWM_Init(FTM0,FTM_CH0,850,  500);//Mot0-PTC1
   FTM_PWM_Init(FTM0,FTM_CH1,850,  0);//Mot1-PTC2 
   FTM_PWM_Init(FTM0,FTM_CH2,850,  500);//Mot2-PTC3
   FTM_PWM_Init(FTM0,FTM_CH3,850,  0);//Mot3-PTC4 
}

void Servo_Init(void)
{
   //舵机频率：275M/2/(2^7)/21484.375=50HZ,FTM3硬件报错
   //舵机频率：275M/2/(2^7)/20000=54HZ,FTM3硬件报错
   ServoFTM_PWM_Init(FTM3,FTM_CH7,20000,Servo_Middle);//Mot11-PTC11    舵机方向左边大右边小
}
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】电机所用PWM占空比控制
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】
u16 Motno, Mot0--3
u32 duty,  0--500--1000,通过两路PWM控制半桥的输出电压，两个压差驱动直流电机正反转

用户也可以自己修改比例系数，以方便自己使用，默认为15
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/ 
void Motor_Duty(u16 Motno, u32 duty)
{    
//	duty = duty * 80/10;
  duty = duty * 85/100;
  //归一化为0--500--1000
  //if(duty<1001)
  {   
    switch(Motno) 
    {
    case Mot0:      
      FTM_CnV_REG(FTM0, FTM_CH0) = duty;   //电机，
      break;      
    case Mot1:
      FTM_CnV_REG(FTM0, FTM_CH1) = duty;   //电机，
      break;      
    case Mot2:
      FTM_CnV_REG(FTM0, FTM_CH2) = duty;   //电机，    
      break;      
    case Mot3:
      FTM_CnV_REG(FTM0, FTM_CH3) = duty;  //电机，
      break;             
    default:
      break; 
    }  
  }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【功能说明】舵机占空比控制
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】u32 duty ,500--2500us
CT_PWM_Duty(CT4_CH0, duty*12/5);6000/0.5ms  18000/1.5ms  30000/2.5ms
用户也可以自己修改比例系数，以方便自己使用，默认为2.4
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Servo_Duty(u32 duty)
{      
  //归一化为2500--12500
  //if((duty>2500)&&(duty<12500))
  { 
    FTM_CnV_REG(FTM3, FTM_CH7) = duty;  //舵机，用PTC11
    //FTM_CnV_REG(FTM3, FTM_CH6) = duty;  //舵机，用PTC10
  }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【参数值】
【软件版本】V1.0
【最后更新】2017年10月27日 
【函数名】
【返回值】无
【参数值】
//通过母板按键和舵机接口，测试舵机转向及舵机标定，显示于OLED
【实例】
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

void Test_Servo(void)
{
  char txt[16];
  uint16_t servopwm=Servo_Middle;   
#ifdef __USE_TFT18
  
#else    
  KEY_SW_Init();          //按键及输入口初始化
  LCD_CLS();           //LCD清屏    
  Servo_Init();        //电机频率设置
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
      Servo_Duty(servopwm);//刷新servopwm频率
//    }
//    else if(!KEY_Read(KEY2))  
//    {
      //if(servopwm<Servo_Right-9) 
//        servopwm+=10;
//      Servo_Duty(servopwm);//刷新servopwm频率
//    }
//    else if(!KEY_Read(KEY1))  
//    {
//      servopwm=Servo_Middle;
//      Servo_Duty(servopwm);//刷新servopwm频率
//    }    
    
    sprintf(txt,"PWM: %05d",servopwm);
#ifdef __USE_TFT18    
    TFTSPI_P8X16Str(2,3,(uint8_t*)txt,u16WHITE,u16BLACK);		//字符串显示   
#else    
    LCD_P8x16Str(2,3,(uint8_t*)txt);
#endif
    
    UART_Put_Str(UART_4,(uint8*)txt); //PTE24 口输出 
    
    //LED闪烁
    LED_Ctrl(LED1, RVS);    
    time_delay_ms(50);
  }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【参数值】
【软件版本】V1.0
【最后更新】2017年10月27日 
【函数名】
【返回值】无
【参数值】
//通过母板按键和电机接口，测试电机各种运转状态及标定，显示于OLED
【实例】
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_Motor(void)
{    
  char txt[16];
  uint16_t motorpwm=500;   
  
  KEY_SW_Init();          //按键及输入口初始化
#ifdef __USE_TFT18
  TFTSPI_CLS(u16BLUE);//蓝色屏幕	
  TFTSPI_P8X16Str(13,0,(uint8_t*)"LQ Motor PWM",u16WHITE,u16BLACK);		//字符串显示   
#else    
  LCD_CLS();           //LCD清屏    
  LCD_P8x16Str(13,0,(uint8_t*)"LQ Motor PWM");
#endif
  Motor_Init();        //电机频率设置
  motorpwm = 0;
  while (1)
  {        
	  motorpwm += 100;
	  if(motorpwm >= 1000) motorpwm = 0;
	  time_delay_ms(100);
	  Motor_Duty(Mot1,motorpwm);//刷新servopwm频率
//	  
//    if(!KEY_Read(KEY0))  
//    {
//      //if(motorpwm>99) 
//        motorpwm-=10;
//      Motor_Duty(Mot1,motorpwm);//刷新servopwm频率
//    }
//    else if(!KEY_Read(KEY2))  
//    {
//      //if(motorpwm<12000) 
//        motorpwm+=10;
//      Motor_Duty(Mot1,motorpwm);//刷新servopwm频率
//    }
//    else if(!KEY_Read(KEY1))  
//    {
//      motorpwm=500;
//      Motor_Duty(Mot1,motorpwm);//刷新servopwm频率
//    }    
    
    sprintf(txt,"PWM: %05d",motorpwm);
#ifdef __USE_TFT18    
    TFTSPI_P8X16Str(2,3,(uint8_t*)txt,u16WHITE,u16BLACK);		//字符串显示  
#else    
    LCD_P8x16Str(2,3,(uint8_t*)txt);
#endif
    
    UART_Put_Str(UART_4,(uint8*)txt); //PTE24 口输出 
    
    //LED闪烁
    LED_Ctrl(LED1, RVS);    
    time_delay_ms(50);
  }
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】CHIUSIR
【参数值】
【软件版本】V1.0
【最后更新】2017年10月27日 
【函数名】
【返回值】无
【参数值】
【实例】
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_AB_Pulse_Cnt(void)
{
  s16 counterVal;
  uint16_t motorpwm=50;  
  char txt[16]; 
  Motor_Init();        //电机频率设置
  Motor_Duty(Mot2,50);//刷新servopwm频率
  FTM_AB_Init(FTM1);           //编码器初始化
  FTM_AB_Init(FTM2);           //编码器初始化    
#ifdef __USE_TFT18
  TFTSPI_CLS(u16BLUE);//蓝色屏幕	
  TFTSPI_P8X16Str(13,0,(uint8_t*)txt,u16WHITE,u16BLACK);		//字符串显示    
#else    
  LCD_CLS();           //LCD清屏  
 // LCD_P8x16Str(13,0,(uint8_t*)"LQ Encoder CNT");
#endif
  
  
  while (1)
  {    if(!KEY_Read(KEY0))  
    {
      //if(motorpwm>99) 
        motorpwm-=10;
      Motor_Duty(Mot2,motorpwm);//刷新servopwm频率
    }
    else if(!KEY_Read(KEY2))  
    {
      //if(motorpwm<12000) 
        motorpwm+=10;
      Motor_Duty(Mot2,motorpwm);//刷新servopwm频率
    }
    else if(!KEY_Read(KEY1))  
    {
      motorpwm=50;
      Motor_Duty(Mot2,motorpwm);//刷新servopwm频率
    }    
    
    
    
    counterVal =FTM_AB_Get(FTM1);     //获取正交解码速度，正负表示方向;     
    
    sprintf(txt,"QAB1: %05d \n",counterVal);
    
#ifdef __USE_TFT18
    TFTSPI_P8X16Str(2,3,(uint8_t*)txt,u16WHITE,u16BLACK);		//字符串显示  
#else    
    LCD_P8x16Str(2,3,(uint8_t*)txt);
#endif     
    UART_Put_Str(UART_4,(uint8*)txt); //PTE24 口输出 
    
    time_delay_ms(200);
    counterVal =FTM_AB_Get(FTM2);     //获取正交解码速度，正负表示方向;   
    //sprintf(txt,"QAB2: %05d \n",counterVal);
    sprintf(txt,"PWM: %05d \n",motorpwm);
#ifdef __USE_TFT18
    TFTSPI_P8X16Str(2,5,(uint8_t*)txt,u16WHITE,u16BLACK);		//字符串显示  
#else    
    LCD_P8x16Str(2,5,(uint8_t*)txt);
#endif 
    UART_Put_Str(UART_4,(uint8*)txt); //PTE24 口输出 
    //LED闪烁
    LED_Ctrl(LED1, RVS);    
    time_delay_ms(200);         
  }
}
