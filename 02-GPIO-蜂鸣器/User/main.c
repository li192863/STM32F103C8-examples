#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "Buzzer.h"


int main(void)
{
    Buzzer_Init();

    while (1)
    {
        int i;
        for (i = 0; i < 8; i++)
        {
            Buzzer_On();
            Delay_ms(100);
            Buzzer_Off();
            Delay_ms(100);
        }
        
    }
}
