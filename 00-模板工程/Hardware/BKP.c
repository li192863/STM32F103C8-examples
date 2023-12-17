#include "stm32f10x.h"

/**
  * @brief  BKP初始化
  * @retval 无
  */
void BKP_Init(void)
{
    // 开启PWR和BKP时钟，使能BKP和RTC的访问
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE); // 使能后备区域的访问
}

/**
  * @brief  写数据寄存器
  * @param  BKP_DR 数据备份寄存器
  * @param  Data 数据
  * @retval 无
  */
void BKP_write(uint16_t BKP_DR, uint16_t Data)
{
    BKP_WriteBackupRegister(BKP_DR, Data);
}

/**
  * @brief  读数据寄存器
  * @param  BKP_DR 数据备份寄存器 
  * @retval 数据
  */
uint16_t BKP_Read(uint16_t BKP_DR)
{
    return BKP_ReadBackupRegister(BKP_DR);
}
