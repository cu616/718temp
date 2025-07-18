#ifndef __UI_H
#define __UI_H
#include "main.h"

//OLED屏幕上的主控模块      
void UI_Control(void);
void further(void);
void config(void);
//发挥部分
void further_task1();
void further_task2();
void further_task3();
void further_task4();
//调试函数
void config1();
void config2();
void config3();
void config4();
void config5();
void config6();
void config7();
void config8();
void config9();
//自定义UI
void superUI(uint8_t name[SUPER_NUMBER][SUPER_TASK_NUMBER], uint16_t value[SUPER_NUMBER][SUPER_TASK_NUMBER]);
void super(int number, uint8_t name[SUPER_NUMBER][SUPER_TASK_NUMBER], uint16_t value[SUPER_NUMBER][SUPER_TASK_NUMBER]);
void operate(uint8_t name[SUPER_TASK_NUMBER], uint16_t value[SUPER_TASK_NUMBER]);
void change(uint8_t name[SUPER_TASK_NUMBER], uint16_t value[SUPER_TASK_NUMBER]);
void single_work(uint8_t name, uint16_t value);
uint16_t set_value();
#endif