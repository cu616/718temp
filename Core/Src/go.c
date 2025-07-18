#include "main.h"
#include"oled.h"
#define basicspeed 20
void go_straight(){
	//read_angle();
	PID* pid_straight = malloc(sizeof(PID));
	pid_straight->Kp = 1.8;
  pid_straight->Ki = 0;
  pid_straight->Kd = 2.5;
  pid_straight->target = Kyaw;//Ŀ��Ƕ�ֵΪ��ǰ�Ƕ�
  pid_straight->minIntegral = -5;
  pid_straight->maxIntegral = 5;
  pid_straight->minOutput = -10;
  pid_straight->maxOutput = 10;
  pid_straight->error = 0.0;        //����Ҫ�޸�
  pid_straight->last_error = 0.0;   //����Ҫ�޸�
  pid_straight->integral = 0.0;     //����Ҫ�޸�
	float transform = 0;
	//read_angle();
	while(1){//����������
		//read_angle();//��ȡ��ǰ�Ƕ�ֵ������ֵ������ȫ�ֱ���Kyaw��
		transform = PID_Compute(pid_straight, Kyaw);
		if(transform>0){
			Set_PWM(basicspeed-transform, basicspeed);//�������ٴ������ƫת
		}
		else if(transform<0){
			Set_PWM(basicspeed, basicspeed+transform);//�������ٴ����Ҳ�ƫת
		}
		else{
			Set_PWM(basicspeed,basicspeed);
		}
		//OLED_ShowNum(10,40,transform,6,8,1);
		//OLED_Refresh();
		//Delay_Ms(10);
	}
}

void turn(float turn){//��������ת����������ת������תʱֻת�����֣�����תʱֻת������
	PID* pid_turn = malloc(sizeof(PID));
	//read_angle();
	float angle_end = Kyaw + turn;//Ŀ��Ƕ�ֵΪ��ǰ�Ƕȼ�����Ҫ��ת�ĽǶ�
	pid_turn->Kp = 36;
  pid_turn->Ki = 0;
  pid_turn->Kd = 1.2;
  pid_turn->target = angle_end;
  pid_turn->minIntegral = -5;
  pid_turn->maxIntegral = 5;
  pid_turn->minOutput = -30;
  pid_turn->maxOutput = 30;
  pid_turn->error = 0.0;           //����Ҫ�޸�
  pid_turn->last_error = 0.0;      //����Ҫ�޸�
  pid_turn->integral = 0.0;        //����Ҫ�޸�
	float transform = 0;
	read_angle();
	if(turn>0){  //����ת��ֻת������
	  while(1){
	  	//read_angle();//��ȡ��ǰ�Ƕ�ֵ������ֵ������ȫ�ֱ���Kyaw��
	  	if( Kyaw > angle_end - 0.5 && Kyaw < angle_end + 0.5 ){ //ע������������ֵ��kp��С���ܵ���transform��С��������ת����
	  		break;
	  	}//����Ƕ������1�����ڱ���Ϊ���ת��
	  	else{
	  		transform = PID_Compute(pid_turn, Kyaw);
	  		Set_PWM(0, transform);//����ת������Kyaw,��������transform������ת����transformͬ�������γɸ�����
	  	}
		//OLED_ShowNum(10,40,transform,6,8,1);
		//OLED_Refresh();
		
	  	//Delay_Ms(10);
	  }
	}
	else if(turn<0){
		while(1){   //����ת��ֻת������
	  	//read_angle();//��ȡ��ǰ�Ƕ�ֵ������ֵ������ȫ�ֱ���Kyaw��
	  	if( Kyaw > angle_end - 0.5 && Kyaw < angle_end + 0.5 ){
	  		break;
	  	}//����Ƕ������1�����ڱ���Ϊ���ת��
	  	else{
	  		transform = PID_Compute(pid_turn, Kyaw);
	  		Set_PWM(-transform, 0);//����ת�ή��Kyaw����������transform������ת����transform�෴�����γɸ�����
	  	}
		//OLED_ShowNum(10,40,transform,6,8,1);
		//OLED_Refresh();
	  	//Delay_Ms(10);
	  }
	}
}
