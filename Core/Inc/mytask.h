#ifndef __MYTASK_H__
#define __MYTASK_H__

#define MY_LINE_FOLLOWING_SPEED 40

#include "main.h"

/**
 * @brief 2021F送药小车主任务
 * 
 */
void MainTask(void);


void Main_Task(void);

/**
 * @brief 实现转90角
 * 
 * @param flag 取值可为1, -1, 0, 1表明左转, -1表明右转, 0表明不转向，直接return 
 */
void TurnRightangel(int flag, float turn_speed);

/**
 * @brief 直线部分循迹, 基于八路灰度传感器
 * 
 */
void Trace(float speed);

/**
 * @brief 倒车
 * 
 */
void Reverse(float speed);

/**
 * @brief 发送讯息到上位机, 读取Target
 * 
 * @return int类型, 返回Target
 */
int GetTargetNum(void);

/**
 * @brief 从上位机获取转向方向
 * 
 * @return int类型, 返回值为1, -1, 0, 1为左转, -1为右转, 0为继续直行
 */
int GetTurnFlag(void);
char* GetTurnData();
#endif