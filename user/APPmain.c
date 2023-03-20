/*******************************************************************************
【平    台】龙邱KV58F24智能车VD母板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2018年3月28日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4及以上版本
【Target  】MKV58F1M0VLQ24
【Crystal 】 50.000Mhz
【busclock】137.500MHz
【pllclock】275.000MHz
------------------------------------------------
没有完美的代码，只有不断的奉献，大家一起努力；
赠人玫瑰手留余香，欢迎大家反馈bug，将开源进行到底；
=============================================================
接口定义：
摄像头          单片机接口    
VCC             3.3V 
GND             GND
Y0-7            PTD0-7共8位并口      
HREF            PTD13
VSY             PTD14
PCK             PTD12
-------------------------------------------------------------
TSL1401模块     单片机接口
VCC             5V
GND             GND
SI              PTE27
SCK             PTE28
ADC             ADC0_SE8
ADC             ADC0_SE4B

SI              PTE2
SCK             PTE3
ADC             ADC0DP0
ADC             ADC0_SE5B
===============================================================
多路电感模块    单片机接口
VCC             3.3V
GND             GND
ADC通道         管脚关系     
ADC0_SE10       PTE5
ADC0_DP2        PTE4
ADC0_SE4A       PTE6
ADC0_DP3        PTE11
ADC0_SE11       PTE12
ADC0_DP1        PTE16
ADC0_SE9        PTE17
ADC0_SE5A       PTE18
-------------------------------------------------------------
电源监控或者它用
ADC0_SE7A       HSADC0CH6  
-------------------------------------------------------------
九轴模块        单片机接口   FLEXCOMM8
VCC             3V3
GND             GND
SDA1            PTD8
SCL1            PTD9
//////////////////////////////////////////////////////////通用部分功能//////////
电机驱动        单片机接口   
VCC             3.3V
FTM0_CH0  PTC1，电机驱动接口
FTM0_CH1  PTC2，电机驱动接口
FTM0_CH2  PTC3，电机驱动接口
FTM0_CH3  PTC4，电机驱动接口
-------------------------------------------------------------
舵机接口        单片机接口
VADJ            可调电源
GND             GND
FTM3_CH6        PTC10，舵机接口
FTM3_CH7        PTC11，舵机接口
-------------------------------------------------------------
龙邱512编码器   单片机接口     
VCC             3V3
GND             GND      
LSB/A           PTA12   
DIR/B           PTA13
LSB/A           PTB18
DIR/B           PTB19
-------------------------------------------------------------
OLED模块        单片机接口  核心板用的是PTC16-19
VCC             3.3V        用户自行修改初始化和管脚定义
GND             GND
RST             PTC13
DC              PTC14
SDA             PTC15
CLK             PTC16
CS              PTC12
-------------------------------------------------------------
蓝牙/USBTTL     单片机接口   
GND             GND
TX              PTE24   UART4_TX 接蓝牙的RX
RX              PTE25   UART4_RX 接蓝牙的TX
-------------------------------------------------------------
LED接口定义：
LED1            PTA17 核心板
LED2            PTC0  核心板
LED3            PTD15 核心板   
LED4            PTE29 核心板
LEDD1           PTC18 母板
LEDD2           PTC19 母板
-------------------------------------------------------------
KEY接口定义：
KEY0            PTB20  
KEY1            PTB21
KEY2            PTB22   //可中断触发
-------------------------------------------------------------
修改历史：
20180208-中断处理函数在startup_MKV58F24.s中，名字必须对应才能触发中断；
20180327-已经修改神眼摄像头的采集模式为DMA，分辨率为188*120，100db HDR；
********************************************************************************/
#include "include.h"
extern uint8 RotaryIslandFlag;
extern uint8 RightInAngle;
extern uint8 LeftInAngle;
extern u32 ServoValue;
extern uint8_t Threshold;
extern u8 Image_Data[IMAGEH][IMAGEW];//extern u8 Image_Data[4800];//[60][150];
void Main_Program();
uint8 flagggg=0;
extern uint8 BlackLeftStep1ScanRow;
extern uint8 BlackRightStep1ScanRow;
extern int32 DeviPre;
extern u32 ServoValue;
extern s16 speed;
uint8 qidongflag=0;  //如果有用OLED修改参数的话，参数flag会被置位
uint8 qidongflag1=0;
uint8 failstop=0;
uint8 QuitFlag = 0;
uint8 read_key0=1;
uint8 read_sw0=1;
uint8 read_key_sw0=1;
uint32 cnv,mod;
//==========================================================================================  
//测试函数名称        测试内部模块及功能           智能车及应用开发               完成状况
//----------------------------------------------------------------------------------------- 
//Test_LED();         //测试GPIO输出口              LED显示及外设控制              已完成
//Test_OLED();       //测试模拟SPI功能              OLED模块功能                   已完成
//Test_GPIO_KEY();   //测试GPIO输入                 按键检测功能                   已完成 
//Test_GPIO_EXINT(); //测试GPIO输入及外部中断       按键、中断检测功能             已完成     
//Test_UART();       //测试UART及中断               蓝牙、USB转TTL调试及通信       已完成
//Test_ADC0();       //测试ADC采集功能              电磁传感器及电源电压监控       部分完成,HSADC不能通过
//void Test_Servo();      //测试用FTM-PWM功能            数字舵机驱动控制               已完成
//Test_Motor();      //测试用FTM-PWM功能            电机驱动控制                   已完成
//Test_AB_Pulse_Cnt();//测试用FTM正交解码功能       编码器测速,电机舵机控制        已完成 
//Test_LPTMR_delay();//测试LPTMR功能                延时功能                       已完成
//Test_LPTMR_Counter();//测试LPTMR功能              计数功能                       已完成
//Test_DMA_Counter();//测试DMA计数功能              计数功能                       已完成
//TestOLED_TSL1401();//测试OLED和TSL1401功能        OLED显示屏及线阵摄像头         已完成
//TestOLED_MT9V034();//测试OLED和MT9V034功能        OLED显示屏及面阵摄像头动图     已完成
//Test_WDG();        //测试看门狗功能               程序监控                       已完成
//========================================================================================== 

void main(void)
{  
	PLL_Init(PLL235);//235         //设置内核及总线频率等
	DisableInterrupts
//        EnableInterrupts
        time_delay_ms(50);        //延时 
  
        Servo_Init();          // 初始化舵机
        time_delay_ms(1000);
//        Servo_Duty((u32)(sever_middle + 80));
	KEY_SW_Init();               //按键及输入口初始化  
	LED_Init();               //LED初始化
	UART_Init(UART_4,1380000);//1500000); //串口初始化//????
	//	默认使用:龙邱 OLED SPI模块
	LCD_Init();               //LCD初始化
	LCD_CLS();                //清屏	  
	LCD_Show_LQLogo();        //显示龙邱LOGO
	time_delay_ms(500);       //延时  
	LCD_CLS();                //清屏
	time_delay_ms(50);        //延时 
        LED_RED_ON;
        
	LED_RED_OFF;
        
        LED_GREEN_ON;
	LED_GREEN_OFF;
        
	
	//电源采集ADC6
//	ADC0_Init();//
	FTM_AB_Init(FTM2);
	PIT_Init(PIT0, 2);	
	Motor_Init();          //初始化电机
        time_delay_ms(2000);

	MT9V034_Init();         //初始化摄像头
	
	Para_Init();        //补充初始化为已有设定值wk
	LCD_CLS();                //清屏 
//        while(1)
//        {
//          cnv=FTM_CnV_REG(FTM3, FTM_CH7);
//          mod=FTM_MOD_REG(FTM3) ;
//        }
	EnableInterrupts;
       
        time_delay_ms(50);        //延时 
        OLED_PrintValueF(72, 0,level,1);
	while(1)
	{       read_key0= gpio_get(BT_SHOW);
                read_sw0=gpio_get(SW1); 
                read_key_sw0=(gpio_get(BT_SHOW)||(!gpio_get(SW1)));
//                Servo_Duty((u32)(sever_middle + 80));
		Pre_Check_BottonPress();
		OLED_PrintValueF(72, 0,level,1);
                                                                        /*
                                                                        作用： 在液晶屏的指定位置显示一个浮点数
                                                                        参数： x:横坐标 取值 0-127
                                                                              y:纵坐标坐标 取值0-7（只能显示8行 每行8列 ） 
                                                                              data：需要显示的值 
                                                                              num：整数加小数部分的长度
                                                                        返回：无
                                                                        */
		if(QuitFlag) 
		{
			time_delay_ms(100);
			break;
		}
	}
	LCD_CLS(); 
	Main_Program();      //主程序
	//-----------------------------------------------------------------------------------------
	while(1)
	{   
		LED_Ctrl(LED1, RVS);//反转       
		time_delay_ms(5000); //延时           
	}
}

void Main_Program()
{
	int i=0;
	Dirc=1;
	new_img=1;

	while(1)
	{
		Check_BottonPress();
		if(0)
		{
			SendPara=0;
			Send_Parameter();
		}
		if(new_img)
		{
			Get_Use_Image();
			Get_01_Value();//更新Image_Use && imgbuff_process
			get_edge();
			new_img = 0;
			Search();
			Direction_Control();
			if(1)
			{
				Send_Begin();
				Variable_update();
				Send_Variable();
				sendimg();
			}
			if(OLED_Refresh)
			{
				OLED_Draw_UI();
			}
		}
	}
}

//////////////////////////////////////===================///////////////////////////
//////////////////////////////////////===================///////////////////////////
//电机控制
void PIT0_IRQHandler()
{
	static uint8 flag_6ms,cnt=0;
	PIT_Flag_Clear(PIT0);       //清中断标志位
	if(!Stop)
	{
		RunTime=RunTime+0.002;
		AverageSpeed=Distance/RunTime;
                LED_BLUE_ON;
	}
        else 
                LED_BLUE_OFF;

	cnt++;
	if(cnt==1)      //4ms运行一次
	{
		LED_RED_TURN;
		Get_Speed();
	}
	if(cnt>=4)	cnt=0;
	//100ms
	flag_6ms++;
	if(flag_6ms>Speed_Filter_Times)
	{
		flag_6ms=0;  
		Speed_Control();  //6ms进行一次速度控制
		SpeedCount=0;
	}
	if(Starting)
	{
		Start_Cnt--; 
		LED_GREEN_TURN;
		if(Start_Cnt==0)
		{
			Starting=0;
			Stop=0;
			LED_GREEN_OFF;
		}
	}
	SpeedCount++;
	Speed_Control_Output();
	Moto_Out();
}