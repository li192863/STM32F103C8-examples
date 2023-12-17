#include "stm32f10x.h"                  // Device header

/**
  * @brief  FLASH读取一个32位的字
  * @param  Address 要读取数据的字地址
  * @retval 指定地址下的数据
  */
uint32_t MyFLASH_ReadWord(uint32_t Address)
{
    return *((__IO uint32_t *) (Address));
}


/**
  * @brief  FLASH读取一个16位的半字
  * @param  Address 要读取数据的半字地址
  * @retval 指定地址下的数据
  */
uint16_t MyFLASH_ReadHalfWord(uint32_t Address)
{
    return *((__IO uint16_t *) (Address));
}

/**
  * @brief  FLASH读取一个8位的字节
  * @param  Address 要读取数据的字节地址
  * @retval 指定地址下的数据
  */
uint8_t MyFLASH_ReadByte(uint32_t Address)
{
    return *((__IO uint8_t *) (Address));
}

/**
  * @brief  FLASH全擦除，调用此函数后，FLASH的所有页都会被擦除（包括程序文件），擦除后，程序将不复存在
  * @retval 无
  */
void MyFLASH_EraseAllPages(void)
{
    FLASH_Unlock(); // 解锁
    FLASH_EraseAllPages(); // 全擦除
    FLASH_Lock(); // 加锁
}

/**
  * @brief  FLASH页擦除
  * @param  PageAddress 要擦除页的页地址
  * @retval 无
  */
void MyFLASH_ErasePage(uint32_t PageAddress)
{
    FLASH_Unlock(); // 解锁
    FLASH_ErasePage(PageAddress); // 页擦除
    FLASH_Lock(); // 加锁
}

/**
  * @brief  FLASH编程字
  * @param  Address 要写入数据的字地址
  * @param  Data 要写入的32位数据
  * @retval 
  */
void MyFLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
    FLASH_Unlock(); // 解锁
    FLASH_ProgramWord(Address, Data); // 编程字
    FLASH_Lock(); // 加锁
}

/**
  * @brief  FLASH编程半字
  * @param  Address 要写入数据的半字地址
  * @param  Data 要写入的16位数据
  * @retval 
  */
void MyFLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
    FLASH_Unlock(); // 解锁
    FLASH_ProgramHalfWord(Address, Data); // 编程半字
    FLASH_Lock(); // 加锁
}
