/**
 * @file    PID.h
 * @version v1.3
 * @author  Bairu
 * @date    2024��8��21�� 16:09:44
 * @brief   PID�㷨ͷ�ļ�������PID�����ṹ�弰����
 */

#ifndef __PID_H
#define __PID_H

#include "stdint.h"

#define K_p 1
#define K_i 2
#define K_d 3

/**
 * PID�����ø�����
 * 1��P������Ӧ�ٶȺ����ȣ���С��Ӧ�������������񵴣���I��D�Ļ�����
 * 2��I����ϵͳ������������ʱ����ƫ���߾��ȣ�ͬʱҲ��������Ӧ�ٶȣ��������壬���������񵴡�
 * 3��D���ƹ�����񵴣���Сϵͳ����壬����������Ӧ�ٶȡ�D������һ�������ǵֿ�����ͻ�����ţ���ֹϵͳ��ͻ�䡣
 */

/**************************** λ��ʽPID ****************************/

typedef struct
{
    float Kp, Ki, Kd;               // ���������֡�΢��ϵ��
    float target;                   // Ŀ��ֵ
    float error;                    // ƫ��ֵ
    float last_error;               // ǰһ��ƫ��
    float integral;                 // ����ֵ
    float maxIntegral, minIntegral; // �����޷�
    float maxOutput, minOutput;     // ����޷�
} PID;

void PID_Init(PID *pid, float Kp, float Ki, float Kd, float target,
              float minIntegral, float maxIntegral,
              float minOutput, float maxOutput);
void PID_ResetTarget(PID *pid, float target);
void PID_Reset_pid(PID *pid, uint8_t Kx, float coefficient);
float PID_Compute(PID *pid, float input);
float PID_Compute_reverse(PID *pid, float input, float Kp);

/******************************************************************/

/**************************** ����ʽPID ****************************/

typedef struct
{
    float Kp, Ki, Kd;           // ���������֡�΢��ϵ��
    float target;               // Ŀ��ֵ
    float error;                // ƫ��ֵ
    float last_error;           // ǰһ��ƫ��
    float prev_error;           // ǰ����ƫ��
    float maxOutput, minOutput; // ����޷�
    float IncPID_Output;        // PID������
} IncPID;

void IncPID_Init(IncPID *incpid, float Kp, float Ki, float Kd, float target,
                 float minOutput, float maxOutput);
void IncPID_ResetTarget(IncPID *incpid, float target);
void IncPID_Reset_pid(IncPID *incpid, uint8_t Kx, float coefficient);
float IncPID_Compute(IncPID *incpid, float input);

/******************************************************************/

/***************************** �˲��� *****************************/

float EWMA_filter(float input, float filtered_value, float alpha);

/******************************************************************/

#endif /* __PID_H */

/************************************************************************
 *        PID�������� - openMVѰ��С�� (MSP430F5529 ������ת��С��)        *
 ************************************************************************
#include "driverlib.h"
#include <stdio.h>
#include "System/Sys_Clock.h"
#include "Hardware/OLED/OLED.h"
#include "Hardware/Car/Car.h"
#include "Hardware/PWM/PWM.h"
#include "Hardware/Encoder/Encoder.h"
#include "Hardware/UART/MSP430F5529_UART.h"
#include "PID/PID.h"

void main(void)
{
    WDT_A_hold(WDT_A_BASE);
    SystemClock_Init();
    __bis_SR_register(GIE);

    OLED_Init();
    AScar_Init();
    Encoder_Init();
    UART_Init(USCI_A0_BASE, 115200);
    UART_Init(USCI_A1_BASE, 115200);

    // �������ת��PID
    PID MotorPID;
    float Motor_Kp = 0.015, Motor_Ki = 0.014, Motor_Kd = 0.001;
    float Motor_target = 370;
    PID_Init(&MotorPID, Motor_Kp, Motor_Ki, Motor_Kd, Motor_target, -1850, 1850, 0, 100);
    float Motor_now = 0;
    float Motor_pidout = 0;

    // ת����PID
    IncPID ServoPID;
    float Servo_Kp = 0.05, Servo_Ki = 0, Servo_Kd = 0.01;
    float Servo_target = 70;
    IncPID_Init(&ServoPID, Servo_Kp, Servo_Ki, Servo_Kd, Servo_target, 4.5, 9.5);
    float Servo_now = 0;
    float Servo_pidout = 0;

    OLED_ShowString(1, 1, "Snow:", 8);
    OLED_ShowString(3, 1, "Spidout:", 8);
    OLED_ShowString(5, 1, "Mnow:", 8);
    OLED_ShowString(7, 1, "Mpidout:", 8);

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);

    uint8_t runFlag = 0;
    while(1)
    {
        // ����1����pid����
        if(get_Uart_RecStatus(USCI_A1_BASE))
        {
            uint8_t i;
            char temp_pid[7];
            float uart_p, uart_i, uart_d;
            // ���ڵ���pid����ʽ��p1.234* �� i1.234* �� d1.234*
            if(UART1_RX_BUF[0] == 'p' || UART1_RX_BUF[0] == 'i' || UART1_RX_BUF[0] == 'd')
            {
                // ��ȡ���ڴ����pidֵ
                for(i = 0; i < get_Uart_RecLength(USCI_A1_BASE) - 1; i++)
                {
                    temp_pid[i] = UART1_RX_BUF[i + 1];
                }
                if(UART1_RX_BUF[0] == 'p')
                {
                    sscanf(temp_pid, "%f", &uart_p);
                    PID_Reset_pid(&MotorPID, K_p, uart_p);
                }
                if(UART1_RX_BUF[0] == 'i')
                {
                    sscanf(temp_pid, "%f", &uart_i);
                    PID_Reset_pid(&MotorPID, K_i, uart_i);
                }
                if(UART1_RX_BUF[0] == 'd')
                {
                    sscanf(temp_pid, "%f", &uart_d);
                    PID_Reset_pid(&MotorPID, K_d, uart_d);
                }
                UART_printf(USCI_A1_BASE, "OK\n");
            }
            else
            {
                UART_printf(USCI_A1_BASE, "ERROR\n");
            }
            Reset_Uart_RecStatus(USCI_A1_BASE);
        }

        // ����0����openMV���ݣ�Ѱ��ƫ������
        if(get_Uart_RecStatus(USCI_A0_BASE))
        {
            uint8_t i;
            for(i = 0; i < get_Uart_RecLength(USCI_A0_BASE); i++)
            {
                Servo_now = UART0_RX_BUF[i];
            }
            Reset_Uart_RecStatus(USCI_A0_BASE);
        }
        OLED_ShowNum(1, 41, Servo_now, 3, 8);

        // �����ֵ��ת��
        Motor_now = getP20PulseNum();
        OLED_ShowNum(5, 41, Motor_now, 4, 8);

        // ת��PID
        Servo_pidout = IncPID_Compute(&ServoPID, Servo_now);
        // UART_printf(USCI_A1_BASE, "%.2f,%.2f\n", (Servo_now / 10.0), Servo_pidout);
        OLED_ShowFloat(3, 65, Servo_pidout, 3, 2, 8);

        // �ٶȻ�PID
        Motor_pidout = PID_Compute(&MotorPID, Motor_now);
        UART_printf(USCI_A1_BASE, "%.2f\n", Motor_now);
        OLED_ShowFloat(7, 65, Motor_pidout, 3, 2, 8);

        // ��������С����ͣ
        if(!GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1))
        {
            delay_ms(10);
            while(!GPIO_getInputPinValue(GPIO_PORT_P2, GPIO_PIN1));
            runFlag = 1;
        }
        if(!GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1))
        {
            delay_ms(10);
            while(!GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1));
            runFlag = 0;
        }

        if(runFlag)
        {
            PID_ResetTarget(&MotorPID, Motor_target);
            AScar_Status(Car_F, 0, Motor_pidout, Servo_pidout);
        } else {
            PID_ResetTarget(&MotorPID, 0);
            AScar_Status(Car_Stop, 0, 0, 7.8);
        }
    }
}

 ************************************************************************/