// 检测轨迹模组(串行)

#include <main.h>
#include <Mode_path_serial.h>

#define ALTERA1 0.5
#define ALTERA2 1.2
#define ALTERA3 4.0
#define INC_ALTERA1 0.5
#define INC_ALTERA2 0.7
#define INC_ALTERA3 1.0
#define INC_ALTERA4 1.5

void get_path_serial(uint8_t value[])
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

uint8_t get_T_serial(uint8_t flag)
{
    uint8_t value[8];
    get_T_serial(value);
    return value[flag - 1];
}

uint8_t get_T_ALL_serial(uint8_t value[])
{
    uint8_t re = 0;
    for (int i = 0; i < 7; i++)
    {
        re += (value[i]);
        re <<= 1;
    }
    re += (value[7]);
    return re;
}

uint8_t get_T_Sum_serial(uint8_t value[])
{
    uint8_t sum = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        sum += value[i];
    }
    return sum;
}

float get_Terror_serial(uint8_t value[])
{
    float error;
    uint8_t trace;

    trace = get_T_ALL_serial(value);

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