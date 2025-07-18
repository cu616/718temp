#ifndef __TASK_H
#define __TASK_H
#define SUPER_NUMBER 1
#define SUPER_TASK_NUMBER 1

#include "main.h"

//任务1
void task1();
//任务2
void task2();
//任务3
void task3();
//任务4
//void task4_simple(float initial_angel);
void task4();
//基本任务
void microtask_12();
void microtask_1212(uint8_t flag);
void microtask_3();
void stop_delay();
//沿初始角直行
void go_straight(float angle, float speed);
//按指定速度倒车
int reverse(float speed);
void reverse_straight(float angle, float speed);
void reverse_encoder(float speed);
//转到设定角度
void turn_both(float turn_angle);//两轮同时转动，可保证旋转途中轮心不动
void turn_single(float turn_angle);//仅外侧一轮转动，可保证内测轮不动
void turn(float turn);//用于选择使用哪种转动方式
void turnto(float aim_angle);
//按指定速度旋转，直至遇到轨迹
void autoturn(float speed);
//循迹部分运行函数,执行此函数即执行循迹功能
//没有轨迹时完成，返回值为0
//遇到十字路口时完成，返回值为1
//此函数为阻塞式
int traceL(PID* TracePID);
int traceR(PID* TracePID);
int trace();
//基于编码器的功能
void trace_encoder(uint16_t encoder_max, float speed);
#endif