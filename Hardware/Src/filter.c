#include "filter.h"
#include "i2c.h"
#include "HMC5883.h"
#include "mpu6050.h"
#include "math.h"
#include "oled.h"
// �������˲�����
float Kroll ,Kpitch,Kyaw  ;



KF_t KF_Yaw = {
	0.001,            // Q_angle
	-0.0001,            // Q_bias
	0.5,              // R
	{{1, 0}, {0, 1}}, // P[2][2]
	0.01              // dt
};

KF_t KF_Roll = {
	0.001,            // Q_angle
	0.003,            // Q_bias
	0.5,              // R
	{{1, 0}, {0, 1}}, // P[2][2]
	0.05              // dt
};

KF_t KF_Pitch = {
	0.001,            // Q_angle
	0.003,            // Q_bias
	0.5,              // R
	{{1, 0}, {0, 1}}, // P[2][2]
	0.05              // dt
};



// �������˲�
float Kalman_Filter(KF_t *kf, float obsValue, float ut)		
{
  // �����������ֵ
	kf->Angle = kf->Angle + (ut - kf->Gyro_bias) * kf->dt;
	kf->Gyro_bias = kf->Gyro_bias;
	
	// �����������Э����
	kf->P[0][0] = kf->P[0][0] - (kf->P[0][1] + kf->P[1][0]) * kf->dt + kf->P[1][1] * kf->dt * kf->dt + kf->Q_angle;
	kf->P[0][1] = kf->P[0][1] - kf->P[1][1] * kf->dt;
	kf->P[1][0] = kf->P[1][0] - kf->P[1][1] * kf->dt;
	kf->P[1][1] = kf->P[1][1] + kf->Q_bias;
	
	// ���¿���������
	kf->K1 = kf->P[0][0] / (kf->P[0][0] + kf->R);
	kf->K2 = kf->P[1][0] / (kf->P[0][0] + kf->R);
	
	// ���¹���ֵ
	kf->Angle = kf->Angle + kf->K1 * (obsValue - kf->Angle);
	kf->Gyro_bias = kf->Gyro_bias + kf->K2 * (obsValue - kf->Angle);
	
	// �������Э����
	kf->P[0][0] = (1 - kf->K1) * kf->P[0][0];
	kf->P[0][1] = (1 - kf->K1) * kf->P[0][1];
	kf->P[1][0] = kf->P[1][0] - kf->P[0][0] * kf->K2;
	kf->P[1][1] = kf->P[1][1] - kf->P[0][1] * kf->K2;
	
	return kf->Angle;
}
void Kalman_getangle(){
		//Kroll  = Kalman_Filter(&KF_Roll , mroll , Gx );
		//Kpitch = Kalman_Filter(&KF_Pitch, mpitch, Gy );
		Kyaw   = Kalman_Filter(&KF_Yaw  , myaw  , Gz );
		
}
float Kalman_Filter1(KF_t *kf, float obsValue, float ut,double ddt)		
{
	kf->dt=ddt;
  // �����������ֵ
	kf->Angle = kf->Angle + (ut - kf->Gyro_bias) * kf->dt;
	kf->Gyro_bias = kf->Gyro_bias;
	
	// �����������Э����
	kf->P[0][0] = kf->P[0][0] - (kf->P[0][1] + kf->P[1][0]) * kf->dt + kf->P[1][1] * kf->dt * kf->dt + kf->Q_angle;
	kf->P[0][1] = kf->P[0][1] - kf->P[1][1] * kf->dt;
	kf->P[1][0] = kf->P[1][0] - kf->P[1][1] * kf->dt;
	kf->P[1][1] = kf->P[1][1] + kf->Q_bias;
	
	// ���¿���������
	kf->K1 = kf->P[0][0] / (kf->P[0][0] + kf->R);
	kf->K2 = kf->P[1][0] / (kf->P[0][0] + kf->R);
	
	// ���¹���ֵ
	kf->Angle = kf->Angle + kf->K1 * (obsValue - kf->Angle);
	kf->Gyro_bias = kf->Gyro_bias + kf->K2 * (obsValue - kf->Angle);
	
	// �������Э����
	kf->P[0][0] = (1 - kf->K1) * kf->P[0][0];
	kf->P[0][1] = (1 - kf->K1) * kf->P[0][1];
	kf->P[1][0] = kf->P[1][0] - kf->P[0][0] * kf->K2;
	kf->P[1][1] = kf->P[1][1] - kf->P[0][1] * kf->K2;
	
	return kf->Angle;
}

void read_angle(){
	int counter;
	double ddt;
	
	counter = __HAL_TIM_GET_COUNTER(&htim7);
	ddt=(counter)/1000000;//���㣬��ԭ����10000����counter
	__HAL_TIM_SET_COUNTER(&htim7,0);
	
//			MPU6050_Read_Result1(ddt);
		Kyaw   = Kalman_Filter1(&KF_Yaw  , myaw  , Gz ,ddt);
	//OLED_ShowNum(10,30,1000*Kyaw,7,8,1);
	 //OLED_Refresh();
}


