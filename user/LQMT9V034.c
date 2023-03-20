/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������KV58F24���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2018��3��28��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4������
��Target  ��MKV58F1M0VLQ24
��Crystal �� 50.000Mhz
��busclock��137.500MHz
��pllclock��275.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

uint8 Image_Data[IMAGEH][IMAGEW];      //ͼ��ԭʼ���ݴ��
uint8 Image_Use[CAMERA_H][CAMERA_W];
uint8 imgbuff_process[CAMERA_SIZE];               //���崦��ͼ���õ�����
uint8 img_edg[CAMERA_SIZE*2];                           //
uint8 LMR[3][CAMERA_H];
uint8 new_img=0;
uint8 GaveValue;
uint8_t Threshold;                  //OSTU��򷨼����ͼ����ֵ
uint8 thresh;
volatile u8  Line_Cont=0;          //�м���

__ramfunc void DMATransDataInit(DMA_CHn CHn,void *SADDR, void *DADDR,PTXn_e ptxn,DMA_BYTEn byten,u32 count,DMA_Count_cfg cfg) ;
__ramfunc void DMATransDataStart(uint8_t CHn,uint32_t address,uint32_t Val) ;
void SCCB_RegWrite(uint8 Device,uint8 Address,uint16 Data);
uint8_t SCCB_RegRead(uint8_t Device,uint8_t Address,uint16_t *Data);
void MT9V034_SetFrameResolution(uint16_t height,uint16_t width);
void MT9V034_SetAutoExposure(bool enable);
void MT9V034_Reset(void);
__ramfunc void Get_Use_Image(void);

void PORTD_IRQHandler(void) 
{  
	//���ж�PTD13 
	if((PORTD_ISFR & 0x2000)) //���ж� PTD13 (1<<13) 
	{ 
		PORTD_ISFR |= 0x2000;   //����жϱ�ʶ 
		if(Line_Cont > IMAGEH)  //�ɼ�����
		{ 
			Line_Cont=0; 
			return ;
		}
		DMATransDataStart(DMA_CH4,(uint32_t)(&Image_Data[Line_Cont][0]),IMAGEW); //DMA��ʼ��������PTD12�ܽŴ���
		++Line_Cont;            //�м���
		return ;
	}
//	char txt[5];
	//���ж�PTD14
	if((PORTD_ISFR & 0x4000))//���ж� PTD14 (1<<14)
	{
//		sprintf(txt,"%03d",Line_Cont);
//		LCD_P6x8Str(60,1,(u8*)txt);
		PORTD_ISFR |= 0x4000;  //����жϱ�ʶ
		Line_Cont = 0;         //�м�������
		new_img = 1;     //��������ʶ
		return ;
	}
}
// MT9V034 Port Init
void MT9V034_Init(void)
{     
	u16 i=0,j=0;
	uint16_t data = 0; 
	
	//GPIO�ڳ�ʼ��
	EXTI_Init(GPIOD,13,rising_down);   //���ж�
        PORT_PCR_REG(PORTD,13) |= PULLDOWN; 
	EXTI_Init(GPIOD,14,falling_up);    //���ж�
        PORT_PCR_REG(PORTD,14) |= PULLUP; 
	GPIO_Init(GPIOD,0,GPI,0);          //��λ���������      
	GPIO_Init(GPIOD,1,GPI,0);
	GPIO_Init(GPIOD,2,GPI,0);
	GPIO_Init(GPIOD,3,GPI,0);
	GPIO_Init(GPIOD,4,GPI,0);
	GPIO_Init(GPIOD,5,GPI,0);
	GPIO_Init(GPIOD,6,GPI,0);
	GPIO_Init(GPIOD,7,GPI,0);
	//GPIO_Init(GPIOD,12,GPI,0);     //����  
	
	//����ͷ�Ĵ�������
	SCCB_Init();                     //������ַ�ڶ����ߣ�ΪMT9V034_I2C_ADDR 
	
	if(SCCB_RegRead(MT9V034_I2C_ADDR>>1,MT9V034_CHIP_VERSION,&data) == 0)//��ȡ����ͷ�汾�Ĵ��� 
	{     
		if(data != MT9V034_CHIP_ID)                                  //оƬID����ȷ��˵��û����ȷ��ȡ�����ݣ��ȴ�      
		{ 
			LCD_P6x8Str(2,1,(u8*)"V034 NG");                      //����ͷʶ��ʧ�ܣ�ֹͣ����
			while(1); 
		} 
		else                                                   //оƬID��ȷ
		{
			LCD_P6x8Str(2,1,(u8*)"V034 OK");
		}
	} 
	else 
	{ 
		while(1); //����ͷʶ��ʧ�ܣ�ֹͣ����
	}  
	/*
	line: 31.5us
	pix:  148.1ns
	
	*/
	//KV58��DMA���Ƶ��ֻ��27.5MHZ����Ȼ
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_RESET, 0x03);          //0x0c  ��λ
	
	MT9V034_SetFrameResolution(IMAGEH, IMAGEW);//��������ͷͼ��4*4��Ƶ���PCLK, 27/4 = 6.75M ,BIT4,5��������:�������Ҿ����� 
	
	MT9V034_SetAutoExposure(true);
	
	SCCB_RegWrite(MT9V034_I2C_ADDR, 0xAC, 0x0001);
	SCCB_RegWrite(MT9V034_I2C_ADDR, 0xAD, 0x01E0);  
	SCCB_RegWrite(MT9V034_I2C_ADDR, 0x2C, 0x0004);
	
	//SCCB_RegWrite(MT9V034_I2C_ADDR, 0x7F, 0x3000);           // test pattern
	
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_ANALOG_CTRL, MT9V034_ANTI_ECLIPSE_ENABLE);
	SCCB_RegWrite(MT9V034_I2C_ADDR, 0x0F, 0x0000);  
//	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_HDR_ENABLE_REG, 0x0101); // 0x0F bit8:1HDR,0linear; bit1:1��ɫ,0�Ҷ�;bit0:1HDR,0linear
	//MT9V034_WriteReg16(MT9V034_HDR_ENABLE_REG, 0x0103);     // 0x0F bit8:1HDR,0linear; bit1:1��ɫ,0�Ҷ�;bit0:1HDR,0linear
	//0x07 Chip Control bit2-0:0����ɨ��,1��Ч��2����3������bit5:1�����Ӿ�ʹ��,bit7:1����ʹ�ܣ�bit8:1ͬ��ģʽ;bit9:1����������bit15:0A/1B
	SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_CHIP_CONTROL, 0x0188);          //Context A  0x0188
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_ROW_NOISE_CORR_CTRL_REG, 0);   //0x70  0x0000 
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_AEC_AGC_ENABLE_REG, 0x0303);   //0xAF  AEC/AGC A~bit0:1AE;bit1:1AG/B~bit2:1AE;bit3:1AG
	
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_MIN_EXPOSURE_REG, 0x0001);     //0xAC  ��С�ֿ��ſ��   0x0001
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_MAX_EXPOSURE_REG, 0x00F0);     //0xAD  ���׿��ſ��   0x01E0-480
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_MAX_GAIN_REG, 50);             //0xAB  ���ģ������     64
	
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_AGC_AEC_PIXEL_COUNT_REG, 188*120);//0xB0  ����AEC/AGCֱ��ͼ������Ŀ,���44000   4096=320*240  
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_ADC_RES_CTRL_REG, 0x0303);     //0x1C  here is the way to regulate darkness :)    
	
	SCCB_RegWrite(MT9V034_I2C_ADDR,0x13,0x2D2E);//We also recommended using R0x13 = 0x2D2E with this setting for better column FPN.  
	SCCB_RegWrite(MT9V034_I2C_ADDR,0x20,0x03C7);//0x01C7�ԱȶȲ���ף�0x03C7�Աȶ���� Recommended by design to improve performance in HDR mode and when frame rate is low.
	SCCB_RegWrite(MT9V034_I2C_ADDR,0x24,0x0010);//Corrects pixel negative dark offset when global reset in R0x20[9] is enabled.
	SCCB_RegWrite(MT9V034_I2C_ADDR,0x2B,0x0003);//Improves column FPN.
	SCCB_RegWrite(MT9V034_I2C_ADDR,0x2F,0x0003);//Improves FPN at near-saturation.  
	//  SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_DARK_AVG_THRESH,0xFF00);
	//SCCB_RegWrite(MT9V034_I2C_ADDR, 0x08, 0x03D4);
	//SCCB_RegWrite(MT9V034_I2C_ADDR, 0x09, 0x03E7);
	//100DB //�����ع�ʱ��
	SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_SHUTTER_WIDTH1,0x01BB);        //0x08 Coarse Shutter IMAGEW 1
	SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_SHUTTER_WIDTH2,0x01D9);        //0x09 Coarse Shutter IMAGEW 2
	SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_SHUTTER_WIDTH_CONTROL,0x0164); //0x0A Coarse Shutter IMAGEW Control  0x0164  �Ǹ�1��auto knee point����(����Ҫ)
	SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_V2_CTRL_REG_A, 0x001A);        //0x32   0x001A  
	SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_TOTAL_SHUTTER_WIDTH,0x00E8);   //0x0B Coarse Shutter IMAGEW Total
	SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_HDR_ENABLE_REG,0x0101);        //0x0F High Dynamic Range enable,bit is set (R0x0F[1]=1), the sensor uses black level correction values from one green plane, which are applied to all colors.
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_AGC_AEC_DESIRED_BIN_REG, 60); //0xA5  ͼ������  50  1-64
	SCCB_RegWrite(MT9V034_I2C_ADDR,MT9V034_ANALOG_GAIN,0x8010);           //0x35
	
	//80dB HDR
	//SCCB_RegWrite(MT9V034_I2C_ADDR, 0x08, 0x03CA);
	//SCCB_RegWrite(MT9V034_I2C_ADDR, 0x09, 0x03DE);
	//SCCB_RegWrite(MT9V034_I2C_ADDR, 0x0A, 0x0064);
	//SCCB_RegWrite(MT9V034_I2C_ADDR, 0x0B, 0x03E8);
	//SCCB_RegWrite(MT9V034_I2C_ADDR, 0x0F, 0x0103);
	//SCCB_RegWrite(MT9V034_I2C_ADDR, 0x35, 0x8010);   
	
	DMATransDataInit(DMA_CH4,(void*)&PTD_BYTE0_IN,(void*)Image_Data,PTD12,DMA_BYTE1,IMAGEW,DMA_rising_down);//��ʼ��DMA�ɼ�  
	PORT_PCR_REG(PORTD,12) |= PULLDOWN; 
}

/***************************************************************  
* 
* �������ƣ�void DMATransDataInit(DMA_CHn CHn,void *SADDR, void *DADDR,PTXn_e ptxn,DMA_BYTEn byten,u32 count,DMA_PORTx2BUFF_cfg cfg) 
* ����˵������ʼ��DMA 
* ����˵����ͨ����ţ�Դ��ַ��Ŀ�ĵ�ַ�������ܽţ��ֽ�����ѭ���������������� 
* �������أ��� 
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
***************************************************************/ 
__ramfunc void DMATransDataInit(DMA_CHn CHn,void *SADDR, void * DADDR,PTXn_e ptxn,DMA_BYTEn byten,u32 count,DMA_Count_cfg cfg) 
{ 
	u8 BYTEs = (byten == DMA_BYTE1 ? 1 : (byten == DMA_BYTE2 ? 2 : (byten == DMA_BYTE4 ? 4 : 16 ) ) ); //���㴫���ֽ���
	//����ʱ�� 
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;                        //��DMAģ��ʱ��
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;                     //��DMA��·������ʱ��
	// ���� DMA ͨ�� �� ������ƿ� TCD ( Transfer Control Descriptor ) 
	DMA_SADDR(CHn) =    (u32)SADDR;                         // ����  Դ��ַ
	DMA_DADDR(CHn) =    (u32)DADDR;                         // ����Ŀ�ĵ�ַ
	DMA_SOFF(CHn)  =    0;                                  // ����Դ��ַ����
	DMA_DOFF(CHn)  =    BYTEs;                                  // ÿ�δ����Ŀ�ļ�BYUEs
	DMA_ATTR(CHn)  =    (0
						 | DMA_ATTR_SMOD(0x0)                // Դ��ַģ����ֹ  Source address modulo feature is disabled
							 | DMA_ATTR_SSIZE(byten)             // Դ����λ�� ��DMA_BYTEn  ��    SSIZE = 0 -> 8-bit ��SSIZE = 1 -> 16-bit ��SSIZE = 2 -> 32-bit ��SSIZE = 4 -> 16-byte
								 | DMA_ATTR_DMOD(0x0)                // Ŀ���ַģ����ֹ
									 | DMA_ATTR_DSIZE(byten)             // Ŀ������λ�� ��DMA_BYTEn  ��  ���òο�  SSIZE
										 );
	DMA_CITER_ELINKNO(CHn)  = DMA_CITER_ELINKNO_CITER(count); //��ǰ��ѭ������
	DMA_BITER_ELINKNO(CHn)  = DMA_BITER_ELINKYES_BITER(count);//��ʼ��ѭ������
	
	DMA_CR &= ~DMA_CR_EMLM_MASK;                            // CR[EMLM] = 0  disable Minor Loop Mapping
	
	DMA_NBYTES_MLNO(CHn) =   DMA_NBYTES_MLNO_NBYTES(BYTEs); // ͨ��ÿ�δ����ֽ�������������ΪBYTEs���ֽڡ�ע��ֵΪ0��ʾ����4GB 
	
	// ���� DMA ���������Ĳ��� 
	DMA_SLAST(CHn)      =   0;                              //����Դ��ַ�ĸ���ֵ,��ѭ��������ָ�Դ��ַ
	DMA_DLAST_SGA(CHn)  =   0;                              //����Ŀ�ĵ�ַ�ĸ���ֵ,��ѭ��������ָ�Ŀ�ĵ�ַ���߱��ֵ�ַ
	DMA_CSR(CHn)        =   (0
							 | DMA_CSR_BWC(3)               //�������,ÿ��һ�Σ�eDMA ����ֹͣ 8 �����ڣ�0��ֹͣ��1������2ֹͣ4���ڣ�3ֹͣ8���ڣ�
							 | DMA_CSR_DREQ_MASK            //��ѭ��������ֹͣӲ������
								 | DMA_CSR_INTMAJOR_MASK        //��ѭ������������ж�
									 );
	// ���� DMA ����Դ 
	DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR, CHn) = (0
											  | DMAMUX_CHCFG_ENBL_MASK                        // Enable routing of DMA request 
												  | DMAMUX_CHCFG_SOURCE((ptxn >> 5) + DMA_Port_A) // ͨ����������Դ:     
													  );
	SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK << (ptxn>>5));                                //����PORTx�˿�
	GPIO_PDDR_REG(GPIOX[(ptxn>>5)]) &= ~(1 << (ptxn & 0x1f));                        //���ö˿ڷ���Ϊ����
	PORT_PCR_REG(PORTX[(ptxn>>5)], (ptxn & 0x1F)) = ( 0
													 | PORT_PCR_MUX(1)               // ����GPIO
														 | PORT_PCR_IRQC(cfg & 0x03 )    // ȷ������ģʽ
															 | ((cfg & 0xc0 ) >> 6)          // �����������������裬����û��
																 );
	GPIO_PDDR_REG(GPIOX[(ptxn>>5)]) &= ~(1 << (ptxn && 0x1F));  
	
	//�����ж� 
	DMA_EN(CHn);                                      //ʹ��ͨ��CHn Ӳ������
//	DMA_IRQ_EN(CHn);                                //����DMAͨ������
} 

/*************************************************************** 

* 
* �������ƣ�void DMATransDataStart(uint8_t CHn,uint32_t address,uint32_t Val) 
* ����˵��������DMA�����Ŀ�ĵ�ַ��ѭ������ 
* ����˵���� 
* �������أ���
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
***************************************************************/ 
__ramfunc void DMATransDataStart(uint8_t CHn,uint32_t address,uint32_t Val) 
{ 
	DMA_DADDR(CHn) = address;                              //Ŀ�ĵ�ַ 
	DMA_CITER_ELINKNO(CHn) = DMA_CITER_ELINKNO_CITER(Val); //��ǰ��ѭ������ 
	DMA_BITER_ELINKNO(CHn) = DMA_BITER_ELINKYES_BITER(Val);//��ʼ��ѭ������ 
	//�����ж� 
	DMA_EN(CHn);                                           //ʹ��ͨ��CHn Ӳ������
//	DMA_IRQ_EN(CHn);                                     //����DMAͨ������
} 

/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Init(void)
*  ����˵��������SCCB��������ΪGPIO���ܣ���ʱ���������ݷ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Init(void)
{
	GPIO_Init(GPIOE, 0,GPO,0);//����ΪGPIO����
	GPIO_Init(GPIOE, 1,GPO,0);//����ΪGPIO���� 
}

/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Wait(void)
*  ����˵����SCCB�ȴ���ʾ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Wait(void)
{
	int i=0;
	for(i=0;i < 1000;i++)
	{ 
		asm ("nop");
	}  
}
/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Star(void)
*  ����˵������������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Star(void)
{
	SCL_Out;
	SDA_Out;
	SCCB_Wait();
	SDA_High;
	SCL_High; 
	SCCB_Wait();
	SDA_Low;
	SCCB_Wait();
	SCL_Low; 
	SCCB_Wait();
}
/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_Stop(void)
*  ����˵����ֹͣ����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_Stop(void)
{
	SCL_Out;
	SDA_Out;
	SCCB_Wait();
	SDA_Low;
	SCCB_Wait();
	SCL_High; 
	SCCB_Wait();
	SDA_High;
	SCCB_Wait();  
}
/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�uint8 SCCB_SendByte(uint8 Data)
*  ����˵����SCCB�����ֽں���
*  ����˵����Ҫ���͵��ֽ�
*  �������أ�Ӧ���ź�
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
uint8 SCCB_SendByte(uint8 Data)
{
	uint8 i;
	uint8 Ack;
	SDA_Out;
	for( i=0; i<8; i++)
	{
		if(Data & 0x80) SDA_High;
		else            SDA_Low;    
		Data <<= 1;
		SCCB_Wait();
		SCL_High;      
		SCCB_Wait();
		SCL_Low;
		SCCB_Wait();
	}
	SDA_High;
	SDA_In;
	SCCB_Wait();
	
	SCL_High;
	SCCB_Wait();
	Ack = SDA_Data;
	SCL_Low;
	SCCB_Wait();
	return Ack;
}
/*************************************************************** 

* 
* �������ƣ�uint8 SCCB_ReadByte(void) 
* ����˵����SCCB��ȡ�ֽں��� 
* ����˵���� 
* �������أ���ȡ�ֽ� 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
uint8 SCCB_ReadByte(void) 
{ 
	uint8 i; 
	uint8_t byte; 
	SCL_Out; 
	SDA_In; //ʹ������
	for( i=0; i<8; i++) 
	{ 
		SCL_Low;
		SCCB_Wait(); 
		SCL_High;
		SCCB_Wait();
		byte = (byte<<1)|(SDA_Data & 1);
	}
	SCL_Low; 
	SDA_Out;
	SCCB_Wait(); 
	return byte; 
} 
/*************************************************************** 

* 
* �������ƣ�static void SCCB_Ack(void) 
* ����˵����IIC�лظ��ź� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
static void SCCB_Ack(void) 
{ 
	SCL_Out; 
	SDA_Out;
	SCL_Low;
	SDA_Low;
	SCCB_Wait();
	SCL_High;
	SCCB_Wait();
	SCL_Low;
	SCCB_Wait();
} 
/*************************************************************** 

* 
* �������ƣ�static void SCCB_NAck(void) 
* ����˵����IIC�޻ظ��ź� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
static void SCCB_NAck(void) 
{ 
	SCL_Out; 
	SDA_Out;
	SCL_Low;
	SCCB_Wait();
	SDA_High;
	SCCB_Wait();
	SCL_High;
	SCCB_Wait();
	SCL_Low;
	SCCB_Wait();
} 

/*************************************************************************
* �����������ܿƼ� KV58���ܳ�ĸ��           
*
*  �������ƣ�void SCCB_RegWrite(uint8 Device,uint8 Address,uint16 Data)
*  ����˵�������豸д����
*  ����˵����Ҫ���͵��ֽ�
*  �������أ�Ӧ���ź�
*  �޸�ʱ�䣺2017��12��5��
*  ��    ע��
*************************************************************************/
void SCCB_RegWrite(uint8 Device,uint8 Address,uint16 Data)
{
	uint8 i;
	uint8 Ack;
	
	for( i=0; i<3; i++)
	{
		SCCB_Star();
		Ack = SCCB_SendByte(Device);
		if( Ack == 1 )
		{
			continue;
		}
		
		Ack = SCCB_SendByte(Address);
		if( Ack == 1 )
		{
			continue;
		}
		
		Ack = SCCB_SendByte((uint8)(Data>>8));
		Ack = SCCB_SendByte((uint8)Data);
		if( Ack == 1 )
		{
			continue;
		}
		
		SCCB_Stop();
		if( Ack == 0 ) break;
	}
}
/*************************************************************** 

* 
* �������ƣ�uint8_t SCB_RegRead(uint8_t Device,uint8_t Address,uint16_t *Data) 
* ����˵������ȡ���� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
uint8_t SCCB_RegRead(uint8_t Device,uint8_t Address,uint16_t *Data) 
{ 
	uint8 i; 
	uint8 Ack = 0;
	Device = Device<<1;
	SCCB_Star();
	Ack += SCCB_SendByte(Device);
	
	Ack += SCCB_SendByte(Address);
	
	SCCB_Star();
	Ack += SCCB_SendByte(Device + 1);
	
	*Data = SCCB_ReadByte();
	SCCB_Ack();
	*Data = *Data<<8;
	
	*Data += SCCB_ReadByte();
	SCCB_NAck();
	
	SCCB_Stop();
	
	return  Ack;
} 
/***************************************************************  
* 
* �������ƣ�int SCCB_Probe(uint8_t chipAddr) 
* ����˵������ѯ�õ�ַ���豸�Ƿ���� 
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2017��12��5�� 
* �� ע�� 
***************************************************************/ 
int SCCB_Probe(uint8_t chipAddr) 
{ 
	uint8_t err;
	err = 0;
	chipAddr <<= 1;
	
	SCCB_Star();
	err = SCCB_SendByte(chipAddr);
	SCCB_Stop();
	
	return err;
}
void MT9V034_SetFrameResolution(uint16_t height,uint16_t width)
{
	uint16_t data = 0;
	
	if((width*4)<=MAX_IMAGE_WIDTH && (height*4)<=MAX_IMAGE_HEIGHT)
	{
		width *= 4;
		height *= 4;
		data |= MT9V034_READ_MODE_ROW_BIN_4;
		data |= MT9V034_READ_MODE_COL_BIN_4;
	}
	else if((width*2)<=MAX_IMAGE_WIDTH && (height*2)<=MAX_IMAGE_HEIGHT)
	{
		width *= 2;
		height *= 2;
		data |= MT9V034_READ_MODE_ROW_BIN_2;
		data |= MT9V034_READ_MODE_COL_BIN_2;
	}
	//  width *= 4;
	//  height *= 2;
	//  data |= MT9V034_READ_MODE_ROW_BIN_4;
	//  data |= MT9V034_READ_MODE_COL_BIN_2;
	
	//SCCB_RegWrite(MT9V034_I2C_ADDR,0x01,MT9V034_COLUMN_START_DEF);     // Column Start
	//SCCB_RegWrite(MT9V034_I2C_ADDR,0x02,MT9V034_ROW_START_DEF);        // Row Start  
	//SCCB_RegWrite(MT9V034_I2C_ADDR,0x03,MT9V034_WINDOW_HEIGHT_DEF);    // height 
	//SCCB_RegWrite(MT9V034_I2C_ADDR,0x04,MT9V034_WINDOW_WIDTH_DEF);     // width  
	//SCCB_RegWrite(MT9V034_I2C_ADDR,0x05,MT9V034_HORIZONTAL_BLANKING_MIN);   // Horizontal Blanking  809-640
	//SCCB_RegWrite(MT9V034_I2C_ADDR,0x06,MT9V034_VERTICAL_BLANKING_MIN);     // Vertical Blanking    499-480 
	
	//����ͼ�������СΪ120*188������ʧ��Ұ��ͬʱ�������ܳ���Ҫ
	//SCCB_RegWrite(MT9V034_I2C_ADDR,0x0D,0x030A);   //��������ͷͼ��4*4��Ƶ���PCLK, 27/4 = 6.75M ,BIT4,5�������� 
	//SCCB_RegWrite(MT9V034_I2C_ADDR,0x0D,0x033A);   //��������ͷͼ��4*4��Ƶ���PCLK, 27/4 = 6.75M ,BIT4,5��������:�������Ҿ����� 
	
	data |= (MT9V034_READ_MODE_ROW_FLIP|MT9V034_READ_MODE_COLUMN_FLIP);       //LQ-MT9V034 needs vertical mirror to capture correct image
	
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_READ_MODE, data);
	
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_WINDOW_WIDTH,  width);
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_WINDOW_HEIGHT, height);
	
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_COLUMN_START, (MAX_IMAGE_WIDTH-width)/2+MT9V034_COLUMN_START_MIN);
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_ROW_START, (MAX_IMAGE_HEIGHT-height)/2+MT9V034_ROW_START_MIN);
}

void MT9V034_SetAutoExposure(bool enable)
{
	uint16_t reg =0;
	SCCB_RegRead(MT9V034_I2C_ADDR, MT9V034_AEC_AGC_ENABLE,&reg);
	if(true == enable)
	{
		SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_AEC_AGC_ENABLE, reg|MT9V034_AEC_ENABLE|MT9V034_AGC_ENABLE);
	}
	else
	{
		SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_AEC_AGC_ENABLE, reg&~(MT9V034_AEC_ENABLE|MT9V034_AGC_ENABLE));
	}
}
void MT9V034_Reset(void)
{
	//Reset MT9V034, but register config will not change.
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_RESET, 0x0001);
	time_delay_ms(10);
	
	//Unlock MT9V034, allowing user to initiate register settings and readout
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_CHIP_CONTROL, 0x0188);
	
	//Reset Again.
	SCCB_RegWrite(MT9V034_I2C_ADDR, MT9V034_RESET, 0x0001);
	time_delay_ms(10);
}

__ramfunc void Get_Use_Image(void)
{
	int i = 0,j = 0,row = 0,line = 0;
	
	for(i = 0; i  < IMAGEH; i+=2)  //120�У�ÿ2�вɼ�һ�У�
	{
		for(j = 15;j < 174; j+=2)  //188��ȡ94��
		{        
			Image_Use[row][line] = Image_Data[i][j];         
			line++;
		}      
		line = 0;
		row++;      
	}  
}
uint8_t GetOSTU(uint8_t tmImage[IMAGEH][IMAGEW])
{
	int16_t i, j;
	uint32_t Amount = 0;
	uint32_t PixelBack = 0;
	uint32_t PixelIntegralBack = 0;
	uint32_t PixelIntegral = 0;
	int32_t PixelIntegralFore = 0;
	int32_t PixelFore = 0;
	double OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��; 
	int16_t MinValue, MaxValue;
	uint8_t Threshold = 0;
	uint8_t HistoGram[256];              //  

	for (j = 0; j < 256; j++)  HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ 

	for (j = 0; j < IMAGEH; j++)
	{
		for (i = 0; i < IMAGEW; i++)
		{
			HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
		}
	}

	for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++);        //��ȡ��С�Ҷȵ�ֵ
	for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--); //��ȡ���Ҷȵ�ֵ

	if (MaxValue == MinValue)     return MaxValue;         // ͼ����ֻ��һ����ɫ    
	if (MinValue + 1 == MaxValue)  return MinValue;        // ͼ����ֻ�ж�����ɫ

	for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  ��������

	PixelIntegral = 0;
	for (j = MinValue; j <= MaxValue; j++)
	{
		PixelIntegral += HistoGram[j] * j;//�Ҷ�ֵ����
	}
	SigmaB = -1;
	for (j = MinValue; j < MaxValue; j++)
	{
		PixelBack = PixelBack + HistoGram[j];    //ǰ�����ص���
		PixelFore = Amount - PixelBack;         //�������ص���
		OmegaBack = (double)PixelBack / Amount;//ǰ�����ذٷֱ�
		OmegaFore = (double)PixelFore / Amount;//�������ذٷֱ�
		PixelIntegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
		PixelIntegralFore = PixelIntegral - PixelIntegralBack;//�����Ҷ�ֵ
		MicroBack = (double)PixelIntegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
		MicroFore = (double)PixelIntegralFore / PixelFore;   //�����ҶȰٷֱ�
		Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//������䷽��
		if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
		{
			SigmaB = Sigma;
			Threshold = j;
		}
	}
	return Threshold;                        //���������ֵ;
}
//���վ�ֵ�ı������ж�ֵ��
void Get_01_Value(void)
{
	int i = 0,j = 0;
	u32 tv=0;
//	char txt[16];
	
	//�ۼ�
	for(i = 0; i <CAMERA_H; i++)
	{    
		for(j = 0; j <CAMERA_W; j++)
		{                            
			tv+=Image_Use[i][j];   //�ۼ�  
		} 
	}
	GaveValue=tv/(CAMERA_H*CAMERA_W);     //��ƽ��ֵ,����Խ��ԽС��ȫ��Լ35��������ĻԼ160��һ������´�Լ100 
//	sprintf(txt,"%03d:%03d",Threshold,GaveValue);//ǰ��Ϊ�����õ���ֵ������Ϊƽ��ֵ  
//	LCD_P6x8Str(80,1,(u8*)txt);
	//���վ�ֵ�ı������ж�ֵ��
        thresh = GetOSTU(Image_Data); //OSTU��� ��ȡȫ����ֵ
	GaveValue=GaveValue*thresh/100;        //�˴���ֵ���ã����ݻ����Ĺ������趨
	
	uint8 tempbyte,tempbit;
	int index = 0, bytecount = 0;
	for(i = 0; i < CAMERA_H; i++)
	{
		for(j = 0; j < CAMERA_W; j++)
		{
			if(Image_Use[i][j] >GaveValue)//ƽ��ֵ��ֵ���׵�
				tempbit = 1;        
			else                                        
				tempbit = 0;
			//[i * 10 + j / 8] += tempbit << (j % 8))
			Image_Use[i][j] = tempbit;
			tempbyte = (tempbyte << 1) + tempbit;
			bytecount++;
			if(bytecount == 8)
			{
				bytecount = 0;
				imgbuff_process[index] = tempbyte;
				index++;
			}
		}    
	}
}