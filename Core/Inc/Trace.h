#ifndef __TRACE_H
#define __TRACE_H

#include "main.h"


//此处选择并行，串行，或者I2C模式，选择相应模式则保留相应宏定义
//PARALLEL：并行 SERIAL：串行

//#define PARALLEL
#define SERIAL
//#define I2C

#ifdef PARALLEL

/*
*TXn代表灰度传感器指定的Channel
*其中X可取L或R，分别代表左右（坐在车头向行驶方向看）
*n代表左或右第n路，从中间向两边数，TR1和TL1在最中间
*/

//此处定义连接到灰度传感器的GPIO的port和pin，使用时须修改，引脚需下拉
#define GPIO_Trace_TL1_PORT BL4_GPIO_Port
#define GPIO_Trace_TL2_PORT BL3_GPIO_Port
#define GPIO_Trace_TL3_PORT BL2_GPIO_Port
#define GPIO_Trace_TL4_PORT BL1_GPIO_Port
#define GPIO_Trace_TR1_PORT BL5_GPIO_Port
#define GPIO_Trace_TR2_PORT BL6_GPIO_Port
#define GPIO_Trace_TR3_PORT BL7_GPIO_Port
#define GPIO_Trace_TR4_PORT BL8_GPIO_Port

#define GPIO_Trace_TL1_PIN BL4_Pin
#define GPIO_Trace_TL2_PIN BL3_Pin
#define GPIO_Trace_TL3_PIN BL2_Pin
#define GPIO_Trace_TL4_PIN BL1_Pin
#define GPIO_Trace_TR1_PIN BL5_Pin
#define GPIO_Trace_TR2_PIN BL6_Pin
#define GPIO_Trace_TR3_PIN BL7_Pin
#define GPIO_Trace_TR4_PIN BL8_Pin

// 检测到黑线值为1
//左1234路
uint8_t get_TL1(void);
uint8_t get_TL2(void);
uint8_t get_TL3(void);
uint8_t get_TL4(void);
//右1234路
uint8_t get_TR1(void);
uint8_t get_TR2(void);
uint8_t get_TR3(void);
uint8_t get_TR4(void);

uint8_t get_T(uint8_t flag);//flag指示读取的传感器，最左侧为1，最右侧为8

//获取八路状态，返回值为八位二进制数，高位为左，低位为右
//示例：00011000表明为中间两路识别到黑色轨道
uint8_t get_T_ALL(void);
//返回训到轨迹的传感器数量
//uint8_t get_T_Inc(void);

//获取八路状态，查表后输出误差
//float get_TerrorR(void);
//float get_TerrorL(void);
//float get_another_Terror(void);
#endif//PARALLEL

#ifdef SERIAL

//此处为相应引脚定义，使用时需修改
#define DAT_GPIO_Port SDA_GPIO_Port
#define CLK_GPIO_Port SCL_GPIO_Port

//#define DAT_Pin SDA_Pin
//#define CLK_Pin SCL_Pin

//串行读入灰度传感器八路状态，并存入数组
void get_T_serial(uint8_t value[]);

uint8_t get_T(uint8_t flag);

uint8_t get_T_ALL(void);

#endif //SERIAL

#ifdef I2C

#define get_T(x) GW_digital_Read_Bit(x)

#define get_T_ALL() GW_digital_Read()

#endif//I2C

float get_Terror(void);

#endif//__TRACE_H
