#ifndef __TURN_H__
#define __TURN_H__

#include <main.h>

void turn(float turn, float speed, float ratio);
void turnto(float aim_angle, float speed, float ratio);
void autoturn(int8_t flag, float speed);
void autoturn_serial(int8_t flag, float speed);

#endif