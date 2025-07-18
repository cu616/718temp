#ifndef _HMC5883_H
#define _HMC5883_H

#define hmci2c hi2c2

void  Single_Write_HMC5883(unsigned char  REG_Address,unsigned char REG_data);   //??????
unsigned char Single_Read_HMC5883(unsigned char  REG_Address);                   //???????????
void  Multiple_Read_HMC5883(void);                                  //????????????
void Init_HMC5883(void);
unsigned char Init_HMC5883_SelfTestMode(void);
void HMC5883_getyaw(void);
void HMC5883_first(void);
void HMC5883_getdata(void);
void HMC5883_cyclecheck(void);

extern unsigned char BUF[8];
extern short Bx,By,Bz;
extern float hyaw,hyawa,hyawb;//before after
extern short offsetx,offsety,offsetz;
#endif
