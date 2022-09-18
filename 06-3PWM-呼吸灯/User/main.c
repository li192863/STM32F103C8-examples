#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"
#include "OLED.h"

uint8_t i;

int main(void)
{
    OLED_Init();
    PWM_Init();
    while (1)
    {
        PWM_SetCompare1(100 - 0);
        OLED_ShowNum(1, 1, 0, 3);
        Delay_s(3);
        PWM_SetCompare1(100 - 25);
        OLED_ShowNum(1, 1, 25, 3);
        Delay_s(3);
        PWM_SetCompare1(100 - 50);
        OLED_ShowNum(1, 1, 50, 3);
        Delay_s(3);
        PWM_SetCompare1(100 - 75);
        OLED_ShowNum(1, 1, 75, 3);
        Delay_s(3);
        PWM_SetCompare1(100 - 100);
        OLED_ShowNum(1, 1, 100, 3);
        Delay_s(3);
    }
}
