/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "oled.h"
#include "display.h"
#include "gpio.h"
#include "rtc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/*1.set osthred id*/
osThreadId led_taskHandle;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId flash_time_taskHandle;
osTimerId myTimer01Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
/*2. set start thread function*/
void start_led_task(void const *argument);
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const *argument);
void start_flash_time_task(void const *argument);
void Callback01(void const *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize);

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize);

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
    *ppxIdleTaskStackBuffer = &xIdleStack[0];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
    /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
    *ppxTimerTaskStackBuffer = &xTimerStack[0];
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
    /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void)
{
    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* Create the timer(s) */
    /* definition and creation of myTimer01 */
    osTimerDef(myTimer01, Callback01);
    myTimer01Handle = osTimerCreate(osTimer(myTimer01), osTimerPeriodic, NULL);
    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /*启动定时器定时1s进入回调函数Callback01*/
    osTimerStart(myTimer01Handle, 1000);
    /* USER CODE END RTOS_TIMERS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */

    /* Create the thread(s) */
    /* definition and creation of defaultTask */
    osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

    /* definition and creation of flash_time_task */
    osThreadDef(flash_time_task, start_flash_time_task, osPriorityAboveNormal, 0, 128);
    flash_time_taskHandle = osThreadCreate(osThread(flash_time_task), NULL);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    osThreadDef(led_task, start_led_task, osPriorityAboveNormal, 0, 128);
    led_taskHandle = osThreadCreate(osThread(led_task), NULL);
    /* USER CODE END RTOS_THREADS */
}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const *argument)
{
    /* USER CODE BEGIN StartDefaultTask */
    /* Infinite loop */
    for (;;)
    {
    }
    /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_start_flash_time_task */
/**
* @brief Function implementing the flash_time_task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_flash_time_task */
void start_flash_time_task(void const *argument)
{
    /* USER CODE BEGIN start_flash_time_task */
    /* Infinite loop */
    for (;;)
    {
        show_string_atype(0, 0, "date:", 5);
        display_date(0, 5);
        show_string_atype(2, 0, "time:", 5);
        display_time(2, 5);
        show_chs_string(4, 0, "苏培佩我爱你！");
        show_string_atype(6, 0, "love you forever", 16);
    }
    /* USER CODE END start_flash_time_task */
}

/* Callback01 function */
void Callback01(void const *argument)
{
    /* USER CODE BEGIN Callback01 */
    get_time(&gettime, &getdate);
    g_flag_time++;
    /* USER CODE END Callback01 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void start_led_task(void const *argument)
{
    for (;;)
    {
        if (g_flag_time == 1)
        {
            red_led_off;
            green_led_on;
        }
        else if (g_flag_time == 2)
        {
            green_led_off;
            blue_led_on;
        }
        else if (g_flag_time == 3)
        {
            blue_led_off;
            red_led_on;
            g_flag_time = 0;
        }
        else
        {
        }
    }
}
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
