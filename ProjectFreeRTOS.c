/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Author: Eldrick Alexander
 */
 
/**
 * @file    Proyecto FreeRTOS.c
 */

/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"


#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"


/* Task priorities. */
#define hello_task_PRIORITY (configMAX_PRIORITIES - 1)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void hello_task(void *pvParameters);
static void mood_task(void *pvParameters);
static void goodbye_task(void *pvParamters);


int main(void) {


    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    BOARD_InitDebugConsole();

    PRINTF("Hello World\n");
    xTaskCreate(hello_task, "Hello_task", configMINIMAL_STACK_SIZE + 10, NULL, hello_task_PRIORITY, NULL);
    xTaskCreate(mood_task, "Mood_task", configMINIMAL_STACK_SIZE + 10, NULL, hello_task_PRIORITY, NULL);
    xTaskCreate(goodbye_task, "Goodbye_task", configMINIMAL_STACK_SIZE + 10, NULL, hello_task_PRIORITY, NULL);

    vTaskStartScheduler();

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}

static void hello_task(void *pvParameters)
{
    for (;;)
    {
    	PRINTF("Hello world.\r\n");
    	PRINTF("I´m working with FreeRTOS \n");
    	PRINTF("My name is 'Proyecto FreeRTOS.c'\n");
        vTaskDelay(10);
    }
}

static void mood_task(void *pvParameters)
{
    for (;;)
    {
        PRINTF("I'm fine, and you?.\r\n");
        PRINTF("Today is a good day\n");
        PRINTF("Better than  yesterday\n");
        vTaskDelay(10);
    }
}

static void goodbye_task(void *pvParameters)
{
    for (;;)
    {
        PRINTF("I have to go, bye!.\r\n");
        PRINTF("See you later!\n");
        PRINTF("Take care. \n");
        vTaskDelay(10);
    }
}
