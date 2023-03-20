/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������KV58F24���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2017��12��19��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4
��Target  ��MKV58F1M0VLQ24
��Crystal �� 50.000Mhz
��busclock��120.000MHz
��pllclock��240.000MHz

ADC0����OK
HSADC�޷��ɼ�����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

//-------------------------------------------------------------------------*
//������: ADC_init                                                         *
//��  ��: ��ʼ��ADC                                                        * 
//��  ��: adc_n:ģ����ADC0��HSADC1                                         *
//��  ��: ��                                                               *
//��  ��: ADC_init��ADC0����ʼ��ADC0ģ��                                   *
//-------------------------------------------------------------------------*
void ADC0_Init(void)
{          
  SIM_SCGC6 |= (SIM_SCGC6_ADC0_MASK );        //����ADC0ʱ��
  SIM_SOPT7 &= ~(SIM_SOPT7_HSADC0AALTTRGEN_MASK  | SIM_SOPT7_HSADC0AALTTRGEN_MASK);
  SIM_SOPT7 |= SIM_SOPT7_HSADC0ATRGSEL(0);    
 }

//-------------------------------------------------------------------------*
//������: adc_start                                                        *
//��  ��: ����ADCת��                                                      * 
//��  ��: adc_n:ģ����ADC0��HSADC1                                         *
//        adc_ch:ͨ�����                                                  *
//        bit:����ѡ��ADC_8bit��ADC_12bit��ADC_10bit��ADC_16bit            * 
//��  ��: ��                                                               *
//��  ��: һ����adc_once�������ã�������ʹ��                               *
//-------------------------------------------------------------------------*
void ADC0_Start(ADC0_Ch_e adc_ch,ADC0_nbit bit)
{    
	int ch=0;
	
	ADC0_CFG1 = (0  | ADC_CFG1_ADIV(2)           //ʱ�ӷ�Ƶѡ��,��Ƶϵ��Ϊ 2^n,2bit
				 | ADC_CFG1_ADLSMP_MASK       //����ʱ�����ã�0Ϊ�̲���ʱ�䣬1 Ϊ������ʱ��
					 | ADC_CFG1_MODE(bit)         //��ȷ��ѡ��
						 | ADC_CFG1_ADICLK(0)         //0Ϊ����ʱ��,1Ϊ����ʱ��/2,2Ϊ����ʱ�ӣ�ALTCLK����3Ϊ �첽ʱ�ӣ�ADACK����
							 );
	
	ADC0_CFG2  = (0  | ADC_CFG2_ADHSC_MASK        //��������,0Ϊ����ת�����У�1Ϊ����ת������
				  | ADC_CFG2_ADLSTS(0)         //������ʱ��ѡ��ADCKΪ4+n������ѭ��������ѭ����0Ϊ20��1Ϊ12��2Ϊ6��3Ϊ2
					  );
	
	
	ch=adc_ch;//ch=0x0e
	ADC0_CFG2 |= ADC_CFG2_MUXSEL_MASK;          // 0ѡ��a  0 ADxxa channels are selected.
	
	//д�� SC1A ����ת��
	ADC0_SC1(0) = (0 | ADC_SC1_AIEN_MASK          // ת������ж�,0Ϊ��ֹ��1Ϊʹ��
				   | ADC_SC1_ADCH(ch)          //ADC0 ͨ��13
                  );
}

//-------------------------------------------------------------------------*
//������: adc_once                                                        
//��  ��: ����ADC����ת��                                                   
//��  ��: adc_n:ģ����ADC0��HSADC1                                           
//        adc_ch:ͨ�����                                                  
//        bit:����ѡ��ADC_8bit��ADC_12bit��ADC_10bit��ADC_16bit             
//��  ��: result                                                              
//��  ��: adc_once(ADC0,HSADC1_SE8,ADC_12bit) ͨ�����Ϊ HSADC1_SE8�����ţ�����
//          һ��ADCת����HSADC1_SE8��Ӧ������鿴ADC.H�ļ�                    
//-------------------------------------------------------------------------*
u16 ADC0_Once(ADC0_Ch_e adc_ch,ADC0_nbit bit) //�ɼ�ĳ·ģ������ADֵ
{   
  int result = 0;
  
  ADC0_Start(adc_ch,bit);      //����ADCת��
  while ((ADC0_SC1(0) & ADC_SC1_COCO_MASK )!= ADC_SC1_COCO_MASK);   //ֻ֧�� ABͨ��
  result = ADC0_R(0);
  ADC0_SC1(0) &= ~ADC_SC1_COCO_MASK;
  return result;  
}

//-------------------------------------------------------------------------*
//������: adc_ave                                                        
//��  ��: ����ADC���ת����ȡƽ��ֵ                                                   
//��  ��: adc_n:ģ����ADC0��HSADC1                                           
//        adc_ch:ͨ�����                                                  
//        bit:����ѡ��ADC_8bit��ADC_12bit��ADC_10bit��ADC_16bit 
//        N  :��ֵ�˲�������1~65535��
//��  ��: tmp                                                              
//��  ��: adc_ave(ADC0,HSADC1_SE8,ADC_12bit,100) ͨ�����Ϊ HSADC1_SE8�����ţ�����
//          100��ADCת���������ƽ��ֵ���ء�                   
//-------------------------------------------------------------------------*
u16 ADC0_Ave(ADC0_Ch_e adc_ch,ADC0_nbit bit,u16 N) //��ֵ�˲�
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
  
  //UART������ʾ
  UART_Init(UART_4,115200);
  UART_Put_Str(UART_4,"LongQiu UART4 ADC \n");
  //UARTIrq_En(UART0);
  LCD_CLS();                   //LCD����
  LCD_P8x16Str(4,0,(uint8_t*)"LQ ADC Test Bat");  
  ADC0_Init();             //��Դ��ѹ����ADC��ʼ��
  while (1)
  {           
    //����ADCת��                                     //��ص�ѹ�ɼ�
    batv=ADC0_Ave(ADC0_SE5b,ADC_12bit,10)*22/91; //330/4095*3,PTA7 
    //if(batv<700)                                    //����7V��OLED��ʾ��ѹ
    {
      sprintf(txt,"BAT:%d.%dV ",batv/100,batv%100);// *3.3/4095*3
      LCD_P8x16Str(20,3,(u8*)txt);
    }  
    UART_Put_Str(UART_4,(u8*)txt);        
    
    //LED��˸
    LED_Ctrl(LED1, RVS);     
    
    //systick�ж���ʱ
    time_delay_ms(500);
  }
}
