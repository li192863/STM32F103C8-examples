#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "PWM.h"
#include "OLED.h"
#include "IC.h"

uint8_t i;

int main(void)
{
    OLED_Init();
    PWM_Init();
    IC_Init();
    
    PWM_SetPrescaler(7200 - 1); // Freq = 72M / (PSC + 1) / (ARR + 1)
    PWM_SetCompare1(80); // Duty = CCR / (ARR + 1)
    
    OLED_ShowString(1, 1, "Freq: 00000Hz");
    OLED_ShowString(2, 1, "Duty: 00%");
    while (1)
    {
        OLED_ShowNum(1, 7, IC_GetFreq(), 5);
        OLED_ShowNum(2, 7, IC_GetDuty(), 2);
    }
}
