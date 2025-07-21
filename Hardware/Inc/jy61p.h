#ifndef __JY61P_H
#define __JY61P_H

#include "main.h" 

void jy61p_ReceiveData(uint8_t RxData);
void jy61p_DataCombine(uint8_t* buffer,int len);
void jy61p_caculate();

extern float Roll,Pitch,Yaw;
extern float Yaw_tran,Yaw_cur;
extern int Yaw_flag;
//extern uint8_t jyreceive[121];
extern uint8_t g_usart2_receivedata;
extern int jytime; 
#endif
