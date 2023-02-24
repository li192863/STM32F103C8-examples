#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "LED.h"


int main(void)
{
    LED_Init();
    GPIO_ResetBits(GPIOA, GPIO_Pin_All);
    while (1)
    {
        GPIO_Write(GPIOA, ~0x0001);  //0000 0000 0000 0001
        Delay_ms(100);
        GPIO_Write(GPIOA, ~0x0002);  //0000 0000 0000 0010
        Delay_ms(100);
        GPIO_Write(GPIOA, ~0x0004);  //0000 0000 0000 0100
        Delay_ms(100);
        GPIO_Write(GPIOA, ~0x0008);  //0000 0000 0000 1000
        Delay_ms(100);
        GPIO_Write(GPIOA, ~0x0010);  //0000 0000 0001 0000
        Delay_ms(100);
        GPIO_Write(GPIOA, ~0x0020);  //0000 0000 0010 0000
        Delay_ms(100);
        GPIO_Write(GPIOA, ~0x0040);  //0000 0000 0100 0000
        Delay_ms(100);
        GPIO_Write(GPIOA, ~0x0080);  //0000 0000 1000 0000
        Delay_ms(100);
    }
}
