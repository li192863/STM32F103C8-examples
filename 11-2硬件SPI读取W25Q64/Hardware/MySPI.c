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
  * @brief  SPI初始化
  * @retval 无
  */
void MySPI_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    SPI_InitTypeDef SPI_InitStructure;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master; // 模式为SPI主模式
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; // 方向2线全双工
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // 数据宽度
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; // 高位先行
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128; // 波特率分频
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; // SPI极性，选择低极性
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; // SPI相位，选择第一个时钟边沿采样，极性和相位决定选择SPI模式0
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; // NSS，软件控制
    SPI_InitStructure.SPI_CRCPolynomial = 7; // CRC多项式，默认值7
    SPI_Init(SPI1, &SPI_InitStructure); // 将结构体变量交给SPI_Init，配置SPI1

    SPI_Cmd(SPI1, ENABLE);

    // 默认电平
    MySPI_W_SS(1); // 高电平空闲状态
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
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != SET); // 等待发送数据寄存器空
    SPI_I2S_SendData(SPI1, ByteSend); // 写入数据到发送数据寄存器，开始产生时序
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) != SET); // 等待接收数据寄存器非空
    return SPI_I2S_ReceiveData(SPI1);
}
