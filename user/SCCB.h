/*!
 * @file       VCAN_SCCB.h
 * @brief      OV摄像头配置总线SCCB函数库
 */


#ifndef _SCCB_H_
#define _SCCB_H_

//SCCB 管脚配置
#define SCL_H()         SCL_High
#define SCL_L()         SCL_Low
#define SCL_DDR_OUT()   SCL_Out
//#define SCL_DDR_IN()    PTXn_T(SCCB_SCL,DDR) = 0

#define SDA_H()         SDA_High
#define SDA_L()         SDA_Low
#define SDA_IN()        SDA_Data
#define SDA_DDR_OUT()   SDA_Out
#define SDA_DDR_IN()    SDA_In

#define SCCB_DELAY()    SCCB_Wait()


extern int SCCB_WriteByte( uint16 WriteAddress , uint8 SendByte);
extern int SCCB_ReadByte(uint8 *pBuffer,   uint16 length,   uint8 ReadAddress);


#endif      //
