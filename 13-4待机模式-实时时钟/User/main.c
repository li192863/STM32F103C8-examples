#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "MyRTC.h"


int main(void)
{
    OLED_Init();
    MyRTC_Init();
    
    // 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    OLED_ShowString(1, 1, "CNT : ");
    OLED_ShowString(2, 1, "ALR : ");
    OLED_ShowString(3, 1, "ALRF: ");
    
    // 引脚唤醒
    PWR_WakeUpPinCmd(ENABLE);
    
    // 设定闹钟
    uint32_t Alarm = RTC_GetCounter() + 10;
    RTC_SetAlarm(Alarm);
    OLED_ShowNum(2, 7, Alarm, 10);
    
    while (1)
    {
        OLED_ShowNum(1, 7, RTC_GetCounter(), 10);
        OLED_ShowNum(3, 7, RTC_GetFlagStatus(RTC_FLAG_ALR), 1); // 显示闹钟标志位
        
        OLED_ShowString(4, 1, "Running");
        Delay_ms(100);
        OLED_ShowString(4, 1, "       ");
        Delay_ms(100);
        
        OLED_ShowString(4, 9, "STANDBY");
        Delay_ms(1000);
        OLED_ShowString(4, 9, "       ");
        Delay_ms(100);
        
        OLED_Clear();
        
        // 进入待机模式
        PWR_EnterSTANDBYMode();
    }
}
