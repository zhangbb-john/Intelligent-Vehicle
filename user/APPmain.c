/*******************************************************************************
��ƽ    ̨������KV58F24���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��3��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4�����ϰ汾
��Target  ��MKV58F1M0VLQ24
��Crystal �� 50.000Mhz
��busclock��137.500MHz
��pllclock��275.000MHz
------------------------------------------------
û�������Ĵ��룬ֻ�в��ϵķ��ף����һ��Ŭ����
����õ���������㣬��ӭ��ҷ���bug������Դ���е��ף�
=============================================================
�ӿڶ��壺
����ͷ          ��Ƭ���ӿ�    
VCC             3.3V 
GND             GND
Y0-7            PTD0-7��8λ����      
HREF            PTD13
VSY             PTD14
PCK             PTD12
-------------------------------------------------------------
TSL1401ģ��     ��Ƭ���ӿ�
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
��·���ģ��    ��Ƭ���ӿ�
VCC             3.3V
GND             GND
ADCͨ��         �ܽŹ�ϵ     
ADC0_SE10       PTE5
ADC0_DP2        PTE4
ADC0_SE4A       PTE6
ADC0_DP3        PTE11
ADC0_SE11       PTE12
ADC0_DP1        PTE16
ADC0_SE9        PTE17
ADC0_SE5A       PTE18
-------------------------------------------------------------
��Դ��ػ�������
ADC0_SE7A       HSADC0CH6  
-------------------------------------------------------------
����ģ��        ��Ƭ���ӿ�   FLEXCOMM8
VCC             3V3
GND             GND
SDA1            PTD8
SCL1            PTD9
//////////////////////////////////////////////////////////ͨ�ò��ֹ���//////////
�������        ��Ƭ���ӿ�   
VCC             3.3V
FTM0_CH0  PTC1����������ӿ�
FTM0_CH1  PTC2����������ӿ�
FTM0_CH2  PTC3����������ӿ�
FTM0_CH3  PTC4����������ӿ�
-------------------------------------------------------------
����ӿ�        ��Ƭ���ӿ�
VADJ            �ɵ���Դ
GND             GND
FTM3_CH6        PTC10������ӿ�
FTM3_CH7        PTC11������ӿ�
-------------------------------------------------------------
����512������   ��Ƭ���ӿ�     
VCC             3V3
GND             GND      
LSB/A           PTA12   
DIR/B           PTA13
LSB/A           PTB18
DIR/B           PTB19
-------------------------------------------------------------
OLEDģ��        ��Ƭ���ӿ�  ���İ��õ���PTC16-19
VCC             3.3V        �û������޸ĳ�ʼ���͹ܽŶ���
GND             GND
RST             PTC13
DC              PTC14
SDA             PTC15
CLK             PTC16
CS              PTC12
-------------------------------------------------------------
����/USBTTL     ��Ƭ���ӿ�   
GND             GND
TX              PTE24   UART4_TX ��������RX
RX              PTE25   UART4_RX ��������TX
-------------------------------------------------------------
LED�ӿڶ��壺
LED1            PTA17 ���İ�
LED2            PTC0  ���İ�
LED3            PTD15 ���İ�   
LED4            PTE29 ���İ�
LEDD1           PTC18 ĸ��
LEDD2           PTC19 ĸ��
-------------------------------------------------------------
KEY�ӿڶ��壺
KEY0            PTB20  
KEY1            PTB21
KEY2            PTB22   //���жϴ���
-------------------------------------------------------------
�޸���ʷ��
20180208-�жϴ�������startup_MKV58F24.s�У����ֱ����Ӧ���ܴ����жϣ�
20180327-�Ѿ��޸���������ͷ�Ĳɼ�ģʽΪDMA���ֱ���Ϊ188*120��100db HDR��
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
uint8 qidongflag=0;  //�������OLED�޸Ĳ����Ļ�������flag�ᱻ��λ
uint8 qidongflag1=0;
uint8 failstop=0;
uint8 QuitFlag = 0;
uint8 read_key0=1;
uint8 read_sw0=1;
uint8 read_key_sw0=1;
uint32 cnv,mod;
//==========================================================================================  
//���Ժ�������        �����ڲ�ģ�鼰����           ���ܳ���Ӧ�ÿ���               ���״��
//----------------------------------------------------------------------------------------- 
//Test_LED();         //����GPIO�����              LED��ʾ���������              �����
//Test_OLED();       //����ģ��SPI����              OLEDģ�鹦��                   �����
//Test_GPIO_KEY();   //����GPIO����                 ������⹦��                   ����� 
//Test_GPIO_EXINT(); //����GPIO���뼰�ⲿ�ж�       �������жϼ�⹦��             �����     
//Test_UART();       //����UART���ж�               ������USBתTTL���Լ�ͨ��       �����
//Test_ADC0();       //����ADC�ɼ�����              ��Ŵ���������Դ��ѹ���       �������,HSADC����ͨ��
//void Test_Servo();      //������FTM-PWM����            ���ֶ����������               �����
//Test_Motor();      //������FTM-PWM����            �����������                   �����
//Test_AB_Pulse_Cnt();//������FTM�������빦��       ����������,����������        ����� 
//Test_LPTMR_delay();//����LPTMR����                ��ʱ����                       �����
//Test_LPTMR_Counter();//����LPTMR����              ��������                       �����
//Test_DMA_Counter();//����DMA��������              ��������                       �����
//TestOLED_TSL1401();//����OLED��TSL1401����        OLED��ʾ������������ͷ         �����
//TestOLED_MT9V034();//����OLED��MT9V034����        OLED��ʾ������������ͷ��ͼ     �����
//Test_WDG();        //���Կ��Ź�����               ������                       �����
//========================================================================================== 

void main(void)
{  
	PLL_Init(PLL235);//235         //�����ں˼�����Ƶ�ʵ�
	DisableInterrupts
//        EnableInterrupts
        time_delay_ms(50);        //��ʱ 
  
        Servo_Init();          // ��ʼ�����
        time_delay_ms(1000);
//        Servo_Duty((u32)(sever_middle + 80));
	KEY_SW_Init();               //����������ڳ�ʼ��  
	LED_Init();               //LED��ʼ��
	UART_Init(UART_4,1380000);//1500000); //���ڳ�ʼ��//????
	//	Ĭ��ʹ��:���� OLED SPIģ��
	LCD_Init();               //LCD��ʼ��
	LCD_CLS();                //����	  
	LCD_Show_LQLogo();        //��ʾ����LOGO
	time_delay_ms(500);       //��ʱ  
	LCD_CLS();                //����
	time_delay_ms(50);        //��ʱ 
        LED_RED_ON;
        
	LED_RED_OFF;
        
        LED_GREEN_ON;
	LED_GREEN_OFF;
        
	
	//��Դ�ɼ�ADC6
//	ADC0_Init();//
	FTM_AB_Init(FTM2);
	PIT_Init(PIT0, 2);	
	Motor_Init();          //��ʼ�����
        time_delay_ms(2000);

	MT9V034_Init();         //��ʼ������ͷ
	
	Para_Init();        //�����ʼ��Ϊ�����趨ֵwk
	LCD_CLS();                //���� 
//        while(1)
//        {
//          cnv=FTM_CnV_REG(FTM3, FTM_CH7);
//          mod=FTM_MOD_REG(FTM3) ;
//        }
	EnableInterrupts;
       
        time_delay_ms(50);        //��ʱ 
        OLED_PrintValueF(72, 0,level,1);
	while(1)
	{       read_key0= gpio_get(BT_SHOW);
                read_sw0=gpio_get(SW1); 
                read_key_sw0=(gpio_get(BT_SHOW)||(!gpio_get(SW1)));
//                Servo_Duty((u32)(sever_middle + 80));
		Pre_Check_BottonPress();
		OLED_PrintValueF(72, 0,level,1);
                                                                        /*
                                                                        ���ã� ��Һ������ָ��λ����ʾһ��������
                                                                        ������ x:������ ȡֵ 0-127
                                                                              y:���������� ȡֵ0-7��ֻ����ʾ8�� ÿ��8�� �� 
                                                                              data����Ҫ��ʾ��ֵ 
                                                                              num��������С�����ֵĳ���
                                                                        ���أ���
                                                                        */
		if(QuitFlag) 
		{
			time_delay_ms(100);
			break;
		}
	}
	LCD_CLS(); 
	Main_Program();      //������
	//-----------------------------------------------------------------------------------------
	while(1)
	{   
		LED_Ctrl(LED1, RVS);//��ת       
		time_delay_ms(5000); //��ʱ           
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
			Get_01_Value();//����Image_Use && imgbuff_process
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
//�������
void PIT0_IRQHandler()
{
	static uint8 flag_6ms,cnt=0;
	PIT_Flag_Clear(PIT0);       //���жϱ�־λ
	if(!Stop)
	{
		RunTime=RunTime+0.002;
		AverageSpeed=Distance/RunTime;
                LED_BLUE_ON;
	}
        else 
                LED_BLUE_OFF;

	cnt++;
	if(cnt==1)      //4ms����һ��
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
		Speed_Control();  //6ms����һ���ٶȿ���
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