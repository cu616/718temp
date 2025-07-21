// 直行模组

#include <main.h>
#include <Mode_config.h>

void config_find_encoder()
{
    int16_t encoder[2] = {0, 0};
    char msgA[20], msgB[20];
    __HAL_TIM_DISABLE(&htim7);
    reset_encoder();
    Set_PWM(60, 60);
	HAL_Delay(150);
    trace_to_cross(60);

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

void config_speed_by_encoder(){
    char msg1[10], msg2[10];
    float PWMAtest, PWMBtest; // 目标PWM输出值
    PID PWMPID;
    float PWMPID_Kp = 0.01, PWMPID_Ki = 0, PWMPID_Kd = 0;
    float PWMPID_Target = 0, PWMPID_MinOutput = -2, PWMPID_MaxOutput = 2;
    int16_t Pencoder_num[2]; // 读编码器的
    int16_t targetB, targetA;
    PWMBtest = -60.0f;
    PWMAtest = PWMBtest;

    __HAL_TIM_DISABLE(&htim7); // 关tim7防止中断影响
    __HAL_TIM_DISABLE_IT(&htim7, TIM_IT_UPDATE);

    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);

    reset_encoder();
    Set_PWM(PWMBtest, PWMAtest);
    HAL_Delay(500);
    read_encoder(Pencoder_num);

    PID_Init(&PWMPID, PWMPID_Kp, PWMPID_Ki, PWMPID_Kd, PWMPID_Target, 0, 0, PWMPID_MinOutput, PWMPID_MaxOutput);

    do
    {  
        targetA = Pencoder_num[0];
        targetB = Pencoder_num[1];
        PWMAtest = PWMBtest - PID_Compute(&PWMPID, targetB - targetA);

        sprintf(msg1, ":%d,%d", Pencoder_num[1], Pencoder_num[0]);
        OLED_ShowString(0, 20, msg1, 8, 1);
        sprintf(msg2, "B:%.2f,A:%.2f", PWMBtest, PWMAtest);
        OLED_ShowString(0, 30, msg2, 8, 1);
        OLED_Refresh();

        reset_encoder();
        Set_PWM(PWMBtest, PWMAtest);
        HAL_Delay(500);
        read_encoder(Pencoder_num);
    }while (abs(Pencoder_num[0] - Pencoder_num[1]) > 2);

    stop();
    {
        sprintf(msg1, ":%d,%d", Pencoder_num[1], Pencoder_num[0]);
        OLED_ShowString(0, 20, msg1, 8, 1);
        sprintf(msg2, "B:%.2f,A:%.2f", PWMAtest, PWMBtest);
        OLED_ShowString(0, 30, msg2, 8, 1);
        OLED_Refresh();
    }
    while(1);
}

void config_show_encoder(float speed1, float speed2){
    int16_t encoder[2] = {0, 0};
    char msgA[20], msgB[20], msgspeed[20];
    __HAL_TIM_DISABLE(&htim7);
    reset_encoder();
    while (1)
    {
        reset_encoder();
        Set_PWM(speed1, speed2);
        HAL_Delay(30);
        read_encoder(encoder);

        sprintf(msgA, "Encoder1: %d", encoder[1]);
        OLED_ShowString(0, 20, msgA, 8, 1);
        sprintf(msgB, "Encoder2: %d", encoder[0]);
        OLED_ShowString(0, 30, msgB, 8, 1);
        OLED_Refresh();
    }
}

void config_show_Kyaw(){
    char msg[9] = {0};
    while(1){
        sprintf(msg,"%f", Kyaw);
        OLED_ShowString(0,20,msg,8,1);
        OLED_Refresh();
        HAL_Delay(10);
    }
}

void config_show_Yaw(){
    char msg[9] = {0};
    while(1){
        sprintf(msg,"%f", Yaw);
        OLED_ShowString(0,20,msg,8,1);
        OLED_Refresh();
        HAL_Delay(10);
    }
}

void config_trace_sensor(){
    char msg[9] = {0};
    while(1){
        for(uint8_t i = 0; i<8; i++){
            msg[i] = get_T(7-i) +'0';
            OLED_ShowString(0,20,msg,8,1);
            OLED_Refresh();
        }
    }
}

void config_trace_sensor_serial(){
    uint8_t value[8];
    char msg[9] = {0};
    while(1){
        get_path_serial(value);
        for(uint8_t i = 0; i<8; i++){
            msg[i] = value[7-i] +'0';
            OLED_ShowString(0,20,msg,8,1);
            OLED_Refresh();
        }
    }
}

void config_moter_Pin(){
    while(1){
        Set_PWM(50,0);
        HAL_Delay(2000);
        Set_PWM(0,50);
        HAL_Delay(2000);
        Set_PWM(50,50);
        HAL_Delay(2000);
    }
}

void config_K230_read_nums(){
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

void config_K230_read_name(){
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
















