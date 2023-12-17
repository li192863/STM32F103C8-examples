#include "stm32f10x.h"                  // Device header

/**
  * @brief  SPI写SS
  * @param  BitValue 0或1
  * @retval 无
  */
void MySPI_W_SS(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitValue);
}

/**
  * @brief  SPI写SCK
  * @param  BitValue 0或1
  * @retval 无
  */
void MySPI_W_SCK(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitValue);
}

/**
  * @brief  SPI写MOSI
  * @param  BitValue 0或1
  * @retval 无
  */
void MySPI_W_MOSI(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitValue);
}

/**
  * @brief  SPI读MISO
  * @retval BitValue 0或1
  */
uint8_t MySPI_R_MISO(void)
{
    return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

/**
  * @brief  SPI初始化
  * @retval 无
  */
void MySPI_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    // 默认电平
    MySPI_W_SS(1); // 高电平空闲状态
    MySPI_W_SCK(0); // 低电平空闲状态
}

/**
  * @brief  SPI起始
  * @retval 无
  */
void MySPI_Start(void)
{
    MySPI_W_SS(0);
}

/**
  * @brief  SPI终止
  * @retval 无
  */
void MySPI_Stop(void)
{
    MySPI_W_SS(1);
}

/**
  * @brief  SPI交换一个字节，模式0
  * @param  ByteSend 要发送的字节
  * @retval 要接收的字节
  */
uint8_t MySPI_SwapByte(uint8_t ByteSend)
{
    uint8_t i;
    for (i = 0; i < 8; i++)
    {
        MySPI_W_MOSI(ByteSend & 0x80);
        ByteSend <<= 1;
        MySPI_W_SCK(1);
        if (MySPI_R_MISO() == 1) ByteSend |= 0x01;
        MySPI_W_SCK(0);
    }
    
    return ByteSend;
}

/**
  * @brief  SPI交换一个字节，模式0
  * @param  ByteSend 要发送的字节
  * @retval 要接收的字节
  */
uint8_t MySPI_SwapByte_v2(uint8_t ByteSend)
{
    uint8_t i, ByteReceive = 0x00;
    
    for (i = 0; i < 8; i++)
    {
        MySPI_W_MOSI(ByteSend & (0x80 >> i));
        MySPI_W_SCK(1);
        if (MySPI_R_MISO() == 1) ByteReceive |= (0x80 >> i);
        MySPI_W_SCK(0);
    }
    
    return ByteReceive;
}
