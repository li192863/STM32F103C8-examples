#include "stm32f10x.h"


/**
  * @brief  初始化定时器
  * @retval 无
  */
void Timer_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    
    TIM_InternalClockConfig(TIM2);
    
    // CK_CNT_OV = CK_PSC / (PSC + 1) / (ARR + 1)
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 10000 - 1; // ARR  10K / 10000 = 1, 0.1ms *  10000 = 1s
    TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1; // PSC  72M / 7200 = 10K, 1/(72M) * 7200 = 0.1ms
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
    
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);
    
    TIM_Cmd(TIM2, ENABLE);
}

/* 中断函数模板
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
*/
