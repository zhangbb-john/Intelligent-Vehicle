/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱KV58F24智能车VD母板
【修    改】在野火K60库基础上修改
【E-mail  】
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
#ifndef _FTM_H_
#define _FTM_H_

//定义当前所用舵机的参数
#define     Servo_Left        810 //左转极限，每个舵机数值不同
#define     Servo_Middle      1670 //中心位置，每个舵机数值不同
#define     Servo_Right       2410 //右转极限，每个舵机数值不同

/**********************************  FTM(引脚复用)已确认20171218*************************/

//      模块通道    端口          可选范围              建议
#define FTM0_CH0    PTC1        //PTC1、PTA3  PTE24 PTD0     PTA3不要用（与JLINK冲突）
#define FTM0_CH1    PTC2        //PTC2、PTA4  PTE25 PTD1
#define FTM0_CH2    PTC3        //PTC3、PTA5  PTE29 PTD2 PTC5
#define FTM0_CH3    PTC4        //PTC4、PTA6  PTE30 PTD3
#define FTM0_CH4    PTD4        //PTD4、PTA7  PTE26 PTD4
#define FTM0_CH5    PTD5        //PTD5、PTA0        PTD5    PTA0不要用（与JLINK冲突）
#define FTM0_CH6    PTD6        //PTD6、PTA1        PTD6    PTA1不要用（与JLINK冲突）
#define FTM0_CH7    PTD7        //PTD7、PTA2        PTD7    PTA2不要用（与JLINK冲突）

//      模块通道    端口          可选范围
#define FTM1_CH0    PTA8       //PTA8、PTA12、PTB0 PTE20 PTA2 PTD6
#define FTM1_CH1    PTA9       //PTA9、PTA13、PTB1 PTE21 PTA1 PTD7

//      模块通道    端口          可选范围
#define FTM2_CH0    PTB18       //PTA10、PTB18 PTE22
#define FTM2_CH1    PTB19       //PTA11、PTB19 PTE23

//      模块通道    端口          可选范围
#define FTM3_CH0    PTE5        // PTE5、PTD0
#define FTM3_CH1    PTE6        // PTE6、PTD1
#define FTM3_CH2    PTE7        // PTE7、PTD2 PTB18 PTA18(晶振输入管脚，不可用)
#define FTM3_CH3    PTE8        // PTE8、PTD3 PTB19
#define FTM3_CH4    PTE9        // PTE9、PTC8
#define FTM3_CH5    PTE10       // PTE10、PTC9
#define FTM3_CH6    PTC10       // PTE11、PTC10
#define FTM3_CH7    PTC11       // PTE12、PTC11

//正交解码模块通道  端口          可选范围
#define FTM1_QDPHA  PTA12       //PTA8、PTA12、PTB0 PTE20
#define FTM1_QDPHB  PTA13       //PTA9、PTA13、PTB1 PTE21

#define FTM2_QDPHA  PTB18       //PTA10、PTB18 PTE22 PTA1
#define FTM2_QDPHB  PTB19       //PTA11、PTB19 PTE23 PTA2

/**********************************  FTM(引脚复用) ***************************************/
typedef enum
{
    Mot0,
    Mot1,
    Mot2,
    Mot3,
    Mot4,
    Mot5,
}Mot_CHn_e;

//定义FTM 通道号
typedef enum
{
    FTM_CH0,
    FTM_CH1,
    FTM_CH2,
    FTM_CH3,
    FTM_CH4,
    FTM_CH5,
    FTM_CH6,
    FTM_CH7,

} FTM_CHn_e;


typedef enum
{
    FTM_Rising,               //上升沿捕捉
    FTM_Falling,              //下降沿捕捉
    FTM_Rising_or_Falling     //跳变沿捕捉
} FTM_Input_cfg;

#define FTM_IRQ_EN(FTMn,CHn)        FTM_CnSC_REG(FTMN[FTMn],CHn) |= FTM_CnSC_CHIE_MASK       //开启 FTMn_CHn 中断
#define FTM_IRQ_DIS(FTMn,CHn)       FTM_CnSC_REG(FTMN[FTMn],CHn) &= ~FTM_CnSC_CHIE_MASK      //关闭 FTMn_CHn 中断
/*********************** PWM功能函数 **************************/
void FTM_PWM_Init(FTM_Type * ftmn, FTM_CHn_e ch, u16 mod, u16 cv);     //电机频率较高，分频较少，FTM_SC_PS(4) 
void ServoFTM_PWM_Init(FTM_Type * ftmn, FTM_CHn_e ch, u16 mod, u16 cv);//舵机频率较低，需要多分频，FTM_SC_PS(7) 
void FTM_PWM_Duty(FTM_Type * ftmn, FTM_CHn_e ch, u16 duty);

/*********************** 输入捕捉及中断功能函数 **************************/
void FTM_Input_init(FTM_Type * ftmn, FTM_CHn_e ch, FTM_Input_cfg cfg);
void FTM0_interrupt(void);
void FTM1_interrupt(void);
void FTM2_interrupt(void);
/*********************** 正交解码功能函数 **************************/
void FTM_AB_Init(FTM_Type * ftmn);         //初始化FTM 的正交解码 功能
s16  FTM_AB_Get(FTM_Type * ftmn);          //获取FTM 正交解码 的脉冲数(负数表示反方向)

void Motor_Init(void);
void Servo_Init(void);
extern void Motor_Duty(u16 Motno, u32 duty);
extern void Servo_Duty(u32 duty);

extern void Test_Servo(void);//舵机测试
extern void Test_Motor(void);//电机测试
extern void Test_AB_Pulse_Cnt(void);//两个编码器脉冲计数
#endif



