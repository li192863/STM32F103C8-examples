#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main(void)
{
    OLED_Init();
    Serial_Init();
    OLED_ShowString(1, 1, "RxData: ");
    while (1)
    {
        if (Serial_GetRxFlag() == 1)
        {
            RxData = Serial_GetRxData();
            Serial_SendByte(RxData);
            OLED_ShowHexNum(1, 9, RxData, 2);
        }
        
        OLED_ShowString(2, 1, "Running");
        Delay_ms(100);
        OLED_ShowString(2, 1, "       ");
        Delay_ms(100);
        
        // 进入低功耗模式
        __WFI(); // Wait For Interrupt 中断唤醒
    }
}
