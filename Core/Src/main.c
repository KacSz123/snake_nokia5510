/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdbool.h"
#include <stdlib.h>
#include "snake.h"
#include "lcd_nokia5510.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
//SPI_HandleTypeDef *spi = &hspi1;
//
typedef enum KEYPAD
{
	KEY_BUTTON_UP,
	KEY_BUTTON_DOWN,
	KEY_BUTTON_LEFT,
	KEY_BUTTON_RIGHT
}KEYPAD;
static volatile KEYPAD key = KEY_BUTTON_UP;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
int _write(int file, char* pData, int len)
{
	HAL_UART_Transmit(&huart2, (uint8_t*)pData, len, HAL_MAX_DELAY);
	return len;
}

//// function settings
////typedef snake
//#define LCD_WIDTH 84
//#define LCD_HEIGHT 48
//#define LCD_BUFFER_SIZE			(LCD_WIDTH * LCD_HEIGHT/8)
//static uint8_t p2[LCD_BUFFER_SIZE];
//
//
//
//typedef struct node
//{
//	bool headFlag;
//	int coords[2];
//	enum{LEFT=20, RIGHT=30, UP=40, DOWN=60} orientation;
//	struct node *next;
//	struct node *prev;
//
//}node_Typedef;
//
//typedef struct fruit
//{
//	int coords[2];
//}fruit_Typedef;
//
//void addSnakeNode(node_Typedef *h)
//{
//	node_Typedef *node_tmp = h;
//	while(node_tmp->next != NULL)
//	{
//		node_tmp = node_tmp->next;
//	}
//	node_tmp->next->coords[0]=node_tmp->coords[0];
//	node_tmp->next->coords[1]=node_tmp->coords[1];
//	node_tmp->next->orientation = node_tmp->coords[1];;
//	node_tmp->next->headFlag=false;
//	node_tmp->next->prev = node_tmp;
//	node_tmp->next->next = NULL;
//}
//void snakeHeadInit(int x, int y, node_Typedef *n)
//{
//	n = (node_Typedef*)malloc(sizeof(node_Typedef));
//	n->coords[0]=x; n->coords[1]=y;
//	n->orientation =UP;
//	n->headFlag=true;
//	n->next = NULL;
//	n->prev = NULL;
//}
//
//void removeSnake(node_Typedef *h){};
//
//void moveSnake(node_Typedef *h)
//{
//	node_Typedef *node_tmp = h;
//	while(node_tmp->next!=NULL)
//	{
//
//	}
//}
//
//
//
//#define LCD_ACT_MODE 0<<2
//#define LCD_POW_D_MODE 1<<2
//
//#define LCD_VAL_HOR 0<<1
//#define LCD_VAL_VER 1<<1
//
//#define LCD_BASIC_CMD 0
//#define LCD_ADD_CMD 1
//
//#define LCD_N5110_FUNSET (0x20|(LCD_ACT_MODE|LCD_VAL_HOR|LCD_ADD_CMD))
////////////////////////////////
//
//#define LCD_Y 5
//#define LCD_N5110_Y_POSE 0x40|LCD_Y
//
//
//void lcd_nokia5110_reset_init()
//{
//	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
//	HAL_Delay(20);
//	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
//}
//void lcd_nokia5110_reset()
//{
//	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
//}
//void lcd_nokia5110_cmd(uint8_t cmd)
//{
//	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
//	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
//	HAL_SPI_Transmit(spi, &cmd, 1, HAL_MAX_DELAY);
//	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
//}
//
//void lcd_nokia5110_data( int size)
//{
//	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
//	HAL_SPI_Transmit(spi, p2, sizeof(p2), 100);
////	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
//}
//
//void drawPixel(int x, int y)
//{
//	p2[x+(y>>3)*LCD_WIDTH] |= 1<<(y&7);
//}
//
//
//void erasePixel(int x, int y)
//{
////	int a=x+(y>>3)*LCD_WIDTH;
//	p2[x+(y>>3)*LCD_WIDTH] &= ~(1<<(y&7));
//}
//
//void clearLCD()
//{
//	memset(p2, 0, LCD_BUFFER_SIZE);
//
//    lcd_nokia5110_cmd(0x40);
//    lcd_nokia5110_cmd(0x80);
//}
//
//

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */
void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{

	if(GPIO_Pin == BUTTON_LEFT_Pin && key!=KEY_BUTTON_LEFT)
	{
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		key = KEY_BUTTON_LEFT;
//		printf("L\n\r");
	}
	else if(GPIO_Pin == BUTTON_RIGHT_Pin && key!=KEY_BUTTON_RIGHT)
	{
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		key = KEY_BUTTON_RIGHT;
//		printf("R\n\r");
	}
	else if(GPIO_Pin == BUTTON_DOWN_Pin && key!=KEY_BUTTON_DOWN)
	{
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		key = KEY_BUTTON_DOWN;
//		printf("D\n\r");
	}
	else if(GPIO_Pin == BUTTON_UP_Pin && key!=KEY_BUTTON_UP)
	{
		HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		key = KEY_BUTTON_UP;
//		printf("U\n\r");
	}
//	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
node_Typedef snake;
snakeHeadInit(1, 1, &snake);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
	LCD_NOKIA5510_resetInit(&hspi1);

//  lcd_nokia5110_cmd(0x40);
//  lcd_nokia5110_cmd(0x80|0x4f);
	LCD_NOKIA5510_cmd(0x21);
	LCD_NOKIA5510_cmd(0x14);
	LCD_NOKIA5510_cmd(0x80 | 0x2f); //Ustawienie kontrastu
	LCD_NOKIA5510_cmd(0x20);
	LCD_NOKIA5510_cmd(0x0c);

	LCD_NOKIA5510_cmd(0x40);
	LCD_NOKIA5510_cmd(0x80);
//  p2[0]=0xff;
//  p2[1]=0x18;
//  p2[2]=0xff;

//	LCD_NOKIA5510_dataBuffer[503 - 84] = 0xff;
//	LCD_NOKIA5510_dataBuffer[0] = 0xff;
//	LCD_NOKIA5510_dataBuffer[0] = 0xff;
//	LCD_NOKIA5510_dataBuffer[83] = 0xff;
//	LCD_NOKIA5510_dataBuffer[503] = 0xff;
//  lcd_nokia5110_data(sizeof(p2));
	LCD_NOKIA5510_sendDataBuffer();
	HAL_Delay(20);
//  p2[503]=0xff;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	KEYPAD tmp =key;
//	HAL_Delay(2000);
	while (1) {

		LCD_NOKIA5510_drawLine2Points(20, 10, 70, 40);
		LCD_NOKIA5510_drawRectangle(20, 10, 70, 10, 70, 40, 20, 40);
	  LCD_NOKIA5510_sendDataBuffer();
		  for(int x = 0; x<LCD_WIDTH;x++)
		  {
			  for(int y = 0; y<LCD_HEIGHT; y++)
			  {

				  if(x==0||y==0||x==LCD_WIDTH-1||y==LCD_HEIGHT-1)
				  {
			      LCD_NOKIA5510_drawPixel(x, y);
		  	  	  HAL_Delay(5);
		  	  	  LCD_NOKIA5510_sendDataBuffer();
				  HAL_Delay(5);
				  }
			  }

		//	  lcd_nokia5110_data(sizeof(p2));
			  LCD_NOKIA5510_sendDataBuffer();
		  };
		  LCD_NOKIA5510_clearScreen();
		  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);

		  HAL_Delay(150);
		  if(key!=tmp)
		  {
			  printf("ZMIANA!]n]r");
			  tmp = key;
		  }
	}

//	  for(int x = 0; x<LCD_WIDTH;x++)
//	  {
//		  for(int y = 0; y<LCD_HEIGHT; y++)
//		  {
//			  drawPixel(x, y);
//			  lcd_nokia5110_data(sizeof(p2));
//			  HAL_Delay(5);
//		  }
//
//	  }
//	  for(int x = 0; x<LCD_WIDTH;x++)
//	  {
//		  for(int y = 0; y<LCD_HEIGHT; y++)
//		  {
//			  erasePixel(x, y);
//			  lcd_nokia5110_data(sizeof(p2));
//			  HAL_Delay(5);
//		  }
//
//	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the peripherals clocks
  */
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* EXTI4_15_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
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
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
