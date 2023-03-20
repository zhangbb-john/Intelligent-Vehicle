/*******************************************************************************
��ƽ    ̨������KV58F24���ܳ�VDĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2017��12��15��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4�����ϰ汾
��Target  ��MKV58F1M0VLQ24
��Crystal �� 50.000Mhz
��busclock��137.500MHz
��pllclock��275.000MHz

���������ڵ����У��û������ڴλ������޸�--20171222
������ܵ��Բ��������ң���������õ���������㣬��Ҷ����л��ģ�����

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
//��ʼ��MPU6050
//����ֵ:0,�ɹ�
//����,�������
uint8_t MPU_Init(void)
{ 
  uint8_t res;
  
  I2C_Init(I2C_1);                       //��ʼ��I2C0 
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_PWR_MGMT1_REG,0X80);//��λMPU6050
  time_delay_ms(100);
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_PWR_MGMT1_REG,0X00);	//����MPU6050 
  MPU_Set_Gyro_Fsr(3);                          //�����Ǵ�����,��2000dps
  MPU_Set_Accel_Fsr(0);				//���ٶȴ�����,��2g
  MPU_Set_Rate(50);				//���ò�����50Hz
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_INT_EN_REG,0X00);	        //�ر������ж�
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_FIFO_EN_REG,0X00);	        //�ر�FIFO
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
  
  res=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_DEVICE_ID_REG);
  if(res==MPU_ADDR)//����ID��ȷ
  {
    I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
    I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
    MPU_Set_Rate(50);				//���ò�����Ϊ50Hz
  }else return 1;
  return 0;
}
  
//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void MPU_Set_Gyro_Fsr(uint8_t fsr)
{
   I2C_WriteAddr(I2C_1,MPU_ADDR,MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}

//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void MPU_Set_Accel_Fsr(uint8_t fsr)
{
   I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void  MPU_Set_LPF(uint16_t lpf)
{
  uint8_t data=0;
  if(lpf>=188)data=1;
  else if(lpf>=98)data=2;
  else if(lpf>=42)data=3;
  else if(lpf>=20)data=4;
  else if(lpf>=10)data=5;
  else data=6; 
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}

//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
void MPU_Set_Rate(uint16_t rate)
{
  uint8_t data;
  if(rate>1000) rate=1000;
  if(rate<4) rate=4;
  data=1000/rate-1;
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
  MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
uint16_t MPU_Get_Temperature(void)
{
  uint8_t buf[2]; 
  uint16_t raw;
  float temp;
  
  buf[0]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_DEVICE_ID_REG);
  buf[1]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_DEVICE_ID_REG);
  raw=((uint16_t)buf[0]<<8)|buf[1];  
  temp=36.53+((double)raw)/340;  
  return ((uint16_t)(temp*100));
}
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
void MPU_Get_Gyroscope(uint16_t *gx,uint16_t *gy,uint16_t *gz)
{
  uint8_t buf[6];  
  
  buf[0]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_GYRO_XOUTH_REG);
  buf[1]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_GYRO_XOUTL_REG);
  buf[2]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_GYRO_YOUTH_REG);
  buf[3]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_GYRO_YOUTL_REG);
  buf[4]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_GYRO_ZOUTH_REG);
  buf[5]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_GYRO_ZOUTL_REG);
  
    *gx=((uint16_t)buf[0]<<8)|buf[1];  
    *gy=((uint16_t)buf[2]<<8)|buf[3];  
    *gz=((uint16_t)buf[4]<<8)|buf[5];
  
}
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
void MPU_Get_Accelerometer(uint16_t *ax,uint16_t *ay,uint16_t *az)
{
  uint8_t buf[6];  
  
  buf[0]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_ACCEL_XOUTH_REG);
  buf[1]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_ACCEL_XOUTL_REG);
  buf[2]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_ACCEL_YOUTH_REG);
  buf[3]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_ACCEL_YOUTL_REG);
  buf[4]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_ACCEL_ZOUTH_REG);
  buf[5]=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_ACCEL_ZOUTL_REG);
  
    *ax=((uint16_t)buf[0]<<8)|buf[1];  
    *ay=((uint16_t)buf[2]<<8)|buf[3];  
    *az=((uint16_t)buf[4]<<8)|buf[5]; 	
  
}


void Test_MPU6050(void)
{
  uint16_t aacx,aacy,aacz;	//���ٶȴ�����ԭʼ����
  uint16_t gyrox,gyroy,gyroz;	//������ԭʼ����
  uint16_t temp;                          //�¶� 
  uint16_t a[8];
  uint8_t  txt[30]="X:";
  MPU_Init();                          //��ʼ��MPU6050
  LCD_Init();
  while(1)
  {
    temp=MPU_Get_Temperature();	//�õ��¶�ֵ
    MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//�õ����ٶȴ���������
    MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//�õ�����������
    sprintf((char*)txt,"ax:%06d",aacx);
    LCD_P6x8Str(0,0,txt);
    sprintf((char*)txt,"ay:%06d",aacy);
    LCD_P6x8Str(0,1,txt);
    sprintf((char*)txt,"az:%06d",aacz);
    LCD_P6x8Str(0,2,txt);
    sprintf((char*)txt,"gx:%06d",gyrox);
    LCD_P6x8Str(0,3,txt);
    sprintf((char*)txt,"gy:%06d",gyroy);
    LCD_P6x8Str(0,4,txt);
    sprintf((char*)txt,"gz:%06d",gyroz);
    LCD_P6x8Str(0,5,txt);
    a[0]=aacx;
    a[1]=aacy;
    a[2]=aacz;
    a[3]=gyrox;
    a[4]=gyroy;
    a[5]=gyroz;    
    UART_Put_Str(UART_4,(u8*)a);  
    time_delay_ms(100);
  }
}

