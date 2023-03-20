#ifndef __SEARCH_H__
#define __SEARCH_H__
#define LINE_Far 120
extern uint8  RoadType,turn_point,circle_stage;
extern float slope_qj;
extern float Previous_Error[20];
void Search();
void get_edge();   
void sendimg();
extern int Loc[3][LINE_Far];
extern float Middle_Err_Sum_Far,Middle_Err_Sum,Middle_Err_Sum_Near,Middle_Err_Sum_Middle;
extern uint8 turn_flag;
extern int SlopeLmax,SlopeLmin,SlopeRmax,SlopeRmin,search_end_line;
extern uint8 il,ir;   //×óÓÒ¹Õµãwk
extern uint8 control_line,stop_line;
extern uint8 control_line_near,control_line_far;
extern uint8 L0,L1,R0,R1;
extern float slope_circuit;
extern uint8 bais;
extern uint8 ramp_cnt,out_cnt;
extern int curve_left,curve_right;
extern uint8 failcount,times_count;
extern float close_slope;
extern float flope_temp;
extern uint8 get_out_of_circle;
extern int search_end_line;
extern uint8 middle_right_q,middle_left_q,middle_straight_q;
extern uint8 middle_continue;
extern uint8 S_flag;
extern int AllWhileStartLine,AllWhileEndLine;
extern uint8 continue_line_left,continue_line_right;
extern uint8 end_line,left_end_line,right_head_line,right_end_line,left_head_line;
extern int slope_q[3][120]; 
extern uint8 str_L,str_L1,str_L2,str_R,str_R1,str_R2,LL,LL1,LL2,LR,LR1,LR2,RR,RR1,RR2,RL,RL1,RL2;
extern uint8 lose_brick;
#endif