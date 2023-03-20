/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱KV58F24智能车VD母板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2017年12月19日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4
【Target  】MKV58F1M0VLQ24
【Crystal 】 50.000Mhz
【busclock】120.000MHz
【pllclock】240.000MHz

ADC0测试OK
HSADC无法采集数据
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

//-------------------------------------------------------------------------*
//函数名: ADC_init                                                         *
//功  能: 初始化ADC                                                        * 
//参  数: adc_n:模块名ADC0或HSADC1                                         *
//返  回: 无                                                               *
//简  例: ADC_init（ADC0）初始化ADC0模块                                   *
//-------------------------------------------------------------------------*
void ADC0_Init(void)
{          
  SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK );        //开启ADC0时钟
  SIM_SOPT7 &= ~(SIM_SOPT7_HSADC0AALTTRGEN_MASK  | SIM_SOPT7_HSADC0AALTTRGEN_MASK);
  SIM_SOPT7 |= SIM_SOPT7_HSADC0ATRGSEL(0);    
 }

//-------------------------------------------------------------------------*
//函数名: adc_start                                                        *
//功  能: 启动ADC转换                                                      * 
//参  数: adc_n:模块名ADC0或HSADC1                                         *
//        adc_ch:通道编号                                                  *
//        bit:精度选择ADC_8bit，ADC_12bit，ADC_10bit，ADC_16bit            * 
//返  回: 无                                                               *
//简  例: 一般由adc_once函数调用，不单独使用                               *
//-------------------------------------------------------------------------*
void ADC0_Start(ADC0_Ch_e adc_ch,ADC0_nbit bit)
{    
	int ch=0;
	
	ADC0_CFG1 = (0  | ADC_CFG1_ADIV(2)           //时钟分频选择,分频系数为 2^n,2bit
				 | ADC_CFG1_ADLSMP_MASK       //采样时间配置，0为短采样时间，1 为长采样时间
					 | ADC_CFG1_MODE(bit)         //精确度选择
						 | ADC_CFG1_ADICLK(0)         //0为总线时钟,1为总线时钟/2,2为交替时钟（ALTCLK），3为 异步时钟（ADACK）。
							 );
	
	ADC0_CFG2  = (0  | ADC_CFG2_ADHSC_MASK        //高速配置,0为正常转换序列，1为高速转换序列
				  | ADC_CFG2_ADLSTS(0)         //长采样时间选择，ADCK为4+n个额外循环，额外循环，0为20，1为12，2为6，3为2
					  );
	
	
	ch=adc_ch;//ch=0x0e
	ADC0_CFG2 |= ADC_CFG2_MUXSEL_MASK;          // 0选择a  0 ADxxa channels are selected.
	
	//写入 SC1A 启动转换
	ADC0_SC1(0) = (0 | ADC_SC1_AIEN_MASK          // 转换完成中断,0为禁止，1为使能
				   | ADC_SC1_ADCH(ch)          //ADC0 通道13
                  );
}

//-------------------------------------------------------------------------*
//函数名: adc_once                                                        
//功  能: 进行ADC单次转换                                                   
//参  数: adc_n:模块名ADC0或HSADC1                                           
//        adc_ch:通道编号                                                  
//        bit:精度选择ADC_8bit，ADC_12bit，ADC_10bit，ADC_16bit             
//返  回: result                                                              
//简  例: adc_once(ADC0,HSADC1_SE8,ADC_12bit) 通道编号为 HSADC1_SE8的引脚，进行
//          一次ADC转换。HSADC1_SE8对应引脚请查看ADC.H文件                    
//-------------------------------------------------------------------------*
u16 ADC0_Once(ADC0_Ch_e adc_ch,ADC0_nbit bit) //采集某路模拟量的AD值
{   
  int result = 0;
  
  ADC0_Start(adc_ch,bit);      //启动ADC转换
  while ((ADC0_SC1(0) & ADC_SC1_COCO_MASK )!= ADC_SC1_COCO_MASK);   //只支持 AB通道
  result = ADC0_R(0);
  ADC0_SC1(0) &= ~ADC_SC1_COCO_MASK;
  return result;  
}

//-------------------------------------------------------------------------*
//函数名: adc_ave                                                        
//功  能: 进行ADC多次转换，取平均值                                                   
//参  数: adc_n:模块名ADC0或HSADC1                                           
//        adc_ch:通道编号                                                  
//        bit:精度选择ADC_8bit，ADC_12bit，ADC_10bit，ADC_16bit 
//        N  :均值滤波次数（1~65535）
//返  回: tmp                                                              
//简  例: adc_ave(ADC0,HSADC1_SE8,ADC_12bit,100) 通道编号为 HSADC1_SE8的引脚，进行
//          100次ADC转换，计算出平均值返回。                   
//-------------------------------------------------------------------------*
u16 ADC0_Ave(ADC0_Ch_e adc_ch,ADC0_nbit bit,u16 N) //均值滤波
{
    u32 tmp = 0;
    u8  i;
    
    for(i = 0; i < N; i++)
       tmp += ADC0_Once(adc_ch,bit); 
    
    tmp = tmp / N; 
    
    return (u16)tmp;
}

//
void Test_ADC0(void)
{
  char txt[16];
  uint16_t batv=0;  
  
  //UART串口演示
  UART_Init(UART_4,115200);
  UART_Put_Str(UART_4,"LongQiu UART4 ADC \n");
  //UARTIrq_En(UART0);
  LCD_CLS();                   //LCD清屏
  LCD_P8x16Str(4,0,(uint8_t*)"LQ ADC Test Bat");  
  ADC0_Init();             //电源低压报警ADC初始化
  while (1)
  {           
    //测试ADC转换                                     //电池电压采集
    batv=ADC0_Ave(ADC0_SE5b,ADC_12bit,10)*22/91; //330/4095*3,PTA7 
    //if(batv<700)                                    //低于7V，OLED提示电压
    {
      sprintf(txt,"BAT:%d.%dV ",batv/100,batv%100);// *3.3/4095*3
      LCD_P8x16Str(20,3,(u8*)txt);
    }  
    UART_Put_Str(UART_4,(u8*)txt);        
    
    //LED闪烁
    LED_Ctrl(LED1, RVS);     
    
    //systick中断延时
    time_delay_ms(500);
  }
}
