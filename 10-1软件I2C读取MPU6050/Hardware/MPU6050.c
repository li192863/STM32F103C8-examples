#include "stm32f10x.h"
#include "MyI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS 0xD0

/**
  * @brief  向指定的MPU6050寄存器写指定数据
  * @param  RegAddress 指定的MPU6050寄存器
  * @param  Data 指定的数据
  * @retval 无
  */
void MPU6050_WirteReg(uint8_t RegAddress, uint8_t Data)
{
    MyI2C_Start();

    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(Data);
    MyI2C_ReceiveAck();

    MyI2C_Stop();
}

/**
  * @brief  向指定的MPU6050寄存器读取数据
  * @param  RegAddress 指定的MPU6050寄存器
  * @retval 指定的MPU6050寄存器的数据
  */
uint8_t MPU6050_ReadReg(uint8_t RegAddress)
{
    uint8_t Data;
    MyI2C_Start();

    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceiveAck();
    
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
    MyI2C_ReceiveAck();
    Data = MyI2C_ReceiveByte();
    MyI2C_SendAck(1);

    MyI2C_Stop();
    return Data;
}

/**
  * @brief  MPU6050初始化
  * @retval 无
  */
void MPU6050_Init(void)
{
    MyI2C_Init();
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
  * @param  AccX 指向AccX的指针
  * @param  AccY 指向AccY的指针
  * @param  AccZ 指向AccZ的指针
  * @param  GyroX 指向gyroX的指针
  * @param  GyroY 指向gyroY的指针
  * @param  GyroZ 指向gyroZ的指针
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
