#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"


int main(void)
{
    OLED_Init();
    Serial_Init();
    
    Serial_SendByte('A');
    
    uint8_t MyArray[] = {0x42, 0x43, 0x44, 0x45};
    Serial_SendArray(MyArray, 4);
    
    Serial_SendString("\r\nhellooo~\r\n");
    
    Serial_SendNumber(12345, 5);
    
    printf("\r\nHellowa~%d\r\n", 123);
    
    Serial_Printf("你好，世界啊！\r\n");
    while (1)
    {
        
    }
}
