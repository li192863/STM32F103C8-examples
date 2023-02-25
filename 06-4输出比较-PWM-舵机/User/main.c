#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "Servo.h"
#include "OLED.h"
#include "Key.h"

uint8_t KeyNum;
float Angle;

int main(void)
{
    OLED_Init();
    Servo_Init();
    OLED_ShowString(1, 1, "Angle: 000");
    Servo_SetAngle(0);
    while (1)
    {
        KeyNum = Key_GetNum();
        if (KeyNum == 1)
        {
            Angle += 30;
            if (Angle > 180)
            {
                Angle = 0;
            }
            Servo_SetAngle(Angle);
            OLED_ShowNum(1, 8, Angle, 3);
        }
    }
}
