#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "BKP.h"
#include "Key.h"

uint8_t KeyNum;

uint16_t ArrayWrite[] = {0x1234, 0x5678};
uint16_t ArrayRead[2];

int main(void)
{
    OLED_Init();
    Key_Init();
    BKP_Init();

    OLED_ShowString(1, 1, "W: ");
    OLED_ShowString(2, 1, "R: ");

    while (1)
    {
        KeyNum = Key_GetNum();
        if (KeyNum == 1)
        {
            ArrayWrite[0]++;
            ArrayWrite[1]++;
            
            BKP_write(BKP_DR1, ArrayWrite[0]);
            BKP_write(BKP_DR2, ArrayWrite[1]);
            
            OLED_ShowHexNum(1, 4, ArrayWrite[0], 4);
            OLED_ShowHexNum(1, 9, ArrayWrite[1], 4);
        }
        
        ArrayRead[0] = BKP_Read(BKP_DR1);
        ArrayRead[1] = BKP_Read(BKP_DR2);
        OLED_ShowHexNum(2, 4, ArrayRead[0], 4);
        OLED_ShowHexNum(2, 9, ArrayRead[1], 4);
        
    }
}
