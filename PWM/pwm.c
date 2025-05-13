#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=20000-1;//计数周期arr
	TIM_TimeBaseInitStructure.TIM_Prescaler=72-1;//预分频器psc
												//对应ccr值的范围是500~2500 对应0.5~2.5ms
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_OCInitTypeDef TIM_OC2InitStructure;
	TIM_OCStructInit(&TIM_OC2InitStructure);//结构体不完全赋初值
	TIM_OC2InitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OC2InitStructure.TIM_OCPolarity=TIM_OCPolarity_High;//输出极性，选择为高，若选择极性为低，则输出高低电平取反
	TIM_OC2InitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OC2InitStructure.TIM_Pulse=0;//设置ccr初值
	TIM_OC2Init(TIM2,&TIM_OC2InitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
}

void PWM_SetCompare2(float ccr)
{
	TIM_SetCompare2(TIM2,ccr);
}
