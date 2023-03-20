#include "include.h"
//��������

float deltaSpeedTarget[7] = {
//	-0.4,	0.3,	0.3,	0.4,	0.4,	0.4,	0.4
	-0.7,	-0.8,	0.7,	0.7,	0.7,	0.7,	0.6
//	-0.3,	-0.05,	0.2,	0.30,	0.35,	0.40,	0.40
	//
};
float deltaKp[5] = {
	1.5,1.3,0.9,0.8,0.8 	// xx%    2 4 6 9 -
};
float deltaServoKp[7] = {
//                  0.5,1.1,1.1,1.2,1.2,1,1
                  0.5,0.7,0.9,1.2,1.3,1,1
//                  0.55,0.70,0.83,1.2,1.1,1.0,0.9
	//0~10	20~50	50~80	80~110	110~140	140~170	170~100000000
};

float deltaServoDout[7] = {
	0.9,	0.9,	0.9,	0.9,	0.9,	0.9
	//0~20	20~50	50~80	80~110	110~140	140~170	170~100000000
};
float deltaServoDback[6] = {
	1.3 ,1.3,	1.3,	1.3,	1.3,	1.3
//        1,	1.01,	1.05,	1.05,	1.06,	1.07
};

uint8 take_off=0;
int errGrade,errFu;
int sDGrade,sDFu;
//�ٶ������
float temp;
float SpeedControlOutNew;
float SpeedControlOutOld;
float SpeedControlIntegral=0,Hill_Slow_Ratio;
uint8  Set_Angle;   //����ǰ��Ƕ�
int   SpeedCount;
int   Speed_Filter_Times=2;    //�ٶ�ƽ�����
float CarSpeed=0,ControlSpeed=0,AverageSpeed,SetSpeed=0,Distance=0;
float CarAcce = 0;
float CarSpeedQueue[6] = {0};
//���������
float DirectionControlOutNew;
float DirectionControlOutOld;
float Turn_Speed=0;
int   DirectionCount;
float Delt_error,Middle_Err;
int Err_Slope_mul50;
float SpeedDevi,SpeedDeviD;
int DeviFar,DeviNear;
float Turn_Out=0;
float Turn_Angle_Integral;
/**������**/
int sever_middle=1780;
int sever_range=260;
//ģ����ϵ��
float  Delta_P;
float  Delta_D;
float  Fuzzy_Kp;
float  Fuzzy_Kd;
uint8 devi_level;
//PID���������
PID PID_SPEED,PID_TURN;

float  MotorOut;   //��������          
uint8   Starting,Stop;
uint8 Encoder_Disable=0;
/*float P_adjust[]={0,0.015,-0.02,0.15,
0.015,0.015,0,0.0                    };     //+jiansu*/
float P_adjust[]={0,-0.012,-0.013,-0.016,
0.055,0.045,0.04,0.0                    };     //+jiansu
float D_adjust[]={0,0.01,-0.007,0,
0,0.01,0,0                    };           //+jiansu
int level=0;
int qd1_result;

void Get_Speed()                     //5msִ��һ��
{  
	static float Speed0 = 0,Speed1 = 0,Speed2 = 0,Speed3 = 0;
	qd1_result =- FTM_AB_Get(FTM2);
	
	Distance += qd1_result/12400.0;  //ת��Ϊ����                      1m3100������
	CarSpeed = qd1_result*250.0/3100/8/1.2;    //�������ת��ΪM/S         1000�����ڣ�250 ��Ӧ4ms
	Speed3 = Speed2;Speed2 = Speed1;Speed1 = Speed0;Speed0 = CarSpeed;
	CarSpeed = (Speed0 + Speed1 + Speed2 + Speed3)/4;
//	if(CarSpeed > 10)Stop=1;
}
float SpeedSpecialDeal(float oriSpeed)
{
  
         if(Stop==1)
        {
           return 0;
        }
         else if(RoadType==4)
         {
           return 3.6-level*0.2+wk2;
         }
         else if(RoadType==5)
        {
          return oriSpeed-0.3-brick_speed-level*0.15;
        }
        else if((RoadType==3 || RoadType==2)&& circle_stage==0)
        {
          if(turn_flag==3)return 2.95-level*0.15;
          else if(turn_flag==1)return 2.45-circle_speed;
          else return 2.8-level*0.15;
        }
		else if((RoadType==3 || RoadType==2)&& circle_stage==1)
		{
			if(turn_flag==3)return oriSpeed-0.1-level*0.15;
			else if(turn_flag==1)return oriSpeed-0.1-level*0.15;
			else return oriSpeed-0.1-level*0.15;
		}
        else if((RoadType==3 || RoadType==2)&& circle_stage==2)
        {
          if(turn_flag==3)return oriSpeed+0.3-level*0.15;
          else if(turn_flag==2)return oriSpeed-level*0.15;
          else return oriSpeed-0.35-level*0.15;      //0.2
        }
        else if((RoadType==3 || RoadType==2)&& circle_stage==3)
        {
			if(turn_flag==3)return oriSpeed-level*0.15;
			else if(turn_flag==2)return oriSpeed-level*0.15;
			else return oriSpeed-0.15-wk1-level*0.15;
        }
	else if(CarSpeed>2.8 && (left_end_line<50 ||left_end_line==255||right_end_line==255||right_end_line<50))
                        return 3;

        
	return oriSpeed;
}
float speedTarget;
int SpeedE,SpeedI = 0,SpeedD;
float Speed_kP,Speed_kI,Speed_kD;
//static int PreErr[20] = {0};
void Speed_Control(void)
{
	int i;	
	//�õ�Ŀ���ٶ�
	speedTarget = SetSpeed - (sDFu * deltaSpeedTarget[sDGrade+1] + (1000-sDFu) * deltaSpeedTarget[sDGrade])/1000-wk*level;
	//Ŀ���ٶȵ����⴦��
	speedTarget = SpeedSpecialDeal(speedTarget);
	///////////////////////////////////////////////
	//PID�㷨��ʼ
	///////////////////////////////////////////////
	//P����
	SpeedE = (int)((speedTarget - CarSpeed)*100.0);
	uint16 temp = ABS(SpeedE);
	//kp
	Speed_kP = PID_SPEED.P-0.15*level;
	if((RoadType==3 || RoadType==2)&& circle_stage==0)              //kkkk
	{
		SpeedE=SpeedE*4;
	}

	
	//I����
	if(Stop == 0)
	{
		if(ABS(SpeedE) < 300)
		{
			SpeedI += SpeedE;
		}
	}
	//SpeedI�޷�
	if(SpeedI > 800) SpeedI = 800;
	else if(SpeedI < -700) SpeedI = -700;
	//ki
	Speed_kI = PID_SPEED.I;
	
	//D����������Delt_Err����
	SpeedD = (int)(SpeedDeviD*100);
	Speed_kD = PID_SPEED.D;
  
	SpeedControlOutOld=SpeedControlOutNew;
	SpeedControlOutNew=(Speed_kP*SpeedE + Speed_kI*SpeedI + Speed_kD*SpeedD +  8)/100.0;
}
//�ٶȿ���
void Speed_Control_Output(void) //2ms����һ��
{
	float fValue; 
	fValue = SpeedControlOutNew - SpeedControlOutOld; 
	PID_SPEED.OUT = fValue * (SpeedCount+1)/Speed_Filter_Times+SpeedControlOutOld;  
}
void Direction_SpecialDeal(void)
{
	if(RoadType==5)
	{
		PID_TURN.pout*=1;
		PID_TURN.dout*=0.65;
	}
	else if((RoadType==3 || RoadType==2) && (circle_stage==1||circle_stage==3))
	{

                if(turn_flag==3)
		{
			PID_TURN.pout *= 0.9;
			PID_TURN.dout*=0.6;
		}
		else 
		{
                        PID_TURN.pout*=1.04;
                        PID_TURN.dout *= 1;
		}
		
		
	}
	else if((RoadType==3 || RoadType==2) && circle_stage==2)
	{
		if(turn_flag==3)
		{
			PID_TURN.pout *= 0.89;
			PID_TURN.dout*=1;
		}
		else if(turn_flag==1)
		{
			PID_TURN.pout *= 1.05;
			PID_TURN.dout*=1;
		}
		else if(turn_flag==2)
		{
			PID_TURN.pout *= 0.9;
			PID_TURN.dout*=1;
		}
	}
        else if(Stop==1)PID_TURN.pout *= 0.75;
	//D���޷�
	if(PID_TURN.dout > 0.8) PID_TURN.dout = 0.8;
	else if(PID_TURN.dout < -0.8) PID_TURN.dout = -0.8;
	
	if(PID_TURN.pout > 0) PID_TURN.pout *= rit_correction;
}
/********************�������������***************/
void Direction_Control(void)
{
	Delta_P = (errFu * deltaServoKp[errGrade+1] + (1000-errFu) * deltaServoKp[errGrade])/1000;
	PID_TURN.pout=(PID_TURN.P*Delta_P)*Middle_Err;
	//D����
	if(Middle_Err > 0 && Delt_error > 0 || Middle_Err < 0 && Delt_error < 0)//����
	{
		Delta_D = deltaServoDout[errGrade];
	}
	else//����
	{
		Delta_D = deltaServoDback[errGrade];
	}
	PID_TURN.dout=(PID_TURN.D*Delta_D)*Delt_error;       //�÷��� kk
	
	Direction_SpecialDeal();
	//����ֵ
	//P+��
	Turn_Out= PID_TURN.pout- PID_TURN.dout;
	
	//ת������˲�
	Turn_Out=Turn_Out_Filter(Turn_Out);
	PID_TURN.OUT=Turn_Out*325;
	//����޷�
	if( PID_TURN.OUT>sever_range) PID_TURN.OUT=sever_range;
	else if( PID_TURN.OUT<-sever_range) PID_TURN.OUT=-sever_range; 
//        FTM_PWM_Duty(FTM1,FTM_CH0,sever_middle-PID_TURN.OUT);    //�����ֵ��0-180 �����仯
	
	Servo_Duty((u32)(Servo_Middle + PID_TURN.OUT));
}


//���pwmֵ���
void Moto_Out() 
{     
	//�ٶȿ�������޷�
	if(PID_SPEED.OUT>0.8)//�������ǰ�㣬��ģ���ٶȿ������Ϊ������֮Ϊ��
		PID_SPEED.OUT=0.8;
	if(PID_SPEED.OUT<-0.8)
		PID_SPEED.OUT=-0.8;
	MotorOut=-PID_SPEED.OUT;
	
	
	if(Stop)                                //���ֹͣ���������
	{
		if(CarSpeed<1)MotorOut=0;
                else MotorOut=0.9;
	}
	else
	{
		if(CarSpeed>0.8)take_off=1;
		if(take_off==0 && CarSpeed<0.8)
		{
			if(MotorOut>0.6)MotorOut=0.6;                     
			if(MotorOut<-0.6)MotorOut=-0.6;
		}
	}
	
	if(!Stop && take_off==1)
	{
		if(CarSpeed<0.5)
		{
			MotorOut=0;
			take_off=0;
		}
	}
	MotorOut=-MotorOut;
	if(MotorOut>=0) //��ת
	{
		Motor_Duty(Mot0, (u32)(MotorOut*500));
		Motor_Duty(Mot1, 0);
	}
	else   //��ת
	{
		Motor_Duty(Mot0, 0);
		Motor_Duty(Mot1, (u32)(-MotorOut*500));
	}
	
}


float  Turn_Out_Filter(float turn_out)    //ת���������˲�      
{
	float Turn_Out_Filtered; 
	static float Pre1_Error[4]; 
	Pre1_Error[3]=Pre1_Error[2];
	Pre1_Error[2]=Pre1_Error[1];
	Pre1_Error[1]=Pre1_Error[0];
	Pre1_Error[0]=turn_out;
	Turn_Out_Filtered=Pre1_Error[0]*0.8+Pre1_Error[1]*0.15+Pre1_Error[2]*0.05;
	return Turn_Out_Filtered;
}
float  Middle_Err_Filter(float middle_err)    //����ƫ���˲�      
{
	float Middle_Err_Fltered; 
	static float Pre3_Error[4]; 
	Pre3_Error[3]=Pre3_Error[2];
	Pre3_Error[2]=Pre3_Error[1];
	Pre3_Error[1]=Pre3_Error[0];
	Pre3_Error[0]=middle_err;
	Middle_Err_Fltered=Pre3_Error[0]*0.4+Pre3_Error[1]*0.3+Pre3_Error[2]*0.2+Pre3_Error[3]*0.1;
	return Middle_Err_Fltered;
}
void Err_Fuzzy(void)
{
	//Middle_Err�ּ�
	int absErr = (int)ABS(Middle_Err);
	if(absErr < 10)//0~10//��ȫֱ�� 8
	{
		errGrade = 0;
		errFu = absErr * 1000 / 10;
	}
	else if(absErr <15)//10~30//ֱ��΢΢ƫ��15
	{
		errGrade = 1;
		errFu = (absErr - 10) * 1000 / 5;
	}
	else if(absErr < 20)//30~60//ֱ���ϴ�ƫ�ƣ���Ҫ����
	{
		errGrade = 2;
		errFu = (absErr - 15) * 1000 / 5;
	}
	else if(absErr < 27)//60~100//��������
	{
		errGrade = 3;
		errFu = (absErr - 20) * 1000 / 7;
	}
	else if(absErr < 40)//100~170//��������
	{
		errGrade = 4;
		errFu = (absErr - 27) * 1000 / 13;
	}
	else if(absErr < 50)//170~230//������
	{
		errGrade = 5;
		errFu = (absErr - 40) * 1000 / 10;
	}
	else//230~100000000
	{
		errGrade = 5;
		errFu = 1000;
	}
	
	
	absErr = (int)ABS(SpeedDevi);
	if(absErr < 5)//0~10//��ȫֱ��
	{
		sDGrade = 0;
		sDFu = absErr * 1000 / 5;
	}
	else if(absErr < 10)//10~30//ֱ��΢΢ƫ��
	{
		sDGrade = 1;
		sDFu = (absErr - 5) * 1000 / 5;
	}
	else if(absErr < 20)//30~60//ֱ���ϴ�ƫ�ƣ���Ҫ����
	{
		sDGrade = 2;
		sDFu = (absErr - 10) * 1000 / 10;
	}
	else if(absErr < 30)//60~100//��������
	{
		sDGrade = 3;
		sDFu = (absErr - 20) * 1000 / 10;
	}
	else if(absErr < 40)//100~170//��������
	{
		sDGrade = 4;
		sDFu = (absErr - 30) * 1000 / 10;
	}
	else if(absErr < 50)//170~230//������
	{
		sDGrade = 5;
		sDFu = (absErr - 40) * 1000 / 10;
	}
	else//230~100000000
	{
		sDGrade = 5;
		sDFu = 1000;
	}
}
void Get_Control_Line(void)
{
	
}