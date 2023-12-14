#include "stm32f10x.h"                  // Device header
#include "PWM.h"

/**
  * @brief  电机初始化
  * @retval 无
  */
void Motor_Init(void)
{
    // Enables the High Speed APB (APB2) peripheral clock.
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    // Initializes the GPIOx peripheral according to GPIO_InitStruct.
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // Out push pull
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    PWM_Init();
}

/**
  * @brief  设置电机速度
  * @param  Speed 电机速度
  * @retval 无
  */
void Motor_SetSpeed(int8_t Speed)
{
    if (Speed >= 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_4);
        GPIO_ResetBits(GPIOA, GPIO_Pin_5);
        PWM_SetCompare3(Speed);
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_4);
        GPIO_SetBits(GPIOA, GPIO_Pin_5);
        PWM_SetCompare3(-Speed);
    }
}
