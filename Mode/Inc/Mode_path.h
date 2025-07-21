#ifndef __MODE_PATH_H__
#define __MODE_PATH_H__

#include <main.h>

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
uint8_t get_T_Sum(void);

float get_Terror(void);

#endif