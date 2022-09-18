#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Encoder.h"
#include "OLED.h"

int16_t Num;

int main(void)
{
    OLED_Init();
    Encoder_Init();
    OLED_ShowString(1, 1, "Count: ");
    while (1)
    {
        Num += Encoder_Get();
        OLED_ShowSignedNum(1, 8, Num, 5);
    }
}


