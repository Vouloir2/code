#include "stm32f10x.h"                  // Device header

int16_t enc_count;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef ENC_InintStructure;
	ENC_InintStructure.GPIO_Mode=GPIO_Mode_IPU;
	ENC_InintStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6;//讲1、2引脚更换成5、6引脚
	ENC_InintStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&ENC_InintStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line=EXTI_Line0|EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure1;
	NVIC_InitStructure1.NVIC_IRQChannel=EXTI1_IRQn;
	NVIC_InitStructure1.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure1.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStructure1);
}


//return 增量值
int16_t Enc_Get(void)
{
	int16_t temp=0;
	temp=enc_count;
	enc_count=0;
	return temp;
}

//正转
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0)	==SET)	
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
		{
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
			{
				enc_count++;
			}
		}
		
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)	==SET)	
	{
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)==0)
		{
			if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
			{
				enc_count--;
			}
		}
		
		EXTI_ClearITPendingBit(EXTI_Line1);
	}
}

