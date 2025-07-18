#include "main.h"

void config_encoder()
{
    int16_t encoder[2] = {0, 0};
    char msgA[20], msgB[20];
    __HAL_TIM_DISABLE(&htim7);
    reset_encoder();
    Set_PWM(60, 60);
	    HAL_Delay(150);
    Trace(60);
    read_encoder(encoder);
    sprintf(msgA, "Encoder1: %d", encoder[0]);
    OLED_ShowString(0, 20, msgA, 8, 1);
    sprintf(msgB, "Encoder2: %d", encoder[1]);
    OLED_ShowString(0, 30, msgB, 8, 1);
    OLED_Refresh();
    stop();
    while (1)
    {
    }
}

void config1()
{
    HAL_TIM_Encoder_Stop_IT(&htim1, TIM_CHANNEL_ALL);
    float speed = 60;
    Trace(speed);
    float initial_angle = Yaw;
    trace_encoder(800,60);  //向前移动

    TurnRightangel(1,speed);
    Trace(speed);

    reverse_straight(initial_angle+90, 60);
    trace_encoder(800,speed);  //

    TurnRightangel(1,speed);
    Trace(speed);
    stop();
}

void config2() // 显示编码器数值
{
    //uint16_t encoder[2];
    //char msg[10];
    //while(1){
    //    reset_encoder();
    //    Set_PWM(50,50);
    //    HAL_Delay(200);
    //    read_encoder(encoder);
    //    sprintf(msg,"%d %d",encoder[0],encoder[1]);
    //    OLED_ShowString(0,20,msg,8,1);
    //    OLED_Refresh();
    //}
    while(1){
        Set_PWM(50,0);
        HAL_Delay(2000);
        Set_PWM(0,50);
        HAL_Delay(2000);
        Set_PWM(50,50);
        HAL_Delay(1000);
    }
}

void config3()
{
    Trace(70);
    TurnRightangel(1,60);
    Trace(70);
    stop();

    //__HAL_TIM_DISABLE_IT(&htim7,TIM_IT_UPDATE);
    //Trace(60);
    //config_encoder();

    //int16_t encoder[2] = {0, 0};
    //char msgA[20], msgB[20], msgspeed[20];
    //float speed = 60;
    //float Inc = 4, Del = 0;
    //__HAL_TIM_DISABLE(&htim7);
    //reset_encoder();
    //while (1)
    //{
    //    reset_encoder();
    //    Set_PWM(62, 60);
    //    HAL_Delay(30);
    //    read_encoder(encoder);
//
    //    sprintf(msgA, "Encoder1: %d", encoder[1]);
    //    OLED_ShowString(0, 20, msgA, 8, 1);
    //    sprintf(msgB, "Encoder2: %d", encoder[0]);
    //    OLED_ShowString(0, 30, msgB, 8, 1);
    //    sprintf(msgspeed, "%.0f  %.0f", speed, speed+Inc-Del);
    //    OLED_ShowString(0, 40, msgspeed, 8, 1);
    //    OLED_Refresh();
    //}
}

void config4()
{
    char fmsg[20] = {0};
    while (1)
    {
        /*sprintf(fmsg, "%f", Kyaw);
        OLED_ShowString(0, 30, fmsg, 8, 1);*/
        sprintf(fmsg, "%f",Yaw);
        OLED_ShowString(0, 30, fmsg, 8, 1);
        OLED_Refresh();
        HAL_Delay(10);
    }
}

void config5()
{
    char data[4];
    while(1){
        HAL_UART_Transmit(&huart1, "get\r\n", 5, 30);
        HAL_UART_Receive(&huart1, data, 4, HAL_MAX_DELAY);
        OLED_ShowString(0, 20, "vision", 8, 1);
        OLED_ShowString(0, 30, data, 8, 1);
        OLED_Refresh();
        HAL_Delay(100);    
    }
}

void config6()
{
    char data[4];
    while(1){
        HAL_UART_Transmit(&huart1, "name\r\n", 6, 30);
        HAL_UART_Receive(&huart1, data, 1, HAL_MAX_DELAY);
        OLED_ShowString(0, 20, "vision", 8, 1);
        OLED_ShowString(0, 30, data, 8, 1);
        OLED_Refresh();
        HAL_Delay(100);    
    }
}

void config7()
{
    uint16_t encoder[2];
    char msg[10];
    while(1){
        reset_encoder();
        Set_PWM(50,50);
        HAL_Delay(200);
        read_encoder(encoder);
        sprintf(msg,"%d %d",encoder[0],encoder[1]);
        OLED_ShowString(0,20,msg,8,1);
        OLED_Refresh();
    }
}

void config8()
{
    char msg[8];
    while (1)
    {
        OLED_ShowString(0, 10, "Running", 8 ,1);
        HAL_UART_Receive(&huart3, msg, 5, 100);
        OLED_ShowString(0, 20, msg, 8, 1);
        OLED_Refresh();
    }
}

void config9()
{
    char kmsg[20];
    for (int i = 0; i < 10000; i++)
    {
        sprintf(kmsg, "%f", Kyaw);
        OLED_ShowString(0, 20, kmsg, 8, 0);
        OLED_Refresh();
        HAL_Delay(10);
        OLED_Clear();
    }
}