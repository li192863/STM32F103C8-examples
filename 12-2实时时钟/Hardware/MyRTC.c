#include <time.h>
#include "stm32f10x.h"

uint16_t MyRTC_Time[] = {2023, 1, 1, 23, 59, 55};

/**
  * @brief  设置RTC时间
  * @retval 无
  */
void MyRTC_SetTime(void)
{
    time_t time_cnt;
    struct tm time_date;
    
    time_date.tm_year = MyRTC_Time[0] - 1900;
    time_date.tm_mon = MyRTC_Time[1] - 1;
    time_date.tm_mday = MyRTC_Time[2];
    time_date.tm_hour = MyRTC_Time[3];
    time_date.tm_min = MyRTC_Time[4];
    time_date.tm_sec = MyRTC_Time[5];
    
    time_cnt = mktime(&time_date) - 8 * 60 * 60; // 时区偏移
    RTC_SetCounter(time_cnt);
    RTC_WaitForLastTask(); // 等待上一次写入操作完成
}


/**
  * @brief  RTC初始化
  * @retval 无
  */
void MyRTC_Init(void)
{
    // 开启PWR和BKP时钟，使能BKP和RTC的访问
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
    PWR_BackupAccessCmd(ENABLE); // 使能后备区域的访问
    
    // 启动LSI时钟
    RCC_LSICmd(ENABLE);
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) != SET);
    
    // 选择时钟源
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
    
    if (BKP_ReadBackupRegister(BKP_DR1) != 0x6666)
    {
        RCC_RTCCLKCmd(ENABLE);
        
        // 等待同步
        RTC_WaitForSynchro(); // 等待同步
        RTC_WaitForLastTask(); // 等待上一次写入操作完成
        
        // 预分频值
        RTC_SetPrescaler(40000 - 1);
        RTC_WaitForLastTask(); // 等待上一次写入操作完成
        
        MyRTC_SetTime();
        
        BKP_WriteBackupRegister(BKP_DR1, 0x6666);
    }
    else
    {
        // 等待同步
        RTC_WaitForSynchro(); // 等待同步
        RTC_WaitForLastTask(); // 等待上一次写入操作完成
    }
    
    
    
}

/**
  * @brief  读取RTC时间
  * @retval 无
  */
void MyRTC_ReadTime(void)
{
    time_t time_cnt;
    struct tm time_date;
    
    time_cnt = RTC_GetCounter() + 8 * 60 * 60; // 时区偏移
    time_date = *localtime(&time_cnt);
    
    MyRTC_Time[0] = time_date.tm_year + 1900;
    MyRTC_Time[1] = time_date.tm_mon + 1;
    MyRTC_Time[2] = time_date.tm_mday;
    MyRTC_Time[3] = time_date.tm_hour;
    MyRTC_Time[4] = time_date.tm_min;
    MyRTC_Time[5] = time_date.tm_sec;
}
