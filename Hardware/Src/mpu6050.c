



#include "mpu6050.h"
#include"math.h"
#include"oled.h"
//定义6个int16_t的数据，一会用于对于接收的数据拼接
//int16_t是有负数的，uint16_t是没负数的
int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;
int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;

//这6个是把拼接好的数据经过计算得到结果
//float Ax, Ay, Az, Gx, Gy, Gz;

//使用加速度计算《加速度欧拉角》，先定义几个变量。_a的意思就是用的加速度
float roll_a, pitch_a;

//使用角速度计算《角速度欧拉角》，先定义几个变量。_g的意思就是用的角速度
float roll_g, pitch_g, yaw_g;


//欧拉角
//float roll, pitch, yaw; 


float Ax = 0.0f;
float Ay = 0.0f;
float Az = 0.0f;
float Gx = 0.0f;
float Gy = 0.0f;
float Gz = 0.0f;
float mroll = 0.0f;
float mpitch = 0.0f;
float myaw = 0.0f;
float moffsetgx=-2.58,moffsetgy=-2.978,moffsetgz=-2.90344;
//以下是函数
void MPU6050_Init(void)//初始化
{
	uint8_t check;
	uint8_t Data;
	HAL_TIM_Base_Start_IT(&htim7);

	HAL_I2C_Mem_Read(&mpui2c, MPU6050_ADDR, WHO_AM_I_REG, 1, &check, 1, 1000);


	if (check == 0x68)//寄存器文档最后一页写了WHO_AM_I_REG就是0x68
	{
		//电源管理1
		Data = 0x01;
		HAL_I2C_Mem_Write(&mpui2c, MPU6050_ADDR, PWR_MGMT_1_REG, 1, &Data, 1, 1000);

		//电源管理2
		Data = 0x00;
		HAL_I2C_Mem_Write(&mpui2c, MPU6050_ADDR, PWR_MGMT_2_REG, 1, &Data, 1, 1000);

		//滤波
		Data = 0x06;
		HAL_I2C_Mem_Write(&mpui2c, MPU6050_ADDR, CONFIG, 1, &Data, 1, 1000);


		//采样频率分频器寄存器
		Data = 0x09;
		HAL_I2C_Mem_Write(&mpui2c, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000);

		//加速度计配置
		Data = 0x18;
		HAL_I2C_Mem_Write(&mpui2c, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000);

		//陀螺仪配置
		Data = 0x18;
		HAL_I2C_Mem_Write(&mpui2c, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);
	}
}

void MPU6050_Read_Accel(void)//读取加速度
{
	uint8_t Rec_Data[6];
	HAL_I2C_Mem_Read(&mpui2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);
	Accel_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);//-反正就是左移八位得到原始数据。具体原理我没细看
	Accel_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
	Accel_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
	Ax = Accel_X_RAW / 2048.0;//-此处2048和下面的16.4都是调了分辨率后修正的值，不必太计较
	Ay = Accel_Y_RAW / 2048.0;
	Az = Accel_Z_RAW  / 2048.0 ;
}


void MPU6050_Read_Gyro(void)//读取角速度
{
	uint8_t Rec_Data[6];
	HAL_I2C_Mem_Read(&mpui2c, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);
	Gyro_X_RAW = (int16_t)(Rec_Data[0] << 8 | Rec_Data[1]);
	Gyro_Y_RAW = (int16_t)(Rec_Data[2] << 8 | Rec_Data[3]);
	Gyro_Z_RAW = (int16_t)(Rec_Data[4] << 8 | Rec_Data[5]);
	Gx = Gyro_X_RAW / 16.384 ;
	Gy = Gyro_Y_RAW / 16.384 ;
	Gz = Gyro_Z_RAW / 16.384 ;
}


//此函数是读取结果，当然这个结果是互补滤波法计算的
//如果你想读取yaw roll pitch 仅需调用此函数
void MPU6050_Read_Result(void){
/*
	//上面函数MPU6050_Read_Accel()中的，改了下变量名，让大家更易懂，你也可以直接调用函数
	uint8_t Rec_Data_A[6];
	HAL_I2C_Mem_Read(&mpui2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data_A, 6, 1000);
	Accel_X_RAW = (int16_t)(Rec_Data_A[0] << 8 | Rec_Data_A[1]);
	Accel_Y_RAW = (int16_t)(Rec_Data_A[2] << 8 | Rec_Data_A[3]);
	Accel_Z_RAW = (int16_t)(Rec_Data_A[4] << 8 | Rec_Data_A[5]);
	Ax = Accel_X_RAW / 2048.0;
	Ay = Accel_Y_RAW / 2048.0;
	Az = Accel_Z_RAW  / 2048.0 ;
*/
	//上面函数MPU6050_Read_Gyro()中的，改了下变量名，让大家更易懂，你也可以直接调用函数
	uint8_t Rec_Data_G[6];
	HAL_I2C_Mem_Read(&mpui2c, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data_G, 6, 1000);
	Gyro_X_RAW = (int16_t)(Rec_Data_G[0] << 8 | Rec_Data_G[1]);
	Gyro_Y_RAW = (int16_t)(Rec_Data_G[2] << 8 | Rec_Data_G[3]);
	Gyro_Z_RAW = (int16_t)(Rec_Data_G[4] << 8 | Rec_Data_G[5]);

	//Gx = Gyro_X_RAW / 16.384-moffsetgx;
	//Gy = Gyro_Y_RAW / 16.384-moffsetgy;
	Gz = Gyro_Z_RAW / 16.384-moffsetgz;


	//使用加速度计算欧拉角，如果用3.1415926，计算结果会慢，C8T6算小数太慢
/*
roll_a = atan2(Ay, Az) /3.14f * 180;
	pitch_a = - atan2(Ax, Az) /3.14f * 180;
*/
	//使用角速度计算欧拉角
	yaw_g = myaw + Gz * 0.010;//这里默认采样间隔0，005，对欧拉角累计
/*	roll_g = mroll + Gx * 0.005;
	pitch_g = mpitch + Gy * 0.005;

	//-互补滤波算法
	const float alpha = 0.98;//这个0.9可以改，0-1之间的数，一般在0.95往上，一次增加0.01调试一下
	mroll = mroll + (roll_a - roll_g ) *alpha;
	mpitch = mpitch + (pitch_a - pitch_g) *alpha;*/
	myaw = yaw_g;
	
}
float MPU6050_stasis(){
	float accumz=0;
	for(int i=0;i<100;i++){
		MPU6050_Read_Gyro();
		accumz+=Gz;
		HAL_Delay(10);
	}//采集100次，共1s
	return accumz;
}
void MPU6050_offsetG(void){
	float gz_init,gz_bias,lastacm;
	uint16_t time=51,i=0;
	char mog[20];
	char qbias[20];
	KF_Yaw.Q_bias=0.0;
	HAL_Delay(5000);//给5s保证陀螺仪静置
    OLED_ShowString(10, 10, "start,waiting...", 8, 0);
	OLED_Refresh();
  for(i=0;i<time;i++){
	lastacm = MPU6050_stasis();
	}	
	moffsetgz=lastacm/100;
	KF_Yaw.Q_bias=(lastacm)/5000;
	KF_Yaw.Q_bias*=-((time-1)*(time-1)/2);
	//printf("Gyro:offz=%.4f\r bias=%.4f\n",moffsetgz,KF_Yaw.Q_bias);
	OLED_Clear();
	sprintf(mog, "oz=%.5f", moffsetgz);
    OLED_ShowString(10, 20, mog, 8, 0);
	OLED_Refresh();
	sprintf(qbias, "qb=%.5f", KF_Yaw.Q_bias);
    OLED_ShowString(10, 30, qbias, 8, 0);
    OLED_Refresh();
	//printf("Gyro offset checking ends,waiting for 10s\n");
	/*if(sumz<0){
		OLED_ShowString(5, 30, "-", 8, 1);
		sumz=-sumz;
	}
OLED_ShowNum(10,30,sumz,6,8,1);
	OLED_Refresh();*/
/*	printf("Gyro: offx=%.4f, offy=%.4f, offz=%.4f\r\n",moffsetgx, moffsetgy, moffsetgz);
	printf("Gyro offset checking ends,waiting for 10s\n");*/
	HAL_Delay(15000);//给15s反应
	OLED_Clear();
}
void MPU6050_Read_Result1(double ddt){
/*
	//上面函数MPU6050_Read_Accel()中的，改了下变量名，让大家更易懂，你也可以直接调用函数
	uint8_t Rec_Data_A[6];
	HAL_I2C_Mem_Read(&mpui2c, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data_A, 6, 1000);
	Accel_X_RAW = (int16_t)(Rec_Data_A[0] << 8 | Rec_Data_A[1]);
	Accel_Y_RAW = (int16_t)(Rec_Data_A[2] << 8 | Rec_Data_A[3]);
	Accel_Z_RAW = (int16_t)(Rec_Data_A[4] << 8 | Rec_Data_A[5]);
	Ax = Accel_X_RAW / 2048.0;
	Ay = Accel_Y_RAW / 2048.0;
	Az = Accel_Z_RAW  / 2048.0 ;
*/
	//上面函数MPU6050_Read_Gyro()中的，改了下变量名，让大家更易懂，你也可以直接调用函数
	uint8_t Rec_Data_G[6];
	HAL_I2C_Mem_Read(&mpui2c, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data_G, 6, 1000);
	Gyro_X_RAW = (int16_t)(Rec_Data_G[0] << 8 | Rec_Data_G[1]);
	Gyro_Y_RAW = (int16_t)(Rec_Data_G[2] << 8 | Rec_Data_G[3]);
	Gyro_Z_RAW = (int16_t)(Rec_Data_G[4] << 8 | Rec_Data_G[5]);

	//Gx = Gyro_X_RAW / 16.384-moffsetgx;
	//Gy = Gyro_Y_RAW / 16.384-moffsetgy;
	Gz = Gyro_Z_RAW / 16.384-moffsetgz;


	//使用加速度计算欧拉角，如果用3.1415926，计算结果会慢，C8T6算小数太慢
/*
roll_a = atan2(Ay, Az) /3.14f * 180;
	pitch_a = - atan2(Ax, Az) /3.14f * 180;
*/
	//使用角速度计算欧拉角
	yaw_g = myaw + Gz * ddt;//这里默认采样间隔0，005，对欧拉角累计
/*	roll_g = mroll + Gx * 0.005;
	pitch_g = mpitch + Gy * 0.005;

	//-互补滤波算法
	const float alpha = 0.98;//这个0.9可以改，0-1之间的数，一般在0.95往上，一次增加0.01调试一下
	mroll = mroll + (roll_a - roll_g ) *alpha;
	mpitch = mpitch + (pitch_a - pitch_g) *alpha;*/
	myaw = yaw_g;
	
}

