/*
 * lcd_nokia5510.c
 *
 *  Created on: Oct 4, 2023
 *      Author: kacper
 */


#include "lcd_nokia5510.h"
#include "gpio.h"
SPI_HandleTypeDef *spi;

void LCD_NOKIA5510_resetInit(SPI_HandleTypeDef *sp)
{
	spi = sp;
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
}
