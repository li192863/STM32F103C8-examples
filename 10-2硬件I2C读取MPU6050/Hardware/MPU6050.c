#include "stm32f10x.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS 0xD0

/**
  * @brief  等待指定事件发生 若超时则退出
  * @param  I2Cx I2C
  * @param  I2C_EVENT 事件
  * @retval 无
  */
void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
    uint32_t Timeout = 10000;
    while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
    {
        Timeout--;
        if (Timeout == 0) break;
    }
}

/**
  * @brief  向指定的MPU6050寄存器写指定数据
  * @param  RegAddress 指定的MPU6050寄存器
  * @param  Data 指定的数据
  * @retval 无
  */
void MPU6050_WirteReg(uint8_t RegAddress, uint8_t Data)
{
    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
    
    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
    
    I2C_SendData(I2C2, RegAddress);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING);
    
    I2C_SendData(I2C2, Data);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
    
    I2C_GenerateSTOP(I2C2, ENABLE);
}

/**
  * @brief  向指定的MPU6050寄存器读取数据
  * @param  RegAddress 指定的MPU6050寄存器
  * @retval 指定的MPU6050寄存器的数据
  */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
    uint8_t Data;

    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
    
    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);
    
    I2C_SendData(I2C2, RegAddress);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);
    
    I2C_GenerateSTART(I2C2, ENABLE);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);
    
    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);
    
    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);
    
    MPU6050_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);
    Data = I2C_ReceiveData(I2C2);
    
    I2C_AcknowledgeConfig(I2C2, ENABLE);

    return Data;
}

/**
  * @brief  MPU6050初始化
  * @retval 无
  */
void MPU6050_Init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;  // 复用开漏
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;  // 引脚
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    I2C_InitTypeDef I2C_InitStruct;
    I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct.I2C_ClockSpeed = 100000; // 标准速度
    I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2; // 快速模式下的速度
    I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // 响应地址的位数
    I2C_InitStruct.I2C_OwnAddress1 = 0x00; // 自身作为从机时地址
    I2C_Init(I2C2, &I2C_InitStruct);
    
    I2C_Cmd(I2C2, ENABLE);
    
    MPU6050_WirteReg(MPU6050_PWR_MGMT_1, 0x01); // 配置电源管理寄存器1
    MPU6050_WirteReg(MPU6050_PWR_MGMT_2, 0x00); // 配置电源管理寄存器2
    
    MPU6050_WirteReg(MPU6050_SMPLRT_DIV, 0x09); // 配置采样率分频
    MPU6050_WirteReg(MPU6050_CONFIG, 0x06); // 配置配置寄存器
    MPU6050_WirteReg(MPU6050_GYRO_CONFIG, 0x18); // 配置陀螺仪配置寄存器
    MPU6050_WirteReg(MPU6050_ACCEL_CONFIG, 0x18); // 配置加速度计配置寄存器
}

/**
  * @brief  MPU6050获取ID值
  * @retval ID值
  */
uint8_t MPU6050_GetID(void)
{
    uint8_t ID = MPU6050_ReadReg(MPU6050_WHO_AM_I); // id号
    return ID;
}

/**
  * @brief  MPU6050读取加速度计和陀螺仪的值
  * @param AccX 指向AccX的指针
  * @param AccY 指向AccY的指针
  * @param AccZ 指向AccZ的指针
  * @param GyroX 指向gyroX的指针
  * @param GyroY 指向gyroY的指针
  * @param GyroZ 指向gyroZ的指针
  * @retval 无
  */
void MPU6050_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
    uint8_t DataH, DataL;
    
    DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    *AccX = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    *AccY = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    *AccZ = (DataH << 8) | DataL;
    
    DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    *GyroX = (DataH << 8) | DataL;
    
    DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    *GyroY = (DataH << 8) | DataL;
    
    DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
    *GyroZ = (DataH << 8) | DataL;
}
