/*******************************************************************************
【平    台】龙邱KV58F24智能车VD母板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2017年12月15日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4及以上版本
【Target  】MKV58F1M0VLQ24
【Crystal 】 50.000Mhz
【busclock】137.500MHz
【pllclock】275.000MHz

本程序尚在调试中，用户可以在次基础上修改--20171222
如果你能调试并共享给大家，相信赠人玫瑰手留余香，大家都会感谢你的！！！

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"
//初始化MPU6050
//返回值:0,成功
//其他,错误代码
uint8_t MPU_Init(void)
{ 
  uint8_t res;
  
  I2C_Init(I2C_1);                       //初始化I2C0 
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_PWR_MGMT1_REG,0X80);//复位MPU6050
  time_delay_ms(100);
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_PWR_MGMT1_REG,0X00);	//唤醒MPU6050 
  MPU_Set_Gyro_Fsr(3);                          //陀螺仪传感器,±2000dps
  MPU_Set_Accel_Fsr(0);				//加速度传感器,±2g
  MPU_Set_Rate(50);				//设置采样率50Hz
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_INT_EN_REG,0X00);	        //关闭所有中断
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_USER_CTRL_REG,0X00);	//I2C主模式关闭
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_FIFO_EN_REG,0X00);	        //关闭FIFO
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_INTBP_CFG_REG,0X80);	//INT引脚低电平有效
  
  res=I2C_ReadAddr(I2C_1, MPU_ADDR,MPU_DEVICE_ID_REG);
  if(res==MPU_ADDR)//器件ID正确
  {
    I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_PWR_MGMT1_REG,0X01);	//设置CLKSEL,PLL X轴为参考
    I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_PWR_MGMT2_REG,0X00);	//加速度与陀螺仪都工作
    MPU_Set_Rate(50);				//设置采样率为50Hz
  }else return 1;
  return 0;
}
  
//设置MPU6050陀螺仪传感器满量程范围
//fsr:0,±250dps;1,±500dps;2,±1000dps;3,±2000dps
//返回值:0,设置成功
//    其他,设置失败 
void MPU_Set_Gyro_Fsr(uint8_t fsr)
{
   I2C_WriteAddr(I2C_1,MPU_ADDR,MPU_GYRO_CFG_REG,fsr<<3);//设置陀螺仪满量程范围  
}

//设置MPU6050加速度传感器满量程范围
//fsr:0,±2g;1,±4g;2,±8g;3,±16g
//返回值:0,设置成功
//    其他,设置失败 
void MPU_Set_Accel_Fsr(uint8_t fsr)
{
   I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_ACCEL_CFG_REG,fsr<<3);//设置加速度传感器满量程范围  
}
//设置MPU6050的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败 
void  MPU_Set_LPF(uint16_t lpf)
{
  uint8_t data=0;
  if(lpf>=188)data=1;
  else if(lpf>=98)data=2;
  else if(lpf>=42)data=3;
  else if(lpf>=20)data=4;
  else if(lpf>=10)data=5;
  else data=6; 
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_CFG_REG,data);//设置数字低通滤波器  
}

//设置MPU6050的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败 
void MPU_Set_Rate(uint16_t rate)
{
  uint8_t data;
  if(rate>1000) rate=1000;
  if(rate<4) rate=4;
  data=1000/rate-1;
  I2C_WriteAddr(I2C_1, MPU_ADDR,MPU_SAMPLE_RATE_REG,data);	//设置数字低通滤波器
  MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}

//得到温度值
//返回值:温度值(扩大了100倍)
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
//得到陀螺仪值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
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
//得到加速度值(原始值)
//gx,gy,gz:陀螺仪x,y,z轴的原始读数(带符号)
//返回值:0,成功
//    其他,错误代码
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
  uint16_t aacx,aacy,aacz;	//加速度传感器原始数据
  uint16_t gyrox,gyroy,gyroz;	//陀螺仪原始数据
  uint16_t temp;                          //温度 
  uint16_t a[8];
  uint8_t  txt[30]="X:";
  MPU_Init();                          //初始化MPU6050
  LCD_Init();
  while(1)
  {
    temp=MPU_Get_Temperature();	//得到温度值
    MPU_Get_Accelerometer(&aacx,&aacy,&aacz);	//得到加速度传感器数据
    MPU_Get_Gyroscope(&gyrox,&gyroy,&gyroz);	//得到陀螺仪数据
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

