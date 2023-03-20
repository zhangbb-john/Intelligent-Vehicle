#include "common.h"
#include "include.h"
float sVariable[20]; //传感器变量
float Variable[20];  //
float Control_Para[15],Control_Para1[15];
float Voltage;
float RunTime;
int   Start_Cnt=0;
uint8 Para_Index_Limit=7;       //一页最多有7个变量序号
uint8 Page_Index=3,Para_Index=1,Light_Tower_Index=0,Para_Checked=0,OLED_Refresh=0;
uint8 Uart_Send=0,SendPara,Dirc,stop_contorl,send_data_contorl=0,beep;
float Step[6]={0.0001,0.001,0.01,0.1,1.0,10.0};   //默认调节步长为0.01
unsigned char Step_Index=4;
void Pre_Check_BottonPress();
//对应不同的页面
char Para_Name[7][12]={"Set_SPEED\0","thresh\0","bais\0","PID_SPEED.P\0",
"PID_SPEED.I\0","PID_DIREC.P\0","PID_DIREC.D\0"};

char Para_Name1[7][12]={"tarsped--\0","cir_dly\0","cir_sped\0","rit_bigger",
"brk_sped","out_cir\0","Str_Sped\0"};

float wk,circle_delay,circle_speed,rit_correction,brick_speed,wk1,wk2;



void my_putchar(char temp)
{
	UART_Put_Char(UART_4,temp);
//      uart_putchar(UART0,temp); //根据实际的串口号来修改
}
/*用来通知上位机新的一组数据开始，要保存数据必须发送它*/
void Send_Begin()
{
  my_putchar(0x55);
  my_putchar(0xaa);
  my_putchar(0x11);
}






void Variable_update()
{
 /* Variable[0]=count_left;
  Variable[1]=count_right;
  Variable[2]=Delta_P;
  Variable[3]=Delta_D;
  Variable[4]=PID_TURN.pout;
  Variable[5]=PID_TURN.dout;
  Variable[6]=PID_TURN.OUT;
  Variable[7]=circle_stage;
  Variable[8]= straight_left ;
  Variable[9]= straight_right ;
  Variable[10]= RoadType;
  Variable[11]= SlopeLmax;
  Variable[12]=SlopeRmin;
  Variable[13]=Middle_Err;
  Variable[14]=il;
  Variable[15]=curve_linel_right;*/
  /*Variable[0]=middle_left_q;
  Variable[1]=curve_left;
  Variable[2]=curve_liner_left;
  Variable[3]=curve_liner_right;
  Variable[4]=straight_right;
  Variable[5]=CarSpeed;
  Variable[6]=search_end_line;
  Variable[7]=middle_right_q;
  Variable[8]= curve_right ;
  Variable[9]= middle_straight_q ;
  Variable[10]= PID_SPEED.OUT;
  Variable[11]= S_flag;
  Variable[12]= RoadType;
  Variable[13]= PID_TURN.OUT;
  Variable[14]=Middle_Err;
  Variable[15]=middle_continue;*/
//  Variable[0]=speedTarget;
//  Variable[1]=Delta_D;
//  Variable[2]=Delta_P;
//  Variable[3]=il;
//  Variable[4]=PID_TURN.pout;
//  Variable[5]=PID_TURN.dout;
//  Variable[6]=PID_TURN.OUT;
//  Variable[7]=control_line;
//  Variable[8]= Middle_Err ;
//  Variable[9]= RunTime ;
//  Variable[10]= CarSpeed;
//  Variable[11]= RoadType;
//  Variable[12]=PID_SPEED.OUT;
//  Variable[13]=middle_left_q;
//  Variable[14]=middle_right_q;
//  Variable[15]=stop_line;
  /*Variable[0]=white_right;
  Variable[1]=Delta_D;
  Variable[2]=left_head_line;
  Variable[3]=ir;
  Variable[4]=PID_TURN.pout;
  Variable[5]=PID_TURN.dout;
  Variable[6]=PID_TURN.OUT;
  Variable[7]=control_line;
  Variable[8]= Middle_Err ;
  Variable[9]= straight_left ;
  Variable[10]= CarSpeed;
  Variable[11]= RoadType;
  Variable[12]=straight_right;
  Variable[13]=SlopeLmax;
  Variable[14]=curve_linel_right;
  Variable[15]=stop_line;*/
  
  
  //wk,
//  Variable[0]= str_L;
//  Variable[1]= turn_flag;
//  Variable[2]= get_out_of_circle;
//  Variable[3]= R1;
//  Variable[4]= slope_circuit;
//  Variable[5]= R0;
//  Variable[6]= left_head_line;
//  Variable[7]= left_end_line;
//  Variable[8]= right_head_line;
//  Variable[9]= right_end_line;
//  Variable[10]=circle_stage;
//  Variable[11]=L1;
//  Variable[12]=RoadType;
//  Variable[13]=slope_circuit;
//  Variable[14]=Middle_Err;
//  Variable[15]=L0;
  

//
  Variable[0]= PID_TURN.OUT;
  Variable[1]= PID_TURN.pout;
  Variable[2]= -PID_TURN.dout;
  Variable[3]= Middle_Err;
  Variable[4]= Delt_error;
  Variable[5]= control_line_far;
  Variable[6]= right_end_line;
  Variable[7]= RoadType;
  Variable[8]= speedTarget;
  Variable[9]= CarSpeed;
  Variable[10]=Speed_kP*SpeedE;
  Variable[11]=Speed_kI*SpeedI;
  Variable[12]=left_end_line;
  Variable[13]=PID_SPEED.OUT;
  Variable[14]=MotorOut;
  Variable[15]=GaveValue;
}
void Para_Update()
{ 
  SetSpeed=Control_Para[0];
  thresh=Control_Para[1];
  bais=(int)Control_Para[2];
  PID_SPEED.P=Control_Para[3];
  PID_SPEED.I=Control_Para[4];
  PID_TURN.P=Control_Para[5];
  PID_TURN.D=Control_Para[6]; 
  
  wk = Control_Para1[0];
  circle_delay = (int)Control_Para1[1];
  circle_speed = Control_Para1[2];
  rit_correction = Control_Para1[3];
  brick_speed = Control_Para1[4];
  wk1 = Control_Para1[5];
  wk2 = Control_Para1[6];
  
}

void Pre_Check_BottonPress()
{
   extern uint8 QuitFlag;
      //退出
   if((BT_SHOW_IN)==0)
   {
      time_delay_ms(30);
      if((BT_SHOW_IN)==0)
      {
		  QuitFlag = 1;
      }
      while((BT_SHOW_IN)==0);  //直到按键松开再运行
      time_delay_ms(30);
   }
   
   if(BT_LEFT_IN==0)
   {
      time_delay_ms(30);
      if(BT_LEFT_IN==0)
      {
		  level = -1;
      }
      while(BT_LEFT_IN==0);//直到按键松开再运行
   }
   //按键6 Right_L
   if(BT_RIGHT_IN==0)
   {
      time_delay_ms(30);
      if(BT_RIGHT_IN==0)
      {
		  level = 1;
      }
      while(BT_RIGHT_IN==0);      //直到按键松开再运行
   }
   //按键4 down
   if(BT_DOWN_IN==0)
   {
      time_delay_ms(30);
      if(BT_DOWN_IN==0)
      {
		  level = 0;
	  }
      while(BT_DOWN_IN==0);  //直到按键松开再运行
   }
   if(BT_UP_IN==0)
   {
      time_delay_ms(30);
      if(BT_UP_IN==0)
      {
		  level--;
		  if(level<-3)level=3;
	  }
      while(BT_UP_IN==0);  //直到按键松开再运行
   }
}
void OLED_Draw_UI()  //画出界面
{
   uint8 i;
   if(Page_Index<=1) 
   {                  
     OLED_PrintValueF(72, 0,Step[Step_Index],5);            //显示调节步进值
     if(Para_Index==7)
     {
        reverse=1; 
         OLED_P6x8Str(116,0,"EE"); 
        reverse=0;
     }
     else  
     {
        OLED_P6x8Str(116,0,"EE"); 
     }
     OLED_Set_Pos(122,7);
     OLED_P6x8Char(Page_Index+48);                         //写出页面序号
   }
  /////////////////////////////////////////////////////////第0页  PID调节
  if(Page_Index==0)                
  {
    for(i=0;i<7;i++)
    {
      if(i==Para_Index&&Para_Checked==false)
      {
       reverse=1;
       OLED_P6x8Str(0,i+1,Para_Name[i]);   //将参量名反转显示
       reverse=0;
      }
      else OLED_P6x8Str(0,i+1,Para_Name[i]);

      
      
      if(i==Para_Index&&Para_Checked)
      {
        reverse=1;
        OLED_PrintValueF(72, i+1,Control_Para[i],5);
        reverse=0;
      }
      else  OLED_PrintValueF(72, i+1,Control_Para[i],5);
      
      OLED_Set_Pos(116,i+1);

    }
  }
  /////////////////////////////////////////////////////////
  if(Page_Index==1)                
  {
    for(i=0;i<7;i++)
    {
      if(i==Para_Index&&Para_Checked==false)
      {
       reverse=1;
       OLED_P6x8Str(0,i+1,Para_Name1[i]);   //将参量名反转显示
       reverse=0;
      }
      else OLED_P6x8Str(0,i+1,Para_Name1[i]);

      
      
      if(i==Para_Index&&Para_Checked)
      {
        reverse=1;
        OLED_PrintValueF(72, i+1,Control_Para1[i],5);
        reverse=0;
      }
      else  OLED_PrintValueF(72, i+1,Control_Para1[i],5);
      
      OLED_Set_Pos(116,i+1);

    }
  }
    /////////////////////////////////////////////////////////第3页 状态显示
  else if(Page_Index==2)
  {


   // OLED_P6x8Str(0,3,"CarSpeed");
   // OLED_PrintValueF(72, 3,CarSpeed,3);
    OLED_P6x8Str(0,2,"Err");
    OLED_PrintValueF(72, 2,Middle_Err,4);
    OLED_P6x8Str(0,3,"delt_err");
    OLED_PrintValueF(72, 3,Delt_error,4);
    OLED_P6x8Str(0,4,"SpeedDevi");
    OLED_PrintValueF(72, 4,SpeedDevi,4);   
    OLED_P6x8Str(0,5,"SpeedDeviD");
    OLED_PrintValueF(72, 5,SpeedDeviD,4);         //补充oled显示wk
    OLED_P6x8Str(0,6,"CarSpeed"); 
    OLED_PrintValueF(72, 6,CarSpeed,4);
    OLED_P6x8Str(0,7,"Distance");
    OLED_PrintValueF(72, 7,Distance,4);
    reverse=0;
    
  } 
  ////////////////////////////////////////////////////////////第4页 传感器显示
  else if(Page_Index==3) 
  {
    OLED_Draw_camera();
    OLED_P6x8Str(82,2,"RoadType");
    OLED_PrintValueF(82, 3,RoadType,4);
    OLED_P6x8Str(82,4,"circle");
    OLED_PrintValueF(82, 5,circle_stage,4);
    OLED_P6x8Str(82, 6,"Middle_Err");
    OLED_PrintValueF(82, 7,Middle_Err,4);
  }
  



}


/*
 * 读拨码开关的值
 */
void Read_Switch() 
{
  if(gpio_get(SW3)==0)  //拨码开关1功能
  {
   Dirc=true;
  }
  else           
  {
    Dirc=false;
  }

  if(gpio_get(SW2)==0)   //拨码开关3功能
  {
	  SendPara=true;
  } 
  else 
  {
	  SendPara=false;
  }
  
  if(gpio_get(SW4)==0)  //拨码开关4功能
  {
//    Dirc=1;
  }
  else 
  {
//    Dirc=0;
  }
 

} 

/*
 * 检测按键是否按下
 */
void Check_BottonPress()
{ 
      //显示按键
   if(BT_SHOW_IN==0)
   {
       time_delay_ms(30);
      if(BT_SHOW_IN==0)
      {
        if(OLED_Refresh==false)
        {
         LCD_Init();
         OLED_Refresh=true;
        }
        else
        {
          //Stop = 0;
          LED_BLUE_OFF;
          OLED_Refresh=false;
          OLED_Fill(0x00);       
        }
      }
      while(BT_SHOW_IN==0);  //直到按键松开再运行
      time_delay_ms(30);
   }
   //按键1 yes
   if(BT_YES_IN==0&&OLED_Refresh) 
   {
       time_delay_ms(30);
      if(BT_YES_IN==0&&OLED_Refresh)
     {    
       if(Para_Index==7) 
       { 
         Para_Index=0; 
       }
       else
       {
         if(Para_Checked==false&&((Page_Index==1)||(Page_Index==0))) Para_Checked=true;
         else Para_Checked=false; 
       }
      }
      while(BT_YES_IN==0); //直到按键松开再运行
   }
   if(BT_YES_IN==0&&!OLED_Refresh) 
   {
       if(Stop)
       { 
         Start_Cnt=700;
         Starting=true;
         //把所有速度控制变量清零
         SpeedControlOutOld=0;
         SpeedControlOutNew=0;
         SpeedControlIntegral=0;  
         PID_SPEED.OUT=0;
         RunTime=0;
         Distance=0;
         ControlSpeed=0;
       }
     while(BT_YES_IN==0); //直到按键松开再运行
   }
        
   //按键2 Left_L
     if(BT_LEFT_IN==0)
   {
	   //去抖
       time_delay_ms(30);
      if(BT_LEFT_IN==0)
      {
        if(Para_Checked) 
        {
          if(Step_Index==5) 
          Step_Index=0;   //最大的步长为10
          else Step_Index++;
        }
        else 
        { 
          Para_Index=0;
          if(Page_Index==0) Page_Index=3; //当参数没被选中的时候，按左右键翻页
          else Page_Index--;
          OLED_Fill(0);//清屏 
        }
      }
      while(BT_LEFT_IN==0);//直到按键松开再运行
   } 
   //按键6 Right_L
     if(BT_RIGHT_IN==0&&OLED_Refresh)
   {
       time_delay_ms(30);
      if(BT_RIGHT_IN==0)
      {
        if(Para_Checked) 
        {
          if(Step_Index==0) 
           Step_Index=0;//最小的步长为0.0001
          else
          {
            Step_Index--;
          }
        }
        else 
        { 
          Para_Index=0;
          if(Page_Index==3) Page_Index=0;
          else Page_Index++;
         OLED_Fill(0);//清屏 
        }
      }
      while(BT_RIGHT_IN==0);      //直到按键松开再运行
   }
   //按键3 up
     if(BT_UP_IN==0&&OLED_Refresh)
   {
       time_delay_ms(30);
      if(BT_UP_IN==0)
      {
   
          if(Para_Checked==false)
          {
           if(Para_Index==0) Para_Index=Para_Index_Limit;
           else Para_Index-=1;
          }
          else
          {
              if(Page_Index==0&&Para_Index<=6)                    //修改第0页的参数
            {
              Control_Para[Para_Index]+=Step[Step_Index];
            }
            
            if(Page_Index==1&&Para_Index<=6)                    //修改第1页的参数
            {
              Control_Para1[Para_Index]+=Step[Step_Index];
            } 
            Para_Update();
          }
      }  
      while(BT_UP_IN==0);//直到按键松开再运行  
   }
   //按键4 down
   if(BT_DOWN_IN==0)
   {
     if(OLED_Refresh)
     {
       time_delay_ms(30);
      if(BT_DOWN_IN==0)
      {
          if(Para_Checked==false)
          {             
            if(Para_Index==Para_Index_Limit)Para_Index=0;   //防止序号超出范围
            else  Para_Index+=1; 
          }
           else 
           {
            if(Page_Index==0&&Para_Index<=6)                    //修改第0页的参数
            {
              Control_Para[Para_Index]-=Step[Step_Index];
            }
             
            if(Page_Index==1&&Para_Index<=6)                    //修改第1页的参数
            {
              Control_Para1[Para_Index]-=Step[Step_Index];
            }
            Para_Update();
          }
      }
     }
     else
     {      
     }

      while(BT_DOWN_IN==0);  //直到按键松开再运行
   }
}



void Send_Variable()
{
  uint8 i=0,ch=0;
  float temp=0;
  uint8 Variable_num=16;
  my_putchar(0x55);
  my_putchar(0xaa);
  my_putchar(0xff);
  my_putchar(0x01);
  my_putchar(Variable_num);
 for(i=0;i<Variable_num;i++)
  {
    temp=Variable[i];
    ch=BYTE0(temp);
    my_putchar(ch);
    ch=BYTE1(temp);
    my_putchar(ch);
    ch=BYTE2(temp);
    my_putchar(ch);
    ch=BYTE3(temp);
    my_putchar(ch);
  }
     my_putchar(0x01);
}




void Modify_Parameter(uint8 *buff)
{
   uint8 i=0,addr=0;
   float temp;
   uint8 Parameter_num=14; //14个可改参数
  /*          修改参数数组         */
   for(i=0;i<Parameter_num;i++)
  {
       BYTE0(temp)=*(uint8*)(buff+addr);
       addr++;
       BYTE1(temp)=*(uint8*)(buff+addr);
       addr++;
       BYTE2(temp)=*(uint8*)(buff+addr);
       addr++;
       BYTE3(temp)=*(uint8*)(buff+addr);
       addr++;
       Control_Para[i]=temp;
   }
   
    Para_Update();
}



void Send_Parameter()
{
  uint8 i=0,ch=0;
  float temp=0;
  uint8 Parameter_num=14;  //14个可改参数
  
 
  my_putchar(0x55);
  my_putchar(0xaa);
  my_putchar(0xff);
  my_putchar(0x02);
  my_putchar(Parameter_num);
  for(i=0;i<Parameter_num;i++)
  { 
     temp=Control_Para[i];
    ch=BYTE0(temp);
    my_putchar(ch);
    ch=BYTE1(temp);
    my_putchar(ch);
    ch=BYTE2(temp);
    my_putchar(ch);
    ch=BYTE3(temp);
    my_putchar(ch);
  }
    my_putchar(0X02);//帧尾
}

void UART0_RX_IRQHandler()
{
  static uint8 recv;
  static uint8 data_cnt=0;
  static uint8 predata[10];
  static uint8 Recv_Buff[100];
  static uint8 Data_Receiving=false;
  
//  if(uart_query(UART0)==1)  uart_getchar (UART0,(char*)(&recv));  //根据实际的串口来修改
  /**********代表正在接收来自上位机的参数数据*********/
  if(Data_Receiving)
  {
      if(data_cnt<56)
      {
       Recv_Buff[data_cnt]= recv;
       data_cnt++;
      }
      else
      {
        data_cnt=0;    //达到帧长
        Data_Receiving=false;
        if(recv==2)  //帧尾
        {
           Modify_Parameter(Recv_Buff);
           SendPara=1;      //参数回传，确认参数修改完成
            beep=1; //开启蜂鸣器
        }
      }
  }

  
  
    if( predata[1]==0x55&&predata[0]==0xAA)
    {
      
        switch(recv)         //判断功能字
         { 
            case 1:           //读取参数 
               if(SendPara==0) SendPara=1;
                beep=1; //开启蜂鸣器
              break;
            
            case 2:           //修改参数
              data_cnt=0;
              Data_Receiving=true;
            case 3:           //保存参数
//              EEPROM_Save();
              beep=1; //开启蜂鸣器
            break;        
           
            case 4:           //功能开关1
             
            break;    
            
            case 5:           //功能开关2
             
            break;     
            
            case 6:           //功能开关3
             
            break; 
            
            case 7:           //功能开关4
             
            break;        
            
            default:           //
             break;
          }
    }
  predata[1]=predata[0];
  predata[0]=recv;
}