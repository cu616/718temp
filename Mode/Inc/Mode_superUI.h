#ifndef __MODE_SUPERUI_H__
#define __MODE_SUPERUI_H__

#include <main.h>

#define SUPER_NUMBER 1
#define SUPER_TASK_NUMBER 1

void superUI(uint8_t name[SUPER_NUMBER][SUPER_TASK_NUMBER], uint16_t value[SUPER_NUMBER][SUPER_TASK_NUMBER]);
void super(int number, uint8_t name[SUPER_NUMBER][SUPER_TASK_NUMBER], uint16_t value[SUPER_NUMBER][SUPER_TASK_NUMBER]);
void operate(uint8_t name[SUPER_TASK_NUMBER], uint16_t value[SUPER_TASK_NUMBER]);
void change(uint8_t name[SUPER_TASK_NUMBER], uint16_t value[SUPER_TASK_NUMBER]);
void single_work(uint8_t name, uint16_t value);
uint16_t set_value();

#endif