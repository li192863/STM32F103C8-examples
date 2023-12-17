#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "W25Q64_Ins.h"

/**
  * @brief  W25Q64初始化
  * @retval 无
  */
void W25Q64_Init(void)
{
    MySPI_Init();
}

/**
  * @brief  W25Q64读取ID
  * @param  MID 厂商ID的指针
  * @param  DID 设备ID的指针
  * @retval 无
  */
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
    MySPI_Start();

    MySPI_SwapByte(W25Q64_JEDEC_ID);
    *MID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    *DID <<= 8;
    *DID |= MySPI_SwapByte(W25Q64_DUMMY_BYTE);

    MySPI_Stop();
}

/**
  * @brief  W25Q64写使能
  * @retval 无
  */
void W25Q64_WriteEnable(void)
{
    MySPI_Start();

    MySPI_SwapByte(W25Q64_WRITE_ENABLE);

    MySPI_Stop();
}

/**
  * @brief  W25Q64等待忙
  * @retval 无
  */
void W25Q64_WaitBusy(void)
{
    uint32_t Timeout = 100000;
    MySPI_Start();

    MySPI_SwapByte(W25Q64_READ_STATUS_REGISTER_1);
    while ((MySPI_SwapByte(W25Q64_DUMMY_BYTE) & 0x01) == 0x01)
    {
        Timeout--;
        if (Timeout == 0)
        {
            /*超时的错误处理代码，可以添加到此处*/
            break;
        }
    }

    MySPI_Stop();
}

/**
  * @brief  W25Q64页编程，写入的地址范围不能跨页
  * @param  Address 页编程的起始地址，范围：0x000000~0x7FFFFF
  * @param  DataArray 用于写入数据的数组
  * @param  Count 要写入数据的数量，范围：0~256
  * @retval 无
  */
void W25Q64_PageProgram(uint32_t Address, uint8_t *DataArray, uint16_t Count)
{
    uint16_t i;
    W25Q64_WriteEnable(); // 写使能
    MySPI_Start();

    MySPI_SwapByte(W25Q64_PAGE_PROGRAM);
    MySPI_SwapByte(Address >> 16);
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    for (i = 0; i < Count; i++)
    {
        MySPI_SwapByte(DataArray[i]);
    }

    MySPI_Stop();
    W25Q64_WaitBusy(); // 等待忙
}

/**
  * @brief  W25Q64扇区擦除（4KB）
  * @param  Address 指定扇区的地址，范围：0x000000~0x7FFFFF
  * @retval 无
  */
void W25Q64_SectorErase(uint32_t Address)
{
    W25Q64_WriteEnable(); // 写使能
    MySPI_Start();

    MySPI_SwapByte(W25Q64_SECTOR_ERASE_4KB);
    MySPI_SwapByte(Address >> 16);
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);

    MySPI_Stop();
    W25Q64_WaitBusy(); // 等待忙
}

/**
  * @brief  W25Q64读取数据
  * @param  Address 读取数据的起始地址，范围：0x000000~0x7FFFFF
  * @param  DataArray 用于接收读取数据的数组，通过输出参数返回
  * @param  Count 要读取数据的数量，范围：0~0x800000
  * @retval 无
  */
void W25Q64_ReadData(uint32_t Address, uint8_t *DataArray, uint32_t Count)
{
    uint32_t i;
    MySPI_Start();

    MySPI_SwapByte(W25Q64_READ_DATA);
    MySPI_SwapByte(Address >> 16);
    MySPI_SwapByte(Address >> 8);
    MySPI_SwapByte(Address);
    for (i = 0; i < Count; i++)
    {
        DataArray[i] = MySPI_SwapByte(W25Q64_DUMMY_BYTE);
    }

    MySPI_Stop();
}

