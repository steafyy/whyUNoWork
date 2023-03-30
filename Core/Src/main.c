/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "usb_host.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

// Basic includes
#include "../../Drivers/BSP/stm32f429i_discovery_lcd.h"
#include "../../Drivers/BSP/stm32f429i_discovery_gyroscope.h"
#include "../../Drivers/BSP/stm32f429i_discovery.h"

#include "stdio.h"
#include "string.h"
#include "stdbool.h"

// RTOS includes
#include "freeRTOS.h"
#include "queue.h"
#include "task.h"

// User headers includes
#include "../Inc/classes.h"
#include "../Inc/init_funcs.h"
#include "../Inc/defines.h"
#include "tasks.h"

// Application entry point
int main(void) {

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	// Creating all game related objects
	cBoard *board = newBoard(BOARD_X, BOARD_Y, BOARD_LEN);
	cBall *ball = newBall();
	cTarget* targetArray = malloc(INITIAL_TARGETS * sizeof(cTarget));

	int *remainingLives = malloc(sizeof(int));

	*remainingLives = INITIAL_LIVES;

	/* Configure the system clock */
	SystemClock_Config();

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_CRC_Init();
	MX_DMA2D_Init();
	MX_FMC_Init();
	MX_I2C3_Init();
	MX_LTDC_Init();
	MX_SPI5_Init();
	MX_TIM1_Init();
	MX_USART1_UART_Init();
	MX_RNG_Init();
	MX_UART5_Init();

	initializeLCD();
	initializeGYRO();
	initializeFont();

	// Creating queues for inter-task communication
	boardQueue = xQueueCreate(2, sizeof(cBoard*));
	ballQueue = xQueueCreate(2, sizeof(cBall*));
	targetQueue = xQueueCreate(2, sizeof(cBall**));
	dataQueue = xQueueCreate(2, sizeof(int*));
	vQueueAddToRegistry(boardQueue, "queueBoard");
	vQueueAddToRegistry(ballQueue, "queueBall");
	vQueueAddToRegistry(targetQueue, "queueTargets");
	vQueueAddToRegistry(dataQueue, "queueGameData");

	// Creating tasks
	xTaskCreate(endScreen, "EndScreen", 100, NULL, 2, &hEndScreen);
	xTaskCreate(startScreen, "StartScreen", 100, NULL, 2, &hStartScreen);

	xTaskCreate(displayGameData, "DisplayGameData", 1000, NULL, 1, &hManageGameData);
	xTaskCreate(moveBall, "MoveBall", 2000, NULL, 1, &hMoveBall);
	xTaskCreate(moveBoard, "MoveBoard", 2000, NULL, 1, &hMoveBoard);
	xTaskCreate(checkTargetCollisions, "CheckTargetCollisions", 1000, NULL, 1, &hCheckTargetCollisions);

	vTaskSuspend(hMoveBoard);
	vTaskSuspend(hMoveBall);
	vTaskSuspend(hCheckTargetCollisions);
	vTaskSuspend(hEndScreen);
	vTaskSuspend(hManageGameData);

	// Sending object data to tasks
	xQueueSend(dataQueue, &remainingLives, portMAX_DELAY);
	xQueueSend(dataQueue, &remainingLives, portMAX_DELAY);

	xQueueSend(boardQueue, (void* ) &board, portMAX_DELAY);
	xQueueSend(boardQueue, (void* ) &board, portMAX_DELAY);
	xQueueSend(targetQueue, (void* ) &targetArray, portMAX_DELAY);
	xQueueSend(targetQueue, (void* ) &targetArray, portMAX_DELAY);
	xQueueSend(ballQueue, (void* ) &ball, portMAX_DELAY);
	xQueueSend(ballQueue, (void* ) &ball, portMAX_DELAY);

	// Create the thread(s)
	// definition and creation of defaultTask
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 4096);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	// Control after this line is taken over by scheduler
	vTaskStartScheduler();

	while (1) {

	}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */
