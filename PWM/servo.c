#include "stm32f10x.h"                  // Device header
#include "pwm.h"

void Srevo_Init()
{
	PWM_Init();
}

//舵机0°——500
//180°——2500
void Servo_SetAngle(float angle)
{
	PWM_SetCompare2(angle/180*2000+500);//计算占空比
}