/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱KV58F24智能车VD母板
【编    写】管脚复用部分由CHIUSIR修改确认，源程序在SDK，野火和苏大基础上移植
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
 
#include "include.h" 

UART_MemMapPtr UARTN[UART_MAX] = {UART0_BASE_PTR, UART1_BASE_PTR, UART2_BASE_PTR, UART3_BASE_PTR, UART4_BASE_PTR, UART5_BASE_PTR}; 

//-------------------------------------------------------------------------*
//函数名: uart_init                                                        
//功  能: 初始化UART                                                        
//参  数: uratn:模块名如：UART0 
//        baud: 波特率
//返  回: 无                                                              
//简  例: uart_init(UART4,115200);UART4对应引脚参考UART.H文件                                   
//-------------------------------------------------------------------------*

void UART_Init (UARTn_e uratn, uint32 baud)
{
    register uint16 sbr, brfa;
    uint8 temp;
    uint32 sysclk;     //时钟

    /* 配置 UART功能的 复用管脚 */
    switch(uratn)
    {
    case UART_0:
        SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;      //使能 UART0 时钟

        if(UART0_RX == PTA1)
        {                    
            PORTA_PCR1= PORT_PCR_MUX(2);       //使能PTA1引脚第二功能，即UART0_RXD
        }
        else if(UART0_RX == PTA15)
        {
             PORTA_PCR15= PORT_PCR_MUX(3);       //使能PTA15引脚第3功能
        }
        else if(UART0_RX == PTB16)
        {
             PORTB_PCR16= PORT_PCR_MUX(3);       //使能PTB16引脚第3功能
        }
        else if(UART0_RX == PTC6)
        {
             PORTC_PCR6= PORT_PCR_MUX(6);       //使能PTC6引脚第5功能
        }
        else if(UART0_RX == PTD6)
        {
             PORTD_PCR6= PORT_PCR_MUX(3);       //使能PTD6引脚第3功能
        }
        else if(UART0_RX == PTE21)
        {
             PORTE_PCR21= PORT_PCR_MUX(4);      
        }
        else if(UART0_RX == PTB1)
        {
             PORTB_PCR1= PORT_PCR_MUX(7);      
        }
        else
        {
            break;
        }

        if(UART0_TX == PTA2)
        {
             PORTA_PCR2= PORT_PCR_MUX(2);       //使能PTA2引脚第二功能
        }
        else if(UART0_TX == PTA14)
        {
             PORTA_PCR14= PORT_PCR_MUX(3);       //PTA14
        }
        else if(UART0_TX == PTB17)
        {
             PORTB_PCR17= PORT_PCR_MUX(3);       //PTB17
        }
        else if(UART0_TX == PTD7)
        {
             PORTD_PCR7= PORT_PCR_MUX(3);       //PTD7
        }
        else if(UART0_TX == PTC7)
        {
             PORTC_PCR7= PORT_PCR_MUX(5);       //PTC7
        }
        else if(UART0_TX == PTE20)
        {
             PORTE_PCR20= PORT_PCR_MUX(4);       
        }
        else if(UART0_TX == PTB0)
        {
             PORTB_PCR0= PORT_PCR_MUX(7);       
        }
        else
        {
             break;
        }

        break;

    case UART_1:
        SIM_SCGC4 |= SIM_SCGC4_UART1_MASK;

        if(UART1_RX == PTC3)
        {
             PORTC_PCR3= PORT_PCR_MUX(3);       //PTC3
        }
        else if(UART1_RX == PTE1)
        {
             PORTE_PCR1= PORT_PCR_MUX(3);       //PTE1
        }
        else
        {
            break;
        }

        if(UART1_TX == PTC4)
        {
             PORTC_PCR4= PORT_PCR_MUX(3);       //PTC4
        }
        else if(UART1_TX == PTE0)
        {
             PORTE_PCR0= PORT_PCR_MUX(3);       //PTE0
        }
        else
        {
            break;
        }

        break;

    case UART_2:
        SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
        if(UART2_RX == PTD2)
        {
             PORTD_PCR2= PORT_PCR_MUX(3);       //PTD2
        }
        else if(UART2_RX == PTE17)
        {
             PORTE_PCR17= PORT_PCR_MUX(3);       //PTE17
        }        
        else
        {
             break;
        }

        if(UART2_TX == PTD3)
        {
             PORTD_PCR3= PORT_PCR_MUX(3);       //PTD3
        }
        else if(UART2_TX == PTE16)
        {
             PORTE_PCR16= PORT_PCR_MUX(3);       //PTE16
        }        
        else
        {
             break;
        }
        break;

    case UART_3:
        SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;

        if(UART3_RX == PTB10)
        {
             PORTB_PCR10= PORT_PCR_MUX(3);       //PTB10
        }
        else if(UART3_RX == PTC16)
        {
             PORTC_PCR16= PORT_PCR_MUX(3);       //PTC16
        }
        else if(UART3_RX == PTE5)
        {
             PORTE_PCR5= PORT_PCR_MUX(3);       //PTE5
        }
        else
        {
             break;
        }

        if(UART3_TX == PTB11)
        {
             PORTB_PCR11= PORT_PCR_MUX(3);       //PTB11
        }
        else if(UART3_TX == PTC17)
        {
             PORTC_PCR17= PORT_PCR_MUX(3);       //PTC17
        }
        else if(UART3_TX == PTE4)
        {
             PORTE_PCR4= PORT_PCR_MUX(3);       //PTE4
        }
        else
        {
             break;
        }
        break;

    case UART_4:
        SIM_SCGC1 |= SIM_SCGC1_UART4_MASK;

        if(UART4_RX == PTC14)
        {
             PORTC_PCR14= PORT_PCR_MUX(9);       //PTC14
        }
        else if(UART4_RX == PTE25)
        {
             PORTE_PCR25= PORT_PCR_MUX(8);       //PTE25
        }
        else
        {
            break;
        }

        if(UART4_TX == PTC15)
        {
             PORTC_PCR15= PORT_PCR_MUX(9);       //PTC15
        }
        else if(UART4_TX == PTE24)
        {
             PORTE_PCR24= PORT_PCR_MUX(8);       //PTE24
        }
        else
        {
             break;
        }
        break;
    case UART_5:
        SIM_SCGC1 |= SIM_SCGC1_UART5_MASK;

        if(UART5_RX == PTD8)
        {
             PORTD_PCR8= PORT_PCR_MUX(3);       //PTD8
        }
        else if(UART5_RX == PTE9)
        {
             PORTE_PCR9= PORT_PCR_MUX(3);       //PTE9
        }
        else
        {
            break;
        }

        if(UART5_TX == PTD9)
        {
             PORTD_PCR9= PORT_PCR_MUX(3);       //PTD9
        }
        else if(UART5_TX == PTE8)
        {
             PORTE_PCR8= PORT_PCR_MUX(3);       //PTE8
        }
        else
        {
             break;
        }
        break;
    default:
        break;
    }

    //设置的时候，应该禁止发送接受
    UART_C2_REG(UARTN[uratn]) &= ~(0
                                   | UART_C2_TE_MASK
                                   | UART_C2_RE_MASK
                                  );


    //配置成8位无校验模式
    //设置 UART 数据格式、校验方式和停止位位数。通过设置 UART 模块控制寄存器 C1 实现；
    UART_C1_REG(UARTN[uratn]) |= (0
                                  //| UART_C2_M_MASK                    //9 位或 8 位模式选择 : 0 为 8位 ，1 为 9位（注释了表示0，即8位） （如果是9位，位8在UARTx_C3里）
                                  //| UART_C2_PE_MASK                   //奇偶校验使能（注释了表示禁用）
                                  //| UART_C2_PT_MASK                   //校验位类型 : 0 为 偶校验 ，1 为 奇校验
                                 );

    //计算波特率，串口0-5使用bus时钟   
    sysclk = (uint32)(bus_clk_M * 1000*1000);                          //bus时钟(是内核时钟的一半)
   

    //UART 波特率 = UART 模块时钟 / (16 × (SBR[12:0] + BRFA))
    //不考虑 BRFA 的情况下， SBR = UART 模块时钟 / (16 * UART 波特率)
    sbr = (uint16)(sysclk / (baud * 16));
    if(sbr > 0x1FFF)sbr = 0x1FFF;                                       //SBR 是 13bit，最大为 0x1FFF

    //已知 SBR ，则 BRFA =  = UART 模块时钟 / UART 波特率 - 16 ×SBR[12:0]
    brfa = (sysclk / baud)  - (sbr * 16);    

    //写 SBR
    temp = UART_BDH_REG(UARTN[uratn]) & (~UART_BDH_SBR_MASK);           //缓存 清空 SBR 的 UARTx_BDH的值
    UART_BDH_REG(UARTN[uratn]) = temp |  UART_BDH_SBR(sbr >> 8);        //先写入SBR高位
    UART_BDL_REG(UARTN[uratn]) = UART_BDL_SBR(sbr);                     //再写入SBR低位

    //写 BRFD
    temp = UART_C4_REG(UARTN[uratn]) & (~UART_C4_BRFA_MASK) ;           //缓存 清空 BRFA 的 UARTx_C4 的值
    UART_C4_REG(UARTN[uratn]) = temp |  UART_C4_BRFA(brfa);             //写入BRFA


    //设置FIFO(FIFO的深度是由硬件决定的，软件不能设置)
    UART_PFIFO_REG(UARTN[uratn]) |= (0
                                     | UART_PFIFO_TXFE_MASK               //使能TX FIFO(注释表示禁止)
                                     //| UART_PFIFO_TXFIFOSIZE(0)         //（只读）TX FIFO 大小，0为1字节，1~6为 2^(n+1)字节
                                     | UART_PFIFO_RXFE_MASK               //使能RX FIFO(注释表示禁止)
                                     //| UART_PFIFO_RXFIFOSIZE(0)         //（只读）RX FIFO 大小，0为1字节，1~6为 2^(n+1)字节
                                    );

    /* 允许发送和接收 */
    UART_C2_REG(UARTN[uratn]) |= (0
                                  | UART_C2_TE_MASK                     //发送使能
                                  | UART_C2_RE_MASK                     //接收使能
                                  //| UART_C2_TIE_MASK                  //发送中断或DMA传输请求使能（注释了表示禁用）
                                  //| UART_C2_TCIE_MASK                 //发送完成中断使能（注释了表示禁用）
                                  //| UART_C2_RIE_MASK                  //接收满中断或DMA传输请求使能（注释了表示禁用）
                                 );
}

//-------------------------------------------------------------------------*
//函数名: uart_getchar                                                        
//功  能: 接收一个字节                                                        
//参  数: uratn:模块名如：UART0 
//        ch: 保存接收数据指针
//返  回: 无                                                              
//简  例: uart_getchar (UART4,a[]) 将接收到的数据保存在a数组里                                
//-------------------------------------------------------------------------*
char UART_Get_Char (UARTn_e uratn)
{

    while (!(UART_S1_REG(UARTN[uratn]) & UART_S1_RDRF_MASK));       //等待接收满了

    //*ch =  UART_D_REG(UARTN[uratn]);
    return(UART_D_REG(UARTN[uratn]));

}


//-------------------------------------------------------------------------*
//函数名: uart_querychar                                                        
//功  能: 查询接收1个字符                                                       
//参  数: uratn:模块名如：UART0 
//          ch: 保存接收数据指针
//返  回: 1代表成功 0代表失败                                                              
//简  例: uart_querychar (UART4,a[]) 将接收到的数据保存在a数组里                                
//-------------------------------------------------------------------------*
char UART_Query_Char (UARTn_e uratn, char *ch)
{
    if( UART_RCFIFO_REG(UARTN[uratn]) )         //查询是否接受到数据
    {
        *ch  =   UART_D_REG(UARTN[uratn]);      //接受到8位的数据
        return  1;                              //返回 1 表示接收成功
    }

    *ch = 0;                                    //接收不到，应该清空了接收区
    return 0;                                   //返回0表示接收失败
}


//-------------------------------------------------------------------------*
//函数名: uart_querychar                                                        
//功  能: 查询接收字符串                                                       
//参  数: uratn:模块名如：UART0 
//         str: 保存接收数据指针
//     max_len: 最大接收长度
//返  回: i为字符串长度（范围在0~max_len）                                                              
//简  例: uart_querystr (UART4,a[],100) 将接收到的数据保存在a数组里                                
//-------------------------------------------------------------------------*
char UART_Query_Str (UARTn_e uratn, char *str, uint32 max_len)
{
    uint32 i = 0;
    while(UART_Query_Char(uratn, str + i)  )
    {
        if( *(str + i) == NULL )    //接收到字符串结束符
        {
            return i;
        }

        i++;
        if(i >= max_len)            //超过设定的最大值，退出
        {
            return i;
        }
    };

    return i;
}


//-------------------------------------------------------------------------*
//函数名: uart_putchar                                                        
//功  能: 发送一个字节                                                       
//参  数: uratn:模块名如：UART0 
//         ch: 发送的字节
//返  回: 无                                                              
//简  例: uart_putchar (UART4, 0x66);                               
//-------------------------------------------------------------------------*
void UART_Put_Char (UARTn_e uratn, char ch)
{
    //等待发送缓冲区空
    while(!(UART_S1_REG(UARTN[uratn]) & UART_S1_TDRE_MASK));

    //发送数据
    UART_D_REG(UARTN[uratn]) = (uint8)ch;
}



//-------------------------------------------------------------------------*
//函数名: uart_query                                                        
//功  能: 查询是否接受到一个字节                                                       
//参  数: uratn:模块名如：UART0 
//返  回: 1代表成功 0代表失败                                                               
//简  例: uart_query (UART4);                               
//-------------------------------------------------------------------------*
char UART_Query (UARTn_e uratn)
{
    if(UART_RCFIFO_REG(UARTN[uratn]))                 //接收到数据数量非0

    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//-------------------------------------------------------------------------*
//函数名: uart_putchar                                                        
//功  能: 发送指定len个字节长度数组 （包括 NULL 也会发送）                                                       
//参  数: uratn:模块名如：UART0 
//        buff: 发送的地址、
//        len : 发送指定长度
//返  回: 无                                                              
//简  例: uart_putchar (UART4, "123456789",5);实际发送5个字节‘1’‘2’‘3’‘4’‘5’                               
//-------------------------------------------------------------------------*
void UART_Put_Buff (UARTn_e uratn, s8 *buff, uint32 len)
{
    while(len--)
    {
        UART_Put_Char(uratn, *buff);
        buff++;
    }
}



//-------------------------------------------------------------------------*
//函数名: uart_putstr                                                        
//功  能: 发送字符串(遇 NULL 停止发送)                                                       
//参  数: uratn:模块名如：UART0 
//        str: 发送的地址、
//返  回: 无                                                              
//简  例: uart_putchar (UART4, "123456789");实际发送9个字节                              
//-------------------------------------------------------------------------*
void UART_Put_Str (UARTn_e uratn, const uint8 *str)
{
    while(*str)
    {
        UART_Put_Char(uratn, *str++);
    }
}


//-------------------------------------------------------------------------*
//函数名: UART_Irq_En                                                        
//功  能: 开串口接收中断                                                      
//参  数: uratn:模块名如：UART0      
//返  回: 无                                                              
//简  例: UART_Irq_En (UART4);                             
//-------------------------------------------------------------------------*
void UART_Irq_En(UARTn_e uratn)
{    
    switch(uratn)
    {
      case UART_0:
          UART0_C2 |= UART_C2_RIE_MASK;    //开放UART接收中断
         // enable_irq((uratn << 1) + 45);	//开接收引脚的IRQ中断
          NVIC_EnableIRQ(UART0_RX_TX_IRQn);
      break;
      case UART_1:
          UART1_C2 |= UART_C2_RIE_MASK;    //开放UART接收中断         
          NVIC_EnableIRQ(UART1_RX_TX_IRQn);
      break;
      case UART_2:
          UART2_C2 |= UART_C2_RIE_MASK;    //开放UART接收中断         
          NVIC_EnableIRQ(UART2_RX_TX_IRQn);
      break;
      case UART_3:
          UART3_C2 |= UART_C2_RIE_MASK;    //开放UART接收中断         
          NVIC_EnableIRQ(UART3_RX_TX_IRQn);
      break;
      case UART_4:
          UART4_C2 |= UART_C2_RIE_MASK;    //开放UART接收中断         
          NVIC_EnableIRQ(UART4_RX_TX_IRQn);
      break;
      case UART_5:
          UART5_C2 |= UART_C2_RIE_MASK;    //开放UART接收中断         
          NVIC_EnableIRQ(UART5_RX_TX_IRQn);
      break;
      default:
      break;
    }
}

//-------------------------------------------------------------------------*
//函数名: UART_Irq_Dis                                                        
//功  能: 关串口接收中断                                                      
//参  数: uratn:模块名如：UART0      
//返  回: 无                                                              
//简  例: UART_Irq_Dis (UART4);                             
//-------------------------------------------------------------------------*
void UART_Irq_Dis(UARTn_e uratn)
{
    switch(uratn)
    {
      case UART_0:
          UART0_C2 &= ~UART_C2_RIE_MASK;    //开放UART接收中断
         // enable_irq((uratn << 1) + 45);	//开接收引脚的IRQ中断
          NVIC_DisableIRQ(UART0_RX_TX_IRQn);
      break;
      case UART_1:
          UART1_C2 &= ~UART_C2_RIE_MASK;    //开放UART接收中断         
          NVIC_DisableIRQ(UART1_RX_TX_IRQn);
      break;
      case UART_2:
          UART2_C2 &= ~UART_C2_RIE_MASK;    //开放UART接收中断         
          NVIC_DisableIRQ(UART2_RX_TX_IRQn);
      break;
      case UART_3:
          UART3_C2 &= ~UART_C2_RIE_MASK;    //开放UART接收中断         
          NVIC_DisableIRQ(UART3_RX_TX_IRQn);
      break;
      case UART_4:
          UART4_C2 &= ~UART_C2_RIE_MASK;    //开放UART接收中断         
          NVIC_DisableIRQ(UART4_RX_TX_IRQn);
      break;
      case UART_5:
          UART5_C2 &= ~UART_C2_RIE_MASK;    //开放UART接收中断         
          NVIC_DisableIRQ(UART5_RX_TX_IRQn);
      break;
      default:
      break;    
    }
}

//中断服务函数      
void UART0_RX_TX_IRQHandler(void)
{
    //接收一个字节数据并回发       
    UART_Put_Char (UART_0,UART_Get_Char(UART_0)); 
}
void UART1_RX_TX_IRQHandler(void)
{
    //接收一个字节数据并回发       
    UART_Put_Char (UART_1,UART_Get_Char(UART_1)); 
}

void UART2_RX_TX_IRQHandler(void)
{
    //接收一个字节数据并回发       
    UART_Put_Char (UART_2,UART_Get_Char(UART_2)); 
}
void UART3_RX_TX_IRQHandler(void)
{
    //接收一个字节数据并回发       
    UART_Put_Char (UART_3,UART_Get_Char(UART_3)); 
}

void UART4_RX_TX_IRQHandler(void)
{
    //接收一个字节数据并回发       
    LED_Ctrl(LED2, RVS);
    UART_Put_Char (UART_4,UART_Get_Char(UART_4)); 
}
void UART5_RX_TX_IRQHandler(void)
{
    //接收一个字节数据并回发       
    UART_Put_Char (UART_5,UART_Get_Char(UART_5)); 
}
// test function 
void Test_UART(void)
{    
    //UART串口演示
    UART_Init(UART_4,115200);
    UART_Irq_En(UART_4);
    UART_Put_Str(UART_4,"LongQiu UART4 ADC\n"); 
 
    UART_Init(UART_0,115200);
    UART_Irq_En(UART_0);
    UART_Put_Str(UART_0,"LongQiu UART0 ADC\n");
    
    UART_Init(UART_1,115200);
    UART_Irq_En(UART_1);
    UART_Put_Str(UART_1,"LongQiu UART1 ADC\n");
    
    UART_Init(UART_2,115200);
    UART_Irq_En(UART_2);
    UART_Put_Str(UART_2,"LongQiu UART2 ADC\n");
    
    UART_Init(UART_3,115200);
    UART_Irq_En(UART_3);
    UART_Put_Str(UART_3,"LongQiu UART3 ADC\n");
    
    UART_Init(UART_5,115200);
    UART_Irq_En(UART_5);
    UART_Put_Str(UART_5,"LongQiu UART5 ADC\n");
    
    while (1)
    {       
      //LED闪烁
      LED_Ctrl(LED1, RVS);
      UART_Put_Str(UART_4,"LongQiu UART4 ADC\n"); 
      //systick中断延时
      time_delay_ms(500);
    }
}

