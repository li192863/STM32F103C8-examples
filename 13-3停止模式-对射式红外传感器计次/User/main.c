#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "CountSensor.h"
#include "OLED.h"


int main(void)
{
    OLED_Init();
	CountSensor_Init();
    
    // 开启时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    
    OLED_ShowString(1, 1, "Count: ");
    while (1)
    {
        OLED_ShowNum(1, 8, CountSensor_Get(), 5);
        
        OLED_ShowString(2, 1, "Running");
        Delay_ms(100);
        OLED_ShowString(2, 1, "       ");
        Delay_ms(100);
        
        // 进入停止模式
        PWR_EnterSTOPMode(PWR_Regulator_ON, PWR_STOPEntry_WFI);
        SystemInit(); // 重新启动HSE并配置72M主频
    }
}


