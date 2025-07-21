// 检测轨迹模组(并行)

#include <main.h>
#include <Mode_path.h>

#define ALTERA1 0.5
#define ALTERA2 1.2
#define ALTERA3 4.0
#define INC_ALTERA1 0.5
#define INC_ALTERA2 0.7
#define INC_ALTERA3 1.0
#define INC_ALTERA4 1.5

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

uint8_t get_T(uint8_t flag)
{
    uint8_t value;
    switch (flag)
    {
    case 1:
        value = get_TL4();
        break;
    case 2:
        value = get_TL3();
        break;
    case 3:
        value = get_TL2();
        break;
    case 4:
        value = get_TL1();
        break;
    case 5:
        value = get_TR1();
        break;
    case 6:
        value = get_TR2();
        break;
    case 7:
        value = get_TR3();
        break;
    case 8:
        value = get_TR4();
        break;
    default:
        break;
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

uint8_t get_T_Sum(void)
{
    uint8_t sum = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        sum += get_T(i);
    }
    return sum;
}

float get_Terror(void)
{
    float error;
    uint8_t trace;

    trace = get_T_ALL();

    switch (trace)
    {
    case 0x18:
    case 0x10:
    case 0x08: // 00011000 00010000 00001000正
        error = 0;
        break;
    case 0x30:
    case 0x38: // 00110000 00111000 偏左
        error = -ALTERA1;
        break;
    case 0x60:
    case 0x70:
    case 0x20: // 01100000 01110000 00100000左
        error = -ALTERA2;
        break;
    case 0xC0:
    case 0xE0:
    case 0x80: // 11000000 11100000 10000000更大偏左
        error = -ALTERA3;
        break;
    case 0x0C:
    case 0x1C: // 00001100 00011100 偏右
        error = +ALTERA1;
        break;
    case 0x06:
    case 0x0E:
    case 0x04: // 00000110 00001110 00000100右
        error = +ALTERA2;
        break;
    case 0x03:
    case 0x07:
    case 0x01: // 00000011 00000111 00000001 更大偏右
        error = +ALTERA3;
        break;
    default:
        error = 0;
        break;
    }

    return error;
}