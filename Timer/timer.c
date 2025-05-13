#include "stm32f10x.h"                  // Device header

void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);//配置时钟源，没有也可以
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period=10000-1;
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;//这个频率下计次10000次刚好是1s
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter=0;//重复周期，高级计数器中使用
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	/*中断输出配置*/
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);						//清除定时器更新标志位
																//TIM_TimeBaseInit函数末尾，手动产生了更新事件
																//若不清除此标志位，则开启中断后，会立刻进入一次中断
																//如果不介意此问题，则不清除此标志位也可
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//使能中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitSructure;
	NVIC_InitSructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitSructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitSructure.NVIC_IRQChannelPreemptionPriority=2;	//抢占优先级2
	NVIC_InitSructure.NVIC_IRQChannelSubPriority=1;		//响应优先级
	NVIC_Init(&NVIC_InitSructure);
	
	TIM_Cmd(TIM2,ENABLE);	
}


////中断函数
//void TIM2_IRQHandler()
//{
//	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)
//	{
//		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志位
//	}
//}