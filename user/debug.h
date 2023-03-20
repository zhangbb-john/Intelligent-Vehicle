#ifndef __DEBUG_H__
#define __DEBUG_H__
#define Vol_ratio 3.3/4096*5.7
extern float Variable[20];
extern float sVariable[20];
extern float Parameter[20];
extern float Control_Para[15],Control_Para1[15];
extern float RunTime;
extern uint8 send_data,Dirc,SendPara,stop_contorl,send_data_contorl,beep;
extern uint8 Starting;
extern int  Start_Cnt;
extern  uint8 Page_Index,Para_Index,Para_Checked,OLED_Refresh,Camera_Drawed;
extern uint8 send_data,Uart_Send;
extern void Pre_Check_BottonPress();
extern float wk,circle_delay,circle_speed,rit_correction,brick_speed,wk1,wk2;

extern  uint8 Stop;
void    Check_BottonPress();
void Read_Switch();
void Variable_update();
void Para_Update();
void Send_SD();
void Send_Begin();
void Send_Parameter();
void Send_Variable();
void UART0_RX_IRQHandler();
void OLED_Draw_UI();  //»­³ö½çÃæ
void my_putchar(char temp);
#endif 