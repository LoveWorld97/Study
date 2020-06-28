/**
  ******************************************************************************
  * File Name          : RTC.c
  * Description        : This file provides code for the configuration
  *                      of the RTC instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

RTC_HandleTypeDef hrtc;

/* RTC init function */
void MX_RTC_Init(void)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef DateToUpdate = {0};

    /** Initialize RTC Only 
  */
    hrtc.Instance = RTC;
    hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
    hrtc.Init.OutPut = RTC_OUTPUTSOURCE_NONE;
    if (HAL_RTC_Init(&hrtc) != HAL_OK)
    {
        Error_Handler();
    }

    /* USER CODE BEGIN Check_RTC_BKUP */
    if (HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1) == 0x5050)
    {
        /*已经配置过RTC*/
        return;
    }
    /* USER CODE END Check_RTC_BKUP */

    /** Initialize RTC and set the Time and Date 
  */
    sTime.Hours = 0x00;
    sTime.Minutes = 0x00;
    sTime.Seconds = 0x0;

    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
    {
        Error_Handler();
    }
    DateToUpdate.WeekDay = RTC_WEEKDAY_MONDAY;
    DateToUpdate.Month = RTC_MONTH_JANUARY;
    DateToUpdate.Date = 0x00;
    DateToUpdate.Year = 0x0;

    if (HAL_RTC_SetDate(&hrtc, &DateToUpdate, RTC_FORMAT_BCD) != HAL_OK)
    {
        Error_Handler();
    }
}

void HAL_RTC_MspInit(RTC_HandleTypeDef *rtcHandle)
{

    if (rtcHandle->Instance == RTC)
    {
        /* USER CODE BEGIN RTC_MspInit 0 */

        /* USER CODE END RTC_MspInit 0 */
        HAL_PWR_EnableBkUpAccess();
        /* Enable BKP CLK enable for backup registers */
        __HAL_RCC_BKP_CLK_ENABLE();
        /* RTC clock enable */
        __HAL_RCC_RTC_ENABLE();

        /* RTC interrupt Init */
        HAL_NVIC_SetPriority(RTC_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(RTC_IRQn);
        /* USER CODE BEGIN RTC_MspInit 1 */

        /* USER CODE END RTC_MspInit 1 */
    }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef *rtcHandle)
{

    if (rtcHandle->Instance == RTC)
    {
        /* USER CODE BEGIN RTC_MspDeInit 0 */

        /* USER CODE END RTC_MspDeInit 0 */
        /* Peripheral clock disable */
        __HAL_RCC_RTC_DISABLE();

        /* RTC interrupt Deinit */
        HAL_NVIC_DisableIRQ(RTC_IRQn);
        /* USER CODE BEGIN RTC_MspDeInit 1 */

        /* USER CODE END RTC_MspDeInit 1 */
    }
}

/* USER CODE BEGIN 1 */
/*设置日期：年：月：日*/
void set_date(uint8_t year, uint8_t month, uint8_t date)
{
    RTC_DateTypeDef mydate;

    mydate.Year = year;
    mydate.Month = month;
    mydate.Date = date;
    HAL_RTC_SetDate(&hrtc, &mydate, RTC_FORMAT_BIN);
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x5050);
}

/*设置时间:时：分：秒*/
void set_time(uint8_t hours, uint8_t minutes, uint8_t seconds)
{
    RTC_TimeTypeDef mytime;

    mytime.Hours = hours;
    mytime.Minutes = minutes;
    mytime.Seconds = seconds;
    HAL_RTC_SetTime(&hrtc, &mytime, RTC_FORMAT_BIN);
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_BKP_DR1, 0x5050);
}

/*获取时间日期*/
void get_time(RTC_DateTypeDef *RTC_Time, RTC_TimeTypeDef *RTC_Date)
{
    //注意必须GetTime在前GetDate在后
    /*get rtc current time*/
    HAL_RTC_GetTime(&hrtc, RTC_Time, RTC_FORMAT_BIN);
    /*get rtc current date*/
    HAL_RTC_GetDate(&hrtc, RTC_Date, RTC_FORMAT_BIN);
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
