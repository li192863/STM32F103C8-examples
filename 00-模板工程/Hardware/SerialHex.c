#include <stdio.h>
#include <stdarg.h>
#include "stm32f10x.h"

uint8_t Serial_TxPacket[4];
uint8_t Serial_RxPacket[4];
uint8_t Serial_RxFlag;


/**
  * @brief  串口初始化
  * @retval 无
  */
void Serial_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600; // 波特率
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_Parity = USART_Parity_No; // 不校验
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStruct);
    
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStruct);
    
    USART_Cmd(USART1, ENABLE);
}

/**
  * @brief  串口发送字节
  * @param Byte 待发送字节
  * @retval 无
  */
void Serial_SendByte(uint8_t Byte)
{
    USART_SendData(USART1, Byte);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/**
  * @brief  串口发送数组
  * @param Array 待发送数组
  * @param Length 数组长度
  * @retval 无
  */
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
    uint16_t i;
    for (i = 0; i < Length; i++)
    {
        Serial_SendByte(Array[i]);
    }
}

/**
  * @brief  串口发送字符串
  * @param String 待发送字符串
  * @retval 无
  */
void Serial_SendString(char *String)
{
    uint16_t i;
    for (i = 0; String[i]; i++)
    {
        Serial_SendByte(String[i]);
    }
}

/**
  * @brief  串口计算幂函数
  * @param X 底数
  * @param Y 指数
  * @retval 结果X^Y
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
    uint32_t i, Result = 1;
    for (i = 0; i < Y; i++)
    {
        Result *= X;
    }
    return Result;
}

/**
  * @brief  串口发送数字
  * @param Number 数字
  * @param Length 数字长度
  * @retval 无
  */
void Serial_SendNumber(uint32_t Number, uint8_t Length)
{
    uint8_t i;
    for (i = 0; i < Length; i++)
    {
        Serial_SendByte(Number / Serial_Pow(10, Length - i - 1) % 10 + '0');
    }
}

/**
  * @brief  串口输出字符
  * @param ch 字符
  * @param f 文件
  * @retval 字符
  */
int fputc(int ch, FILE *f)
{
    Serial_SendByte(ch);
    return ch;
}

/**
  * @brief  串口打印函数
  * @param format 格式化字符串
  * @retval 无
  */
void Serial_Printf(char *format, ...)
{
    char String[100];
    va_list arg;
    va_start(arg, format);
    vsprintf(String, format, arg);
    va_end(arg);
    Serial_SendString(String);
}

/**
  * @brief  串口发送包数据
  * @retval 无
  */
void Serial_SendPacket(void)
{
    Serial_SendByte(0xFF); // 包头定义为0xFF
    Serial_SendArray(Serial_TxPacket, 4);
    Serial_SendByte(0xFE); // 包尾定义为0xFE
}

/**
  * @brief  获取串口接收标志位
  * @retval 接收是否完成
  */
uint8_t Serial_GetRxFlag(void)
{
    if (Serial_RxFlag == 1)
    {
        Serial_RxFlag = 0;
        return 1;
    }
    return 0;
}

/**
  * @brief  USART1中断处理函数
  * @retval 无
  */
void USART1_IRQHandler(void)
{
    static uint8_t RxState = 0;
    static uint8_t pRxPacket = 0;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        uint8_t RxData = USART_ReceiveData(USART1);
        if (RxState == 0)  // 等待包头状态
        {
            if (RxData == 0xFF)
            {
                RxState = 1;
                pRxPacket = 0;
            }
        }
        else if (RxState == 1)  // 接收数据状态
        {
            Serial_RxPacket[pRxPacket++] = RxData;
            if (pRxPacket >= 4)
            {
                RxState = 2;
            }
            
        }
        else if (RxState == 2)  // 等待包尾状态
        {
            if (RxData == 0xFE)
            {
                RxState = 0;
                Serial_RxFlag = 1;
            }
        }
        
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }
}
