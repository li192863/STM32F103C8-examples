#include "stm32f10x.h" // Device header
#include "Delay.h"


int main(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    
    // Enables the High Speed APB (APB2) peripheral clock.
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    // Initializes the GPIOx peripheral according to GPIO_InitStruct.
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // Out push pull
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    while (1)
    {
        int i;
        for (i = 0; i < 8; i++)
        {
            GPIO_ResetBits(GPIOB, GPIO_Pin_12);
            Delay_ms(100);
            GPIO_SetBits(GPIOB, GPIO_Pin_12);
            Delay_ms(100);
            GPIO_ResetBits(GPIOB, GPIO_Pin_12);
            Delay_ms(100);
            GPIO_SetBits(GPIOB, GPIO_Pin_12);
            Delay_ms(700);
        }
        
    }
}
