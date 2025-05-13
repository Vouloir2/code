#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#include "key.h"
#include "led.h"
#include "OLED.h"
//#include "OLED_Font.h"//引用这个头文件会导致库重定义
#include "buzzer.h"
#include "Encoder.h"
#include "time.h"
#include "servo.h"
//uint16_t Num;//定时中断
	float angle;
int main(void)
{
	
	//初始化
	Key_Init();
	LED_Init();
	Buzzer_Init();
	OLED_Init();
	Encoder_Init();
	Srevo_Init();
	
	//按键状态标志
	uint8_t keynum = 0;
	
	
	/*
	//OLED显示
	OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(1, 3, "HelloWorld");
	OLED_ShowNum(2, 1, 12345, 5);
	OLED_ShowSignedNum(2, 7, -66, 2);
	OLED_ShowHexNum(3, 1, 0xAA55, 4);
	OLED_ShowBinNum(4, 1, 0xAA55, 16);
	*/
	
	/*
	//蜂鸣器
	Buzzer_beep();
	*/
	
	/*
	//编码器
	int16_t enc_num;
	OLED_ShowString(1,0,"enc_count:");
	*/
	
	/*
	//定时中断
	Timer_Init();
	OLED_ShowString(1, 1, "Num:");
	*/
	
	//舵机

	OLED_ShowString(1,1,"angle:");
	
	while(1)
	{
		/*
		//按键led
		keynum = Get_Keynum();
		
		if(keynum == 1) 
		{
//			LED1_Turn();
			LED1_ON();
			Delay_ms(500);
			LED1_OFF();
			Delay_ms(500);
		}
				
		if(keynum == 2) 
		{
//			LED2_Turn();
			LED2_ON();
			Delay_ms(500);
			LED2_OFF();
			Delay_ms(500);
		}
		*/
		
		/*
		//编码器
		enc_num+=Enc_Get();
		OLED_ShowSignedNum(2,1,enc_num,5);//OLED_ShowSignedNum显示正负
		*/
		
		/*
		//定时中断
		OLED_ShowNum(1, 5, Num, 5);
		*/
		
		/*
		//舵机
		keynum = Get_Keynum();	
		
		OLED_ShowNum(2,8,keynum,1);
		if (keynum == 1)
		{
			angle += 30;
			if (angle > 180)
			{
				angle = 0;
			}
		}
		Servo_SetAngle(angle);
		OLED_ShowNum(1, 7, angle, 3);
		*/
	}
}


//void TIM2_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)		//判断是否是TIM2的更新事件触发的中断
//	{
//		Num ++;												//Num变量自增，用于测试定时中断
//		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);			//清除TIM2更新事件的中断标志位
//															//中断标志位必须清除
//															//否则中断将连续不断地触发，导致主程序卡死
//	}
//}
