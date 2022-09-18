#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Timer.h"
#include "OLED.h"


uint16_t Num;

int main(void)
{
    OLED_Init();
    Timer_Init();
    OLED_ShowString(1, 1, "Time: ");
    while (1)
    {
        OLED_ShowNum(1, 7, Num, 3);
    }
}

void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        Num++;
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
