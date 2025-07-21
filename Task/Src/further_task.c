#include <main.h>
#include <further_task.h>

void further_task1()
{
        int8_t flag = 0;
    int8_t i = 0;
    float initial_angle;
    encoder_flag = 0;
    float speed = 80;
    float turn_speed = 70;
    char tag = 0;//用于提醒另一辆小车采取下一步行动
    //需要用到的相关变量及其初始化

    GetTargetNum();

    HAL_UART_Receive(&huart3,read_data,2,HAL_MAX_DELAY);
    //接收到小车1传来信号后启动

    while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) ==  GPIO_PIN_SET)  {}
    //出发前读取纸片并等待装药

    if(read_data[0] == target + '0'){
        flag = 1;
    }
    else{
        flag = -1;
    }
    //计算小车B的转向方向

    trace(100);
    //
    trace(100);
    //
    trace(speed);
    initial_angle = Yaw;
    HAL_GPIO_TogglePin(LEDY_GPIO_Port, LEDY_Pin);
    //先进军到暂停位置

    HAL_UART_Transmit(&huart3,&tag,1,30);
    //暂停后提醒小车1开始撤回

    HAL_UART_Receive(&huart3, &tag, 1, HAL_MAX_DELAY);
    HAL_GPIO_TogglePin(LEDY_GPIO_Port, LEDY_Pin);


    HAL_UART_Receive(&huart3,&tag,1,HAL_MAX_DELAY);
    //等待小车1完成倒车

    //reverse_encoder(60);
    reverse_straight(initial_angle, 50);
    //Reverse(40);
    autoturn_serial(flag, turn_speed);
    trace(40);
    HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
    while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) ==  GPIO_PIN_RESET)  {}
    //倒车至路口并转入送药房并等待卸药

    /* Reverse(40);
    autoturn_serial(flag);
    trace(40);
    trace(40);
    //从药房回家 */
/*
    int8_t flag = 0;
    int8_t i = 0;
    float initial_angle;
    encoder_flag = 0;
    float speed = 80;
    float turn_speed = 70;
    char tag = 0;//用于提醒另一辆小车采取下一步行动
    //需要用到的相关变量及其初始化

    GetTargetNum();

    HAL_UART_Receive(&huart3,read_data,2,HAL_MAX_DELAY);
    //接收到小车1传来信号后启动

    while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) ==  GPIO_PIN_SET)  {}
    //出发前读取纸片并等待装药

    if(read_data[0] == target + '0'){
        flag = 1;
    }
    else{
        flag = -1;
    }
    //计算小车B的转向方向

    trace(100);
    //
    trace(100);
    //
    trace(speed);
    initial_angle = Yaw;
    HAL_GPIO_TogglePin(LEDY_GPIO_Port, LEDY_Pin);
    //先进军到暂停位置

    HAL_UART_Transmit(&huart3,tag,1,30);
    //暂停后提醒小车1开始撤回

    HAL_UART_Receive(&huart3, tag, 1, HAL_MAX_DELAY);
    HAL_GPIO_TogglePin(LEDY_GPIO_Port, LEDY_Pin);


    HAL_UART_Receive(&huart3,tag,1,HAL_MAX_DELAY);
    //等待小车1完成倒车

    //reverse_encoder(60);
    reverse_straight(initial_angle, 50);
    //Reverse(40);
    autoturn_serial(flag, turn_speed);
    trace(40);
    HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
    while (HAL_GPIO_ReadPin(DETECT_GPIO_Port, DETECT_Pin) ==  GPIO_PIN_RESET)  {}
    //倒车至路口并转入送药房并等待卸药

    /* Reverse(40);
    autoturn_serial(flag);
    trace(40);
    trace(40);
    //从药房回家 */
}

void further_task2()
{
    char msg[10], msg1[3] = {0};//接受讯息
    int8_t flag_far, flag, flag_A;
    float speed = 80;
    float turn_speed = 70;
    char tag = 0;

    GetTargetNum();
    HAL_UART_Receive(&huart3, msg, 5, HAL_MAX_DELAY);
    if (target == (msg[0]-'0') || target == (msg[1]-'0'))
        flag_far = 1;
    else
        flag_far = -1;
    flag_A = msg[4]-'0';
    tag = flag_far+'0';
    HAL_UART_Transmit(&huart3, tag, 1, 30);

    trace(100);
    //
    trace(100);
    //
    trace_encoder(2500,60);
    stop();
    HAL_UART_Receive(&huart3, tag, 1, HAL_MAX_DELAY);
    //副车到达错车路口后等待主车信号

	trace(speed);
    autoturn_serial(flag_far,turn_speed);
    tag = 2;
    HAL_UART_Transmit(&huart3, tag, 1, 30);
    //副车完成转向后向主车传递信号

    trace(speed);
    flag = encoder_flag;
    autoturn_serial(flag,turn_speed);
    trace(40);
    HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
    //if(flag_far == flag_A)
    //{
    //    HAL_UART_Receive(&huart3, msg, 1, HAL_MAX_DELAY);
    //    trace(speed);
    //    autoturn_serial(flag_far);
    //    trace(speed);
    //    HAL_UART_Transmit(&huart3, "ok", 2, 100);
    //    flag = encoder_flag;
    //    autoturn_serial(flag);
    //    trace(40);
    //    HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
    //}
    //else
    //{
    //    trace(speed);
    //    autoturn_serial(flag_far);
    //    trace(speed);
    //    flag = encoder_flag;
    //    autoturn_serial(flag);
    //    trace(40);
    //    HAL_GPIO_TogglePin(LEDR_GPIO_Port, LEDR_Pin);
    //}
}

void further_task3()
{
}

void further_task4()
{
}