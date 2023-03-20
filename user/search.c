#include "include.h"    //20行=90cm
#define LIM 255
#define LINE_Far 120
#define GAP_THRE 30
uint8 bais;
uint8 L0=255,L1=255,R0=255,R1=255;
float flope_temp;
uint16 whiteCount;
uint8 lose_brick;
uint8 brick_con=255;
uint8 con_brick;
float slope_circuit=0;
uint8 str_L,str_L1,str_L2,str_R,str_R1,str_R2,LL,LL1,LL2,LR,LR1,LR2,RR,RR1,RR2,RL,RL1,RL2;
float slope_qj;
int slope_q[3][120];    //储存斜率
uint8 end_line;  //有效行末行
uint8 line=30; //控制行
uint8  RoadType=0;   //右圆环2   左圆环3  十字1  直道4
float Previous_Error[20];
int Loc[3][LINE_Far];
uint8 continue_line_left=0,continue_line_right=0;
uint16 edgposition[CAMERA_H];
uint8 left_head_line,right_head_line,right_end_line,left_end_line;
int search_end_line;
uint16 cont;
uint8 control_line,stop_line=0;
uint8 control_line_near,control_line_far;
static float SpeedDevi_His[10] = {0};
uint8 il,ir;   //左右拐点wk
uint8 xierushizi=0;
uint8 failcount=0;
uint8 get_out_of_circle;
uint8 times_count=0;
int curve_left,curve_right;
uint8 last_control_line=255;
uint8 S_flag=0,first_white_right;
uint8 ramp_cnt=0,out_cnt=0;
int map_y[60]={
  519	,415	,343	,291	,252	,221	,196	,175	,158	,143	,130	,119	,110	,101	,94	,87	,81	,75	,70	,65	,61	,57	,54	,50	,47	,44	,42	,39	,37	,34	,32	,30	,28	,27	,25	,23	,22	,20	,19	,18	,16	,15	,14	,13	,12	,11	,10	,9	,8	,7	,6	,6	,5	,4	,3	,3	,2	,1	,1	,0	
};
int AllWhileStartLine,AllWhileEndLine;
uint8 turn_point=60;   //拐点对应的行数wk
uint8 circle_stage=0;
uint8 circle_cnt=0;
int slopeL[60],slopeR[60];
uint8 turn_flag;
int SlopeLmax,SlopeLmin,SlopeRmax,SlopeRmin;
float Middle_Err_Sum,Middle_Err_Sum_Near,Middle_Err_Sum_Middle,Middle_Err_Sum_Far;
uint8 Black_record[10]={40,40,40,40,40,40,40,40,40,40};
int ARCTANG[80] = {
0,115	,229	,343	,457	,571	,684	,797	,909	,1020	,1131	,1241	,1350	,1457	,1564	,1670	,1774	,1878	,1980	,2081	,2180	,2278	,2375	,2470	,2564	,2657	,2747	,2837	,2925	,3011	,3096	,3180	,3262	,3342	,3422	,3499	,3575	,3650	,3723	,3795	,3866	,3935	,4003	,4070	,4135	,4199	,4261	,4323	,4383	,4442	,4500	,4557	,4612	,4667	,4720	,4773	,4824	,4874	,4924	,4972	,5019	,5066	,5112	,5156	,5200	,5243	,5285	,5327	,5367	,5407	,5446	,5485	,5522	,5559	,5595	,5631	,5666	,5700	,5734	,5767

};
void Push_And_Pull(float *buff,int len,float newdata)
{
	int i;
	for(i=len-1;i>0;i--)
	{
		*(buff+i)=*(buff+i-1);
	}
	*buff=newdata; 
}
void Push_And_Pull_int(int *buff,int len,int newdata)
{//0最新
	int i;
	for(i=len-1;i>0;i--)
	{
		*(buff+i)=*(buff+i-1);
	}
	*buff=newdata; 
}
float  delta_error_Filter(float delta)    //转向控制输出滤波      
{
	float delta_Filtered; 
	static float Pre_Error[4]; 
	Pre_Error[3]=Pre_Error[2];
	Pre_Error[2]=Pre_Error[1];
	Pre_Error[1]=Pre_Error[0];
	Pre_Error[0]=delta;
	delta_Filtered=Pre_Error[0]*0.5+Pre_Error[1]*0.2+Pre_Error[2]*0.2+Pre_Error[3]*0.1;
	return delta_Filtered;
}
int CurveGet(int AX, int AY, int BX, int BY, int CX, int CY)
{
  int SABC_temp; //三角形的面积，有正负。
  int tempab, tempbc, tempac;
  int AB, BC, AC; //三角形的边长，均为正。
  int result;
  //int K;        //曲率结果，有正负。
  
  SABC_temp = ((BX - AX) * (CY - AY) - (CX - AX) * (BY - AY));
  
  tempab = (BX - AX) * (BX - AX) + (BY - AY) * (BY - AY);
  if(tempab > 100) 
  {
    AB = sqrt(tempab / 100) * 10; //失掉两位的精度，因为求根运算范围的限制。
  }
  else
  {
    AB = sqrt(tempab);
  }
  
  tempbc = (BX - CX) * (BX - CX) + (BY - CY) * (BY - CY);
  if(tempbc > 100) 
  {
    BC = sqrt(tempbc / 100) * 10; //失掉两位的精度，因为求根运算范围的限制。
  }
  else
  {
    BC = sqrt(tempbc);
  }
  
  tempac = (CX - AX) * (CX - AX) + (CY - AY) * (CY - AY);
  if(tempac > 100) 
  {
    AC = sqrt(tempac / 100) * 10; //失掉两位的精度，因为求根运算范围的限制。
  }
  else
  {
    AC = sqrt(tempac);
  }
  
  result = 2000 * SABC_temp / AB / BC / AC;
  if(result >= 255) 
  {
    result = 255 - 1;           //不能大过MaxValUint8
  }
  else if(result + 255 < 0)
  {
    result = 1 - 255;           //不能小过-MaxValUint8
  }
  else
  {
  }
  
  return result;
}


float Slope_Calculate_Uint8(uint8 begin,uint8 end,int *p)    //最小二乘法拟合斜率
{
	float xsum=0,ysum=0,xysum=0,x2sum=0;
	uint8 i=0;
	int temp=40;
	float result=0;
//	static float resultlast;
	p=p+begin;
	temp=*p;
	for(i=begin;i<end;i++)
	{
		xsum+=i;
		ysum+=*p-temp;
		xysum+=i*(*p-temp);
		x2sum+=i*i;
		p=p+1;
	}
	if((end-begin)*x2sum-xsum*xsum) //判断除数是否为零 
	{
		result=((end-begin)*xysum-xsum*ysum)/((end-begin)*x2sum-xsum*xsum);
//		resultlast=result;
	}
	else
	{
		result=0;//resultlast;
	}
	return result;
}


void sendimg()
{
	uint8 ch=0;
	float temp=0;
	uint16 i=0,num,j;
	my_putchar(0x55);
	my_putchar(0xaa);
	my_putchar(0xff);
	my_putchar(0xa2);
	my_putchar(RoadType); //小车状态
	
	num=cont+2+180+36;  
	//统计将要传输的数据量 2是因为要传输关键字即0xf0和0xf2   (0xf2 所有数据结束，0xf0图像数据结束，180=60*3)
	//180是边线的位 36是变量的位 如果不传输就不要加上！
	
	my_putchar(BYTE0(num)); 
	my_putchar(BYTE1(num));
	for(i=0;i< cont;i++)
	{
		my_putchar(img_edg[i]);
	}
	my_putchar(0xf0);  //代表图像数据发完了
	/******************星号围起来的可以不传输*******************/
	// for(i=179;i>=0;i--)
	// {
	////  if(Loc[i*2/LINE_Far][i*2%LINE_Far]/2>=-40 && Loc[i*2/LINE_Far][i*2%LINE_Far]/2<=40)
	//  my_putchar( Loc[(179-i)*2/LINE_Far][i*2%LINE_Far]/2+40);
	// }
	for(i=0;i<3;i++)
	{
		for(j=60;j>0;j--)
		{
			if(Loc[i][(j-1)*2]<=80 && Loc[i][(j-1)*2]>=-80)
				my_putchar(Loc[i][(j-1)*2]/2+40);
			else 
				my_putchar(0);
		}
	}
	for(i=0;i<9;i++)
	{
		temp=sVariable[i];
		ch=BYTE0(temp);
		my_putchar(ch);
		ch=BYTE1(temp);
		my_putchar(ch);
		ch=BYTE2(temp);
		my_putchar(ch);
		ch=BYTE3(temp);
		my_putchar(ch);
	}
	/*****************************************************/
	my_putchar(0xf2); //代表整个数据都发完了
	
}
uint8 absint(uint8 a,uint8 b)
{
	return (a<b)?(b-a):(a-b);
}

void get_edge_left(uint8 line,uint8 start_point)   //0黑
{
	uint8 x,i,j,n,temp;
	x=10*line;
	j=start_point/8;
	
	
	for(;j>=0;j--)
	{
		if(imgbuff_process[x+j]==0xff)
		{
			continue;
		}
		else if(imgbuff_process[x+j]==0)
		{
			LMR[0][line]=j*8;
			break;
		}
		else
		{
			for(n=0;n<=7;n++)
			{
				temp=(imgbuff_process[x+j]>>n)&1;// 获取该点像素值 （0或1）     
				if(temp==1) 
				{
					continue;
				}
				else 
				{
					LMR[0][line]=j*8+7-n;
					break;
				}
			} 
			
		}
	}
	
}

void get_edge_right(uint8 line,uint8 start_point)   //0黑
{
	uint8 x,i,j,n,temp;
	x=10*line;
	j=start_point/8;
	
	for(;j<10;j++)
	{
		if(imgbuff_process[x+j]==0xff)
		{
			continue;
		}
		else if(imgbuff_process[x+j]==0)
		{
			LMR[0][line]=j*8;
		}
		else
		{
			for(n=7;n>=0;n--)
			{
				temp=(imgbuff_process[x+j]>>n)&1;// 获取该点像素值 （0或1）     
				if(temp==1) 
				{
					continue;
				}
				else 
				{
					LMR[2][line]=j*8+7-n;
				}
			} 
			
		}
	}
	
}



void get_edge()   //尽量减少乘法运算
{
	static int16 i=0,j=0,last=0,x=0,y=0,n=0;
	uint8 temp=0,find=0;
	cont=0;
	uint8 flag_ban=0;
	uint8 flag_bw=0;
	uint8 qipao=0;
	for(i=0;i<60;i++)
	{
		last=0; 
		x=i*10;
		find=0;
		edgposition[i]=0;
		flag_bw=0;
		
		for(j=0;j<10;j++)
		{
			if(imgbuff_process[x+j]==0xff)
			{
				if(j>=3 && j<=6)flag_bw++;
				if(last==0)
				{
					y=j<<3;
					if(find==0)
					{
						edgposition[i]=cont;
					}
					img_edg[cont++]=y;   //左移动5相当于乘以32 左移动3相当于乘以8 
					find=1;
				}
				last=1;
				continue;
			}
			if(imgbuff_process[x+j]==0)
			{
				if(j>=3 && j<=6)flag_bw++;
				if(last==1)
				{          
					y=j<<3;
					if(find==0)
					{
						edgposition[i]=cont;
					}
					img_edg[cont++]=y;   //左移动5相当于乘以32 左移动3相当于乘以8  
					find=1;
				}
				last=0;
				continue;
			}
			
			for(n=7;n>=0;n--)
			{
				temp=(imgbuff_process[x+j]>>n)&1;// 获取该点像素值 （0或1）     
				if(temp!=last) //与上一个值不相同 出现了跳变沿            
				{
					y=j<<3;  
					if(find==0)
					{
						edgposition[i]=cont;
					}
					img_edg[cont++]=y+7-n;   //左移动5相当于乘以32 左移动3相当于乘以8 
					find=1;
				}
				last=temp;                //存储该点的值
			} 
		} 
		img_edg[cont++]=0xff;   //左移动5相当于乘以32 左移动3相当于乘以8
		if(i<50 && i>15 && flag_bw==0 && cont-edgposition[i]>13 ) 
		{
//			if(Distance>20)Stop=1;
			qipao++;
		}
		
	}
	if(qipao>=1)stop_line=1;
	else stop_line=0;
	
}
/*img_edg是一个一维数组 记录了摄像头每行的跳变沿的坐标值  每行跳变沿 由上升沿开始（由黑变白）然后接下降沿（由白变黑） 
0xff用于指示该行的跳变沿完了，开始记录下一行
如果每行图像以白色部分开始，那么该行跳变沿起始位置为0
如果该行全黑 那么该行记录为0xff
如果该行为全白 记录为 0 0xff


oxff代表本行坐标值结束，进入下一行
//edgposition[i]代表第i行的 跳变沿 在 img_edg 中坐标起点

*/
void fix_break_line() //修复断开的线
{
	
}

uint8 str_confirm(uint8 lr)
{
	uint8 i;
	float slope;
	uint8 wrong=0;
	float temp=0;
	
	if(lr==0)
	{
		uint8 end=LIMIT(left_end_line,80,0);
		if(end-left_head_line>37)
		{
			slope=Slope_Calculate_Uint8(left_head_line+10,end-10,Loc[0]);
//			slope=(Loc[0][end-1]-Loc[0][left_head_line+1])*1.0/(end-left_head_line-2);
			for(i=left_head_line+2;i<end-1;i++)
			{
				temp=Loc[0][left_head_line+1]+slope*(i-left_head_line-1);
				if(ABS(Loc[0][i]-temp)>4)wrong=wrong+3;
				else if(ABS(Loc[0][i]-temp)>2)wrong++;
			}
		}
		else
			return 0;
		if(wrong<5)return 1;
		else return 0;
	}	
	if(lr==2)
	{
		uint8 end=LIMIT(right_end_line,80,0);
		if(end-right_head_line>37)
		{
			slope=Slope_Calculate_Uint8(right_head_line+10,end-10,Loc[2]);
//			slope=(Loc[2][end-1]-Loc[2][right_head_line+1])/(end-right_head_line-2);
			for(i=right_head_line+2;i<right_end_line-1;i++)
			{
				temp=Loc[2][right_head_line+1]+slope*(i-right_head_line-1);
				if(ABS(Loc[2][i]-temp)>4)wrong=wrong+3;				
				else if(ABS(Loc[2][i]-temp)>2)wrong++;
			}
		}
		else
			return 0;
		if(wrong<5)return 1;
		else return 0;
	}
}

uint8 str_confirm_brick(uint8 lr)
{
	uint8 i;
	float slope;
	uint8 wrong=0;
	float temp=0;
	
	if(lr==0)
	{
          slope=Slope_Calculate_Uint8(20,80,Loc[0]);
          //			slope=(Loc[0][end-1]-Loc[0][left_head_line+1])*1.0/(end-left_head_line-2);
          for(i=22;i<80;i++)
          {
            temp=Loc[0][21]+slope*(i-21);
            if(ABS(Loc[0][i]-temp)>4)wrong=wrong+3;
            else if(ABS(Loc[0][i]-temp)>2)wrong++;
          }
          if(wrong<6)return 1;
          else return 0;
	}	
	if(lr==2)
	{
          slope=Slope_Calculate_Uint8(20,80,Loc[2]);
          for(i=22;i<80;i++)
          {
            temp=Loc[2][21]+slope*(i-21);
            if(ABS(Loc[2][i]-temp)>4)wrong=wrong+3;				
            else if(ABS(Loc[2][i]-temp)>2)wrong++;
          }
          if(wrong<6)return 1;
          else return 0;
	}
}


uint8 find_circle(uint8 *src,uint8 startline)    //寻找环状黑线
{
	uint8 i;
	uint8 turn_left=0,turn_right=0;
	uint8 countl=0,countr=0,count=0;;
	for(i=startline;i>startline-24;i=i-2)
	{
		if(src[i-2]<src[i])
		{
			countr=0;
			countl++;
			if(countl==1 && turn_right==1)
			{
				turn_right=2;      
			}
			else if(countl==5 && turn_right==0)
			{
				turn_left=1;
			}
		}
		if(src[i-2]>src[i])
		{
			countl=0;
			countr++;
			if(countr==1 && turn_left==1)
			{
				turn_left=2;      //先左后右
			}
			else if(countr==5 && turn_left==0)
			{
				turn_right=1;
			}
		}   
		
		if(src[i-2]==0||src[i-2]==80)
		{
			break;
		}
	}
	
	if(turn_left==2 && turn_right!=2) return 1;
	else if(turn_left!=2 && turn_right==2) return 2;
	else return 0;
	
}

void fix_line(uint8 *src,uint8 startline)
{
	uint8 i;
	int slope;
	slope=(src[startline+4]-src[startline+6]+src[startline+3]-src[startline+5]);
	for(i=startline;i>0;i--)
	{
		src[i]=src[i+4]+slope;
		if(src[i]>75||src[i]<5)break;
	}
	
}

void insert(uint8 lr,uint8 start,uint8 end)
{
	uint8 i;
	float slope;
	slope=(Loc[lr][end]-Loc[lr][start])*1.0/(end-start);
	for(i=start+1;i<end;i++)
	{
		Loc[lr][i]=(int)(Loc[lr][start]+slope*(i-start));
	}
}
uint8 break_point_find(int *src)   //寻找拐点 wk
{
	uint8 i;
	int deta=0;
	int deta_pre=255;
	int deta_pre2=255;
	int deta_pre3=255;
	uint8 count=0;
	for(i=0;i<80;i+=2)
	{
		if(src[i]!=-LIM && src[i]!=LIM && src[i+2]!=-LIM && src[i+2]!=LIM && absint(src[i],src[i+2])<10)
		{
			count=0;
			deta_pre3=deta_pre2;
			deta_pre2=deta_pre;
			deta_pre=deta;
			deta=(src[i+2]-src[i]);
			if(deta_pre2!=255)
			{
				if(deta_pre2*deta<=-4)    //break_point_find修改，前面有*10 wk
					return i-2;
			}
			if(deta_pre3!=255)
			{
				if(deta_pre3*deta<-4)    //break_point_find修改，前面有*10 wk
					return i-4;
			}
		}
		else
		{
			count++;
		}
		if(count==2)
		{
			deta_pre2=255;
			deta_pre=255;
			deta=0;    
		}  
		if(count>18)
		{
			break;
		}
	}
	return LIM;
}


void Search()
{
	//从底部往上搜线
        uint8 fix_flag=0;
	uint8 start_brick=255,stop_brick=255;
	uint8 brick_dir=255;  //0左 1右
	static uint8 ruwan_flag;
	static uint8 search_time;
        static uint8 wait_time;
	int i,j;
	uint8 half=25; //赛道半宽
        uint8 find=0;
        get_out_of_circle=0;
	for(i=0;i<60;i++)  //清空数组
	{  
		LMR[0][i]=0; //左边线数列
		LMR[1][i]=40;  //中线数列
		LMR[2][i]=80; //右边线数列
	}
	for(i=0;i<30;i++)
	{
		slope_q[0][i]=255;
		slope_q[1][i]=255;
		slope_q[2][i]=255;
	}
	for(i=0;i<LINE_Far;i++)  //清空数组
	{ 
		Loc[0][i]=-LIM;
		Loc[1][i]=LIM;
		Loc[2][i]=LIM;
	}
//        for(i=0;i<3;i++)
//        {
//                curve[i]=255;
//        }
	search_time++;
	con_brick=0;
	end_line=0;
	first_white_right=60;
	S_flag=0;
	curve_left=curve_right=0;
	AllWhileStartLine=AllWhileEndLine=0;
	search_end_line=0;
	SlopeLmax=SlopeRmax=-255;
	SlopeLmin=SlopeRmin=255;
	str_L=0,str_L1=0,str_L2=0,str_R=0,str_R1=0,str_R2=0,LL=0,LL1=0,LL2=0,LR=0,LR1=0,LR2=0,RR=0,RR1=0,RR2=0,RL=0,RL1=0,RL2=0;
	continue_line_left=0;
	continue_line_right=0;
	left_head_line=255;
	right_head_line=255;
	left_end_line=255;
	right_end_line=255;
	Middle_Err_Sum_Near=0;
	Middle_Err_Sum_Far=0;
	Middle_Err_Sum=0;
	for(i=59;i>7;i--) //从第59行开始搜线 至11行
	{
		if(edgposition[i]==0) //全黑行 置为丢线
		{
			break;
		}
		j=edgposition[i];//该行跳变沿开始的位置  j代表黑变白 即左边线 j+1代表变黑 即右边线 
		if(i==59)  //底部开始行
		{   
			while(img_edg[j]!=255)
			{  
				if((img_edg[j]<Black_record[9])&&(img_edg[j+1]>Black_record[9]))  //左边沿小于55 右边沿大于25
				{
					if((img_edg[j+1]-img_edg[j])>20) //右边沿-左边沿大于20
					{
						LMR[0][i]=img_edg[j];
						
						if(img_edg[j+1]==255)
						{
							LMR[2][i]=80;      
						}
						else
						{
							LMR[2][i]=img_edg[j+1];
							
						}
						break;//while
					}
				}
				if(img_edg[j+1]==255)
				{
					break;//while
				}
				j=j+2;
			}
			
		}
		else   //不是底部开始行
		{ 
			find=0;
			while(img_edg[j]!=255)
			{
				if((img_edg[j]<=LMR[2][i+1]-5)&&(img_edg[j+1]>=LMR[0][i+1]+5)&&(img_edg[j+1]-img_edg[j])>11)     //左边沿小于上一行的右边线 右边沿大于上一行的左边线是连通域；  //差值改为13 kk
				{
					find=1;
					if(LMR[0][i]==0&& img_edg[j]!=0 /*&& !(absint(img_edg[j],LMR[0][i+1])>12 && LMR[0][i+1]!=0)*/)     //阈值修改为6 kk
					{
						if(LMR[2][i]==80)
						{
							if(i>56)
							{
								if(img_edg[j]<Black_record[i-50])LMR[0][i]=img_edg[j];
								else LMR[0][i]=0;
							}
							else LMR[0][i]=img_edg[j];
						}
						
					} 
					if(img_edg[j+1]!=255&&(LMR[2][i]==80)&& !(absint(img_edg[j+1],LMR[2][i+1])>12 && LMR[2][i+1]!=80))
					{
						if(i>50)
						{
							if(img_edg[j+1]>Black_record[i-50])LMR[2][i]=img_edg[j+1];
							else LMR[2][i]=80;
						}
						else LMR[2][i]=img_edg[j+1];
					}
				}
				if(img_edg[j+1]==255) //该行的跳变沿结束了
				{
					if(img_edg[j]==0) //说明该行为全白 
					{ 
						if(AllWhileStartLine==0)
						{
							AllWhileStartLine=i; //全白行开始的位置
						}
						AllWhileEndLine=i;
					}
					break;//while
				}
				if(img_edg[j+1]>77 && img_edg[j]<3)
				{
					
					if(AllWhileStartLine==0)
					{
						AllWhileStartLine=i; //全白行开始的位置
					}
					AllWhileEndLine=i;
					
					break;//while
					
				}
				j=j+2;
			}
		}
	}
    //================================================================================================================================//
	//错误判断
	//================================================================================================================================//
        
    whiteCount = 0;
	if(Stop == 0)
	{
		for(i = 480;i <= 570; i+=10)
		{
			for(j = 0; j <= 9; j++)
			{
				if(imgbuff_process[i+j] == 0xff)
				{
					whiteCount++;
				}
			}
		}
		if(whiteCount<=25)
		{
			failcount++;
		}
		else
		{
			failcount=0;
		}
//		if(failcount > 30) Stop = 1;
	}
    
	
	//================================================================================================================================//
	//逆透视
	//================================================================================================================================//
//	uint8 y2,last_y0,last_y2;
//	last_y0=0;
//	last_y2=0;
//	for(i=59;i>10;i--)
//	{
//		y2=map_y[i];
//		y2=MIN(y2,119);
//		if(LMR[0][i]!=0)
//		{ 
//			Loc[0][y2]=map[i][LMR[0][i]];
//			if(Loc[0][y2]>=80)Loc[0][y2]=LIM;
//			else if(Loc[0][y2]<-80)Loc[0][y2]=-LIM;
//			else
//			{
//				if(y2-last_y0>1 && y2-last_y0<12 && last_y0!=0)
//				{
//					insert(0,last_y0,y2);
//				}
//				last_y0=y2;
//			}
//		}
//		if(LMR[2][i]!=80)
//		{
//			Loc[2][y2]=map[i][LMR[2][i]];
//			if(Loc[2][y2]>80)Loc[2][y2]=LIM;
//			else if(Loc[2][y2]<-80)Loc[2][y2]=-LIM;
//			else
//			{
//				if(y2-last_y2>1 && y2-last_y2<11 && last_y2!=0)
//				{
//					insert(2,last_y2,y2);
//				}
//				last_y2=y2;
//			}
//		}
//	}
	uint8 y2,last_y0,last_y2;
	last_y0=0;
	last_y2=0;
	for(i=59;i>10;i--)
	{
		y2=map_y[i];
		y2=MIN(y2,119);
		if(LMR[0][i]!=0)
		{ 
			Loc[0][y2]=map[i][LMR[0][i]];
			if(Loc[0][y2]>=80)Loc[0][y2]=LIM;
			else if(Loc[0][y2]<-80)Loc[0][y2]=-LIM;
			else
			{
				if(i<59 && map_y[i+1]==last_y0)
				{
					insert(0,last_y0,y2);
				}
				last_y0=y2;
			}
		}
		if(LMR[2][i]!=80)
		{
			Loc[2][y2]=map[i][LMR[2][i]];
			if(Loc[2][y2]>80)Loc[2][y2]=LIM;
			else if(Loc[2][y2]<-80)Loc[2][y2]=-LIM;
			else
			{
				if(i<59 && map_y[i+1]==last_y2)
				{
					insert(2,last_y2,y2);
				}
				last_y2=y2;
			}
		}
	}
	for(i=3;i<100;i++)
	{
		if(Loc[2][i]- Loc[0][i] <28 && Loc[2][i]- Loc[0][i] >16)
		{
			con_brick++;
		}
	}
	//================================================================================================================================//
	//十字判断
	//================================================================================================================================//
	if((map_y[AllWhileEndLine]-map_y[AllWhileStartLine])>23 && RoadType==0 && AllWhileStartLine<51)  
		//且两边边线都找到过 排除顶部20行的干扰
	{
		RoadType=1; //进入十字了
                left_head_line=5;
                right_head_line=5;
	}
	if(RoadType==1 && AllWhileEndLine<20 && (AllWhileStartLine>54||AllWhileStartLine==0))
	{
		RoadType=0;
	}
        
	//================================================================================================================================//
	//有效性判断
	//================================================================================================================================//
	//障碍物判断
	
	uint8 gapl=0,gapr=0;
	uint8 losel=0,loser=0;
	if(RoadType==4 || ((str_confirm_brick(0) || str_confirm_brick(2)) && RoadType==0))
	{
		for(i=10;i<100;i++)
		{
			if(Loc[0][i]!=-LIM && Loc[2][i]!=LIM)
			{
				if(Loc[2][i]- Loc[0][i] <28 && Loc[2][i]- Loc[0][i] >16)
				{
					if(start_brick==255)
					{
						start_brick=i;
					}
                                        stop_brick=i;
					if(brick_dir==255)
					{
						if(Loc[0][i-5]!=-LIM && Loc[0][i]-Loc[0][i-5]>10 && Loc[2][i-5]!=LIM && Loc[2][i-5]-Loc[2][i]<8 )brick_dir=1;
						else if(Loc[0][i-5]!=-LIM && Loc[0][i]-Loc[0][i-5]<8 && Loc[2][i-5]!=LIM && Loc[2][i-5]-Loc[2][i]>10 )brick_dir=0;
						else brick_dir=255;
					}
				} 
				else
				{
					if(stop_brick-start_brick>12)
					{
						RoadType=5;
                                                if(brick_dir!=255)brick_con=brick_dir;
						break;
					}
					if(stop_brick-start_brick<5)
					{
						start_brick=255;
						brick_dir=255;
					}
				}
			}
			else
			{
				if(stop_brick-start_brick>12)
				{
					RoadType=5;
                                        if(brick_dir!=255)brick_con=brick_dir;
					break;
				}
				if(stop_brick-start_brick<5)
				{
					start_brick=255;
					brick_dir=255;
				}
			}       
		}
                left_end_line=LIMIT(stop_brick,70,40);
                right_end_line=LIMIT(stop_brick,70,40);
	}
	
	else if(RoadType==5 ||(con_brick>6 && RoadType==0))
	{
		for(i=10;i<100;i++)
		{
			if(Loc[0][i]!=-LIM && Loc[2][i]!=LIM)
			{
				if(Loc[2][i]- Loc[0][i] <28 && Loc[2][i]- Loc[0][i] >16)
				{
					if(start_brick==255)start_brick=i;
					stop_brick=i;
					if(brick_dir==255)
					{
						if(Loc[0][i-5]!=-LIM && Loc[0][i]-Loc[0][i-5]>10 && Loc[2][i-5]!=LIM && Loc[2][i-5]-Loc[2][i]<8 )brick_dir=1;
						else if(Loc[0][i-5]!=-LIM && Loc[0][i]-Loc[0][i-5]<8 && Loc[2][i-5]!=LIM && Loc[2][i-5]-Loc[2][i]>10 )brick_dir=0;
						else brick_dir=255;
					}
					if(stop_brick-start_brick>12)
					{
						break;
					}
				}
				else
				{
					if(stop_brick-start_brick>12)
					{
						break;
					}
					if(stop_brick-start_brick<5)
					{
						start_brick=255;
						brick_dir=255;
					}
				}
			}
			else
			{
				if(stop_brick-start_brick>12)
				{
					break;
				}
				if(stop_brick-start_brick<5)
				{
					start_brick=255;
					brick_dir=255;
				}
			}
			
		}
		if(brick_dir==255)
                {
                  lose_brick++;
                }
		else lose_brick=0;
		if(lose_brick>1)
		{
			RoadType=0;
			lose_brick=0;
                        brick_con=255;
		}
		else
		{
			left_end_line=LIMIT(stop_brick,70,40);
			right_end_line=LIMIT(stop_brick,70,40);
//			end_line=MIN(stop_brick,80);
		}
                if(brick_dir!=255)brick_con=brick_dir;
	}
	
	else if(RoadType==1)
	{
              
		last_y0=255;
		last_y2=255;
		uint8 fl=0,fr=0;
		if(Loc[0][1]>-36 && Loc[2][1]<36)
		{
			for(i=3;i<120;i++)
			{
				
				if(last_y0==255 &&(Loc[0][i]-Loc[0][i-3]<-3||Loc[0][i]==-LIM) && Loc[0][i-3]!=-LIM)
				{
					last_y0=i-3;
				}
				if(fl==0 && last_y0!=255  &&ABS(Loc[0][i]-Loc[0][i+1])<3 && ABS(Loc[0][i+2]-Loc[0][i+3])<2 && Loc[0][i]>-35)
				{
					fl=i+1;
					continue_line_left=i+1;
					insert(0,last_y0,i+1);
//					left_end_line=i+30;
				}
				if(last_y2==255 &&(Loc[2][i]-Loc[2][i-3]>3 ||Loc[2][i]==LIM) && Loc[2][i-3]!=LIM)
				{
					last_y2=i-3;
				}
				if(fr==0 && last_y2!=255  &&ABS(Loc[2][i]-Loc[2][i+1])<3 && ABS(Loc[2][i+2]-Loc[2][i+3])<2 && Loc[2][i]<35)
				{
					fr=i+1;
					continue_line_right=i+1;
					insert(2,last_y2,i+1);
//					right_end_line=i+30;
				}
				if((i>fl+9 && fl!=0) || (i>fr+9&&fr!=0) )
				{
//					end_line=(fl+fr)/2+18;
					break;
				}
			}
		}
		else
		{
			for(i=5;i<120;i++)
			{
				if(fl==0 && ABS(Loc[0][i]-Loc[0][i+2])<=1 && ABS(Loc[0][i+2]-Loc[0][i+4])<=1 && ABS(Loc[0][i+4]-Loc[0][i+6])<=1&& Loc[0][i]>-60)
				{
					fl=i;
					continue_line_left=i+2;
                                        float fit_temp2=0;
                                        fit_temp2=Slope_Calculate_Uint8(continue_line_left,continue_line_left+6,Loc[0]);
                                        for(j=0;j<continue_line_left;j++)
                                        {
                                                Loc[0][j]=Loc[0][continue_line_left]+fit_temp2*(i-continue_line_left);
                                                if(Loc[0][j]>40)
                                                {
                                                        Loc[0][j]=40;
                                                }
                                                else if(Loc[0][j]<-40)
                                                {
                                                        Loc[0][j]=-40;
                                                }
                                        }
//					left_end_line=i+25;
				}
				if(fr==0 && Loc[2][i-5]==LIM && ABS(Loc[2][i]-Loc[2][i+1])<3 && ABS(Loc[2][i+2]-Loc[2][i+3])<2 && Loc[2][i]<35)
				{
					fr=i;
					continue_line_right=i+1;
                                        float fit_temp3=0;
                                        fit_temp3=Slope_Calculate_Uint8(continue_line_right,continue_line_right+6,Loc[2]);
                                        for(j=0;j<continue_line_right;j++)
                                        {
                                                Loc[2][j]=Loc[2][continue_line_right]+fit_temp3*(i-continue_line_right);
                                                if(Loc[2][j]>40)
                                                {
                                                        Loc[2][j]=40;
                                                }
                                                else if(Loc[2][j]<-40)
                                                {
                                                        Loc[2][j]=-40;
                                                }
                                        }
//					right_end_line=i+25;
				}
				if((i>fl+9 && fl!=0) || (i>fr+9&&fr!=0) )
				{
//					end_line=(fl+fr)/2+18;
					break;
				}
			}
		}
	}
        else if(circle_stage==2)
        {
            if(RoadType==3)
            {
                for(i=5;i<right_end_line;i++)
                {
                  if(Loc[2][i+3]>Loc[2][i] && Loc[2][i+4]>Loc[2][i+1] && Loc[2][i]>-18 && Loc[2][i+3]!=LIM)
                  {
                    get_out_of_circle=i;
                    break;
                  }
                }
            }
            else if(RoadType==2)
            {
              for(i=5;i<left_end_line;i++)
              {
                if(Loc[0][i+3]<Loc[0][i] && Loc[0][i+4]<=Loc[0][i+1] && Loc[0][i]<18 && Loc[0][i+3]!=-LIM)
                {
                  get_out_of_circle=i;
                  break;
                }
              }
            }
        }
	//除十字赛道判断有效性
	if(RoadType!=5 /*&& RoadType!=1*/)
	{
		last_y0=4;
		last_y2=4;
		for(i=5;i<110;i++) 
		{
			if(Loc[0][i]!=-LIM && Loc[0][i-2]!=-LIM)
			{
				slope_q[0][i]=(Loc[0][i]-Loc[0][i-2])*100;
			}
			if(Loc[2][i]!=LIM && Loc[2][i+2]!=LIM )
			{
				slope_q[2][i]=(Loc[2][i]-Loc[2][i-2])*100;
			}
//                        if(Loc[0][i]!=-LIM && Loc[0][i-1]!=-LIM && Loc[0][i-2]!=-LIM && Loc[0][i-3]!=-LIM)
//			{
//                          slope_q[0][i]=(Loc[0][i]-Loc[0][i-2]+Loc[0][i-1]-Loc[0][i-3])*100;
//			}
//			if(Loc[2][i]!=LIM && Loc[2][i+1]!=LIM && Loc[2][i+2]!=LIM && Loc[2][i+3]!=LIM)
//			{
//                          slope_q[2][i]=(Loc[2][i]-Loc[2][i-2]+Loc[2][i-1]-Loc[2][i-3])*100;
//			}
			if(Loc[0][i]!=-LIM)
			{
				if(losel==0)
				{
					gapl=0;
					if((Loc[0][i-2]!=-LIM && (ABS(slope_q[0][i]-slope_q[0][i-4])<=300|| slope_q[0][i-4]==255 ||slope_q[0][i]==255) && ABS( Loc[0][i]-Loc[0][i-2])<6)||(Loc[0][i-2]==-LIM && Loc[0][i+2]!=LIM && /*ABS(Loc[0][i+2]-Loc[0][i]-Loc[0][last_y2]+Loc[0][last_y2-2])<=3 && */ABS( Loc[0][i]-Loc[0][last_y0])<=6 && last_y0!=4) ||(Loc[0][i-2]==-LIM  && Loc[0][i]<0 && last_y0==4))
					{
						if((i-last_y0<GAP_THRE - 10 && last_y0!=4) ||(last_y0==4 && i-last_y0<GAP_THRE+15))
						{
							left_end_line=i;
							if(left_head_line==255)left_head_line=i;
							losel=0;
							if(last_y0!=4 && i-last_y0>1)
							{
								insert(0,last_y0,i);
							}
							last_y0=i;
						}
						else
						{
							losel=1;
							Loc[0][i]=-LIM;
						}
					}
					else
					{
						if(i-last_y0>=GAP_THRE)losel=1;
						Loc[0][i]=-LIM;
						
					}
				}
			}
			else 
			{
				gapl++;
			}
			if(Loc[2][i]!=LIM )
			{
				if(loser==0)
				{
					gapr=0;
					if((Loc[2][i-2]!=LIM && (ABS(slope_q[2][i]-slope_q[2][i-4])<=300 || slope_q[2][i-4]==255 ||slope_q[2][i]==255) && ABS( Loc[2][i]-Loc[2][i-2])<6)||(Loc[2][i-2]==LIM && Loc[2][i+2]!=LIM /*&& ABS(Loc[2][i+2]-Loc[2][i]-Loc[2][last_y2]+Loc[2][last_y2-2])<=3 */&&  ABS( Loc[2][i]-Loc[2][last_y2-2])<=6 && last_y2!=4) ||(Loc[2][i-2]==LIM  && Loc[2][i]>0 && last_y2==4))
					{
						if((i-last_y2<GAP_THRE - 10 && last_y2!=4) ||(last_y2==4 && i-last_y2<GAP_THRE+15))
						{
							right_end_line=i;
							if(right_head_line==255)right_head_line=i;
							loser=0;
							if(last_y2!=4 && i-last_y2>1)
							{
								insert(2,last_y2,i);
							}
							last_y2=i;
						}
						else
						{
							loser=1;
							Loc[2][i]=LIM;
						}
					}
					else
					{
						if(i-last_y2>=GAP_THRE)loser=1;
						Loc[2][i]=LIM;
					}
				}
			}
			else
			{
				gapr++;
			}
			if((loser==1 && losel==1) || (gapr>10 && losel==1) || (loser==1 && gapl>10))
			{
				if(last_y2>=last_y0)end_line=last_y2;
				else end_line=last_y0;
				break;
			}
		}
		if(end_line==0)
		{
			if(last_y2>=last_y0)end_line=last_y2;
			else end_line=last_y0;
		}
	}
	if(left_end_line==255)left_end_line=0;
	if(right_end_line==255)right_end_line=0;
        left_end_line=MIN(left_end_line,110);
        right_end_line=MIN(right_end_line,110);
	for(i=left_end_line;i<=MIN(end_line,110);i++)
	{
		Loc[0][i]=-LIM;
	}
	for(i=right_end_line;i<=MIN(end_line,110);i++)
	{
		Loc[2][i]=LIM;
	}
	//================================================================================================================================//
	//特征量计算
	//================================================================================================================================//
	//近行曲率求解       
	for(i=3;i<40;i++)
	{
		if(Loc[0][i]!=-LIM && Loc[0][i-3]!=-LIM)
		{
			//左线曲率
			if(Loc[0][i]==Loc[0][i-3]) str_L1++;          
			else if(Loc[0][i]<Loc[0][i-3])LL1++;
			else LR1++;
		}
		if(Loc[2][i]!=LIM && Loc[2][i-3]!=LIM)
		{
			//右线曲率
			if(Loc[2][i]==Loc[2][i-3]) str_R1++;          
			else if(Loc[2][i]>Loc[2][i-3])RR1++;
			else RL1++;
		}   
	}
	//远行曲率求解       
	for(i=40;i<end_line;i++)
	{
		if(Loc[0][i]!=-LIM && Loc[0][i-3]!=-LIM)
		{
			//左线曲率
			if(Loc[0][i]==Loc[0][i-3]) str_L2++;          
			else if(Loc[0][i]<Loc[0][i-3])LL2++;
			else LR2++;
		}
		if(Loc[2][i]!=LIM && Loc[2][i-3]!=LIM)
		{
			//右线曲率
			if(Loc[2][i]==Loc[2][i-3]) str_R2++;          
			else if(Loc[2][i]>Loc[2][i-3])RR2++;
			else RL2++;
		}   
	}
	//全局斜率曲率求取
	str_L=str_L1+str_L2;  
	str_R=str_R1+str_R2;
	LL=LL1+LL2;
	LR=LR1+LR2;
	RR=RR1+RR2;
	RL=RL1+RL2;
        
        
//================================================================================================================================//
//赛道识别
//================================================================================================================================//
	//左圆环
	uint8 strl_confirm=0;
	strl_confirm=str_confirm(2);
	if((RoadType==0||RoadType==1) && (str_R>43||strl_confirm) && ABS(Loc[2][80]-Loc[2][30])<8 && LL>5 && left_end_line-left_head_line<90)
	{ 
          L0=0,L1=0,R0=0,R1=0;
          for(i=left_head_line;i<left_end_line;i++)
          {
              if(R0==0 && Loc[0][i+2]>Loc[0][i] && Loc[0][i+3]>Loc[0][i+1] && Loc[0][i+4]>Loc[0][i+2])R0=i;
              else if(R0!=0 && R1==0 && Loc[0][i+2]<Loc[0][i])R1=i;
              
              if(L0==0 && Loc[0][i+2]<Loc[0][i] && Loc[0][i+3]<Loc[0][i+1] && Loc[0][i+4]<Loc[0][i+2])L0=i;
              else if(L0!=0 && L1==0 && Loc[0][i+2]>Loc[0][i])L1=i;
          }
          if(L0!=0 && L1==0)L1=left_end_line;
          if(L0>=R1 && R1-R0>3 && L1-L0>12)circle_cnt++;
          else if(L0>=R1 && R1-R0>0 && L1-L0>13 && str_R>55)circle_cnt++;
          else if(left_head_line!=255 && left_end_line-left_head_line>12)
          {
              int near_s=0,far_s=0;
              uint8 temp=0;
              for(i=left_head_line+3;i<left_head_line+11;i++)
              {
                if(slope_q[0][i]!=255)
                {
                  near_s+=slope_q[0][i];
                  temp++;
                }
              }
              if(temp>1)near_s/=temp;
              temp=0;
              for(i=left_end_line;i>left_end_line-8;i--)
              {
                if(slope_q[0][i]!=255)
                {
                  far_s+=slope_q[0][i];
                  temp++;
                }
              }
              if(temp>1)far_s/=temp;
              if(near_s>100 && far_s<-100)circle_cnt++; 
          }	        
	}
        if(circle_cnt>1)
        {
          RoadType=3;
          circle_cnt=0;
        }
	
	
        //右圆环
        uint8 strr_confirm=0;
	strr_confirm=str_confirm(0);
	if((RoadType==0||RoadType==1) &&  (str_L>43||strr_confirm)&& ABS(Loc[0][80]-Loc[0][30])<8 && RR>5 && right_end_line-right_head_line<90)
	{ 
          L0=0,L1=0,R0=0,R1=0;
          for(i=right_head_line;i<right_end_line;i++)
          {
              if(L0==0 && Loc[2][i+2]<Loc[2][i] && Loc[2][i+3]<Loc[2][i+1] && Loc[2][i+4]<Loc[2][i+2])L0=i;
              else if(L0!=0 && L1==0 && Loc[2][i+2]>Loc[2][i])L1=i;
              
              if(R0==0 && Loc[2][i+2]>Loc[2][i] && Loc[2][i+3]>Loc[2][i+1] &&  Loc[2][i+4]>Loc[2][i+2])R0=i;
              else if(R0!=0 && R1==0 && Loc[2][i+2]<Loc[2][i])R1=i;
          }
          if(R0!=0 && R1==0)R1=right_end_line;
          if(R0>=L1 && L1-L0>3 && R1-R0>12)circle_cnt++;
          else if(R0>=L1 && L1-L0>0 && R1-R0>13 && str_L>55)circle_cnt++;
          else if(right_head_line!=255 && right_end_line-right_head_line>12)
          {
              int near_s=0,far_s=0;
              uint8 temp=0;
              for(i=right_head_line+3;i<right_head_line+11;i++)
              {
                if(slope_q[2][i]!=255)
                {
                  near_s+=slope_q[2][i];
                  temp++;
                }
              }
              if(temp>1)near_s/=temp;
              temp=0;
              for(i=right_end_line;i>right_end_line-8;i--)
              {
                if(slope_q[2][i]!=255)
                {
                  far_s+=slope_q[2][i];
                  temp++;
                }
              }
              if(temp>1)far_s/=temp;
              if(near_s>100 && far_s<-100)circle_cnt++; 
          }	        
	}
        if(circle_cnt>1)
        {
          RoadType=2;
          circle_cnt=0;
        }
        //直道
	if(RoadType==0 && str_L>40 && str_R>40)
	{
		RoadType=4;         
	}
	if(RoadType==4)
	{
		if(str_L<25 || str_R<25)
		{
			RoadType=0;
			end_line=70;
		}
	}
        
       
//================================================================================================================================//
//赛道特别处理
//================================================================================================================================//
	//左圆环
        if(RoadType==3)                    
	{
		if(circle_stage==0)
		{
                  
                        if(str_L1>30)RoadType=0;
                        L0=255,L1=255,R0=255,R1=255;
                        for(i=left_head_line;i<60;i++)
                        {
                          if(R0==255 && Loc[0][i+3]>Loc[0][i] && Loc[0][i+4]>Loc[0][i+1]  && Loc[0][i+1]!=-LIM)R0=i;
                          else if(R0!=255 && R1==255 && Loc[0][i+3]<Loc[0][i] && Loc[0][i+4]<Loc[0][i+1])R1=i;
                          
                          if(L0==255 && Loc[0][i+3]<Loc[0][i] && Loc[0][i+4]<Loc[0][i+1] &&Loc[0][i+3]!=-LIM && Loc[0][i+4]!=-LIM)L0=i;
                          else if(L0!=255 && L1==255 && Loc[0][i+4]>Loc[0][i+1] && Loc[0][i+3]>Loc[0][i]  )L1=i;
                        }
                        int temp=-255;
                        for(i=left_head_line+1;i<left_end_line-1;i++)
                        {
                          if(Loc[0][i]>temp)temp=Loc[0][i];
                        }
                        temp--;
                        slope_circuit=0;
                        for(i=left_head_line+1;i<left_end_line-1;i++)
                        {
                          if(ABS(Loc[0][i]-temp)<2)slope_circuit++;
                        }
                        if(turn_flag==0 && left_end_line!=0 &&left_head_line!=255)
			{
                                
				if(left_end_line-left_head_line>63 && str_L>15 && slope_circuit>25 )
                                {
                                  turn_flag=3;
                                  //if(LL2<20)turn_flag=2;
                                }
				//else if(left_end_line-left_head_line>=75)turn_flag=2;
				else if(left_end_line-left_head_line<75 && left_end_line-left_head_line>25 && str_L<19 && slope_circuit<28)
                                {
                                  turn_flag=1;
                                  //if(LL2>25)turn_flag=2;
                                }
                                else if(left_end_line-left_head_line>80)turn_flag=3;
                                else if(left_end_line-left_head_line<60 && left_end_line-left_head_line>25)turn_flag=1;
                                else if(slope_circuit<20)turn_flag=1;
                                else if(slope_circuit>25)turn_flag=3;
                                else  turn_flag=2;  //报警吧
			}
//                        uint8 lr_cont=0;
//                        uint8 lim_cont=0;
//                        for(i=0;i<20;i++)
//                        {
//                            if(Loc[0][i]<Loc[0][i+1])lr_cont++;
//                            if(Loc[0][i]==-LIM)lim_cont++;
//                        }

                        if(wait_time>0)
                        {  
						  uint8 temp=0;
						  if(CarSpeed>2.85)temp=0;
//						  else if(CarSpeed>2.7)temp=2;//+circle_delay;
//						  else if(CarSpeed>2.65)temp=circle_delay;
//						  else if(CarSpeed>2.80)temp=3;
						  else temp=circle_delay;
                          if(wait_time>temp)
                          {
                            circle_stage=1;
                            wait_time=0;
                          }
                          else wait_time++;
                        }
                        else if((R0==255 && L0<20))
			{
                          
                          wait_time++;
                          if(turn_flag==3)
                          {
                            circle_stage=1;
                            wait_time=0;
                          }
			}
//			if(/*LL>6 &&*/ LR1<=2 && lr_cont<=2 && lim_cont<=7 && (left_head_line==255||left_head_line<10))
//			{
//				circle_stage=1;
//			}
                        
		}
		else if(circle_stage==1)
		{
                  	wait_time++;
			if(wait_time>222)wait_time=222;
                        
                        if(left_head_line>20 || left_end_line<15)
                        {
                          for(i=0;i<51;i++)
                          {
                            Loc[0][i]=-17-i;
                          }
                          left_end_line=50;
                        }
                        else if(left_end_line<50)
                        {
                          float slope_temp=0;
                          slope_temp=Loc[0][left_end_line-3]-Loc[0][left_end_line-5]+Loc[0][left_end_line-4]-Loc[0][left_end_line-6];
                          for(i=left_end_line;i<=50;i++)
                          {
                            Loc[0][i]=Loc[0][left_end_line-1]+slope_temp*(i-left_end_line+1)/4;
                            if(Loc[0][i]>0)
                            {
                              Loc[0][i]=0;
                            }
                            else if(Loc[0][i]<-65)
                            {
                              Loc[0][i]=-65;
                            }
                          }
                          left_end_line=50;
                        }
                        
			
			if(((RL1>25 || (RL1>8 && right_head_line==5))&& str_R<10)||wait_time>125)
                        {
                          circle_stage=2;
                          wait_time=0;
                        }
		}
		else if(circle_stage==2) 
		{
			wait_time++;
			if(wait_time>222)wait_time=222;
			//     for(j=59;j>20;j--)
			//     {
			//        if(LMR[2][j]!=80)
			//        {
			//          if(LMR[2][j]>LMR[2][j-2] && LMR[2][j-1]>LMR[2][j-3])left_flag=1;
			//          else if(left_flag==1 && LMR[2][j]<LMR[2][j-2] && LMR[2][j-1]<LMR[2][j-3])
			//          {
			//            ir2=j+2;
			//            break;
			//          }
			//        }
			//     }
			
			if(right_end_line>7)
			{
				for(i=right_head_line;i<right_end_line;i++)
				{
					if(Loc[2][i]>Loc[2][i-2] && Loc[2][i+1]>=Loc[2][i-1])
					{
						right_end_line=i-2;
						end_line=right_end_line;
						break;
					}
				}
				//                          if(i<8)
				//                          {
				//                            for(i=i-2;i<15;i++)
				//                            {
				//                              Loc[2][i]=47-i/2;
				//                            }
				//                            if(right_end_line>29)right_end_line=29;
				//                            end_line=29;
				//                          }                                                               
			}
//			uint8 j,left_flag=0,ir2=60;
//			ir=60;
//			for(j=59;j>20;j--)
//			{
//				if(LMR[2][j]!=80)
//				{
//					if(LMR[2][j]>LMR[2][j-2] && LMR[2][j-1]>LMR[2][j-3])left_flag=1;
//					else if(left_flag==1 && LMR[2][j]<LMR[2][j-2] && LMR[2][j-1]<LMR[2][j-3])
//					{
//						ir2=j+2;
//						break;
//					}
//				}
//			}
//			if(ir2>23 && ir2<45 && LMR[2][ir2]>8)
//			{
//				circle_stage=3;
//				wait_time=0;
//			}
            uint8 temp=0;
			if(turn_flag>1)temp=5;
			if(((get_out_of_circle <20 + temp && get_out_of_circle >5) /*|| right_end_line<7*/) && wait_time>50  )
			{
				circle_stage=3;
				wait_time=0;
			}
		}
		else if(circle_stage==3)
		{
                        wait_time++;
			if(wait_time>222)wait_time=222;
			search_end_line = 30;
			if(left_head_line>15 || left_end_line<15)
			{
                                uint8 temp=0;
                                if(turn_flag==1)temp=5;
				for(i=0;i<51;i++)
				{
					Loc[0][i]=-16-i-temp;
				}
				left_end_line=50;
			}
			else if(left_end_line<50)
			{
				float slope_temp=0;
				slope_temp=Loc[0][left_end_line-3]-Loc[0][left_end_line-5]+Loc[0][left_end_line-4]-Loc[0][left_end_line-6];
				for(i=left_end_line;i<=50;i++)
				{
					Loc[0][i]=Loc[0][left_end_line-1]+slope_temp*(i-left_end_line+1)/4;
					if(Loc[0][i]>0)
					{
						Loc[0][i]=0;
					}
					else if(Loc[0][i]<-65)
					{
						Loc[0][i]=-65;
					}
				}
                                left_end_line=50;
			}
			if((str_R>16 || (right_end_line-right_head_line>60 && right_head_line!=255 && right_end_line!=255))&& wait_time>4)
			{
				circle_stage=4;
                                wait_time=0;
			}
		}
                
		else if(circle_stage==4)
		{
                  wait_time++;
                  if(str_L>20 || wait_time>=40)
                  {
                    RoadType=0;
                    circle_stage=0;
                    turn_flag=0;
                    wait_time=0;
                  }
		}
	}
        //右圆环
        else if(RoadType==2)                    
	{
		if(circle_stage==0)
		{
                        if(str_R1>30)RoadType=0;
                        L0=255,L1=255,R0=255,R1=255;
                        for(i=right_head_line;i<60;i++)
                        {
                          if(L0==255 && Loc[2][i+3]<Loc[2][i] && Loc[2][i+4]<Loc[2][i+1] && Loc[2][i+1]!=LIM)L0=i;
                          else if(L0!=255 && L1==255 && Loc[2][i+3]>Loc[2][i] && Loc[2][i+4]>Loc[2][i+1])L1=i;
                          
                          if(R0==255 && Loc[2][i+3]>Loc[2][i] && Loc[2][i+4]>Loc[2][i+1] &&  Loc[2][i+4]!=LIM &&  Loc[2][i+3]!=LIM)R0=i;
                          else if(R0!=255 && R1==255 && Loc[2][i+3]<Loc[2][i] && Loc[2][i+4]<Loc[2][i+1])R1=i;
                        }
                        
                        int temp=255;
                        for(i=right_head_line+1;i<right_end_line-1;i++)
                        {
                          if(Loc[2][i]<temp)temp=Loc[2][i];
                        }
                        temp++;
                        slope_circuit=0;
                        for(i=right_head_line+1;i<right_end_line-1;i++)
                        {
                          if(ABS(Loc[2][i]-temp)<2)slope_circuit++;
                        }
                        
                        if(turn_flag==0 && right_end_line!=0 &&right_head_line!=255)
			{
                                
				if(right_end_line-right_head_line>63 && str_R>15 && slope_circuit>25 )
                                {
                                  turn_flag=3;
                                  //if(LL2<20)turn_flag=2;
                                }
				//else if(left_end_line-left_head_line>=75)turn_flag=2;
				else if(right_end_line-right_head_line<75 && right_end_line-right_head_line>25 && str_R<19 && slope_circuit<28)
                                {
                                  turn_flag=1;
                                  //if(LL2>25)turn_flag=2;
                                }
                                else if(right_end_line-right_head_line>80)turn_flag=3;
                                else if(right_end_line-right_head_line<60 && right_end_line-right_head_line>25)turn_flag=1;
                                else if(slope_circuit<20)turn_flag=1;
                                else if(slope_circuit>25)turn_flag=3;
                                else  turn_flag=2;  //报警吧
			}
                        if(wait_time>0)
                        {
						  uint8 temp=0;
						  if(CarSpeed>2.85 )temp=0;
//						  else if(CarSpeed>2.7)temp=1;
//						  else if(CarSpeed>2.65)temp=circle_delay;
//						  else if(CarSpeed>2.80)temp=3;
						  else temp=circle_delay;
						  
                          if(wait_time>temp)
                          {
                            circle_stage=1;
                            wait_time=0;
                          }
                          else wait_time++;
                        }
                        else if((L0==255 && R0<20))
			{
                          
                          wait_time++;
                          if(turn_flag>1)
                          {
                            circle_stage=1;
                            wait_time=0;
                          }
			}
		}
		if(circle_stage==1)
		{
                        wait_time++;
			if(wait_time>222)wait_time=222;
			if(right_head_line==255 || right_end_line<15)
			{
				for(i=0;i<51;i++)
				{
					Loc[2][i]=17+i;
				}
				right_end_line=50; 
			}
			else if(right_end_line<50)
			{
				float slope_temp=0;
				slope_temp=Loc[2][right_end_line-3]-Loc[2][right_end_line-5]+Loc[2][right_end_line-4]-Loc[2][right_end_line-6];
				for(i=right_end_line;i<=50;i++)
				{
					Loc[2][i]=Loc[2][right_end_line-1]+slope_temp*(i-right_end_line+1)/4;
					if(Loc[2][i]<0)
					{
						Loc[2][i]=0;
					}
					else if(Loc[2][i]>65)
					{
						Loc[2][i]=65;
					}
				}
                                right_end_line=50;
			}
			
			if(((LR1>25 || (LR1>8 && left_head_line==5))&& str_L<10)||wait_time>125)                       
                        {
                          circle_stage=2;
                          wait_time=0;
                        }
		}
		else if(circle_stage==2) 
		{
                        wait_time++;
                        if(wait_time>222)wait_time=222;
                        if(left_end_line>7)
                        {
                          for(i=left_head_line;i<left_end_line;i++)
                          {
                            if(Loc[0][i]<Loc[0][i-2] && Loc[0][i+1]<=Loc[0][i-1])
                            {
                              left_end_line=i-2;
                              end_line=left_end_line;
                              break;
                            }
                          }
                        }
                        uint8 temp=0;
			if(turn_flag>1)temp=5;
			if(((get_out_of_circle <20+temp  && get_out_of_circle >5) /*|| right_end_line<6*/) && wait_time>50 )
                        {
                          circle_stage=3;
                          wait_time=0;
                        }
		}
		else if(circle_stage==3)
		{
                        wait_time++;
			if(wait_time>222)wait_time=222;
			search_end_line = 30;
                        if(right_head_line==255 || right_end_line<15)
			{
                                uint8 temp=0;
                                if(turn_flag==1)temp=5;
				for(i=0;i<51;i++)
				{
					Loc[2][i]=16+i+temp;
				}
				right_end_line=50;
			}
			else if(right_end_line<50)
			{
				float slope_temp=0;
				slope_temp=Loc[2][right_end_line-3]-Loc[2][right_end_line-5]+Loc[2][right_end_line-4]-Loc[2][right_end_line-6];
				for(i=right_end_line;i<=50;i++)
				{
					Loc[2][i]=Loc[2][right_end_line-1]+slope_temp*(i-right_end_line+1)/4;
					if(Loc[2][i]<0)
					{
						Loc[2][i]=0;
					}
					else if(Loc[2][i]>65)
					{
						Loc[2][i]=65;
					}
				}
                                right_end_line=50;
			}
			if((str_L>16 || (left_end_line-left_head_line>60 && left_head_line!=255 && left_end_line!=255))&& wait_time>4)
			{
				circle_stage=4;
                                wait_time=0;
			}
		}
                
		else if(circle_stage==4)
		{
                  wait_time++;
                  if(str_R>20 || wait_time>=40)
                  {
                    RoadType=0;
                    circle_stage=0;
                    turn_flag=0;
                    wait_time=0;
                  }
		}
	}
	else if(RoadType==0)          //补充斜入十字的情况
        {
          uint8 il=LIM,ir=LIM;
          
          il=break_point_find(Loc[0]);
          if(il!=LIM && il>13)
          {
             float flope_temp;
             flope_temp=Slope_Calculate_Uint8(il-13,il-3,Loc[0]);
             for(i=il-2;i<=60;i++)
             {
               Loc[0][i]=Loc[0][il-3]+flope_temp*(i-il+3);
               if(Loc[0][i]>40)
               {
                 Loc[0][i]=40;
                 break;
               }
               else if(Loc[0][i]<-40)
               {
                 Loc[0][i]=-40;
                 break;
               }
             }
          }
          
          ir=break_point_find(Loc[2]);
          if(ir!=LIM && ir>13)
          {
             float flope_temp;
             flope_temp=Slope_Calculate_Uint8(ir-13,ir-3,Loc[2]);
             for(i=ir-2;i<=60;i++)
             {
               Loc[2][i]=Loc[2][ir-3]+flope_temp*(i-ir+3);
               if(Loc[2][i]>40)
               {
                 Loc[2][i]=40;
                 break;
               }
               else if(Loc[2][i]<-40)
               {
                 Loc[2][i]=-40;
                 break;
               }
             }
          }       
        }
        	
//================================================================================================================================//
//中线提取
//================================================================================================================================//
	
	if( RoadType==3)
	{
          if(circle_stage==1)
          {
            for(i=0; i<left_end_line;i++)
            {
              if(turn_flag==1)Loc[1][i]=Loc[0][i]+20;
              else if(turn_flag==3)Loc[1][i]=Loc[0][i]+24;
              else Loc[1][i]=Loc[0][i]+20;
              
            }
            end_line=left_end_line-1;
          }
          else if(circle_stage==3)
          {
            if(left_end_line>1)
            {
              for(i=0; i<left_end_line;i++)
              {
                Loc[1][i]=Loc[0][i]+20;
              }
              end_line=left_end_line-1;
            }
            else
              end_line=0;
          }
          else if(circle_stage==2)
          {
              uint8 temp=0;
              if(turn_flag==1)
              {
                if(wait_time<15)temp=13;
                else temp=7;
              }
              for(i=0; i<right_end_line;i++)
              {
                Loc[1][i]=Loc[2][i]-half;
              }
              end_line=right_end_line-1;
          }
          else if(circle_stage==0 )
          {
            if(right_end_line>1)
            {
              for(i=0; i<right_end_line;i++)
              {
                Loc[1][i]=Loc[2][i]-half;
              }
              end_line=right_end_line-1;
            }
            else
              end_line=0;
          }
          else if(circle_stage==4 )
          {
            for(i=0; i<right_end_line;i++)
            {
              Loc[1][i]=Loc[2][i]-17;
            }
            end_line=right_end_line-1;
          }
	}
        else if(RoadType==2)
	{
          if(circle_stage==1)
          {
            for(i=0; i<right_end_line;i++)
            {
              if(turn_flag==1)Loc[1][i]=Loc[2][i]-20;
              else if(turn_flag==3)Loc[1][i]=Loc[2][i]-24;
              else Loc[1][i]=Loc[2][i]-20;
              
            }
            end_line=right_end_line-1;
          }
          else if(circle_stage==3)
          {
            if(right_end_line>1)
            {
              for(i=0; i<right_end_line;i++)
              {
                Loc[1][i]=Loc[2][i]-20;
              }
              end_line=right_end_line-1;
            }
            else
              end_line=0;
          }
          else if(circle_stage==2)
          {
              uint8 temp=0;
              if(turn_flag==1)
              {
                if(wait_time<15)temp=13;
                else temp=7;
              }
              for(i=0; i<left_end_line;i++)
              {
                Loc[1][i]=Loc[0][i]+half;
              }
              end_line=left_end_line-1;
          }
          else if(circle_stage==0 )
          {
            if(left_end_line>1)
            {
              for(i=0; i<left_end_line;i++)
              {
                Loc[1][i]=Loc[0][i]+half;
              }
              end_line=left_end_line-1;
            }
            else
              end_line=0;
          }
          else if(circle_stage==4 )
          {
            for(i=0; i<left_end_line;i++)
            {
              Loc[1][i]=Loc[0][i]+17;
            }
            end_line=left_end_line-1;
          }
	}
        
	else if(RoadType==5)
	{
		if(brick_con==0)
		{
			for(i=0;i<left_end_line;i++)
			{
                          if(Loc[0][i]!=-LIM)
				Loc[1][i]=Loc[0][i]+13;
                          else 
                                Loc[1][i]=0;
			}   
			end_line=left_end_line-1;
		}
		else if(brick_con==1)
		{
			for(i=0;i<right_end_line;i++)
			{
                          if(Loc[2][i]!=LIM)
				Loc[1][i]=Loc[2][i]-13;
                          else 
                            Loc[1][i]=0;
			}   
			end_line=right_end_line-1;
		}
		else
		{
			for(i=0;i<=60;i++)
			{
				Loc[1][i]=0;
			}
			end_line=60;
		}
	}
	else if(RoadType==1)
	{
		
		for(i=0;i<end_line;i++)
		{ 
			//左右线
			if(Loc[0][i]!=-255 && Loc[2][i]!=255)
			{
				Loc[1][i]=(Loc[0][i]+Loc[2][i])/2;
			}
			else if(Loc[0][i]!=-255)
			{
				Loc[1][i]=Loc[0][i]+half;
			}
			else if(Loc[2][i]!=255)
			{
				Loc[1][i]=Loc[2][i]-half;
			}
			else
			{
				Loc[1][i]=0;
			}
			if(Loc[1][i]>LIM)
			{
				Loc[1][i]=LIM;
				end_line=i-1;
				break;
			}
			if(Loc[1][i]<-LIM)
			{
				Loc[1][i]=-LIM;
				end_line=i-1;
				break;
			}
			if(i>5)
			{
				if(ABS(Loc[1][i]-Loc[1][i-1])>7 && left_end_line>i && right_end_line>i)
				{
					end_line=i-2;
				}
				else if(ABS(Loc[1][i]-Loc[1][i-2]-Loc[1][i-2]+Loc[1][i-4])>8)
				{
					end_line=i-4;
				}
			}
		}
		if(end_line<45)
		{
			if(end_line>10)
			{
				flope_temp=Slope_Calculate_Uint8(end_line-11,end_line-1,Loc[1]);
				for(i=end_line;i<=60;i++)
				{
					Loc[1][i]=Loc[1][end_line-1]+flope_temp*(i-end_line+1);
					if(Loc[1][i]>60)
					{
						Loc[1][i]=60;
						break;
					}
					else if(Loc[1][i]<-60)
					{
						Loc[1][i]=-60;
						break;
					}
				}
				if(i<60)end_line=i;
		        else end_line=60;
			}
			else
			{
				for(i=end_line;i<=40;i++)
				{
					Loc[1][i]=0;
				}
				if(i<40)end_line=i;
		        else end_line=40;
			}
		}
	}
	else
	{
		//   if(left_end_line>50)
		//   {
		//    if(left_end_line>70)line1=70;
		//    else line1=left_end_line;
		//    for(i=line1;i>line1-10;i--)
		//    {  
		//        if(slope_q[0][i]>=500)
		//        {
		//          con2++;   
		//        }
		//    }
		//    for(i=4;i<40;i++)
		//    {
		//     if(ABS(slope_q[0][i])<300 &&slope_q[0][i]!=255 )con1++;
		//    }
		//    if(con1>10 && con2>3 && RoadType==0)ruwan_flag=1;
		//    if(ruwan_flag==1 &&( con1<3 || con2<2 || RoadType!=0))ruwan_flag=0;
		//   }
		
		if(ruwan_flag==1)
		{
			for(i=0;i<left_end_line;i++) 
				Loc[1][i]=Loc[0][i]+10;
		}
		else 
		{
			for(i=0;i<end_line;i++)
			{ 
				//左右线
				if(Loc[0][i]!=-255 && Loc[2][i]!=255)
				{
					Loc[1][i]=(Loc[0][i]+Loc[2][i])/2;
				}
				else if(Loc[0][i]!=-255)
				{
                                  //
                                  if(i==0)Loc[1][i]=Loc[0][i]+half;
                                  else
                                  {
                                    if(Loc[0][i-1]!=-LIM)
                                      Loc[1][i]=Loc[0][i]-Loc[0][i-1]+Loc[1][i-1];
                                    else
                                      Loc[1][i]=Loc[0][i]+half;
                                  }
				}
				else if(Loc[2][i]!=255)
				{
                                  //	
                                  if(i==0)Loc[1][i]=Loc[2][i]-half;
                                  else
                                  {
                                    if(Loc[2][i-1]!=LIM)
                                      Loc[1][i]=Loc[2][i]-Loc[2][i-1]+Loc[1][i-1];
                                    else
                                      Loc[1][i]=Loc[2][i]-half;
                                  }
				}
				else 
				{
					Loc[1][i]=0;
				}
				if(Loc[1][i]>LIM)
				{
					Loc[1][i]=LIM;
					end_line=i;
					break;
				}
				if(Loc[1][i]<-LIM)
				{
					Loc[1][i]=-LIM;
					end_line=i;
					break;
				}
//				if(i>5)
//				{
//					if(ABS(Loc[1][i]-Loc[1][i-1])>20)
//					{
//						end_line=i-2;
//					}
////					else if(ABS(Loc[1][i]-Loc[1][i-2]-Loc[1][i-2]+Loc[1][i-4])>15)
////					{
////						end_line=i-4;
////					}
//				}
			}
		}
                for(i=2;i<=end_line;i++)
                {
                    if(ABS(Loc[1][i-1]-Loc[1][i])>20)
                    {
                      end_line=i-1;
                      break;
                    }
                    else if(ABS(Loc[1][i+3]-Loc[1][i+1]-Loc[1][i+2]+Loc[1][i])>=400)
                    {
                      end_line=i;
                      break;
                    }
                    else if(Loc[2][i]-Loc[0][i]<5)
                    {
                      end_line=i;
                      break;
                    }
                }
	}
        flope_temp=0;
	for(i=59;i>50;i--)
	{
		Black_record[i-50]=(LMR[0][i]+LMR[2][i])/2;
	}
	if(end_line<60 && end_line>10 && RoadType!=1 && !(left_end_line>10 && right_end_line>10 && end_line<30))
	{
//                uint8 temp=0;
//                for(i=0;i<end_line;i++)
//                {
//                  if(ABS(Loc[1][i])<7 && abs(Loc[1][i+1]-Loc[1][i+1])<2)temp++;
//                }
//                if(temp<5)
//                {
                  fix_flag=1;
                  flope_temp=Slope_Calculate_Uint8(end_line-11,end_line-1,Loc[1]);
                  for(i=end_line;i<=70;i++)
                  {
                    Loc[1][i]=Loc[1][end_line-1]+flope_temp*(i-end_line+1);
                    if(Loc[1][i]>60)
                    {
                      Loc[1][i]=60;
                      break;
                    }
                    else if(Loc[1][i]<-60)
                    {
                      Loc[1][i]=-60;
                      break;
                    }
                  }
                  if(i<70)end_line=i;
                  else end_line=70;
//                }
	}
        for(i=4;i<end_line;i++)
        {
			if(Loc[1][i] != LIM && Loc[1][i-3] != LIM && Loc[1][i-2] != LIM && Loc[1][i-1] != LIM)
			{
				slope_q[1][i]=(Loc[1][i]-Loc[1][i-2]+Loc[1][i-1]-Loc[1][i-3])*100;
			}
			else
			{
				slope_q[1][i] = LIM;
			}
        }

	//================================================================================================================================//
	//控制行
	//================================================================================================================================//
	uint8 temp2=0;
        uint8 line_c;
	if(CarSpeed < 1.8)
	{
		line = bais;
	}
	else if(CarSpeed < 2.5)
	{
		line = bais + (CarSpeed - 1.8) * 18;
	}
	else if(CarSpeed < 3.3)
	{
		line = bais + 13 + (CarSpeed - 2.5) * 20;
	}
	else
	{
		line = bais + 29 + (CarSpeed - 3.3) * 15;
	}
	
	line_c = line + 30;
	if(line>=end_line-3)line=end_line-3;
	if(RoadType==1)
	{
		if(line<continue_line_left)line=continue_line_left;
		if(line<continue_line_right)line=continue_line_right;
	}
	
	if(line_c>=end_line-3)line_c=end_line-3;
	if(RoadType==1)
	{
		if(line_c<continue_line_left)line_c=continue_line_left;
		if(line_c<continue_line_right)line_c=continue_line_right;
	}
	
	control_line_far = line;
	control_line_near = 18 + (int)(CarSpeed * 2.5);
        if(control_line_near > end_line-3)control_line_near=end_line-3;
        

        
        //舵机偏差
        temp2 = 0;
        if(end_line>6 && end_line<130 && control_line_far >= 5 && control_line_near >=5)
        {
                temp2 = 0;
                //FAR分量
                for(i = control_line_far - 8; i < control_line_far; i++)
                {
                        if(Loc[1][i] != LIM)
                        {
                                Middle_Err_Sum_Far += Loc[1][i];
                                temp2++;
                        }
                }
                if(temp2 != 0)
                        Middle_Err_Sum_Far /= temp2;
                //NEAR分量
                
                temp2=0;
                for(i = control_line_near - 6; i < control_line_near; i++)
                {
                        if(Loc[1][i] != LIM)
                        {
                                Middle_Err_Sum_Near += Loc[1][i];
                                temp2++;
                        }
                }
                if(temp2 != 0)
                        Middle_Err_Sum_Near /= temp2;
                
                int Err_temp;
                Err_temp = (Middle_Err_Sum_Far) * 50 / MAX(1,(control_line_far-10));
                Err_temp = LIMIT(Err_temp,79,-79);
                
                if(Err_temp >= 0)
                {
                        Middle_Err_Sum_Far = ARCTANG[Err_temp]*1.0/100;
                }
                else
                {
                        Middle_Err_Sum_Far = - ARCTANG[-Err_temp]*1.0/100;
                }
                
                
                Err_temp = (Middle_Err_Sum_Near) * 50 / (control_line_near-0);
                Err_temp = LIMIT(Err_temp,79,-79);
                if(Err_temp >= 0)
                {
                        Middle_Err_Sum_Near = ARCTANG[Err_temp]*1.0/100;
                }
                else
                {
                        Middle_Err_Sum_Near = - ARCTANG[-Err_temp]*1.0/100;
                }
                Middle_Err=(7*Middle_Err_Sum_Far+3*Middle_Err_Sum_Near)/10;
        }
        else
        {
        
        }
/******************************************************************/
                                                                                                                                /**/
        temp2 = 0;
        int DeviFar=0;
        for(i = line_c - 8; i < line_c; i++)
        {
                if(Loc[1][i] != LIM)
                {
                        DeviFar += Loc[1][i];
                        temp2++;
                }
        }
        if(temp2 != 0)
                DeviFar /= temp2;
        
        DeviFar = (DeviFar) * 50 / MAX(10,(line_c - 10));
        DeviFar = LIMIT(DeviFar,79,-79);
        
        if(DeviFar >= 0)
        {
                DeviFar = ARCTANG[DeviFar]/100.0;
        }
        else
        {
                DeviFar = ARCTANG[-DeviFar]/100.0;
        }
        SpeedDevi = (ABS(DeviFar) * 5 + ABS(Middle_Err_Sum_Near) * 5)/10;

        if(circle_stage==1||circle_stage==3)
        {
          if(turn_flag==3)
          {
            if(RoadType==3 && Middle_Err>-5)Middle_Err=-5;
            if(RoadType==2 && Middle_Err<5)Middle_Err=5;
          }
          else if(turn_flag==2)
          {
            if(RoadType==3 && Middle_Err>-8)Middle_Err=-8;
            if(RoadType==2 && Middle_Err<8)Middle_Err=8;
          }
           else if(turn_flag==1)
          {
            if(RoadType==3 && Middle_Err>-46)Middle_Err=-46;
            if(RoadType==2 && Middle_Err<46)Middle_Err=46;
          }
        }
        if(circle_stage==2)
        {
          if(turn_flag==1)
          {
            if(RoadType==3 && Middle_Err>-35)Middle_Err=-35;
            if(RoadType==2 && Middle_Err<35)Middle_Err=35;
          }
        }
	
	if(search_time%2==0)
	{
          Middle_Err = Middle_Err * 0.7 + Previous_Error[0] * 0.2+ Previous_Error[1] * 0.1;
          Push_And_Pull(Previous_Error,20,Middle_Err);
          Delt_error=-10*Slope_Calculate(0,5,Previous_Error);
	}
        if(search_time%2==0)
	{
//          SpeedDevi=ABS(Middle_Err);
		SpeedDevi = SpeedDevi * 0.7 + SpeedDevi_His[0] * 0.2 + SpeedDevi_His[0] * 0.1;
          Push_And_Pull(SpeedDevi_His,ARR_SIZE(SpeedDevi_His),SpeedDevi);
          SpeedDeviD = Slope_Calculate(0,10,SpeedDevi_His);
	}
	
        
	Err_Fuzzy();
}