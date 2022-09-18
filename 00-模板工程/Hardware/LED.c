#include "stm32f10x.h"                  // Device header


/**
  * @brief  LED初始化
  * @retval 无
  */
void LED_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;  // 引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_SetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);  // 置引脚初始高电平熄灭LED
}

/**
  * @brief  翻转LED1状态
  * @retval 无
  */
void LED1_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_1);
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    }
}

/**
  * @brief  点亮LED1
  * @retval 无
  */
void LED1_On(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_1);
}

/**
  * @brief  熄灭LED1
  * @retval 无
  */
void LED1_Off(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_1);
}

/**
  * @brief  翻转LED2状态
  * @retval 无
  */
void LED2_Turn(void)
{
    if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0)
    {
        GPIO_SetBits(GPIOA, GPIO_Pin_2);
    }
    else
    {
        GPIO_ResetBits(GPIOA, GPIO_Pin_2);
    }
}

/**
  * @brief  点亮LED2
  * @retval 无
  */
void LED2_On(void)
{
    GPIO_ResetBits(GPIOA, GPIO_Pin_2);
}

/**
  * @brief  熄灭LED2
  * @retval 无
  */
void LED2_Off(void)
{
    GPIO_SetBits(GPIOA, GPIO_Pin_2);
}
