#include "stm32f10x.h"                  // Device header
#include "MyFLASH.h"

// 存储起始地址
#define STORE_START_ADDRESS        0x0800FC00
// 存储数据个数
#define STORE_COUNT                512

uint16_t Store_Data[STORE_COUNT];

/**
  * @brief  参数存储模块初始化
  * @retval 无
  */
void Store_Init(void)
{
    // 判断是不是第一次使用
    if (MyFLASH_ReadHalfWord(STORE_START_ADDRESS) != 0x6666)
    {
        MyFLASH_ErasePage(STORE_START_ADDRESS);
        MyFLASH_ProgramHalfWord(STORE_START_ADDRESS, 0x6666);
        // 除了标志位的有效数据全部清0
        for (uint16_t i = 1; i < STORE_COUNT; i++) // 循环STORE_COUNT次，除了第一个标志位
        {
            MyFLASH_ProgramHalfWord(STORE_START_ADDRESS + i * 2, 0x0000);
        }
    }
    
    // 将闪存数据加载回SRAM数组
    for (uint16_t i = 0; i < STORE_COUNT; i++) // 循环STORE_COUNT次，包括第一个标志位
    {
        Store_Data[i] = MyFLASH_ReadHalfWord(STORE_START_ADDRESS + i * 2);
    }
}

/**
  * @brief  参数存储模块保存数据到闪存
  * @retval 无
  */
void Store_Save(void)
{
    // 擦除指定页
    MyFLASH_ErasePage(STORE_START_ADDRESS);
    for (uint16_t i = 0; i < STORE_COUNT; i++) // 循环STORE_COUNT次，包括第一个标志位
    {
        MyFLASH_ProgramHalfWord(STORE_START_ADDRESS + i * 2, Store_Data[i]);
    }
}

/**
  * @brief  参数存储模块将所有有效数据清0
  * @retval 无
  */
void Store_Clear(void)
{
    for (uint16_t i = 1; i < STORE_COUNT; i++) // 循环STORE_COUNT次，除了第一个标志位
    {
        Store_Data[i] = 0x0000; // SRAM数组有效数据清0
    }
    Store_Save(); // 保存数据到闪存
}
