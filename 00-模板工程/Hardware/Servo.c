#include "stm32f10x.h"                  // Device header
#include "PWM.h"


/**
  * @brief  舵机初始化
  * @retval 无
  */
void Servo_Init(void)
{
    PWM_Init();
}

/**
  * @brief  设置舵机角度
  * @param Angle 角度
  * @retval 无
  */
void Servo_SetAngle(float Angle)
{
    PWM_SetCompare2(Angle / 180. * (2500 - 500) + 500);
}
