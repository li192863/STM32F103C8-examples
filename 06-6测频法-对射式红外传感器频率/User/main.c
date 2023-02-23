#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "CountSensor.h"
#include "OLED.h"
#include "Timer.h"

uint16_t count;

int main(void)
{
    OLED_Init();
    Timer_Init();
	CountSensor_Init();
    OLED_ShowString(1, 1, "Freq: ");
    while (1)
    {
        count += CountSensor_Get();
        OLED_ShowNum(1, 8, CountSensor_Get(), 5);
    }
}


