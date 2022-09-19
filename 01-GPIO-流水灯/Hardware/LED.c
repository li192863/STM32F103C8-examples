#include "stm32f10x.h"                  // Device header


void LED_Init(void)
{
    // Enables the High Speed APB (APB2) peripheral clock.
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    // Initializes the GPIOx peripheral according to GPIO_InitStruct.
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // Out push pull
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}
