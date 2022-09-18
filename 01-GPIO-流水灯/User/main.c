#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "LED.h"


int main(void)
{
    LED_Init();
    GPIO_ResetBits(GPIOA, GPIO_Pin_1 | GPIO_Pin_2);
    while (1)
    {
        
    }
}
