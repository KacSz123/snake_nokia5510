/*
 * lcd_nokia5510.c
 *
 *  Created on: Oct 4, 2023
 *      Author: kacper
 */


#include "lcd_nokia5510.h"
#include "gpio.h"
#include "stdlib.h"
#include "memory.h"


SPI_HandleTypeDef *spi;
//spi = &

void LCD_NOKIA5510_resetInit(SPI_HandleTypeDef* sp)
{
	spi = sp;
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
	HAL_Delay(20);
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(20);

	memset(LCD_NOKIA5510_dataBuffer, 0, LCD_BUFFER_SIZE);
}



void LCD_NOKIA5510_reset()
{
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_SET);
}

void LCD_NOKIA5510_cmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}
void LCD_NOKIA5510_sendData(uint8_t *data, int size)
{
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, data, size, HAL_MAX_DELAY);
//	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
}

void LCD_NOKIA5510_sendDataBuffer()
{
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1,LCD_NOKIA5510_dataBuffer , LCD_BUFFER_SIZE, 100);
//	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
}

void LCD_NOKIA5510_drawPixel(uint8_t x, uint8_t y)
{
	LCD_NOKIA5510_dataBuffer[x+(y>>3)*LCD_WIDTH] |= 1<<(y&7);
}


void LCD_NOKIA5510_erasePixel(uint8_t x, uint8_t y)
{
	LCD_NOKIA5510_dataBuffer[x+(y>>3)*LCD_WIDTH] &= ~(1<<(y&7));
}


void LCD_NOKIA5510_clearScreen()
{
	memset(LCD_NOKIA5510_dataBuffer, 0, LCD_BUFFER_SIZE);

	LCD_NOKIA5510_cmd(0x40);
	LCD_NOKIA5510_cmd(0x80);
}


void LCD_NOKIA5510_drawLine2Points(uint8_t x1, uint8_t y1,uint8_t x2, uint8_t y2)
{

}
void LCD_NOKIA5510_drawRectangle();
void LCD_NOKIA5510_drawCircle();
