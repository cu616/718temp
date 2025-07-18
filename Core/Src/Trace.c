#include "Trace.h"

//识别到轨道对应高电平，未识别到为低电平
#define ORDER_ALTERA1 0.5
#define ORDER_ALTERA2 1.2
#define ORDER_ALTERA3 4.0
#define AGAINST_ALTERA1 -0.7
#define AGAINST_ALTERA2 -1.2
#define AGAINST_ALTERA3 -4.0
#define ALTERA1 0.5
#define ALTERA2 1.2
#define ALTERA3 4.0
#define INC_ALTERA1 0.5
#define INC_ALTERA2 0.7
#define INC_ALTERA3 1.0
#define INC_ALTERA4 1.5

#ifdef PARALLEL
uint8_t get_TL1(void)
{
    return !HAL_GPIO_ReadPin(GPIO_Trace_TL1_PORT, GPIO_Trace_TL1_PIN);
}

uint8_t get_TL2(void)
{
    return !HAL_GPIO_ReadPin(GPIO_Trace_TL2_PORT, GPIO_Trace_TL2_PIN);
}

uint8_t get_TL3(void)
{
    return !HAL_GPIO_ReadPin(GPIO_Trace_TL3_PORT, GPIO_Trace_TL3_PIN);
}

uint8_t get_TL4(void)
{
    return !HAL_GPIO_ReadPin(GPIO_Trace_TL4_PORT, GPIO_Trace_TL4_PIN);
}

uint8_t get_TR1(void)
{
    return !HAL_GPIO_ReadPin(GPIO_Trace_TR1_PORT, GPIO_Trace_TR1_PIN);
}

uint8_t get_TR2(void)
{
    return !HAL_GPIO_ReadPin(GPIO_Trace_TR2_PORT, GPIO_Trace_TR2_PIN);
}

uint8_t get_TR3(void)
{
    return !HAL_GPIO_ReadPin(GPIO_Trace_TR3_PORT, GPIO_Trace_TR3_PIN);
}

uint8_t get_TR4(void)
{
    return !HAL_GPIO_ReadPin(GPIO_Trace_TR4_PORT, GPIO_Trace_TR4_PIN);
}

uint8_t get_T(uint8_t flag){
	uint8_t value;
	switch(flag){
		case 1: value = get_TL4(); break;
		case 2: value = get_TL3(); break;
		case 3: value = get_TL2(); break;
		case 4: value = get_TL1(); break;
		case 5: value = get_TR1(); break;
		case 6: value = get_TR2(); break;
		case 7: value = get_TR3(); break;
		case 8: value = get_TR4(); break;
		default: break;
	}
    return value; 
}

uint8_t get_T_ALL(void)
{
    uint8_t temp = 0;
    temp += get_TL4();
    temp <<= 1;
    temp += get_TL3();
    temp <<= 1;
    temp += get_TL2();
    temp <<= 1;
    temp += get_TL1();
    temp <<= 1;
    temp += get_TR1();
    temp <<= 1;
    temp += get_TR2();
    temp <<= 1;
    temp += get_TR3();
    temp <<= 1;
    temp += get_TR4();
    return temp;
}

uint8_t get_T_Inc(void){
    uint8_t sum = 0;
    for(uint8_t i =0;i<8;i++){
        sum+=get_T(i);
    }
    return sum;
}


//float get_TerrorR(void)
//{
//    float error;
//    uint8_t trace;
//
//    trace = get_T_ALL();
//
//    switch (trace)
//    {
//    case 0x18: case 0x10: case 0x08://00011000 00010000 00001000正
//        error = 0;
//        break;
//    case 0x30: case 0x38: //00110000 00111000 偏左
//        error = AGAINST_ALTERA1;
//        break;
//    case 0x60: case 0x70: //01100000 01110000 左
//        error = AGAINST_ALTERA2;
//        break;
//    case 0xC0: case 0xE0: case 0x80://11000000 11100000 10000000更大偏左
//        error = AGAINST_ALTERA3;
//        break;
//    case 0x0C: case 0x1C: //00001100 00011100 偏右
//        error = ORDER_ALTERA1;
//        break;
//    case 0x06: case 0x0E: //00000110 00001110 右
//        error = ORDER_ALTERA2;
//        break;
//    case 0x03: case 0x07: case 0x01://00000011 00000111 00000001 更大偏右
//        error = ORDER_ALTERA3;
//        break;
//    default:
//        error = -0.4;
//        break;
//    }
//    
//    return error;
//}
//
//float get_TerrorL(void)
//{
//    float error;
//    uint8_t trace;
//
//    trace = get_T_ALL();
//
//    switch (trace)
//    {
//    case 0x18: case 0x10: case 0x08://00011000 00010000 00001000正
//        error = 0;
//        break;
//    case 0x0C: case 0x1C: //00001100 00011100 偏右
//        error = AGAINST_ALTERA1;
//        break;
//    case 0x06: case 0x0E: //00000110 00001110 右
//        error = AGAINST_ALTERA2;
//        break;
//    case 0x03: case 0x07: case 0x01://00000011 00000111 00000001 更大偏右
//        error = AGAINST_ALTERA3;
//        break;
//    case 0x30: case 0x38: //00110000 00111000 偏左
//        error = ORDER_ALTERA1;
//        break;
//    case 0x60: case 0x70: //01100000 01110000 左
//        error = ORDER_ALTERA2;
//        break;
//    case 0xC0: case 0xE0: case 0x80://11000000 11100000 10000000更大偏左
//        error = ORDER_ALTERA3;
//        break;
//    default:
//        error = -0.4;
//        break;
//    }
//    
//    return error;
//}

//float get_Terror_Inc(void){
//    float error;
//    error += (get_TR1() - get_TL1()) * INC_ALTERA1;
//    error += (get_TR2() - get_TL2()) * INC_ALTERA2;
//    error += (get_TR3() - get_TL3()) * INC_ALTERA3;
//    error += (get_TR4() - get_TL4()) * INC_ALTERA4;
//    return error;
//}
#endif

#ifdef SERIAL
void get_T_serial(uint8_t value[])
{
    for (uint8_t i = 0; i < 8; i++)
    {
        HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, 0);
        // ret[0] = HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin) + '0';
        value[i] = !HAL_GPIO_ReadPin(SDA_GPIO_Port, SDA_Pin);
        HAL_GPIO_WritePin(SCL_GPIO_Port, SCL_Pin, 1);
        Delay_Us(5);
        
    }
} // 并口的刷新速率为1.5kHZ，即1s内最多读取1500次

uint8_t get_T(uint8_t flag)
{
    uint8_t value[8];
    get_T_serial(value);
    return value[flag-1];
}

uint8_t get_T_ALL(void)
{
    uint8_t value[8], re = 0;
    get_T_serial(value);
    for (int i = 0; i < 7; i++)
    {
        re += (value[i]);
        re <<= 1;
    }
    re += (value[7]);
    return re;
}

#endif

float get_Terror(void)
{
    float error;
    uint8_t trace;

    trace = get_T_ALL();

    switch (trace)
    {
    case 0x18: case 0x10: case 0x08://00011000 00010000 00001000正
        error = 0;
        break;
    case 0x30: case 0x38: //00110000 00111000 偏左
        error = -ALTERA1;
        break;
    case 0x60: case 0x70: case 0x20: //01100000 01110000 00100000左
        error = -ALTERA2;
        break;
    case 0xC0: case 0xE0: case 0x80: //11000000 11100000 10000000更大偏左
        error = -ALTERA3;
        break;
    case 0x0C: case 0x1C: //00001100 00011100 偏右
        error = +ALTERA1;
        break;
    case 0x06: case 0x0E: case 0x04: //00000110 00001110 00000100右
        error = +ALTERA2;
        break;
    case 0x03: case 0x07: case 0x01://00000011 00000111 00000001 更大偏右
        error = +ALTERA3;
        break;
    default:
        error = 0;
        break;
    }
    
    return error;
}