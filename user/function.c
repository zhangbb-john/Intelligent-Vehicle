#include "common.h"
#include "include.h"

float h[3][3]=
{4.6,      0,      -186.3,
        0,      -4.45,     275,
        0,      0.12,     0.6};
int map[60][80];
//配置中断复位函数

void PORTC_IRQHandler();
void DMA0_IRQHandler();
void PIT_IRQHandler();
void map_init();

void map_init()
{
  float s;
  float x;
  float xx,yy,deltax,deltay;
  uint8 col,row;
  for(row=0;row<60;row++)
  {
    for(col=0;col<80;col++)
    {
      xx = col - 39.5;
      yy = 29.5 - row;
      deltax = (xx*xx+yy*yy)*xx/100000;
      deltay = (xx*xx+yy*yy)*yy/100000;
      s=h[2][0] * (col + deltax) + h[2][1] * row + h[2][2];
      x=h[0][0] * (col + deltax) + h[0][1] * row + h[0][2];
      x=x/s;
      map[row][col]=(int)(x+0.5);
    }
  }
}

void Para_Init()
{
  	Stop=1;
	map_init();
	PID_SPEED.P=0.50;
	PID_SPEED.I=0.012;
	PID_SPEED.D=0.033;
	PID_TURN.P=0.0130;//0.0126;
	PID_TURN.D=-0.006;//-0.005;
	Fuzzy_Kp=0.0005;
	Fuzzy_Kd=0.0004;
	SetSpeed=3.2;
	Set_Angle=50;
	bais=40;//22;
	wk = 0.1;          //targetspeed-wk*level;
	wk1=0.02;  //出圆环速度减
	circle_delay=4;
	rit_correction = 0.99;
	circle_speed=0;  //入圆环速度减
	brick_speed=0.05;
	wk2 =0;
	Control_Para[0]=SetSpeed;
	Control_Para[1]=thresh;
	Control_Para[2]=bais;
	Control_Para[3]=PID_SPEED.P;
	Control_Para[4]=PID_SPEED.I;
	Control_Para[5]=PID_TURN.P;
	Control_Para[6]=PID_TURN.D;
	Control_Para1[0]=wk;
	Control_Para1[1]=circle_delay;
	Control_Para1[2]=circle_speed;
	Control_Para1[3]=rit_correction;
	Control_Para1[4]=brick_speed;
	Control_Para1[5]=wk1;
	Control_Para1[6]=wk2;
}


float Slope_Calculate(uint8 begin,uint8 end,float *p)    //最小二乘法拟合斜率
{
	float xsum=0,ysum=0,xysum=0,x2sum=0;
	uint8 i=0;
	float result=0;
//	static float resultlast;
	p=p+begin;
	for(i=begin;i<end;i++)
	{
		xsum+=i;
		ysum+=*p;
		xysum+=i*(*p);
		x2sum+=i*i;
		p=p+1;
	}
	if((end-begin)*x2sum-xsum*xsum) //判断除数是否为零 (begin = 0的情况下永远都不可能是0)
	{
		result=((end-begin)*xysum-xsum*ysum)/((end-begin)*x2sum-xsum*xsum);
//		resultlast=result;
	}
	else
	{
		result = 0;
//		result=resultlast;
	}
	return result;
}
