#include "stm32f10x.h"                  // Device header


/**
  * @brief  蜂鸣器初始化
  * @retval 无
  */
void Buzzer_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
  * @brief  翻转蜂鸣器状态
  * @retval 无
  */
void Buzzer_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_12) == 0)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_12);
    }
    else
    {
        GPIO_ResetBits(GPIOB, GPIO_Pin_12);
    }
}

/**
  * @brief  蜂鸣器鸣叫
  * @retval 无
  */
void Buzzer_On(void)
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_12);
}

/**
  * @brief  蜂鸣器关闭
  * @retval 无
  */
void Buzzer_Off(void)
{
    GPIO_SetBits(GPIOB, GPIO_Pin_12);
}
