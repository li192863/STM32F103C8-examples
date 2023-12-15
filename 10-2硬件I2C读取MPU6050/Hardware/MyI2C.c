#include "stm32f10x.h"

/**
  * @brief  I2C初始化
  * @retval 无
  */
void MyI2C_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;  // 复用开漏 硬件I2C需要开启复用开漏模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;  // 引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    I2C_InitTypeDef I2C_InitStruct;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_ClockSpeed = 100000; // 标准速度
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2; // 快速模式下的速度
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable; // 是否给应答
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // 响应地址的位数
    I2C_InitStruct.I2C_OwnAddress1 = 0x00; // 自身作为从机时地址
    I2C_Init(I2C2, &I2C_InitStruct);
    
    I2C_Cmd(I2C2, ENABLE);
}

/**
  * @brief  等待指定事件发生 若超时则退出
  * @param  I2Cx I2C
  * @param  I2C_EVENT 事件
  * @retval 无
  */
void MyI2C_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
    uint32_t Timeout = 10000;
    while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
    {
        Timeout--;
        if (Timeout == 0) break;
    }
}
