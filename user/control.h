#ifndef _CONTROL_H_
#define _CONTROL_H_
typedef struct PID{float P,pout,I,iout,D,dout,OUT;}PID;
extern  PID PID_SPEED,PID_TURN;
extern int errGrade,errFu;
extern int sDGrade,sDFu;
extern float temp;
extern int Speed_Filter_Times;
extern int SpeedCount;
extern float CarSpeed,ControlSpeed,Hill_Slow_Ratio;
extern float CarAcce;
extern float CarSpeedQueue[6];
extern float SetSpeed;
extern uint8 Set_Angle;
extern float AverageSpeed;
extern float Distance;
extern float SpeedControlOutOld,SpeedControlOutNew;
extern float SpeedControlIntegral;
extern float MotorOut;
//模糊化相关
extern float  Delta_P;
extern float  Delta_D;
extern float  Fuzzy_Kp;
extern float  Fuzzy_Kd;
//方向控制相关
extern int    DirectionCount;
extern float  Delt_error,Middle_Err;
extern int Err_Slope_mul50;
extern float SpeedDevi,SpeedDeviD;
extern int DeviFar,DeviNear;
extern float  Turn_Speed,Turn_Out,Turn_Angle_Integral;
extern float speedTarget;
extern int SpeedE,SpeedI,SpeedD;
extern float Speed_kP,Speed_kI;

//电机相关
extern int level;

/**舵机相关**/
extern int sever_middle;
extern int sever_range;

extern uint8 Starting,Stop;

void Get_Attitude();
void Get_Speed();
void Strong_Turn();
void Moto_Out();
void Speed_Control();
void Speed_Control_Output();
void Direction_Control();

float  Middle_Err_Filter(float middle_err);  
float  Turn_Out_Filter(float turn_out);
void Err_Fuzzy(void);
#endif
