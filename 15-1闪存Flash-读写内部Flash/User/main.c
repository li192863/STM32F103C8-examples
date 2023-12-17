#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Store.h"
#include "Key.h"

uint8_t KeyNum;

int main(void)
{
    OLED_Init();
    Key_Init();
    Store_Init();

    OLED_ShowString(1, 1, "Flag: ");
    OLED_ShowString(2, 1, "Data: ");
    
    while (1)
    {
        KeyNum = Key_GetNum();
        
        if (KeyNum == 1)
        {
            Store_Data[1]++; // 变换测试数据
            Store_Data[2] += 2;
            Store_Data[3] += 3;
            Store_Data[4] += 4;
            Store_Save(); // 将Store_Data的数据备份保存到闪存，实现掉电不丢失
        }
        
        if (KeyNum == 2)
        {
            Store_Clear(); // 将Store_Data的数据全部清0
        }
        
        OLED_ShowHexNum(1, 7, Store_Data[0], 4); // 显示Store_Data的第一位标志位
        OLED_ShowHexNum(3, 1, Store_Data[1], 4); // 显示Store_Data的有效存储数据
        OLED_ShowHexNum(3, 7, Store_Data[2], 4);
        OLED_ShowHexNum(4, 1, Store_Data[3], 4);
        OLED_ShowHexNum(4, 7, Store_Data[4], 4);
    }
}
